
// Demo_BasicDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#define TIMERID_GET_FPS   1
#define MSG_TRACE         WM_USER + 100

typedef unsigned (WINAPI *PBEGINTHREADEX_FUNC)(LPVOID lpParam);
typedef unsigned *PBEGINTHREADEX_ID;

struct GRAB_THREAD_CONTEXT
{
	void *pDlg;
	int   nDeviceIndex;
};

/// ����������Ҫ���߳������Ϣ�������ؼ�����Ҫ�Զ�����Ϣ��ʹ��PostMessage���ͣ�����Ҫʹ��ȫ�ֵ�Buffer���������ַ�����
#define BUFFER_NUM  4

extern TCHAR     g_szTraceInfo[BUFFER_NUM][128];    /// ��һ��buffer���У��Է�ֹPostMessage����
extern int       g_nTraceNum;

#define TRACE_API(_FUNCTION_) \
{\
	int       nReturnCode; \
	TCHAR    *pszReturnCode = NULL; \
	TCHAR    *pszFunctionName = _T(#_FUNCTION_); \
	nReturnCode = _FUNCTION_; \
	_stprintf_s(g_szTraceInfo[g_nTraceNum % BUFFER_NUM], 128, _T("%s, %s"), pszFunctionName, GetReturnCodeString(nReturnCode)); \
	PostMessage(MSG_TRACE, 0, (LPARAM)g_szTraceInfo[g_nTraceNum % BUFFER_NUM]); \
	g_nTraceNum++;\
}


// CDemo_BasicDlg �Ի���
class CDemo_BasicDlg : public CDialogEx
{
// ����
public:
	CDemo_BasicDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DEMO_BASIC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckOpenCloseDevice();
	afx_msg void OnClose();
	afx_msg void OnCbnSelchangeComboDevicesList();
	
	LRESULT OnTraceMsg(WPARAM wParam, LPARAM lParam);


private:
	int m_nDeviceCurSel;
private:
	void Update_ListBoxDeviceInfo();
	void Update_ComboBoxParamNames();
	// ���������б�ѡ��仯ʱ��������Ӧ�Ĳ�����Ϣ
	void Update_Interface_When_ParamNames_Selected();
	void Update_ComboBoxCommandNames();
	void Update_Interface_When_Device_Selected();
public:
	afx_msg void OnCbnSelchangeComboParamNames();
	afx_msg void OnBnClickedCheckStartCallbackGrab();
	afx_msg void OnBnClickedCheckStartGrab();
	afx_msg void OnCbnSelchangeComboParamInfo();
	afx_msg void OnBnClickedButtonExecuteCommand();

public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT_PTR nIDEvent);


public:
	void DisplayImage(int nDeviceIndex, MVD_GRAB_IMAGE_INFO *pGrabImageInfo, unsigned char *pGrabImageData);
private:
	void InitialBmpInfo();
	BITMAPINFO    *m_pBitmapInfo;

public:
	void GrabImageThreadX(int nDeviceIndex);
private:
	bool StartGrabImageThread(bool bStart);

	GRAB_THREAD_CONTEXT    m_GrabImageThread[MVD_MAX_DEVICE_NUM];
	HANDLE m_hGrabImageExitEvent[MVD_MAX_DEVICE_NUM];    ///< ���ڶ�̨���ͬʱ�����ɼ�����������й����߳�
	HANDLE m_hGrabImageThread[MVD_MAX_DEVICE_NUM];

private:
	MVD_DEVICE_INFORMATION_LIST    m_DeviceInformationList;
public:
	// �������������Ϣ
	CListBox m_ListTrace;
	afx_msg void OnBnClickedButtonSetting();
};
