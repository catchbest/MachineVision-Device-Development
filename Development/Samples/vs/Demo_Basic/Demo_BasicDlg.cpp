
// Demo_BasicDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Demo_Basic.h"
#include "Demo_BasicDlg.h"
#include "afxdialogex.h"
#include "MvDeviceManager.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMERID_GET_FPS   1


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDemo_BasicDlg 对话框



CDemo_BasicDlg::CDemo_BasicDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CDemo_BasicDlg::IDD, pParent), m_pMvDeviceManager(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pMvDeviceManager = new CMvDeviceManager();

	m_nDeviceCurSel = -1;    // 当前操作设备的索引号
}

void CDemo_BasicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDemo_BasicDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_OPEN_CLOSE_DEVICE, &CDemo_BasicDlg::OnBnClickedCheckOpenCloseDevice)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICES_LIST, &CDemo_BasicDlg::OnCbnSelchangeComboDevicesList)
	ON_CBN_SELCHANGE(IDC_COMBO_PARAM_NAMES, &CDemo_BasicDlg::OnCbnSelchangeComboParamNames)
	ON_BN_CLICKED(IDC_CHECK_START_CALLBACK_GRAB, &CDemo_BasicDlg::OnBnClickedCheckStartCallbackGrab)
	ON_CBN_SELCHANGE(IDC_COMBO_PARAM_INFO, &CDemo_BasicDlg::OnCbnSelchangeComboParamInfo)
	ON_BN_CLICKED(IDC_BUTTON_EXECUTE_COMMAND, &CDemo_BasicDlg::OnBnClickedButtonExecuteCommand)
	ON_BN_CLICKED(IDC_CHECK_START_GRAB, &CDemo_BasicDlg::OnBnClickedCheckStartGrab)
	ON_WM_HSCROLL()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_SETTINGS, &CDemo_BasicDlg::OnBnClickedCheckSettings)
END_MESSAGE_MAP()

void CDemo_BasicDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDemo_BasicDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDemo_BasicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDemo_BasicDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	MVD_Uninitial();

	if (m_pMvDeviceManager != NULL)
	{
		delete m_pMvDeviceManager;
		m_pMvDeviceManager = NULL;
	}
	CDialogEx::OnClose();
}

// CDemo_BasicDlg 消息处理程序
BOOL CDemo_BasicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	CComboBox    *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_DEVICES_LIST);
	pComboBox->ResetContent();

	// 获取SDK版本号
	int nSdkVersion = m_pMvDeviceManager->QuerySdkVersion();
	TCHAR szSdkVersion[128] = { 0 };
	_stprintf(szSdkVersion, _T("%d-%d-%d-%d"), (nSdkVersion & 0xff000000) >> 24, (nSdkVersion & 0x00ff0000) >> 16, (nSdkVersion & 0x0000ff00) >> 8, (nSdkVersion & 0x000000ff));
	SetWindowText(szSdkVersion);

	// 获取设备数目
	int nDeviceNum = m_pMvDeviceManager->GetDeviceNum();

	// 获取设备信息列表，并显示简单的设备信息在“设备列表下拉框”里
	MVD_DEVICE_INFO    stDeviceInfo;
	unsigned char ucIp1, ucIp2, ucIp3, ucIp4;
	for (int i = 0; i < nDeviceNum; i++)
	{
		memset(&stDeviceInfo, 0, sizeof(MVD_DEVICE_INFO));

		// 获取设备的信息
		m_pMvDeviceManager->GetDeviceInfo(i, &stDeviceInfo);

		if (stDeviceInfo.DeviceInterfaceType == MVD_DEVICE_INTERFACE_TYPE_GIGE)
		{
			ucIp1 = ((stDeviceInfo.Info.stDeviceInfoGige.uiDeviceIpCurrent & 0xff000000) >> 24);
			ucIp2 = ((stDeviceInfo.Info.stDeviceInfoGige.uiDeviceIpCurrent & 0x00ff0000) >> 16);
			ucIp3 = ((stDeviceInfo.Info.stDeviceInfoGige.uiDeviceIpCurrent & 0x0000ff00) >> 8);
			ucIp4 = (stDeviceInfo.Info.stDeviceInfoGige.uiDeviceIpCurrent & 0x000000ff);

     		// 千兆网接口设备信息
			TCHAR szDeviceInfo[128] = { 0 };
			_stprintf(szDeviceInfo, _T("%d-%s-%s-IP:%d.%d.%d.%d"), i, stDeviceInfo.Info.stDeviceInfoGige.szDeviceModelName, \
				stDeviceInfo.Info.stDeviceInfoGige.szDeviceSerialNumber, \
				ucIp4, ucIp3, ucIp2, ucIp1);
			pComboBox->AddString(szDeviceInfo);
		}
	}

	// 默认选择的设备索引，如果没有设备，将索引设为-1
	m_nDeviceCurSel = nDeviceNum == 0 ? -1 : 0;     
	pComboBox->SetCurSel(m_nDeviceCurSel);

	// 更加选择的设备，更新界面
	Update_Interface_When_Device_Selected();    

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 因为只有一个窗口，同一时刻只让被选择的设备显示
int CDemo_BasicDlg::SetOnlySelectedDeviceDisplay()
{
	CStatic *pStaticDisplay = ((CStatic*)GetDlgItem(IDC_STATIC_DISPLAY));

	RECT    rtDisplay = { 0 };
	pStaticDisplay->GetClientRect(&rtDisplay);

	MVD_DISPLAY_POSITION_INFO    stDisplayPositionInfo = { 0 };

	int nDeviceNum = m_pMvDeviceManager->GetDeviceNum();
	for (int i = 0; i < nDeviceNum; i++)
	{
		if (i == m_nDeviceCurSel)
		{
			stDisplayPositionInfo.hDisplayWnd = pStaticDisplay->GetSafeHwnd();
			stDisplayPositionInfo.nX          = rtDisplay.left;
			stDisplayPositionInfo.nY          = rtDisplay.top;
			stDisplayPositionInfo.nWidth      = rtDisplay.right - rtDisplay.left;
			stDisplayPositionInfo.nHeight     = rtDisplay.bottom - rtDisplay.top;
		}
		else
		{
			memset(&stDisplayPositionInfo, 0, sizeof(MVD_DISPLAY_POSITION_INFO));
		}

	    m_pMvDeviceManager->SetDisplayInfo(i, &stDisplayPositionInfo);

	}

	return 0;
}

