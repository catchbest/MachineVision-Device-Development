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

	// ������ֹͣ�����ɼ��߳�
	bool StartGrabImageThread(bool bStart);   

	bool IsGrabImageThreadRunning();
private:
	HANDLE        m_hGrabImageThread;       // �����ɼ��߳̾��
	HANDLE        m_hGrabImageExitEvent;    // ֪ͨ�����ɼ��߳��˳����¼�

	int           m_nDeviceIndex;

};

