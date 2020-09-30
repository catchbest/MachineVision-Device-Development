
// Demo_BasicDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Demo_Basic.h"
#include "Demo_BasicDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



TCHAR     g_szTraceInfo[BUFFER_NUM][128] = { 0 };
int       g_nTraceNum = 0;


//using namespace MVDSDK;

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
: CDialogEx(CDemo_BasicDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


	m_nDeviceCurSel = -1;    // 当前操作设备的索引号

	memset(m_hGrabImageExitEvent, NULL, MVD_MAX_DEVICE_NUM * sizeof(HANDLE));
	memset(m_hGrabImageThread, NULL, MVD_MAX_DEVICE_NUM * sizeof(HANDLE));
	memset(&m_GrabImageThread, NULL, MVD_MAX_DEVICE_NUM * sizeof(GRAB_THREAD_CONTEXT));

	m_pBitmapInfo = NULL;

	InitialBmpInfo();        /// 初始化图像信息，用于显示
}

void CDemo_BasicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TRACE, m_ListTrace);
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
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CDemo_BasicDlg::OnBnClickedButtonSetting)
	ON_MESSAGE(MSG_TRACE, &CDemo_BasicDlg::OnTraceMsg)
END_MESSAGE_MAP()

LRESULT CDemo_BasicDlg::OnTraceMsg(WPARAM wParam, LPARAM lParam)
{
	m_ListTrace.AddString((LPCTSTR)lParam);
	return 0;
}


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
	StartGrabImageThread(false);    /// 用户如果开启了主动采集线程需要在调用Uninitial之前结束

	if (m_pBitmapInfo)
	{
		delete [] m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}


	Uninitial();    

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

	TRACE_API( Initial(DIT_ALL, &m_DeviceInformationList) );

	for (unsigned int i = 0; i < m_DeviceInformationList.uiDeviceNum; i++)
	{
		TCHAR szString[256] = { 0 };
		_stprintf_s(szString, 256, _T("Model: %s, Serial Number: %d"),
			m_DeviceInformationList.pDeviceInformation[i]->szModelName,
			m_DeviceInformationList.pDeviceInformation[i]->uiSerialNumber
			);
		pComboBox->AddString(szString);
	}

	// 默认选择的设备索引，如果没有设备，将索引设为-1
	m_nDeviceCurSel = m_DeviceInformationList.uiDeviceNum == 0 ? -1 : 0;
	pComboBox->SetCurSel(m_nDeviceCurSel);

	// 更加选择的设备，更新界面
	Update_Interface_When_Device_Selected();    

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

/// 初始化图像信息头，用于显示函数
void CDemo_BasicDlg::InitialBmpInfo()
{
	if (m_pBitmapInfo != NULL)    return;

	m_pBitmapInfo = (LPBITMAPINFO)new char[sizeof(BITMAPINFOHEADER)+256 * sizeof(RGBQUAD)];
	memset((VOID*)m_pBitmapInfo, 0, sizeof(BITMAPINFOHEADER)+256 * sizeof(RGBQUAD));

	if (m_pBitmapInfo == NULL)
	{
		return;
	}

	m_pBitmapInfo->bmiHeader.biSize = sizeof(tagBITMAPINFOHEADER);
	m_pBitmapInfo->bmiHeader.biPlanes = 1;
	m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;
	m_pBitmapInfo->bmiHeader.biSizeImage = 0;
	m_pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo->bmiHeader.biClrImportant = 0;

	m_pBitmapInfo->bmiHeader.biWidth = 0;
	m_pBitmapInfo->bmiHeader.biHeight = 0;
	m_pBitmapInfo->bmiHeader.biBitCount = 0;
	m_pBitmapInfo->bmiHeader.biSizeImage = 0;  //m_nWidth * m_nHeight * ( m_nBitCount >> 3 );
	for (int i = 0; i<256; i++)
	{
		m_pBitmapInfo->bmiColors[i].rgbBlue = (BYTE)i;
		m_pBitmapInfo->bmiColors[i].rgbGreen = (BYTE)i;
		m_pBitmapInfo->bmiColors[i].rgbRed = (BYTE)i;
		m_pBitmapInfo->bmiColors[i].rgbReserved = (BYTE)i;
	}
}

