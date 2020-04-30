
// Demo_BasicDlg.h : ͷ�ļ�
//

#pragma once

class CMvDeviceManager;


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


private:
	MVD_DEVICE_INFO_LIST    m_DeviceInfoList;
	int m_nDeviceCurSel;
private:
	void Update_ListBoxDeviceInfo();
	void Update_ComboBoxParamNames();
	// ���������б�ѡ��仯ʱ��������Ӧ�Ĳ�����Ϣ
	void Update_Interface_When_ParamNames_Selected();
	void Update_ComboBoxCommandNames();
	void Update_Interface_When_Device_Selected();
	// ��Ϊֻ��һ�����ڣ�ͬһʱ��ֻ�ñ�ѡ����豸��ʾ
	int SetOnlySelectedDeviceDisplay();
public:
	afx_msg void OnCbnSelchangeComboParamNames();
	afx_msg void OnBnClickedCheckStartCallbackGrab();
	afx_msg void OnBnClickedCheckStartGrab();
	afx_msg void OnCbnSelchangeComboParamInfo();
	afx_msg void OnBnClickedButtonExecuteCommand();

private:
	CMvDeviceManager    *m_pMvDeviceManager;
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheckSettings();
};
