#pragma once

typedef unsigned (WINAPI *PBEGINTHREADEX_FUNC)(LPVOID lpParam);
typedef unsigned *PBEGINTHREADEX_ID;

class CMvDevice
{
public:
	CMvDevice(int nDeviceIndex);
	~CMvDevice();

public:
	static UINT WINAPI GrabImageThread(LPVOID pParam);

	void GrabImageThreadX();

	// 启动、停止主动采集线程
	bool StartGrabImageThread(bool bStart);   

	bool IsGrabImageThreadRunning();
private:
	HANDLE        m_hGrabImageThread;       // 主动采集线程句柄
	HANDLE        m_hGrabImageExitEvent;    // 通知主动采集线程退出的事件

	int           m_nDeviceIndex;

};