/// 显示采集的图像
void CDemo_BasicDlg::DisplayImage(int nDeviceIndex, MVD_GRAB_IMAGE_INFO *pGrabImageInfo, unsigned char *pGrabImageData)
{
	if (pGrabImageInfo == NULL)    return;
	if (nDeviceIndex != m_nDeviceCurSel)    return;

	HWND   hStaticDisplay = (HWND)::GetDlgItem(m_hWnd, IDC_STATIC_DISPLAY);
	HDC    hDC = ::GetDC(hStaticDisplay);
	int    nOldMode = -1;

	/// 根据采集图像基本信息修改图像信息头
	m_pBitmapInfo->bmiHeader.biWidth = pGrabImageInfo->ImageBaseInfo.nImageWidth;
	m_pBitmapInfo->bmiHeader.biHeight = pGrabImageInfo->ImageBaseInfo.nImageHeight;
	m_pBitmapInfo->bmiHeader.biBitCount = pGrabImageInfo->ImageBaseInfo.nImageBitCount;
	m_pBitmapInfo->bmiHeader.biSizeImage = pGrabImageInfo->ImageBaseInfo.nTotalBytes;


	RECT   rt;
	::GetClientRect(hStaticDisplay, &rt);
	nOldMode = ::SetStretchBltMode(hDC, COLORONCOLOR);

	/// 显示图像在Static控件上
	::StretchDIBits(hDC,
		rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top,
		0, 0, pGrabImageInfo->ImageBaseInfo.nImageWidth, pGrabImageInfo->ImageBaseInfo.nImageHeight,
		pGrabImageData,
		(BITMAPINFO *)m_pBitmapInfo,
		DIB_RGB_COLORS,
		SRCCOPY);

	::SetStretchBltMode(hDC, nOldMode);

	::ReleaseDC(hStaticDisplay, hDC);

	return;
}

/// 主要用于显示帧率
void CDemo_BasicDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (m_nDeviceCurSel == -1)    return;

	/// 显示帧率计时器
	if (nIDEvent == TIMERID_GET_FPS)
	{
		float fFps;

		TRACE_API(GetGrabbingFps(m_nDeviceCurSel, &fFps));
		TCHAR   szFps[32] = { '\0' };
		_stprintf_s(szFps, 32, _T("Grab Fps = %0.2f"), fFps);
		SetWindowText(szFps);
	}

	CDialogEx::OnTimer(nIDEvent);
}


/// 当用户改变当前选择设备
void CDemo_BasicDlg::OnCbnSelchangeComboDevicesList()
{
	/// 先获取当前被选择的设备索引
	CComboBox    *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_DEVICES_LIST);
	m_nDeviceCurSel = pComboBox->GetCurSel();

	Update_Interface_When_Device_Selected();
}

/// 打开、关闭设备
void CDemo_BasicDlg::OnBnClickedCheckOpenCloseDevice()
{
	if (m_nDeviceCurSel == -1)    return;

	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_OPEN_CLOSE_DEVICE))->GetCheck();

	TRACE_API(SetDeviceOpen(m_nDeviceCurSel, bCheck ? true : false));

	Update_Interface_When_Device_Selected();
}


/// 采集回调
void __stdcall GrabbingCallback(int nDeviceIndex, MVD_GRAB_IMAGE_INFO* pGrabImageInfo, unsigned char *pGrabImageData, void* pUser)
{
	CDemo_BasicDlg *pDlg = (CDemo_BasicDlg*)pUser;

	TCHAR szBuf[128] = { 0 };
	_stprintf_s(szBuf, 128, _T("GrabbingCallback( uiFrameCounter = %d, Elapse = %d, ImageData = %p )\n"), 
		pGrabImageInfo->ImageExtendInfo.uiFrameCounter, 
		pGrabImageInfo->ImageExtendInfo.ui64ElapseTimeMicrosecond, 
		pGrabImageData);
	// m_ListTrace.AddString(szBuf);

	/// 显示图像
	pDlg->DisplayImage(nDeviceIndex, pGrabImageInfo, pGrabImageData);
}

