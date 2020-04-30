
// Demo_BasicDlg.cpp : ʵ���ļ�
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
: CDialogEx(CDemo_BasicDlg::IDD, pParent), m_pMvDeviceManager(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pMvDeviceManager = new CMvDeviceManager();

	m_nDeviceCurSel = -1;    // ��ǰ�����豸��������
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
	MVD_Uninitial();

	if (m_pMvDeviceManager != NULL)
	{
		delete m_pMvDeviceManager;
		m_pMvDeviceManager = NULL;
	}
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

	// ��ȡSDK�汾��
	int nSdkVersion = m_pMvDeviceManager->QuerySdkVersion();
	TCHAR szSdkVersion[128] = { 0 };
	_stprintf(szSdkVersion, _T("%d-%d-%d-%d"), (nSdkVersion & 0xff000000) >> 24, (nSdkVersion & 0x00ff0000) >> 16, (nSdkVersion & 0x0000ff00) >> 8, (nSdkVersion & 0x000000ff));
	SetWindowText(szSdkVersion);

	// ��ȡ�豸��Ŀ
	int nDeviceNum = m_pMvDeviceManager->GetDeviceNum();

	// ��ȡ�豸��Ϣ�б�����ʾ�򵥵��豸��Ϣ�ڡ��豸�б���������
	MVD_DEVICE_INFO    stDeviceInfo;
	unsigned char ucIp1, ucIp2, ucIp3, ucIp4;
	for (int i = 0; i < nDeviceNum; i++)
	{
		memset(&stDeviceInfo, 0, sizeof(MVD_DEVICE_INFO));

		// ��ȡ�豸����Ϣ
		m_pMvDeviceManager->GetDeviceInfo(i, &stDeviceInfo);

		if (stDeviceInfo.DeviceInterfaceType == MVD_DEVICE_INTERFACE_TYPE_GIGE)
		{
			ucIp1 = ((stDeviceInfo.Info.stDeviceInfoGige.uiDeviceIpCurrent & 0xff000000) >> 24);
			ucIp2 = ((stDeviceInfo.Info.stDeviceInfoGige.uiDeviceIpCurrent & 0x00ff0000) >> 16);
			ucIp3 = ((stDeviceInfo.Info.stDeviceInfoGige.uiDeviceIpCurrent & 0x0000ff00) >> 8);
			ucIp4 = (stDeviceInfo.Info.stDeviceInfoGige.uiDeviceIpCurrent & 0x000000ff);

     		// ǧ�����ӿ��豸��Ϣ
			TCHAR szDeviceInfo[128] = { 0 };
			_stprintf(szDeviceInfo, _T("%d-%s-%s-IP:%d.%d.%d.%d"), i, stDeviceInfo.Info.stDeviceInfoGige.szDeviceModelName, \
				stDeviceInfo.Info.stDeviceInfoGige.szDeviceSerialNumber, \
				ucIp4, ucIp3, ucIp2, ucIp1);
			pComboBox->AddString(szDeviceInfo);
		}
	}

	// Ĭ��ѡ����豸���������û���豸����������Ϊ-1
	m_nDeviceCurSel = nDeviceNum == 0 ? -1 : 0;     
	pComboBox->SetCurSel(m_nDeviceCurSel);

	// ����ѡ����豸�����½���
	Update_Interface_When_Device_Selected();    

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// ��Ϊֻ��һ�����ڣ�ͬһʱ��ֻ�ñ�ѡ����豸��ʾ
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

// ���û��ı䵱ǰѡ���豸
void CDemo_BasicDlg::OnCbnSelchangeComboDevicesList()
{
	// �Ȼ�ȡ��ǰ��ѡ����豸����
	CComboBox    *pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_DEVICES_LIST);
	m_nDeviceCurSel = pComboBox->GetCurSel();

	Update_Interface_When_Device_Selected();
}

// �򿪡��ر��豸
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

