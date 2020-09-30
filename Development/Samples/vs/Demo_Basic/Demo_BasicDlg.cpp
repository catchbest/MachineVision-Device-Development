
// Demo_BasicDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CDemo_BasicDlg �Ի���


CDemo_BasicDlg::CDemo_BasicDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CDemo_BasicDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


	m_nDeviceCurSel = -1;    // ��ǰ�����豸��������

	memset(m_hGrabImageExitEvent, NULL, MVD_MAX_DEVICE_NUM * sizeof(HANDLE));
	memset(m_hGrabImageThread, NULL, MVD_MAX_DEVICE_NUM * sizeof(HANDLE));
	memset(&m_GrabImageThread, NULL, MVD_MAX_DEVICE_NUM * sizeof(GRAB_THREAD_CONTEXT));

	m_pBitmapInfo = NULL;

	InitialBmpInfo();        /// ��ʼ��ͼ����Ϣ��������ʾ
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDemo_BasicDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDemo_BasicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDemo_BasicDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	StartGrabImageThread(false);    /// �û���������������ɼ��߳���Ҫ�ڵ���Uninitial֮ǰ����

	if (m_pBitmapInfo)
	{
		delete [] m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}


	Uninitial();    

	CDialogEx::OnClose();
}



// CDemo_BasicDlg ��Ϣ�������
BOOL CDemo_BasicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
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

	// Ĭ��ѡ����豸���������û���豸����������Ϊ-1
	m_nDeviceCurSel = m_DeviceInformationList.uiDeviceNum == 0 ? -1 : 0;
	pComboBox->SetCurSel(m_nDeviceCurSel);

	// ����ѡ����豸�����½���
	Update_Interface_When_Device_Selected();    

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

/// ��ʼ��ͼ����Ϣͷ��������ʾ����
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

/// ��ʾ�ɼ���ͼ��
void CDemo_BasicDlg::DisplayImage(int nDeviceIndex, MVD_GRAB_IMAGE_INFO *pGrabImageInfo, unsigned char *pGrabImageData)
{
	if (pGrabImageInfo == NULL)    return;
	if (nDeviceIndex != m_nDeviceCurSel)    return;

	HWND   hStaticDisplay = (HWND)::GetDlgItem(m_hWnd, IDC_STATIC_DISPLAY);
	HDC    hDC = ::GetDC(hStaticDisplay);
	int    nOldMode = -1;

	/// ���ݲɼ�ͼ�������Ϣ�޸�ͼ����Ϣͷ
	m_pBitmapInfo->bmiHeader.biWidth = pGrabImageInfo->ImageBaseInfo.nImageWidth;
	m_pBitmapInfo->bmiHeader.biHeight = pGrabImageInfo->ImageBaseInfo.nImageHeight;
	m_pBitmapInfo->bmiHeader.biBitCount = pGrabImageInfo->ImageBaseInfo.nImageBitCount;
	m_pBitmapInfo->bmiHeader.biSizeImage = pGrabImageInfo->ImageBaseInfo.nTotalBytes;


	RECT   rt;
	::GetClientRect(hStaticDisplay, &rt);
	nOldMode = ::SetStretchBltMode(hDC, COLORONCOLOR);

	/// ��ʾͼ����Static�ؼ���
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

/// ��Ҫ������ʾ֡��
void CDemo_BasicDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (m_nDeviceCurSel == -1)    return;

	/// ��ʾ֡�ʼ�ʱ��
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


/// ���û��ı䵱ǰѡ���豸
void CDemo_BasicDlg::OnCbnSelchangeComboDevicesList()
{
	/// �Ȼ�ȡ��ǰ��ѡ����豸����
	CComboBox    *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_DEVICES_LIST);
	m_nDeviceCurSel = pComboBox->GetCurSel();

	Update_Interface_When_Device_Selected();
}

/// �򿪡��ر��豸
void CDemo_BasicDlg::OnBnClickedCheckOpenCloseDevice()
{
	if (m_nDeviceCurSel == -1)    return;

	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_OPEN_CLOSE_DEVICE))->GetCheck();

	TRACE_API(SetDeviceOpen(m_nDeviceCurSel, bCheck ? true : false));

	Update_Interface_When_Device_Selected();
}