/// 启动、停止回调采集
void CDemo_BasicDlg::OnBnClickedCheckStartCallbackGrab()
{
	if (m_nDeviceCurSel == -1)    return;

	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB))->GetCheck();

	if (bCheck)
	{
		m_ListTrace.ResetContent();

		/// 需先启动采集
		TRACE_API(SetGrabbingStart(m_nDeviceCurSel, true));
		/// 再开启回调
		TRACE_API(SetGrabbingCallback(m_nDeviceCurSel, &GrabbingCallback, this));
		/// 启动计时器显示帧率
		SetTimer(TIMERID_GET_FPS, 2000, NULL);    
	}
	else
	{
		/// 需先停止回调
		TRACE_API(SetGrabbingCallback(m_nDeviceCurSel, NULL, NULL));
		/// 再停止采集
		TRACE_API(SetGrabbingStart(m_nDeviceCurSel, false));
		KillTimer(TIMERID_GET_FPS);
	}

	((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB))->SetWindowText( bCheck ? _T("停止回调采集") : _T("启动回调采集"));

	CButton            *pBtnStartCallbackGrab = ((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB));
	CButton            *pBtnStartGrab = ((CButton*)GetDlgItem(IDC_CHECK_START_GRAB));

	pBtnStartGrab->EnableWindow(bCheck ? false : true);
}

/// 主动采集线程
UINT WINAPI GrabImageThread(LPVOID pParam)
{
	GRAB_THREAD_CONTEXT    *pGrabThreadContext = (GRAB_THREAD_CONTEXT*)pParam;
	CDemo_BasicDlg *pDlg = (CDemo_BasicDlg*)pGrabThreadContext->pDlg;

	pDlg->GrabImageThreadX(pGrabThreadContext->nDeviceIndex);
	return 0;
}

void CDemo_BasicDlg::GrabImageThreadX(int nDeviceIndex)
{
	if (nDeviceIndex == -1)    return;

	int nRet = MVD_SUCCESS;

	while (TRUE)
	{
		if (WAIT_OBJECT_0 == WaitForSingleObject(m_hGrabImageExitEvent[nDeviceIndex], 0))
		{ /// 退出线程事件通知
			break;
		}

		/// 采集一帧图像，这时的图像信息及数据都在pImageOut结构中，这个是SDK分配的，要尽快调用GrabImageRelease释放。
		MVD_GRAB_IMAGE_INFO *pGrabImageInfo = NULL;
		unsigned char       *pGrabImageData = NULL;
		TRACE_API(GrabImage(nDeviceIndex, &pGrabImageInfo, &pGrabImageData));

		TCHAR szBuf[128] = { 0 };
		_stprintf_s(szBuf, 128, _T("GrabImageThreadX( uiFrameCounter = %d, Elapse = %d, ImageData = %p )\n"),
			pGrabImageInfo->ImageExtendInfo.uiFrameCounter, 
			pGrabImageInfo->ImageExtendInfo.ui64ElapseTimeMicrosecond, 
			pGrabImageData);
		// m_ListTrace.AddString(szBuf);

		/// 显示图像到Static窗口
		DisplayImage(nDeviceIndex, pGrabImageInfo, pGrabImageData);

#if 0
		/// 保存图像
		TCHAR chImageName[256] = { 0 };
		_stprintf_s(chImageName, 256, _T("Image_w%d_h%d_fn%08d.bmp"), pImageOut->ImageBaseInfo.nImageWidth, pImageOut->ImageBaseInfo.nImageHeight, pImageOut->ImageExtendInfo.ui64DeviceTimeStamp);

		MVD_SAVE_IMAGE_INFORMATION SaveImageParam = { 0 };
		SaveImageParam.pszImageName = chImageName;
		SaveImageParam.SaveImageFormat = SIF_JPG;
		SaveImageParam.nJpgQuality = 0;
		nRet = SaveImage(pImageOut, SaveImageParam);
#endif
		// 当MVD_GrabImage返回的内存使用完之后，必须要调用GrabImageRelease进行释放。
		TRACE_API(GrabImageRelease(m_nDeviceCurSel));
	}

}