// 当用户改变当前选择设备
void CDemo_BasicDlg::OnCbnSelchangeComboDevicesList()
{
	// 先获取当前被选择的设备索引
	CComboBox    *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_DEVICES_LIST);
	m_nDeviceCurSel = pComboBox->GetCurSel();

	Update_Interface_When_Device_Selected();
}

// 打开、关闭设备
void CDemo_BasicDlg::OnBnClickedCheckOpenCloseDevice()
{
	if (m_nDeviceCurSel == -1)    return;

	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_OPEN_CLOSE_DEVICE))->GetCheck();

	if (bCheck)
	{
		m_pMvDeviceManager->OpenDevice(m_nDeviceCurSel, true);
	}
	else
	{
		m_pMvDeviceManager->OpenDevice(m_nDeviceCurSel, false);
	}

	Update_Interface_When_Device_Selected();
}

void __stdcall ImageCallback(MVD_FRAME_OUT* pFrameOut, void* pUser)
{
	CDemo_BasicDlg *pDlg = (CDemo_BasicDlg*)pUser;

	TCHAR szBuf[128] = { 0 };
	_stprintf(szBuf, _T("FrameId    = %d\n"), pFrameOut->stFrameOutInfo.uiFrameId);
	OutputDebugString(szBuf);
	_stprintf(szBuf, _T("FrameData  = %d\n"), pFrameOut->ucFrameData);
	OutputDebugString(szBuf);

}

// 启动、停止回调采集
void CDemo_BasicDlg::OnBnClickedCheckStartCallbackGrab()
{
	if (m_nDeviceCurSel == -1)    return;

	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB))->GetCheck();


	if (bCheck)
	{
		MVD_StartGrabbing(m_nDeviceCurSel);
		MVD_SetCallBack(m_nDeviceCurSel, &ImageCallback, this);
		MVD_StartCallback(m_nDeviceCurSel);     // 在回调里获取图像

		((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB))->SetWindowText(_T("停止回调采集"));

		SetTimer(TIMERID_GET_FPS, 2000, NULL);//启动计时器显示帧率
	}
	else
	{
		MVD_StopCallback(m_nDeviceCurSel);      // 停止在回调里获取图像
		MVD_StopGrabbing(m_nDeviceCurSel);

		((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB))->SetWindowText(_T("启动回调采集"));

		KillTimer(TIMERID_GET_FPS);          //关闭计时器
	}

	CButton            *pBtnStartCallbackGrab = ((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB));
	CButton            *pBtnStartGrab = ((CButton*)GetDlgItem(IDC_CHECK_START_GRAB));
	if (m_pMvDeviceManager->QueryIsCallbackGrab(m_nDeviceCurSel))
	{
		// 启动回调采集，就不能进行主动采集
		pBtnStartGrab->EnableWindow(false);
	}
	else
	{
		pBtnStartGrab->EnableWindow(true);
	}

	if (m_pMvDeviceManager->IsGrabImageThreadRunning(m_nDeviceCurSel))
	{
		// 启动主动采集，就不能进行回调采集
		pBtnStartCallbackGrab->EnableWindow(false);
	}
	else
	{
		pBtnStartCallbackGrab->EnableWindow(true);
	}
}

