#include "stdafx.h"
#include "MvDeviceManager.h"
#include "MvDevice.h"


CMvDeviceManager::CMvDeviceManager()
{
	int nRet = MVD_SUCCESS;


	memset(m_pMvDevice, NULL, MAX_DEVICE_NUM *sizeof(CMvDevice*));

	nRet = MVD_Initial(MVD_DEVICE_INTERFACE_TYPE_GIGE | MVD_DEVICE_INTERFACE_TYPE_USB, &m_stDeviceInfoList);

	for (int i = 0; i < m_stDeviceInfoList.uiDeviceNum; i++)
	{
		m_pMvDevice[i] = new CMvDevice(i);
	}
}


CMvDeviceManager::~CMvDeviceManager()
{
	for (int i = 0; i < MAX_DEVICE_NUM; i++)
	{
		if (NULL != m_pMvDevice[i])
		{
			delete m_pMvDevice[i];
			m_pMvDevice[i] = NULL;
		}
	}

	MVD_Uninitial();
}

int CMvDeviceManager::QuerySdkVersion()
{
	int nRet = MVD_SUCCESS;

	MVD_QUERY_INFO stQueryInfo;
	nRet = MVD_QueryInfo(-1, MVD_QUERY_INFO_TYPE_SDK_VERSION, &stQueryInfo);    // 第一个参数没有用

	ASSERT(stQueryInfo.enInfoType == MVD_VALUE_TYPE_INT);
	ASSERT(stQueryInfo.nValueNum == 1);

	return stQueryInfo.unValues[0].nValue;

}

int CMvDeviceManager::QueryParamNames(int nIndex, MVD_QUERY_INFO *pstQueryInfo)
{
	return MVD_QueryInfo(nIndex, MVD_QUERY_INFO_TYPE_PARAM_NAMES, pstQueryInfo);
}

int CMvDeviceManager::QueryCommandNames(int nIndex, MVD_QUERY_INFO *pstQueryInfo)
{
	return MVD_QueryInfo(nIndex, MVD_QUERY_INFO_TYPE_COMMAND_NAMES, pstQueryInfo);
}

float CMvDeviceManager::QueryGrabFps(int nIndex)
{
	int nRet = MVD_SUCCESS;

	MVD_QUERY_INFO   stQueryInfo;
	nRet = MVD_QueryInfo(nIndex, MVD_QUERY_INFO_TYPE_GRAB_FPS, &stQueryInfo);

	return stQueryInfo.unValues[0].fValue;
}

bool CMvDeviceManager::QueryIsOpen(int nIndex)
{
	int nRet = MVD_SUCCESS;

	MVD_QUERY_INFO   stQueryInfo;
	nRet = MVD_QueryInfo(nIndex, MVD_QUERY_INFO_TYPE_IS_OPEN, &stQueryInfo);

	return stQueryInfo.unValues[0].nValue ? true : false;
}


bool CMvDeviceManager::QueryIsGrabbingStart(int nIndex)
{
	int nRet = MVD_SUCCESS;

	MVD_QUERY_INFO   stQueryInfo;
	nRet = MVD_QueryInfo(nIndex, MVD_QUERY_INFO_TYPE_IS_GRABBING_START, &stQueryInfo);

	return stQueryInfo.unValues[0].nValue ? true : false;
}

bool CMvDeviceManager::QueryIsCallbackGrab(int nIndex)
{
	int nRet = MVD_SUCCESS;

	MVD_QUERY_INFO  stQueryInfo;
	nRet = MVD_QueryInfo(nIndex, MVD_QUERY_INFO_TYPE_IS_CALLBACK_GRAB, &stQueryInfo);

	return stQueryInfo.unValues[0].nValue ? true : false;
}


int CMvDeviceManager::GetDeviceNum()
{
	return m_stDeviceInfoList.uiDeviceNum;
}

int CMvDeviceManager::GetDeviceInfo(int nIndex, MVD_DEVICE_INFO *pstDeviceInfo)
{
	if (nIndex >= m_stDeviceInfoList.uiDeviceNum)    return MVD_E_PARAMETER;
	if (NULL == pstDeviceInfo)                       return MVD_E_PARAMETER;

	memcpy(pstDeviceInfo, m_stDeviceInfoList.pDeviceInfo[nIndex], sizeof(MVD_DEVICE_INFO));

	return MVD_SUCCESS;
}

int CMvDeviceManager::GetDeviceIndex(MVD_DEVICE_INFO *pstDeviceInfo)
{
	for (int i = 0; i < m_stDeviceInfoList.uiDeviceNum; i++)
	{
		if ( 0 == memcmp(pstDeviceInfo, m_stDeviceInfoList.pDeviceInfo[i], sizeof(MVD_DEVICE_INFO)) )
		{
			return i;
		}
	}

	return -1;
}

int CMvDeviceManager::SetDisplayInfo(int nIndex, MVD_DISPLAY_POSITION_INFO *pDisplayInfo)
{
	return 	MVD_SetDisplayPosition(nIndex, *pDisplayInfo);
}

int CMvDeviceManager::StartGrabImageThread(int nIndex, bool bStart)
{
	if (m_pMvDevice[nIndex] == NULL)    return MVD_E_PARAMETER;

	return m_pMvDevice[nIndex]->StartGrabImageThread(bStart);
}

// 开启、关闭设备
int CMvDeviceManager::OpenDevice(int nIndex, bool bOpen)
{
	if (bOpen)
		return 	MVD_OpenDevice(nIndex);
	else
	{
		StartGrabImageThread(nIndex, false);    // 用户开启的采集线程需要在关闭之前停止。
		return 	MVD_CloseDevice(nIndex);
	}
}


int CMvDeviceManager::GetParam(IN int nIndex, IN const TCHAR *pchParamName, OUT MVD_GET_PARAME_VALUE *pstGetParamValue)
{
	return 	MVD_GetParam(nIndex, pchParamName, pstGetParamValue);
}

int CMvDeviceManager::SetParam(IN int nIndex, IN const TCHAR *pchParamName, IN MVD_SET_PARAME_VALUE stSetParamValue)
{
	return  MVD_SetParam(nIndex, pchParamName, stSetParamValue);

}

bool  CMvDeviceManager::IsGrabImageThreadRunning(int nIndex)
{
	if (m_pMvDevice[nIndex] == NULL)    return false;

	return m_pMvDevice[nIndex]->IsGrabImageThreadRunning();
}