/// �ɼ��ص�
void __stdcall GrabbingCallback(int nDeviceIndex, MVD_GRAB_IMAGE_INFO* pGrabImageInfo, unsigned char *pGrabImageData, void* pUser)
{
	CDemo_BasicDlg *pDlg = (CDemo_BasicDlg*)pUser;

	TCHAR szBuf[128] = { 0 };
	_stprintf_s(szBuf, 128, _T("GrabbingCallback( uiFrameCounter = %d, Elapse = %d, ImageData = %p )\n"), 
		pGrabImageInfo->ImageExtendInfo.uiFrameCounter, 
		pGrabImageInfo->ImageExtendInfo.ui64ElapseTimeMicrosecond, 
		pGrabImageData);
	// m_ListTrace.AddString(szBuf);

	/// ��ʾͼ��
	pDlg->DisplayImage(nDeviceIndex, pGrabImageInfo, pGrabImageData);
}

/// ������ֹͣ�ص��ɼ�
void CDemo_BasicDlg::OnBnClickedCheckStartCallbackGrab()
{
	if (m_nDeviceCurSel == -1)    return;

	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB))->GetCheck();

	if (bCheck)
	{
		m_ListTrace.ResetContent();

		/// ���������ɼ�
		TRACE_API(SetGrabbingStart(m_nDeviceCurSel, true));
		/// �ٿ����ص�
		TRACE_API(SetGrabbingCallback(m_nDeviceCurSel, &GrabbingCallback, this));
		/// ������ʱ����ʾ֡��
		SetTimer(TIMERID_GET_FPS, 2000, NULL);    
	}
	else
	{
		/// ����ֹͣ�ص�
		TRACE_API(SetGrabbingCallback(m_nDeviceCurSel, NULL, NULL));
		/// ��ֹͣ�ɼ�
		TRACE_API(SetGrabbingStart(m_nDeviceCurSel, false));
		KillTimer(TIMERID_GET_FPS);
	}

	((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB))->SetWindowText( bCheck ? _T("ֹͣ�ص��ɼ�") : _T("�����ص��ɼ�"));

	CButton            *pBtnStartCallbackGrab = ((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB));
	CButton            *pBtnStartGrab = ((CButton*)GetDlgItem(IDC_CHECK_START_GRAB));

	pBtnStartGrab->EnableWindow(bCheck ? false : true);
}

/// �����ɼ��߳�
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
		{ /// �˳��߳��¼�֪ͨ
			break;
		}

		/// �ɼ�һ֡ͼ����ʱ��ͼ����Ϣ�����ݶ���pImageOut�ṹ�У������SDK����ģ�Ҫ�������GrabImageRelease�ͷš�
		MVD_GRAB_IMAGE_INFO *pGrabImageInfo = NULL;
		unsigned char       *pGrabImageData = NULL;
		TRACE_API(GrabImage(nDeviceIndex, &pGrabImageInfo, &pGrabImageData));

		TCHAR szBuf[128] = { 0 };
		_stprintf_s(szBuf, 128, _T("GrabImageThreadX( uiFrameCounter = %d, Elapse = %d, ImageData = %p )\n"),
			pGrabImageInfo->ImageExtendInfo.uiFrameCounter, 
			pGrabImageInfo->ImageExtendInfo.ui64ElapseTimeMicrosecond, 
			pGrabImageData);
		// m_ListTrace.AddString(szBuf);

		/// ��ʾͼ��Static����
		DisplayImage(nDeviceIndex, pGrabImageInfo, pGrabImageData);

#if 0
		/// ����ͼ��
		TCHAR chImageName[256] = { 0 };
		_stprintf_s(chImageName, 256, _T("Image_w%d_h%d_fn%08d.bmp"), pImageOut->ImageBaseInfo.nImageWidth, pImageOut->ImageBaseInfo.nImageHeight, pImageOut->ImageExtendInfo.ui64DeviceTimeStamp);

		MVD_SAVE_IMAGE_INFORMATION SaveImageParam = { 0 };
		SaveImageParam.pszImageName = chImageName;
		SaveImageParam.SaveImageFormat = SIF_JPG;
		SaveImageParam.nJpgQuality = 0;
		nRet = SaveImage(pImageOut, SaveImageParam);
#endif
		// ��MVD_GrabImage���ص��ڴ�ʹ����֮�󣬱���Ҫ����GrabImageRelease�����ͷš�
		TRACE_API(GrabImageRelease(m_nDeviceCurSel));
	}

}