// 启动、停止主动采集
void CDemo_BasicDlg::OnBnClickedCheckStartGrab()
{
	if (m_nDeviceCurSel == -1)    return;

	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_START_GRAB))->GetCheck();

	// 开启主动调用采集函数的线程
	if (bCheck)
	{
		m_pMvDeviceManager->StartGrabImageThread(m_nDeviceCurSel, true);

		((CButton*)GetDlgItem(IDC_CHECK_START_GRAB))->SetWindowText(_T("停止主动采集"));

		SetTimer(TIMERID_GET_FPS, 2000, NULL);//启动计时器显示帧率
	}
	else
	{
		m_pMvDeviceManager->StartGrabImageThread(m_nDeviceCurSel, false);

		((CButton*)GetDlgItem(IDC_CHECK_START_GRAB))->SetWindowText(_T("启动主动采集"));

		KillTimer(TIMERID_GET_FPS);          //关闭计时器
	}

	CButton            *pBtnStartCallbackGrab = ((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB));
	CButton            *pBtnStartGrab = ((CButton*)GetDlgItem(IDC_CHECK_START_GRAB));
	if (m_pMvDeviceManager->QueryIsCallbackGrab(m_nDeviceCurSel))
	{
		// 启动回调采集，就不能进行主动采集
		pBtnStartGrab->EnableWindow(false);
	}
	else
	{
		pBtnStartGrab->EnableWindow(true);
	}

	if (m_pMvDeviceManager->IsGrabImageThreadRunning(m_nDeviceCurSel))
	{
		// 启动主动采集，就不能进行回调采集
		pBtnStartCallbackGrab->EnableWindow(false);
	}
	else
	{
		pBtnStartCallbackGrab->EnableWindow(true);
	}
}

//
// 界面状态，根据不同的设备和操作进行更新
//

