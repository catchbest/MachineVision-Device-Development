
// Demo_BasicDlg.h : 头文件
//

#pragma once

class CMvDeviceManager;


// CDemo_BasicDlg 对话框
class CDemo_BasicDlg : public CDialogEx
{
// 构造
public:
	CDemo_BasicDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DEMO_BASIC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	// 当参数名列表选择变化时，更新相应的参数信息
	void Update_Interface_When_ParamNames_Selected();
	void Update_ComboBoxCommandNames();
	void Update_Interface_When_Device_Selected();
	// 因为只有一个窗口，同一时刻只让被选择的设备显示
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
