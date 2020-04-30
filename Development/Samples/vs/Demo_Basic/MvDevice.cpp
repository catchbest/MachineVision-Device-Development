#include "stdafx.h"
#include "MvDevice.h"



CMvDevice::CMvDevice(int nDeviceIndex) : m_nDeviceIndex(nDeviceIndex),
m_hGrabImageThread(NULL),
m_hGrabImageExitEvent(NULL)
{

}


CMvDevice::~CMvDevice()
{
	StartGrabImageThread(false);
}

UINT WINAPI CMvDevice::GrabImageThread(LPVOID pParam)
{
	CMvDevice *pMvDevice = (CMvDevice*)pParam;
	pMvDevice->GrabImageThreadX();
	return 0;
}

void CMvDevice::GrabImageThreadX()
{
	MVD_StartGrabbing(m_nDeviceIndex);

	int nRet = MVD_SUCCESS;

	while (TRUE)
	{
		if (WAIT_OBJECT_0 == WaitForSingleObject(m_hGrabImageExitEvent, 0))
		{ // Exit Capture Thread
			break;
		}

		MVD_FRAME_OUT *pImageOut = NULL;
		nRet = MVD_GrabImage(m_nDeviceIndex, &pImageOut);
		if (nRet != MVD_SUCCESS)    continue;

		// TODO: ��ʱ��ͼ����Ϣ�����ݶ���pImageOut�ṹ�У������SDK����ģ�Ҫ�����ͷš�
#if 0
		TCHAR chImageName[128] = { 0 };
		_stprintf(chImageName, 128, _T("Image_w%d_h%d_fn%03d.bmp"), pImageOut->stFrameOutInfo.uiWidth, pImageOut->stFrameOutInfo.uiHeight, pImageOut->stFrameOutInfo.uiFrameId);

		MVD_SAVE_IMAGE_PARAM SaveImageParam = { 0 };
		SaveImageParam.pchImageName  = chImageName;
		SaveImageParam.enImageFormat = MVD_IMAGE_FORMAT_BMP;
		SaveImageParam.nJpgQuality   = 0;
		nRet = MVD_SaveImage(pImageOut, &SaveImageParam);
#endif
		// ��MVD_GrabImage���ص��ڴ�ʹ����֮�󣬱���Ҫ����MVD_GrabImageRelease�����ͷš�
		nRet = MVD_GrabImageRelease(m_nDeviceIndex);
	}
	
	MVD_StopGrabbing(m_nDeviceIndex);
}



// ������ֹͣ�����ɼ��߳�
bool CMvDevice::StartGrabImageThread(bool bStart)
{
	if (bStart)
	{
		m_hGrabImageExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);		// Manual Reset, No signal

		DWORD    dwThreadID;
		m_hGrabImageThread = (HANDLE)_beginthreadex(NULL, 0, (PBEGINTHREADEX_FUNC)CMvDevice::GrabImageThread, this, 0, (PBEGINTHREADEX_ID)&dwThreadID);

		if (m_hGrabImageThread != NULL)
		{
			return true;
		}
	}
	else
	{
		if (m_hGrabImageExitEvent != NULL)
		{
			SetEvent(m_hGrabImageExitEvent);
		}

		if (WAIT_OBJECT_0 != WaitForSingleObject(m_hGrabImageThread, 5000))
		{
			TerminateThread(m_hGrabImageThread, 0);
		}

		CloseHandle(m_hGrabImageThread);
		m_hGrabImageThread = NULL;

		CloseHandle(m_hGrabImageExitEvent);
		m_hGrabImageExitEvent = NULL;

		return true;
	}

	return true;
}

bool CMvDevice::IsGrabImageThreadRunning()
{
	return m_hGrabImageThread == NULL ? false : true;
}