// 当用户选择一个设备，更新相应的界面
void CDemo_BasicDlg::Update_Interface_When_Device_Selected()
{
	if (m_nDeviceCurSel == -1)    return;

	// 因为只有一个窗口，同一时刻只让被选择的设备显示
	SetOnlySelectedDeviceDisplay();

	// 首先更新设备信息
	Update_ListBoxDeviceInfo();


	CButton            *pBtnOpenDevice = ((CButton*)GetDlgItem(IDC_CHECK_OPEN_CLOSE_DEVICE));
	CButton            *pBtnStartCallbackGrab = ((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB));
	CButton            *pBtnStartGrab = ((CButton*)GetDlgItem(IDC_CHECK_START_GRAB));
	CComboBox          *pComboBoxParamNames = (CComboBox*)GetDlgItem(IDC_COMBO_PARAM_NAMES);
	CComboBox          *pComboBoxParamInfo = (CComboBox*)GetDlgItem(IDC_COMBO_PARAM_INFO);
	CSliderCtrl        *pSliderCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_PARAM_VALUE);
	CSpinButtonCtrl    *pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_PARAM_VALUE);
	CEdit              *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PARAM_VALUE);
	CComboBox          *pComboBoxCommandNames = (CComboBox*)GetDlgItem(IDC_COMBO_COMMAND_NAMES);
	CButton            *pBtnExecuteCommand = ((CButton*)GetDlgItem(IDC_BUTTON_EXECUTE_COMMAND));

	// 判断设备是否打开
	if (!m_pMvDeviceManager->QueryIsOpen(m_nDeviceCurSel))
	{
		// 如果设备没有打开，所有操作无效
		pBtnOpenDevice->SetCheck(false);
		pBtnOpenDevice->SetWindowText(_T("打开设备"));

		pBtnStartCallbackGrab->SetCheck(false);
		pBtnStartCallbackGrab->EnableWindow(false);

		pBtnStartGrab->SetCheck(false);
		pBtnStartGrab->EnableWindow(false);

		pComboBoxParamNames->ResetContent();
		pComboBoxParamNames->EnableWindow(false);

		pComboBoxParamInfo->ResetContent();
		pComboBoxParamInfo->ShowWindow(SW_SHOW);
		pComboBoxParamInfo->EnableWindow(false);


		pSliderCtrl->ShowWindow(SW_HIDE);
		pSliderCtrl->EnableWindow(false);

		pSpin->ShowWindow(SW_HIDE);
		pSpin->EnableWindow(false);
		pEdit->ShowWindow(SW_HIDE);
		pEdit->EnableWindow(false);

		pComboBoxCommandNames->ResetContent();
		pComboBoxCommandNames->EnableWindow(false);
		pBtnExecuteCommand->EnableWindow(false);

		return;
	}

	// 设备已经打开
	pBtnOpenDevice->SetCheck(true);
	pBtnOpenDevice->SetWindowText(_T("关闭设备"));

	// 更新参数名称列表
	pComboBoxParamNames->ResetContent();
	pComboBoxParamNames->EnableWindow(true);
	Update_ComboBoxParamNames();

	// 更新命令名称列表
	pComboBoxCommandNames->ResetContent();
	pComboBoxCommandNames->EnableWindow(true);
	pBtnExecuteCommand->EnableWindow(true);
	Update_ComboBoxCommandNames();

	// 更新回调采集、主动采集按钮
	pBtnStartCallbackGrab->EnableWindow(true);
	pBtnStartGrab->EnableWindow(true);


	// 判断是否正在回调采集
	if (m_pMvDeviceManager->QueryIsCallbackGrab(m_nDeviceCurSel))
	{
		// 回调采集已经启动，就不能进行主动采集
		pBtnStartCallbackGrab->SetWindowText(_T("停止回调采集"));
		pBtnStartCallbackGrab->SetCheck(true);
		pBtnStartGrab->EnableWindow(false);
	}
	else
	{
		// 回调采集没有启动
		pBtnStartCallbackGrab->SetWindowText(_T("启动回调采集"));
		pBtnStartCallbackGrab->SetCheck(false);
		pBtnStartGrab->EnableWindow(true);
	}
}

