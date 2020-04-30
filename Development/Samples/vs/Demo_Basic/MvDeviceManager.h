#pragma once

#define MAX_DEVICE_NUM     16
class CMvDevice;

class CMvDeviceManager
{
public:
	CMvDeviceManager();
	~CMvDeviceManager();

public:
	int GetDeviceIndex(MVD_DEVICE_INFO *pstDeviceInfo);

	int GetDeviceNum();
	int GetDeviceInfo(int nIndex, MVD_DEVICE_INFO *pstDeviceInfo);
	int SetDisplayInfo(int nIndex, MVD_DISPLAY_POSITION_INFO *pDisplayInfo);
	int StartGrabImageThread(int nIndex, bool bStart);
	int QuerySdkVersion();
	int QueryParamNames(int nIndex, MVD_QUERY_INFO *pstQueryInfo);
	int QueryCommandNames(int nIndex, MVD_QUERY_INFO *pstQueryInfo);
	float QueryGrabFps(int nIndex);
	bool  QueryIsOpen(int nIndex);
	bool  QueryIsGrabbingStart(int nIndex);
	bool  QueryIsCallbackGrab(int nIndex);

	bool  IsGrabImageThreadRunning(int nIndex);

	// 开启、关闭设备
	int OpenDevice(int nIndex, bool bOpen);
	int GetParam(IN int nIndex, IN const TCHAR *pchParamName, OUT MVD_GET_PARAME_VALUE *pstGetParamValue);
	int SetParam(IN int nIndex, IN const TCHAR *pchParamName, IN MVD_SET_PARAME_VALUE stSetParamValue);
private:
	MVD_DEVICE_INFO_LIST     m_stDeviceInfoList;

	CMvDevice               *m_pMvDevice[MAX_DEVICE_NUM];

};

