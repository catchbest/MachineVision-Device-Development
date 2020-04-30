// SimpleGrab.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int nRet;

	MVD_QUERY_INFO stQueryInfo;
	nRet = MVD_QueryInfo(-1, MVD_QUERY_INFO_TYPE_SDK_VERSION, &stQueryInfo);

	_tprintf(_T("MVD_GetSDKVersion(get sdk version) : version = 0x%08x, Return = %d\n"), stQueryInfo.unValues[0].nValue, nRet);

	MVD_DEVICE_INFO_LIST     stDeviceInfoList;

	nRet = MVD_Initial(MVD_DEVICE_INTERFACE_TYPE_GIGE | MVD_DEVICE_INTERFACE_TYPE_USB, &stDeviceInfoList);

	_tprintf(_T("MVD_Initial(intial sdk and enum devices) : device num = %d, Return = %d\n"), stDeviceInfoList.uiDeviceNum, nRet);

	for (int i = 0; i < stDeviceInfoList.uiDeviceNum; i++)
	{
		if (stDeviceInfoList.pDeviceInfo[i]->DeviceInterfaceType == MVD_DEVICE_INTERFACE_TYPE_GIGE)
		{
			_tprintf(_T("MVD_DEVICE_INTERFACE_TYPE_GIGE\n"));
			_tprintf(_T("szDeviceModelName = %s\n"), stDeviceInfoList.pDeviceInfo[i]->Info.stDeviceInfoGige.szDeviceModelName);
			_tprintf(_T("szAdapterFriendlyName = %s\n"), stDeviceInfoList.pDeviceInfo[i]->Info.stDeviceInfoGige.szAdapterFriendlyName);
			//...
		}

		MVD_OpenDevice(i);

		MVD_StartGrabbing(i);

		MVD_FRAME_OUT    *pFrameOut = NULL;

		nRet = MVD_GrabImage(i, &pFrameOut);
		if (nRet != MVD_SUCCESS)
		{
			goto Leave;
		}

		MVD_SAVE_IMAGE_PARAM SaveImageParam = {0};
		SaveImageParam.enImageFormat = MVD_IMAGE_FORMAT_BMP;
		SaveImageParam.pszImageName  = _T("1.bmp");
		SaveImageParam.nJpgQuality   = 0;

		MVD_SaveImage(pFrameOut, &SaveImageParam);

Leave:
		MVD_GrabImageRelease(i);

		MVD_StopGrabbing(i);

		MVD_CloseDevice(i);
	}

	nRet = MVD_Uninitial();

	printf("MVD_Uninitial(uninitial sdk release all resource)\n");

	return 0;
}