// 当IDC_COMBO_DEVICES_LIST中的选择变化时需要调用更新设备信息列表
void CDemo_BasicDlg::Update_ListBoxDeviceInfo()
{
	if (m_nDeviceCurSel == -1)    return;

	CListBox *pListBox = (CListBox*)GetDlgItem(IDC_LIST_DEVICE_INFO);
	pListBox->ResetContent();

	MVD_DEVICE_INFO    stDeviceInfo;
	memset(&stDeviceInfo, 0, sizeof(MVD_DEVICE_INFO));

	m_pMvDeviceManager->GetDeviceInfo(m_nDeviceCurSel, &stDeviceInfo);

	TCHAR szDeviceInfo[128] = { 0 };
	// 更新设备信息列表框
	unsigned char ucIp1, ucIp2, ucIp3, ucIp4;

	if (stDeviceInfo.DeviceInterfaceType == MVD_DEVICE_INTERFACE_TYPE_GIGE)
	{
		_stprintf(szDeviceInfo, _T("index = %d"), m_nDeviceCurSel);
		pListBox->AddString(szDeviceInfo);

		_stprintf(szDeviceInfo, _T("szDeviceModelName = %s"), stDeviceInfo.Info.stDeviceInfoGige.szDeviceModelName);
		pListBox->AddString(szDeviceInfo);

		_stprintf(szDeviceInfo, _T("szDeviceSerialNumber = %s"), stDeviceInfo.Info.stDeviceInfoGige.szDeviceSerialNumber);
		pListBox->AddString(szDeviceInfo);

		ucIp1 = ((stDeviceInfo.Info.stDeviceInfoGige.uiDeviceIpCurrent & 0xff000000) >> 24);
		ucIp2 = ((stDeviceInfo.Info.stDeviceInfoGige.uiDeviceIpCurrent & 0x00ff0000) >> 16);
		ucIp3 = ((stDeviceInfo.Info.stDeviceInfoGige.uiDeviceIpCurrent & 0x0000ff00) >> 8);
		ucIp4 = (stDeviceInfo.Info.stDeviceInfoGige.uiDeviceIpCurrent & 0x000000ff);

		_stprintf(szDeviceInfo, _T("uiDeviceIpCurrent = %d.%d.%d.%d"), ucIp4, ucIp3, ucIp2, ucIp1 );
		//in_addr  iaDeviceIp;
		//iaDeviceIp.S_un.S_addr = stDeviceInfo.Info.stDeviceInfoGige.uiDeviceIpCurrent;
		//_stprintf(szDeviceInfo, _T("uiDeviceIpCurrent = %s"), inet_ntoa(iaDeviceIp));
		pListBox->AddString(szDeviceInfo);

		_stprintf(szDeviceInfo, _T("Device Mac = %02x-%02x-%02x-%02x-%02x-%02x"), stDeviceInfo.Info.stDeviceInfoGige.ucDeviceMac[0], stDeviceInfo.Info.stDeviceInfoGige.ucDeviceMac[1], stDeviceInfo.Info.stDeviceInfoGige.ucDeviceMac[2], stDeviceInfo.Info.stDeviceInfoGige.ucDeviceMac[3], stDeviceInfo.Info.stDeviceInfoGige.ucDeviceMac[4], stDeviceInfo.Info.stDeviceInfoGige.ucDeviceMac[5]);
		pListBox->AddString(szDeviceInfo);


		_stprintf(szDeviceInfo, _T("Adapter Mac = %02x-%02x-%02x-%02x-%02x-%02x"), stDeviceInfo.Info.stDeviceInfoGige.ucAdapterMac[0], stDeviceInfo.Info.stDeviceInfoGige.ucAdapterMac[1], stDeviceInfo.Info.stDeviceInfoGige.ucAdapterMac[2], stDeviceInfo.Info.stDeviceInfoGige.ucAdapterMac[3], stDeviceInfo.Info.stDeviceInfoGige.ucAdapterMac[4], stDeviceInfo.Info.stDeviceInfoGige.ucAdapterMac[5]);
		pListBox->AddString(szDeviceInfo);

		ucIp1 = ((stDeviceInfo.Info.stDeviceInfoGige.ulAdapterIp & 0xff000000) >> 24);
		ucIp2 = ((stDeviceInfo.Info.stDeviceInfoGige.ulAdapterIp & 0x00ff0000) >> 16);
		ucIp3 = ((stDeviceInfo.Info.stDeviceInfoGige.ulAdapterIp & 0x0000ff00) >> 8);
		ucIp4 = (stDeviceInfo.Info.stDeviceInfoGige.ulAdapterIp & 0x000000ff);

		_stprintf(szDeviceInfo, _T("Adapter Ip = %d.%d.%d.%d"), ucIp4, ucIp3, ucIp2, ucIp1);
		pListBox->AddString(szDeviceInfo);

		ucIp1 = ((stDeviceInfo.Info.stDeviceInfoGige.ulAdapterSubnetMask & 0xff000000) >> 24);
		ucIp2 = ((stDeviceInfo.Info.stDeviceInfoGige.ulAdapterSubnetMask & 0x00ff0000) >> 16);
		ucIp3 = ((stDeviceInfo.Info.stDeviceInfoGige.ulAdapterSubnetMask & 0x0000ff00) >> 8);
		ucIp4 = (stDeviceInfo.Info.stDeviceInfoGige.ulAdapterSubnetMask & 0x000000ff);

		_stprintf(szDeviceInfo, _T("Adapter SubnetMask = %d.%d.%d.%d"), ucIp4, ucIp3, ucIp2, ucIp1);
		pListBox->AddString(szDeviceInfo);

		_stprintf(szDeviceInfo, _T("Adapter FriendlyName = %s"), stDeviceInfo.Info.stDeviceInfoGige.szAdapterFriendlyName);
		pListBox->AddString(szDeviceInfo);

		_stprintf(szDeviceInfo, _T("Adapter Description = %s"), stDeviceInfo.Info.stDeviceInfoGige.szAdapterDescription);
		pListBox->AddString(szDeviceInfo);

		_stprintf(szDeviceInfo, _T("Adapter Ip = %d-%d-%d-%d"), stDeviceInfo.Info.stDeviceInfoGige.ucAdapterIp[0], stDeviceInfo.Info.stDeviceInfoGige.ucAdapterIp[1], stDeviceInfo.Info.stDeviceInfoGige.ucAdapterIp[2], stDeviceInfo.Info.stDeviceInfoGige.ucAdapterIp[3]);
		pListBox->AddString(szDeviceInfo);

		_stprintf(szDeviceInfo, _T("Adapter Dns = %d-%d-%d-%d"), stDeviceInfo.Info.stDeviceInfoGige.ucAdapterDns[0], stDeviceInfo.Info.stDeviceInfoGige.ucAdapterDns[1], stDeviceInfo.Info.stDeviceInfoGige.ucAdapterDns[2], stDeviceInfo.Info.stDeviceInfoGige.ucAdapterDns[3]);
		pListBox->AddString(szDeviceInfo);
	}
}