/// 启动、停止主动采集线程
bool CDemo_BasicDlg::StartGrabImageThread(bool bStart)
{
	if (m_nDeviceCurSel == -1)    return false;

	if (bStart)
	{
		if (m_hGrabImageThread[m_nDeviceCurSel] != NULL)   return true;

		TRACE_API(SetGrabbingStart(m_nDeviceCurSel, true));

		m_hGrabImageExitEvent[m_nDeviceCurSel] = CreateEvent(NULL, TRUE, FALSE, NULL);		// Manual Reset, No signal

		DWORD    dwThreadID;

		/// 为了区分多台相机，将相机的索引传递给线程作为线程的上下文
		m_GrabImageThread[m_nDeviceCurSel].pDlg = this;
		m_GrabImageThread[m_nDeviceCurSel].nDeviceIndex = m_nDeviceCurSel;

		m_hGrabImageThread[m_nDeviceCurSel] = (HANDLE)_beginthreadex(NULL, 0, (PBEGINTHREADEX_FUNC)GrabImageThread, &m_GrabImageThread[m_nDeviceCurSel], 0, (PBEGINTHREADEX_ID)&dwThreadID);

		if (m_hGrabImageThread[m_nDeviceCurSel] != NULL)
		{
			return true;
		}

	}
	else
	{
		if (m_hGrabImageThread[m_nDeviceCurSel] == NULL)   return true;

		if (m_hGrabImageExitEvent[m_nDeviceCurSel] != NULL)
		{
			SetEvent(m_hGrabImageExitEvent[m_nDeviceCurSel]);
		}

		if (WAIT_OBJECT_0 != WaitForSingleObject(m_hGrabImageThread[m_nDeviceCurSel], 5000))
		{
			TerminateThread(m_hGrabImageThread[m_nDeviceCurSel], 0);
		}

		CloseHandle(m_hGrabImageThread[m_nDeviceCurSel]);
		m_hGrabImageThread[m_nDeviceCurSel] = NULL;

		CloseHandle(m_hGrabImageExitEvent[m_nDeviceCurSel]);
		m_hGrabImageExitEvent[m_nDeviceCurSel] = NULL;

		TRACE_API(SetGrabbingStart(m_nDeviceCurSel, false));

		return true;
	}

	return true;
}

/// 点击启动、停止主动采集按钮
void CDemo_BasicDlg::OnBnClickedCheckStartGrab()
{
	if (m_nDeviceCurSel == -1)    return;

	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_START_GRAB))->GetCheck();

	// 开启主动调用采集函数的线程
	if (bCheck)
	{
		// m_ListTrace.ResetContent();

		StartGrabImageThread(true);

		((CButton*)GetDlgItem(IDC_CHECK_START_GRAB))->SetWindowText(_T("停止主动采集线程"));

		SetTimer(TIMERID_GET_FPS, 2000, NULL);//启动计时器显示帧率
	}
	else
	{
		StartGrabImageThread(false);

		((CButton*)GetDlgItem(IDC_CHECK_START_GRAB))->SetWindowText(_T("启动主动采集线程"));

		KillTimer(TIMERID_GET_FPS);          //关闭计时器
	}

	CButton            *pBtnStartCallbackGrab = ((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB));
	CButton            *pBtnStartGrab = ((CButton*)GetDlgItem(IDC_CHECK_START_GRAB));

	pBtnStartCallbackGrab->EnableWindow(bCheck ? false : true);

}

//
// 界面状态，根据不同的设备和操作进行更新
//