/// ������ֹͣ�����ɼ��߳�
bool CDemo_BasicDlg::StartGrabImageThread(bool bStart)
{
	if (m_nDeviceCurSel == -1)    return false;

	if (bStart)
	{
		if (m_hGrabImageThread[m_nDeviceCurSel] != NULL)   return true;

		TRACE_API(SetGrabbingStart(m_nDeviceCurSel, true));

		m_hGrabImageExitEvent[m_nDeviceCurSel] = CreateEvent(NULL, TRUE, FALSE, NULL);		// Manual Reset, No signal

		DWORD    dwThreadID;

		/// Ϊ�����ֶ�̨�������������������ݸ��߳���Ϊ�̵߳�������
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

/// ���������ֹͣ�����ɼ���ť
void CDemo_BasicDlg::OnBnClickedCheckStartGrab()
{
	if (m_nDeviceCurSel == -1)    return;

	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_START_GRAB))->GetCheck();

	// �����������òɼ��������߳�
	if (bCheck)
	{
		// m_ListTrace.ResetContent();

		StartGrabImageThread(true);

		((CButton*)GetDlgItem(IDC_CHECK_START_GRAB))->SetWindowText(_T("ֹͣ�����ɼ��߳�"));

		SetTimer(TIMERID_GET_FPS, 2000, NULL);//������ʱ����ʾ֡��
	}
	else
	{
		StartGrabImageThread(false);

		((CButton*)GetDlgItem(IDC_CHECK_START_GRAB))->SetWindowText(_T("���������ɼ��߳�"));

		KillTimer(TIMERID_GET_FPS);          //�رռ�ʱ��
	}

	CButton            *pBtnStartCallbackGrab = ((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB));
	CButton            *pBtnStartGrab = ((CButton*)GetDlgItem(IDC_CHECK_START_GRAB));

	pBtnStartCallbackGrab->EnableWindow(bCheck ? false : true);

}

//
// ����״̬�����ݲ�ͬ���豸�Ͳ������и���
//

// ���û�ѡ��һ���豸��������Ӧ�Ľ���
void CDemo_BasicDlg::Update_Interface_When_Device_Selected()
{
	if (m_nDeviceCurSel == -1)    return;

	// ���ȸ����豸��Ϣ
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

	/// ��ȡ�豸�Ƿ��Ѿ���
	bool bOpen;
	TRACE_API(GetDeviceOpen(m_nDeviceCurSel, &bOpen));

	/// �����豸�����رհ�ť
	pBtnOpenDevice->SetCheck(bOpen);
	pBtnOpenDevice->SetWindowText(bOpen ? _T("�ر��豸") : _T("���豸"));

	PMVD_GRABBING_CALLBACK pfCallback = NULL;
	 /// ��ȡ�ɼ��ص�������Ϣ�������ȡ��pfCallbackΪNULL�����ʾ�ɼ��ص�û�п���
	TRACE_API(GetGrabbingCallback(m_nDeviceCurSel, &pfCallback, NULL));

	/// ���»ص��ɼ���ť
	pBtnStartCallbackGrab->EnableWindow((m_hGrabImageThread[m_nDeviceCurSel] == NULL && bOpen) ? true : false);
	pBtnStartCallbackGrab->SetWindowText(pfCallback == NULL ? _T("�����ص��ɼ�") : _T("ֹͣ�ص��ɼ�"));
	pBtnStartCallbackGrab->SetCheck(pfCallback == NULL ? false : true);

	/// ���������ɼ���ť
	pBtnStartGrab->EnableWindow((pfCallback == NULL && bOpen) ? true : false);
	pBtnStartGrab->SetWindowText(m_hGrabImageThread[m_nDeviceCurSel] == NULL ? _T("���������ɼ��߳�") : _T("ֹͣ�����ɼ��߳�"));
	pBtnStartGrab->SetCheck(m_hGrabImageThread[m_nDeviceCurSel] == NULL ? false : true);

}