// 根据选择的设备，更新参数名称下拉列表
void CDemo_BasicDlg::Update_ComboBoxParamNames()
{
	if (m_nDeviceCurSel == -1)    return;

	// 查询可以设置的参数名，填入参数名下拉列表框
	MVD_QUERY_INFO stQueryInfo = { (MVD_VALUE_TYPE)0 };
	m_pMvDeviceManager->QueryParamNames(m_nDeviceCurSel, &stQueryInfo);

	CComboBox    *pComboBoxParamNames = (CComboBox*)GetDlgItem(IDC_COMBO_PARAM_NAMES);
	pComboBoxParamNames->ResetContent();

	// 将查询到的参数名填入下拉列表框，这些名字可以作为MVD_SetParam和MVD_GetParam函数的第二个参数
	for (int i = 0; i < stQueryInfo.nValueNum; i++)
	{
		ASSERT(stQueryInfo.enInfoType == MVD_VALUE_TYPE_STRING);
		pComboBoxParamNames->AddString(stQueryInfo.unValues[i].pszValue);
	}

	// 默认选择第一个参数名
	pComboBoxParamNames->SetCurSel(0);

	// 根据选择的参数名，更新相应的参数信息
	Update_Interface_When_ParamNames_Selected();
}

// 更新设备支持的命令名下拉列表
void CDemo_BasicDlg::Update_ComboBoxCommandNames()
{
	if (m_nDeviceCurSel == -1)    return;

	// 查询可以执行的命令名，填入命令名列表框
	MVD_QUERY_INFO stQueryInfo = { (MVD_VALUE_TYPE)0 };
	m_pMvDeviceManager->QueryCommandNames(m_nDeviceCurSel, &stQueryInfo);

	CComboBox    *pComboBoxCommandNames = (CComboBox*)GetDlgItem(IDC_COMBO_COMMAND_NAMES);
	pComboBoxCommandNames->ResetContent();

	for (int i = 0; i < stQueryInfo.nValueNum; i++)
	{
		pComboBoxCommandNames->AddString(stQueryInfo.unValues[i].pszValue);
	}

	pComboBoxCommandNames->SetCurSel(0);

}