// 当用户选择一个设备，更新相应的界面
void CDemo_BasicDlg::Update_Interface_When_Device_Selected()
{
	if (m_nDeviceCurSel == -1)    return;

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

	/// 获取设备是否已经打开
	bool bOpen;
	TRACE_API(GetDeviceOpen(m_nDeviceCurSel, &bOpen));

	/// 更新设备开启关闭按钮
	pBtnOpenDevice->SetCheck(bOpen);
	pBtnOpenDevice->SetWindowText(bOpen ? _T("关闭设备") : _T("打开设备"));

	PMVD_GRABBING_CALLBACK pfCallback = NULL;
	 /// 获取采集回调设置信息，如果获取的pfCallback为NULL，则表示采集回调没有开启
	TRACE_API(GetGrabbingCallback(m_nDeviceCurSel, &pfCallback, NULL));

	/// 更新回调采集按钮
	pBtnStartCallbackGrab->EnableWindow((m_hGrabImageThread[m_nDeviceCurSel] == NULL && bOpen) ? true : false);
	pBtnStartCallbackGrab->SetWindowText(pfCallback == NULL ? _T("启动回调采集") : _T("停止回调采集"));
	pBtnStartCallbackGrab->SetCheck(pfCallback == NULL ? false : true);

	/// 更新主动采集按钮
	pBtnStartGrab->EnableWindow((pfCallback == NULL && bOpen) ? true : false);
	pBtnStartGrab->SetWindowText(m_hGrabImageThread[m_nDeviceCurSel] == NULL ? _T("启动主动采集线程") : _T("停止主动采集线程"));
	pBtnStartGrab->SetCheck(m_hGrabImageThread[m_nDeviceCurSel] == NULL ? false : true);

}

// 当IDC_COMBO_DEVICES_LIST中的选择变化时需要调用更新设备信息列表
void CDemo_BasicDlg::Update_ListBoxDeviceInfo()
{
	if (m_nDeviceCurSel == -1)    return;

	CListBox *pListBox = (CListBox*)GetDlgItem(IDC_LIST_DEVICE_INFO);
	pListBox->ResetContent();

	TCHAR szDeviceInfo[128] = { 0 };

	_stprintf_s(szDeviceInfo, 128, _T("%s: %d"), 
		g_Language == L_CHS ? _T("设备型号ID") : _T("DeviceModel"),
		m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->uiDeviceModel);
	pListBox->AddString(szDeviceInfo);

	_stprintf_s(szDeviceInfo, 128, _T("%s: %s"), 
		g_Language == L_CHS ? _T("设备型号名") : _T("ModelName"),
		m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->szModelName);
	pListBox->AddString(szDeviceInfo);

	_stprintf_s(szDeviceInfo, 128, _T("%s: %d"), 
	    g_Language == L_CHS ? _T("设备序列号") : _T("SerialNumber"),
	    m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->uiSerialNumber);
	pListBox->AddString(szDeviceInfo);

	_stprintf_s(szDeviceInfo, 128, _T("FirmwareVersion = %d.%d"), 
		m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->FirmwareVersion.sValue.ucMajor, m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->FirmwareVersion.sValue.ucMinor);
	pListBox->AddString(szDeviceInfo);

	_stprintf_s(szDeviceInfo, 128, _T("FpgaVersion = %d.%d"), 
		m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->FpgaVersion.sValue.ucMajor, m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->FpgaVersion.sValue.ucMinor);
	pListBox->AddString(szDeviceInfo);

	_stprintf_s(szDeviceInfo, 128, _T("UserDefinedName = %s"), 
		m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->szUserDefinedName);
	pListBox->AddString(szDeviceInfo);

	if (m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->DeviceInterfaceType == DIT_USB)
	{
		_stprintf_s(szDeviceInfo, 128, _T("%s:  USB"), g_Language == L_CHS ? _T("设备接口类型") : _T("DeviceInterfaceType"));
		pListBox->AddString(szDeviceInfo);
	}
	else if (m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->DeviceInterfaceType == DIT_GIGE)
	{
		_stprintf_s(szDeviceInfo, 128, _T("%s:  GIGE"), g_Language == L_CHS ? _T("设备接口类型") : _T("DeviceInterfaceType"));
		pListBox->AddString(szDeviceInfo);

		_stprintf_s(szDeviceInfo, 128, _T("%s: %s"), g_Language == L_CHS ? _T("网卡名称") : _T("AdapterName"), m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.szAdapterFriendlyName);
		pListBox->AddString(szDeviceInfo);

	    _stprintf_s(szDeviceInfo, 128, _T("%s: %x-%x-%x-%x-%x-%x"), 
			g_Language == L_CHS ? _T("网卡物理地址") : _T("AdapterMac"),
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterMac[0],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterMac[1],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterMac[2],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterMac[3],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterMac[4],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterMac[5]);
	    pListBox->AddString(szDeviceInfo);

		_stprintf_s(szDeviceInfo, 128, _T("%s: %d.%d.%d.%d"),
			g_Language == L_CHS ? _T("网卡IP地址") : _T("AdapterIp"),
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterIp[0],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterIp[1],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterIp[2],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterIp[3]);
		pListBox->AddString(szDeviceInfo);

		_stprintf_s(szDeviceInfo, 128, _T("AdapterSubnetMask = %d.%d.%d.%d"),
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterSubnetMask[0],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterSubnetMask[1],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterSubnetMask[2],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterSubnetMask[3]);
		pListBox->AddString(szDeviceInfo);

		_stprintf_s(szDeviceInfo, 128, _T("AdapterDefaultGateWay = %d.%d.%d.%d"),
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterDefaultGateWay[0],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterDefaultGateWay[1],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterDefaultGateWay[2],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterDefaultGateWay[3]);
		pListBox->AddString(szDeviceInfo);

		_stprintf_s(szDeviceInfo, 128, _T("AdapterMtu = %d"),
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.uiMtu);
			pListBox->AddString(szDeviceInfo);

		_stprintf_s(szDeviceInfo, 128, _T("%s: %x-%x-%x-%x-%x-%x"),
			g_Language == L_CHS ? _T("设备物理地址") : _T("DeviceMac"),
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceMac[0],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceMac[1],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceMac[2],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceMac[3],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceMac[4],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceMac[5]);
		pListBox->AddString(szDeviceInfo);

		_stprintf_s(szDeviceInfo, 128, _T("%s: %d.%d.%d.%d"),
			g_Language == L_CHS ? _T("设备IP地址") : _T("DeviceIp"),
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceIp[0],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceIp[1],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceIp[2],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceIp[3]);
		pListBox->AddString(szDeviceInfo);

		_stprintf_s(szDeviceInfo, 128, _T("DeviceSubnetMask = %d.%d.%d.%d"),
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceSubnetMask[0],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceSubnetMask[1],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceSubnetMask[2],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceSubnetMask[3]);
		pListBox->AddString(szDeviceInfo);

		_stprintf_s(szDeviceInfo, 128, _T("DeviceDefaultGateWay = %d.%d.%d.%d"),
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceDefaultGateWay[0],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceDefaultGateWay[1],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceDefaultGateWay[2],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceDefaultGateWay[3]);
		pListBox->AddString(szDeviceInfo);

	}

}