// ��IDC_COMBO_DEVICES_LIST�е�ѡ��仯ʱ��Ҫ���ø����豸��Ϣ�б�
void CDemo_BasicDlg::Update_ListBoxDeviceInfo()
{
	if (m_nDeviceCurSel == -1)    return;

	CListBox *pListBox = (CListBox*)GetDlgItem(IDC_LIST_DEVICE_INFO);
	pListBox->ResetContent();

	TCHAR szDeviceInfo[128] = { 0 };

	_stprintf_s(szDeviceInfo, 128, _T("%s: %d"), 
		g_Language == L_CHS ? _T("�豸�ͺ�ID") : _T("DeviceModel"),
		m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->uiDeviceModel);
	pListBox->AddString(szDeviceInfo);

	_stprintf_s(szDeviceInfo, 128, _T("%s: %s"), 
		g_Language == L_CHS ? _T("�豸�ͺ���") : _T("ModelName"),
		m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->szModelName);
	pListBox->AddString(szDeviceInfo);

	_stprintf_s(szDeviceInfo, 128, _T("%s: %d"), 
	    g_Language == L_CHS ? _T("�豸���к�") : _T("SerialNumber"),
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
		_stprintf_s(szDeviceInfo, 128, _T("%s:  USB"), g_Language == L_CHS ? _T("�豸�ӿ�����") : _T("DeviceInterfaceType"));
		pListBox->AddString(szDeviceInfo);
	}
	else if (m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->DeviceInterfaceType == DIT_GIGE)
	{
		_stprintf_s(szDeviceInfo, 128, _T("%s:  GIGE"), g_Language == L_CHS ? _T("�豸�ӿ�����") : _T("DeviceInterfaceType"));
		pListBox->AddString(szDeviceInfo);

		_stprintf_s(szDeviceInfo, 128, _T("%s: %s"), g_Language == L_CHS ? _T("��������") : _T("AdapterName"), m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.szAdapterFriendlyName);
		pListBox->AddString(szDeviceInfo);

	    _stprintf_s(szDeviceInfo, 128, _T("%s: %x-%x-%x-%x-%x-%x"), 
			g_Language == L_CHS ? _T("���������ַ") : _T("AdapterMac"),
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterMac[0],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterMac[1],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterMac[2],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterMac[3],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterMac[4],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucAdapterMac[5]);
	    pListBox->AddString(szDeviceInfo);

		_stprintf_s(szDeviceInfo, 128, _T("%s: %d.%d.%d.%d"),
			g_Language == L_CHS ? _T("����IP��ַ") : _T("AdapterIp"),
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
			g_Language == L_CHS ? _T("�豸�����ַ") : _T("DeviceMac"),
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceMac[0],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceMac[1],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceMac[2],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceMac[3],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceMac[4],
			m_DeviceInformationList.pDeviceInformation[m_nDeviceCurSel]->SpecialInfo.stGigEInfo.ucDeviceMac[5]);
		pListBox->AddString(szDeviceInfo);

		_stprintf_s(szDeviceInfo, 128, _T("%s: %d.%d.%d.%d"),
			g_Language == L_CHS ? _T("�豸IP��ַ") : _T("DeviceIp"),
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

/// �򿪿������ҳ��
void CDemo_BasicDlg::OnBnClickedButtonSetting()
{
	TRACE_API(OpenSettingPage(m_nDeviceCurSel, m_hWnd, 0, 0));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                      �������û��ʵ�֣�����ο�
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ѡ����豸�����²������������б�
void CDemo_BasicDlg::Update_ComboBoxParamNames()
{
	if (m_nDeviceCurSel == -1)    return;


	// ����ѡ��Ĳ�������������Ӧ�Ĳ�����Ϣ
	Update_Interface_When_ParamNames_Selected();
}



// ��"�����������б�"ѡ��仯ʱ��������Ӧ�Ĳ�����Ϣ��
void CDemo_BasicDlg::Update_Interface_When_ParamNames_Selected()
{
	if (m_nDeviceCurSel == -1)    return;

}

// ���û��ı䵱ǰ�Ĳ���
void CDemo_BasicDlg::OnCbnSelchangeComboParamNames()
{
	Update_Interface_When_ParamNames_Selected();
}


// �������ò���
void CDemo_BasicDlg::OnCbnSelchangeComboParamInfo()
{
	// ���Ȼ�ȡ������
	CComboBox    *pComboBoxParamNames = (CComboBox*)GetDlgItem(IDC_COMBO_PARAM_NAMES);
	int nParameterSel = pComboBoxParamNames->GetCurSel();

	TCHAR chParamName[128] = { 0 };
	pComboBoxParamNames->GetLBText(nParameterSel, chParamName);

	// ��ȡ����ֵ
	CComboBox    *pComboBoxParameterValue = (CComboBox*)GetDlgItem(IDC_COMBO_PARAM_INFO);
	int nParameterValueSel = pComboBoxParameterValue->GetCurSel();

	TCHAR chParamValue[128] = { 0 };
	pComboBoxParameterValue->GetLBText(nParameterValueSel, chParamValue);


}
void CDemo_BasicDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (m_nDeviceCurSel == -1)    return;
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CSpinButtonCtrl    *pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_PARAM_VALUE);

	int                 nValue = ((CSliderCtrl*)pScrollBar)->GetPos();

	CComboBox    *pComboBoxParamNames = (CComboBox*)GetDlgItem(IDC_COMBO_PARAM_NAMES);
	int nParameterSel = pComboBoxParamNames->GetCurSel();

	TCHAR chParamName[128] = { 0 };
	pComboBoxParamNames->GetLBText(nParameterSel, chParamName);


	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

// �����豸֧�ֵ������������б�
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