// ������ֹͣ�ص��ɼ�
void CDemo_BasicDlg::OnBnClickedCheckStartCallbackGrab()
{
	if (m_nDeviceCurSel == -1)    return;

	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB))->GetCheck();


	if (bCheck)
	{
		MVD_StartGrabbing(m_nDeviceCurSel);
		MVD_SetCallBack(m_nDeviceCurSel, &ImageCallback, this);
		MVD_StartCallback(m_nDeviceCurSel);     // �ڻص����ȡͼ��

		((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB))->SetWindowText(_T("ֹͣ�ص��ɼ�"));

		SetTimer(TIMERID_GET_FPS, 2000, NULL);//������ʱ����ʾ֡��
	}
	else
	{
		MVD_StopCallback(m_nDeviceCurSel);      // ֹͣ�ڻص����ȡͼ��
		MVD_StopGrabbing(m_nDeviceCurSel);

		((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB))->SetWindowText(_T("�����ص��ɼ�"));

		KillTimer(TIMERID_GET_FPS);          //�رռ�ʱ��
	}

	CButton            *pBtnStartCallbackGrab = ((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB));
	CButton            *pBtnStartGrab = ((CButton*)GetDlgItem(IDC_CHECK_START_GRAB));
	if (m_pMvDeviceManager->QueryIsCallbackGrab(m_nDeviceCurSel))
	{
		// �����ص��ɼ����Ͳ��ܽ��������ɼ�
		pBtnStartGrab->EnableWindow(false);
	}
	else
	{
		pBtnStartGrab->EnableWindow(true);
	}

	if (m_pMvDeviceManager->IsGrabImageThreadRunning(m_nDeviceCurSel))
	{
		// ���������ɼ����Ͳ��ܽ��лص��ɼ�
		pBtnStartCallbackGrab->EnableWindow(false);
	}
	else
	{
		pBtnStartCallbackGrab->EnableWindow(true);
	}
}

// ������ֹͣ�����ɼ�
void CDemo_BasicDlg::OnBnClickedCheckStartGrab()
{
	if (m_nDeviceCurSel == -1)    return;

	BOOL bCheck = ((CButton*)GetDlgItem(IDC_CHECK_START_GRAB))->GetCheck();

	// �����������òɼ��������߳�
	if (bCheck)
	{
		m_pMvDeviceManager->StartGrabImageThread(m_nDeviceCurSel, true);

		((CButton*)GetDlgItem(IDC_CHECK_START_GRAB))->SetWindowText(_T("ֹͣ�����ɼ�"));

		SetTimer(TIMERID_GET_FPS, 2000, NULL);//������ʱ����ʾ֡��
	}
	else
	{
		m_pMvDeviceManager->StartGrabImageThread(m_nDeviceCurSel, false);

		((CButton*)GetDlgItem(IDC_CHECK_START_GRAB))->SetWindowText(_T("���������ɼ�"));

		KillTimer(TIMERID_GET_FPS);          //�رռ�ʱ��
	}

	CButton            *pBtnStartCallbackGrab = ((CButton*)GetDlgItem(IDC_CHECK_START_CALLBACK_GRAB));
	CButton            *pBtnStartGrab = ((CButton*)GetDlgItem(IDC_CHECK_START_GRAB));
	if (m_pMvDeviceManager->QueryIsCallbackGrab(m_nDeviceCurSel))
	{
		// �����ص��ɼ����Ͳ��ܽ��������ɼ�
		pBtnStartGrab->EnableWindow(false);
	}
	else
	{
		pBtnStartGrab->EnableWindow(true);
	}

	if (m_pMvDeviceManager->IsGrabImageThreadRunning(m_nDeviceCurSel))
	{
		// ���������ɼ����Ͳ��ܽ��лص��ɼ�
		pBtnStartCallbackGrab->EnableWindow(false);
	}
	else
	{
		pBtnStartCallbackGrab->EnableWindow(true);
	}
}

//
// ����״̬�����ݲ�ͬ���豸�Ͳ������и���
//