// 当"参数名下拉列表"选择变化时，更新相应的参数信息。
void CDemo_BasicDlg::Update_Interface_When_ParamNames_Selected()
{
	if (m_nDeviceCurSel == -1)    return;

	// 首先获取参数名列表的选择项，并获取这个选择的参数名
	CComboBox    *pComboBoxParamNames = (CComboBox*)GetDlgItem(IDC_COMBO_PARAM_NAMES);
	int nParameterSel = pComboBoxParamNames->GetCurSel();

	TCHAR chParamName[128] = { 0 };
	pComboBoxParamNames->GetLBText(nParameterSel, chParamName);

	// 获取这个参数的信息
	MVD_GET_PARAME_VALUE stGetParamInfo = { (MVD_VALUE_TYPE)0 };
	m_pMvDeviceManager->GetParam(m_nDeviceCurSel, chParamName, &stGetParamInfo);

	CComboBox          *pComboBoxParamInfo = (CComboBox*)GetDlgItem(IDC_COMBO_PARAM_INFO);
	CSliderCtrl        *pSliderCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_PARAM_VALUE);
	CSpinButtonCtrl    *pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_PARAM_VALUE);
	CEdit              *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PARAM_VALUE);

	// 对于MVD_VALUE_TYPE_STRING类型的参数，我们用下拉列表框来显示
	if (stGetParamInfo.enParamType == MVD_VALUE_TYPE_STRING)
	{
		pComboBoxParamInfo->ShowWindow(SW_SHOW);
		pComboBoxParamInfo->EnableWindow(true);

		pSliderCtrl->ShowWindow(SW_HIDE);
		pSliderCtrl->EnableWindow(false);
		pSpin->ShowWindow(SW_HIDE);
		pSpin->EnableWindow(false);
		pEdit->ShowWindow(SW_HIDE);
		pEdit->EnableWindow(false);

		pComboBoxParamInfo->ResetContent();

		for (int i = 0; i < stGetParamInfo.nValueNum; i++)
		{
			pComboBoxParamInfo->AddString(stGetParamInfo.unValues[i].pszValue);
		}

		// 使当前值被选择
		int nCurSel = pComboBoxParamInfo->FindString(0, stGetParamInfo.unValueCur.pszValue);
		pComboBoxParamInfo->SetCurSel(nCurSel);

		if (stGetParamInfo.enAccessMode == MVD_ACCESS_MODE_RO)    pComboBoxParamInfo->EnableWindow(false);
		else                                                      pComboBoxParamInfo->EnableWindow(true);
	}

	// 对于MVD_VALUE_TYPE_INT并且nValueNum != 0的类型参数，也就是参数的值是离散的整型数据，我们也用下拉列表列出
	else if (stGetParamInfo.enParamType == MVD_VALUE_TYPE_INT && stGetParamInfo.nValueNum != 0)
	{
		pComboBoxParamInfo->ShowWindow(SW_SHOW);
		pComboBoxParamInfo->EnableWindow(true);

		pSliderCtrl->ShowWindow(SW_HIDE);
		pSliderCtrl->EnableWindow(false);
		pSpin->ShowWindow(SW_HIDE);
		pSpin->EnableWindow(false);
		pEdit->ShowWindow(SW_HIDE);
		pEdit->EnableWindow(false);

		pComboBoxParamInfo->ResetContent();
		for (int i = 0; i < stGetParamInfo.nValueNum; i++)
		{
			pComboBoxParamInfo->AddString(_itot(stGetParamInfo.unValues[i].nValue, NULL, 10));
		}

		// 使当前值被选择
		int nCurSel = pComboBoxParamInfo->FindString(0, _itot(stGetParamInfo.unValueCur.nValue, NULL, 10));
		pComboBoxParamInfo->SetCurSel(nCurSel);

		if (stGetParamInfo.enAccessMode == MVD_ACCESS_MODE_RO)    pComboBoxParamInfo->EnableWindow(false);
		else                                                      pComboBoxParamInfo->EnableWindow(true);

	}

	// 对于MVD_VALUE_TYPE_INT并且nValueNum == 0的类型参数，也就是参数的值是连续的整型数据，我们用滑动控件来设置显示
	else if (stGetParamInfo.enParamType == MVD_VALUE_TYPE_INT && stGetParamInfo.nValueNum == 0)
	{
		pComboBoxParamInfo->ShowWindow(SW_HIDE);
		pComboBoxParamInfo->EnableWindow(false);

		pSliderCtrl->ShowWindow(SW_SHOW);
		pSliderCtrl->EnableWindow(true);
		pSpin->ShowWindow(SW_SHOW);
		pSpin->EnableWindow(true);
		pEdit->ShowWindow(SW_SHOW);
		pEdit->EnableWindow(true);

		pSliderCtrl->SetRange(stGetParamInfo.unValueMin.nValue, stGetParamInfo.unValueMax.nValue);
		pSliderCtrl->SetPos(stGetParamInfo.unValueCur.nValue);
		pSliderCtrl->SetLineSize(stGetParamInfo.unValueInc.nValue);    // 左右键移动间隔

		DWORD   dwStyle = pSpin->GetStyle();
		pSpin->SetRange32(stGetParamInfo.unValueMin.nValue, stGetParamInfo.unValueMax.nValue);
		pSpin->SetPos32(stGetParamInfo.unValueCur.nValue);

		if (stGetParamInfo.enAccessMode == MVD_ACCESS_MODE_RO)
		{
			pSliderCtrl->EnableWindow(false);
			pSpin->EnableWindow(false);
			pEdit->EnableWindow(false);
		}
		else
		{
			pSliderCtrl->EnableWindow(true);
			pSpin->EnableWindow(false);
			pEdit->EnableWindow(false);
		}

	}

}

// 当用户改变当前的参数
void CDemo_BasicDlg::OnCbnSelchangeComboParamNames()
{
	Update_Interface_When_ParamNames_Selected();
}