/// 打开快捷设置页面
void CDemo_BasicDlg::OnBnClickedButtonSetting()
{
	TRACE_API(OpenSettingPage(m_nDeviceCurSel, m_hWnd, 0, 0));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                      下面代码没有实现，不需参考
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 根据选择的设备，更新参数名称下拉列表
void CDemo_BasicDlg::Update_ComboBoxParamNames()
{
	if (m_nDeviceCurSel == -1)    return;


	// 根据选择的参数名，更新相应的参数信息
	Update_Interface_When_ParamNames_Selected();
}



// 当"参数名下拉列表"选择变化时，更新相应的参数信息。
void CDemo_BasicDlg::Update_Interface_When_ParamNames_Selected()
{
	if (m_nDeviceCurSel == -1)    return;

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


	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

// 更新设备支持的命令名下拉列表
void CDemo_BasicDlg::Update_ComboBoxCommandNames()
{
	if (m_nDeviceCurSel == -1)    return;
}

void CDemo_BasicDlg::OnBnClickedButtonExecuteCommand()
{
	if (m_nDeviceCurSel == -1)    return;

	CComboBox    *pComboBoxCommandNames = (CComboBox*)GetDlgItem(IDC_COMBO_COMMAND_NAMES);
	int nCommandSel = pComboBoxCommandNames->GetCurSel();

	TCHAR chCommandName[128] = { 0 };
	pComboBoxCommandNames->GetLBText(nCommandSel, chCommandName);

}