// ���û�ѡ��һ���豸��������Ӧ�Ľ���
void CDemo_BasicDlg::Update_Interface_When_Device_Selected()
{
	if (m_nDeviceCurSel == -1)    return;

	// ��Ϊֻ��һ�����ڣ�ͬһʱ��ֻ�ñ�ѡ����豸��ʾ
	SetOnlySelectedDeviceDisplay();

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

	// �ж��豸�Ƿ��
	if (!m_pMvDeviceManager->QueryIsOpen(m_nDeviceCurSel))
	{
		// ����豸û�д򿪣����в�����Ч
		pBtnOpenDevice->SetCheck(false);
		pBtnOpenDevice->SetWindowText(_T("���豸"));

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

	// �豸�Ѿ���
	pBtnOpenDevice->SetCheck(true);
	pBtnOpenDevice->SetWindowText(_T("�ر��豸"));

	// ���²��������б�
	pComboBoxParamNames->ResetContent();
	pComboBoxParamNames->EnableWindow(true);
	Update_ComboBoxParamNames();

	// �������������б�
	pComboBoxCommandNames->ResetContent();
	pComboBoxCommandNames->EnableWindow(true);
	pBtnExecuteCommand->EnableWindow(true);
	Update_ComboBoxCommandNames();

	// ���»ص��ɼ��������ɼ���ť
	pBtnStartCallbackGrab->EnableWindow(true);
	pBtnStartGrab->EnableWindow(true);


	// �ж��Ƿ����ڻص��ɼ�
	if (m_pMvDeviceManager->QueryIsCallbackGrab(m_nDeviceCurSel))
	{
		// �ص��ɼ��Ѿ��������Ͳ��ܽ��������ɼ�
		pBtnStartCallbackGrab->SetWindowText(_T("ֹͣ�ص��ɼ�"));
		pBtnStartCallbackGrab->SetCheck(true);
		pBtnStartGrab->EnableWindow(false);
	}
	else
	{
		// �ص��ɼ�û������
		pBtnStartCallbackGrab->SetWindowText(_T("�����ص��ɼ�"));
		pBtnStartCallbackGrab->SetCheck(false);
		pBtnStartGrab->EnableWindow(true);
	}
}

// ��IDC_COMBO_DEVICES_LIST�е�ѡ��仯ʱ��Ҫ���ø����豸��Ϣ�б�
void CDemo_BasicDlg::Update_ListBoxDeviceInfo()
{
	if (m_nDeviceCurSel == -1)    return;

	CListBox *pListBox = (CListBox*)GetDlgItem(IDC_LIST_DEVICE_INFO);
	pListBox->ResetContent();

	MVD_DEVICE_INFO    stDeviceInfo;
	memset(&stDeviceInfo, 0, sizeof(MVD_DEVICE_INFO));

	m_pMvDeviceManager->GetDeviceInfo(m_nDeviceCurSel, &stDeviceInfo);

	TCHAR szDeviceInfo[128] = { 0 };
	// �����豸��Ϣ�б��
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

// ����ѡ����豸�����²������������б�
void CDemo_BasicDlg::Update_ComboBoxParamNames()
{
	if (m_nDeviceCurSel == -1)    return;

	// ��ѯ�������õĲ���������������������б��
	MVD_QUERY_INFO stQueryInfo = { (MVD_VALUE_TYPE)0 };
	m_pMvDeviceManager->QueryParamNames(m_nDeviceCurSel, &stQueryInfo);

	CComboBox    *pComboBoxParamNames = (CComboBox*)GetDlgItem(IDC_COMBO_PARAM_NAMES);
	pComboBoxParamNames->ResetContent();

	// ����ѯ���Ĳ��������������б����Щ���ֿ�����ΪMVD_SetParam��MVD_GetParam�����ĵڶ�������
	for (int i = 0; i < stQueryInfo.nValueNum; i++)
	{
		ASSERT(stQueryInfo.enInfoType == MVD_VALUE_TYPE_STRING);
		pComboBoxParamNames->AddString(stQueryInfo.unValues[i].pszValue);
	}

	// Ĭ��ѡ���һ��������
	pComboBoxParamNames->SetCurSel(0);

	// ����ѡ��Ĳ�������������Ӧ�Ĳ�����Ϣ
	Update_Interface_When_ParamNames_Selected();
}

// �����豸֧�ֵ������������б�
void CDemo_BasicDlg::Update_ComboBoxCommandNames()
{
	if (m_nDeviceCurSel == -1)    return;

	// ��ѯ����ִ�е��������������������б��
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

// ��"�����������б�"ѡ��仯ʱ��������Ӧ�Ĳ�����Ϣ��
void CDemo_BasicDlg::Update_Interface_When_ParamNames_Selected()
{
	if (m_nDeviceCurSel == -1)    return;

	// ���Ȼ�ȡ�������б��ѡ�������ȡ���ѡ��Ĳ�����
	CComboBox    *pComboBoxParamNames = (CComboBox*)GetDlgItem(IDC_COMBO_PARAM_NAMES);
	int nParameterSel = pComboBoxParamNames->GetCurSel();

	TCHAR chParamName[128] = { 0 };
	pComboBoxParamNames->GetLBText(nParameterSel, chParamName);

	// ��ȡ�����������Ϣ
	MVD_GET_PARAME_VALUE stGetParamInfo = { (MVD_VALUE_TYPE)0 };
	m_pMvDeviceManager->GetParam(m_nDeviceCurSel, chParamName, &stGetParamInfo);

	CComboBox          *pComboBoxParamInfo = (CComboBox*)GetDlgItem(IDC_COMBO_PARAM_INFO);
	CSliderCtrl        *pSliderCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_PARAM_VALUE);
	CSpinButtonCtrl    *pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_PARAM_VALUE);
	CEdit              *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PARAM_VALUE);

	// ����MVD_VALUE_TYPE_STRING���͵Ĳ����������������б������ʾ
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

		// ʹ��ǰֵ��ѡ��
		int nCurSel = pComboBoxParamInfo->FindString(0, stGetParamInfo.unValueCur.pszValue);
		pComboBoxParamInfo->SetCurSel(nCurSel);

		if (stGetParamInfo.enAccessMode == MVD_ACCESS_MODE_RO)    pComboBoxParamInfo->EnableWindow(false);
		else                                                      pComboBoxParamInfo->EnableWindow(true);
	}

	// ����MVD_VALUE_TYPE_INT����nValueNum != 0�����Ͳ�����Ҳ���ǲ�����ֵ����ɢ���������ݣ�����Ҳ�������б��г�
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

		// ʹ��ǰֵ��ѡ��
		int nCurSel = pComboBoxParamInfo->FindString(0, _itot(stGetParamInfo.unValueCur.nValue, NULL, 10));
		pComboBoxParamInfo->SetCurSel(nCurSel);

		if (stGetParamInfo.enAccessMode == MVD_ACCESS_MODE_RO)    pComboBoxParamInfo->EnableWindow(false);
		else                                                      pComboBoxParamInfo->EnableWindow(true);

	}

	// ����MVD_VALUE_TYPE_INT����nValueNum == 0�����Ͳ�����Ҳ���ǲ�����ֵ���������������ݣ������û����ؼ���������ʾ
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
		pSliderCtrl->SetLineSize(stGetParamInfo.unValueInc.nValue);    // ���Ҽ��ƶ����

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

	// ��ȡ�˲�����������Ϣ������stGetParam.enParamType��ȡ����ֵ�����ͣ����ͣ������ͣ��ַ��ͣ�
	MVD_GET_PARAME_VALUE stGetParam;
	MVD_GetParam(m_nDeviceCurSel, chParamName, &stGetParam);
	if (stGetParam.enAccessMode == MVD_ACCESS_MODE_RO)    return;

	// ���ò���ֵ
	MVD_SET_PARAME_VALUE stSetParam;

	stSetParam.enParamType = stGetParam.enParamType;

	// ���ݲ���ֵ�����ͣ�������Ӧ����ֵ
	if (stSetParam.enParamType == MVD_VALUE_TYPE_STRING)
	{// �ַ���
		stSetParam.unValue.pszValue = chParamValue;
	}
	else if (stSetParam.enParamType == MVD_VALUE_TYPE_INT)
	{// ����
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == TIMERID_GET_FPS)//��ʾ֡�ʼ�ʱ��
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CButton            *pBtnSettings = ((CButton*)GetDlgItem(IDC_CHECK_SETTINGS));

	BOOL bCheck = pBtnSettings->GetCheck();
	
	if (bCheck)
		MVD_OpenSettings(m_hWnd, 0, 0);
	else
		MVD_CloseSettings();
}