// 用于设置参数
void CDemo_BasicDlg::OnCbnSelchangeComboParamInfo()
{
	// 首先获取参数名
	CComboBox    *pComboBoxParamNames = (CComboBox*)GetDlgItem(IDC_COMBO_PARAM_NAMES);
	int nParameterSel = pComboBoxParamNames->GetCurSel();

	TCHAR chParamName[128] = { 0 };
	pComboBoxParamNames->GetLBText(nParameterSel, chParamName);

	// 获取参数值
	CComboBox    *pComboBoxParameterValue = (CComboBox*)GetDlgItem(IDC_COMBO_PARAM_INFO);
	int nParameterValueSel = pComboBoxParameterValue->GetCurSel();

	TCHAR chParamValue[128] = { 0 };
	pComboBoxParameterValue->GetLBText(nParameterValueSel, chParamValue);

	// 获取此参数的完整信息，根据stGetParam.enParamType获取参数值的类型（整型，浮点型，字符型）
	MVD_GET_PARAME_VALUE stGetParam;
	MVD_GetParam(m_nDeviceCurSel, chParamName, &stGetParam);
	if (stGetParam.enAccessMode == MVD_ACCESS_MODE_RO)    return;

	// 设置参数值
	MVD_SET_PARAME_VALUE stSetParam;

	stSetParam.enParamType = stGetParam.enParamType;

	// 根据参数值的类型，设置相应的数值
	if (stSetParam.enParamType == MVD_VALUE_TYPE_STRING)
	{// 字符型
		stSetParam.unValue.pszValue = chParamValue;
	}
	else if (stSetParam.enParamType == MVD_VALUE_TYPE_INT)
	{// 整型
		stSetParam.unValue.nValue = _ttoi(chParamValue);
	}

	MVD_SetParam(m_nDeviceCurSel, chParamName, stSetParam);
}


void CDemo_BasicDlg::OnBnClickedButtonExecuteCommand()
{
	if (m_nDeviceCurSel == -1)    return;

	CComboBox    *pComboBoxCommandNames = (CComboBox*)GetDlgItem(IDC_COMBO_COMMAND_NAMES);
	int nCommandSel = pComboBoxCommandNames->GetCurSel();

	TCHAR chCommandName[128] = { 0 };
	pComboBoxCommandNames->GetLBText(nCommandSel, chCommandName);

	MVD_ExecuteCommand(m_nDeviceCurSel, chCommandName);
}

void CDemo_BasicDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (m_nDeviceCurSel == -1)    return;
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CSpinButtonCtrl    *pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_PARAM_VALUE);

	int                 nValue = ((CSliderCtrl*)pScrollBar)->GetPos();

	CComboBox    *pComboBoxParamNames = (CComboBox*)GetDlgItem(IDC_COMBO_PARAM_NAMES);
	int nParameterSel = pComboBoxParamNames->GetCurSel();

	TCHAR chParamName[128] = { 0 };
	pComboBoxParamNames->GetLBText(nParameterSel, chParamName);

	MVD_GET_PARAME_VALUE stGetParam;
	MVD_GetParam(m_nDeviceCurSel, chParamName, &stGetParam);

	switch (pScrollBar->GetDlgCtrlID())
	{
	case IDC_SLIDER_PARAM_VALUE:
		MVD_SET_PARAME_VALUE stSetParam;
		stSetParam.enParamType = stGetParam.enParamType;
		stSetParam.unValue.nValue = nValue;
		MVD_SetParam(m_nDeviceCurSel, chParamName, stSetParam);

		pSpin->SetPos32(nValue);

		break;
	default:
		break;
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDemo_BasicDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (m_nDeviceCurSel == -1)    return;
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == TIMERID_GET_FPS)//显示帧率计时器
	{
		float fFps = m_pMvDeviceManager->QueryGrabFps(m_nDeviceCurSel);
		TCHAR   szFps[32] = { '\0' };
		_stprintf(szFps, _T("Grab Fps = %0.2f"), fFps);
		SetWindowText(szFps);
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CDemo_BasicDlg::OnBnClickedCheckSettings()
{
	// TODO:  在此添加控件通知处理程序代码
	CButton            *pBtnSettings = ((CButton*)GetDlgItem(IDC_CHECK_SETTINGS));

	BOOL bCheck = pBtnSettings->GetCheck();
	
	if (bCheck)
		MVD_OpenSettings(m_hWnd, 0, 0);
	else
		MVD_CloseSettings();
}
