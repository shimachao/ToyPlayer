
// ToyPlayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ToyPlayer.h"
#include "ToyPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CToyPlayerDlg �Ի���




CToyPlayerDlg::CToyPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CToyPlayerDlg::IDD, pParent)
	, m_pMediaControl(new CMediaControl)
	, m_bMute(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ControlPanelPos.left = 0;
	m_ControlPanelPos.right = 500;
}

void CToyPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CToyPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_GRAPH_EVENT, &CToyPlayerDlg::OnGraphEvent)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_PLAY, &CToyPlayerDlg::OnPlay)
	ON_MESSAGE(WM_PAUSE, &CToyPlayerDlg::OnPause)
	ON_MESSAGE(WM_FORWORD, &CToyPlayerDlg::OnForword)
	ON_MESSAGE(WM_RETREAT, &CToyPlayerDlg::OnRetreat)
	ON_WM_LBUTTONDBLCLK()
	ON_MESSAGE(WM_VOLUME_UP, &CToyPlayerDlg::OnVolumeUp)
	ON_MESSAGE(WM_VOLUME_DOWN, &CToyPlayerDlg::OnVolumeDown)
	ON_MESSAGE(WM_SET_VOLUME, &CToyPlayerDlg::OnSetVolume)
	ON_MESSAGE(WM_MUTE, &CToyPlayerDlg::OnMute)
	ON_MESSAGE(WM_UNMUTE, &CToyPlayerDlg::OnUnmute)
	ON_MESSAGE(WM_SHOW_LIST, &CToyPlayerDlg::OnShowList)
	ON_BN_CLICKED(IDC_OPEN_FILE, &CToyPlayerDlg::OnBnClickedOpenFile)
	ON_MESSAGE(WM_OPEN_FILE, &CToyPlayerDlg::OnOpenFile)
	ON_MESSAGE(WM_SCREENSHOT, &CToyPlayerDlg::OnScreenshot)
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_OPEN, &CToyPlayerDlg::OnOpen)
	ON_COMMAND(ID_CLOSE, &CToyPlayerDlg::OnClose)
	ON_COMMAND(ID_PLAY_PAUSE, &CToyPlayerDlg::OnPlayPause)
	ON_COMMAND(ID_FULLSCREEN, &CToyPlayerDlg::OnFullscreen)
	ON_COMMAND(ID_FULL_SCREEN, &CToyPlayerDlg::OnFullScreen)
	ON_COMMAND(ID_MAX_SCREEN, &CToyPlayerDlg::OnMaxScreen)
	ON_COMMAND(ID_DOUBLE_SCREEN, &CToyPlayerDlg::OnDoubleScreen)
	ON_COMMAND(ID_RAW_SCREEN, &CToyPlayerDlg::OnRawScreen)
	ON_COMMAND(ID_ONE_AND_HALF_SCREEN, &CToyPlayerDlg::OnOneAndHalfScreen)
	ON_COMMAND(ID_HALF_SCREEN, &CToyPlayerDlg::OnHalfScreen)
	ON_COMMAND(ID_SCREENSHOT, &CToyPlayerDlg::OnScreenshot)
	ON_COMMAND(ID_MUTE_UNMUTE, &CToyPlayerDlg::OnMuteUnmute)
	ON_COMMAND(ID_LISTDLG, &CToyPlayerDlg::OnListdlg)
	ON_COMMAND(ID_QUIT, &CToyPlayerDlg::OnQuit)
	ON_COMMAND(ID_TOP_WIND, &CToyPlayerDlg::OnTopWind)
	ON_COMMAND(ID_PRE_FILE, &CToyPlayerDlg::OnPreFile)
	ON_COMMAND(ID_NEXT, &CToyPlayerDlg::OnNext)
	ON_COMMAND(ID_FORWARD, &CToyPlayerDlg::OnForward)
	ON_COMMAND(ID_BACKWARD, &CToyPlayerDlg::OnBackward)
	ON_COMMAND(ID_REPLAY, &CToyPlayerDlg::OnReplay)
	ON_COMMAND(ID_ACCELERATOR_PLAY, &CToyPlayerDlg::OnAcceleratorPlay)
	ON_COMMAND(ID_ACCELERATOR_FORWARD, &CToyPlayerDlg::OnAcceleratorForward)
	ON_COMMAND(ID_ACCELERATOR_BACKWARD, &CToyPlayerDlg::OnAcceleratorBackward)
	ON_COMMAND(ID_ACCELERATOR_VOLUME_UP, &CToyPlayerDlg::OnAcceleratorVolumeUp)
	ON_COMMAND(ID_ACCELERATOR_VOLUME_DOWN, &CToyPlayerDlg::OnAcceleratorVolumeDown)
END_MESSAGE_MAP()


// CToyPlayerDlg ��Ϣ�������
HACCEL hAccel;
BOOL CToyPlayerDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_Menu.LoadMenu(IDR_PLAYDLG_MENU);
	hAccel = LoadAccelerators(theApp.m_hInstance,MAKEINTRESOURCE(IDR_PLAYDLG_ACCELERATOR));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CToyPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CToyPlayerDlg::OnPaint()
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
HCURSOR CToyPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


afx_msg LRESULT CToyPlayerDlg::OnGraphEvent(WPARAM wParam, LPARAM lParam)
{
	//TODO ���graph��Ϣ������
	return 0;
}


int CToyPlayerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  �ڴ������ר�õĴ�������
	
	m_ControlPanelDlg.Create(IDD_CONTROL_PANEL_DLG,this);
	

	m_pMediaControl->SetVideoWnd(m_hWnd);
	m_pMediaControl->SetNotifyWnd(m_hWnd);
	//��ʼ�������б�Ի���
	m_PlaylistDlg.Create(IDD_PLAYLIST_DLG,this);
	//SetTimer(CURRENT_TIMER,1000,NULL);
	return 0;
}


void CToyPlayerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: �ڴ˴������Ϣ����������
	//������Ƶ�����С
	RECT rc;
	GetClientRect(&rc);
	m_pMediaControl->SetScreenSize(&rc);
	//���ÿ�������λ��
	ClientToScreen(&rc);
	if (rc.right - rc.left < 600)
	{
		int mid = (rc.right + rc.left)/2;
		//int length = m_ControlPanelPos.right - m_ControlPanelPos.left;
		m_ControlPanelPos.left = mid - 250;
		m_ControlPanelPos.right = mid + 250;
	}
	else
	{
		m_ControlPanelPos.left = rc.left+50;
		m_ControlPanelPos.right = rc.right - 50;
	}
	m_ControlPanelPos.bottom = rc.bottom - 20;
	m_ControlPanelPos.top = rc.bottom - 90;
	//SetWindowPos(&m_ControlPanelDlg,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);//���ֿ��������ǰ
	m_ControlPanelDlg.MoveWindow(&m_ControlPanelPos);
}


void CToyPlayerDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);
	// TODO: �ڴ˴������Ϣ����������
	RECT rc;
	GetClientRect(&rc);
	//���ÿ�������λ��
	ClientToScreen(&rc);
	int mid = (rc.right + rc.left)/2;
	int length = m_ControlPanelPos.right - m_ControlPanelPos.left;
	m_ControlPanelPos.left = mid - length/2;
	m_ControlPanelPos.right = mid + length/2;
	m_ControlPanelPos.bottom = rc.bottom - 20;
	m_ControlPanelPos.top = rc.bottom - 90;
	m_ControlPanelDlg.MoveWindow(&m_ControlPanelPos);
}


void CToyPlayerDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ClientToScreen(&point);
	if (point.y > m_ControlPanelPos.top && point.y < m_ControlPanelPos.bottom
		&& point.x > m_ControlPanelPos.left && point.x < m_ControlPanelPos.right)
	{
		m_ControlPanelDlg.ShowWindow(TRUE);
	}
	else
	{
		m_ControlPanelDlg.ShowWindow(SW_HIDE);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


afx_msg LRESULT CToyPlayerDlg::OnPlay(WPARAM wParam, LPARAM lParam)
{
	if (m_pMediaControl != NULL)
	{
		m_pMediaControl->Play();
	}
	return 0;
}


afx_msg LRESULT CToyPlayerDlg::OnPause(WPARAM wParam, LPARAM lParam)
{
	if (m_pMediaControl != NULL)
	{
		m_pMediaControl->Pause();
	}
	return 0;
}


afx_msg LRESULT CToyPlayerDlg::OnForword(WPARAM wParam, LPARAM lParam)
{
	if (m_pMediaControl != NULL)
	{
		m_pMediaControl->Forword();
	}
	return 0;
}


afx_msg LRESULT CToyPlayerDlg::OnRetreat(WPARAM wParam, LPARAM lParam)
{
	if (m_pMediaControl != NULL)
	{
		m_pMediaControl->Retreat();
	}
	return 0;
}


void CToyPlayerDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	FullScreen();
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


afx_msg LRESULT CToyPlayerDlg::OnVolumeUp(WPARAM wParam, LPARAM lParam)
{
	if (m_pMediaControl != NULL)
	{
		m_pMediaControl->VolumeUp();
	}
	return 0;
}


afx_msg LRESULT CToyPlayerDlg::OnVolumeDown(WPARAM wParam, LPARAM lParam)
{
	if (m_pMediaControl != NULL)
	{
		m_pMediaControl->VolumeDown();
	}
	return 0;
}


afx_msg LRESULT CToyPlayerDlg::OnSetVolume(WPARAM wParam, LPARAM lParam)
{
	if (m_pMediaControl != NULL)
	{
		m_pMediaControl->SetVolume((int)wParam);
	}
	return 0;
}


afx_msg LRESULT CToyPlayerDlg::OnMute(WPARAM wParam, LPARAM lParam)
{
	TRACE(L"\n-->receive MUTE\n");
	if (m_pMediaControl != NULL)
	{
		m_pMediaControl->Mute();
		m_bMute = true;
	}
	return 0;
}


afx_msg LRESULT CToyPlayerDlg::OnUnmute(WPARAM wParam, LPARAM lParam)
{
	TRACE(L"\n-->receive UNMUTE\n");
	if (m_pMediaControl != NULL)
	{
		m_pMediaControl->Unmute();
		m_bMute = false;
	}
	return 0;
}


afx_msg LRESULT CToyPlayerDlg::OnShowList(WPARAM wParam, LPARAM lParam)
{
	if (!m_PlaylistDlg.IsWindowVisible())
	{
		//���ò����б�λ��
		RECT rc;
		GetWindowRect(&rc);
		m_PlaylistDlg.MoveWindow(rc.right,rc.top,250,rc.bottom - rc.top-20);
		m_PlaylistDlg.ShowWindow(SW_SHOW);
	}
	else
	{
		m_PlaylistDlg.ShowWindow(SW_HIDE);
	}
	return 0;
}


void CToyPlayerDlg::OnBnClickedOpenFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OpenMediaFile();
	//GetDlgItem(IDC_OPEN_FILE)->EnableWindow(FALSE);
}


BOOL CToyPlayerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	extern HACCEL hAccel;
	if (TranslateAccelerator(m_hWnd,hAccel,pMsg))
	{
		return TRUE;
	}
	//����ESC��ENTER��
	if(pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN 
									   || pMsg->wParam == VK_ESCAPE))   
	{    
		return   TRUE;   
	}   
	return CDialogEx::PreTranslateMessage(pMsg);
}


afx_msg LRESULT CToyPlayerDlg::OnOpenFile(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_OPEN_FILE)->ShowWindow(SW_HIDE);
	m_pMediaControl->OpenMediaFile((LPCTSTR)wParam);
	//�����Ƶͼ���С
	SIZE vsize = m_pMediaControl->GetVideSize();
	//������Ƶ��С�����湤������С���ò��Ŵ��ڴ�С
	RECT workarearc;//��������С
	SystemParametersInfo(SPI_GETWORKAREA,0,&workarearc,0);
	int caphight = GetSystemMetrics(SM_CYCAPTION);//�������߶�
	int framew = GetSystemMetrics(SM_CYFRAME);	//�߿�߶Ȼ���
	if (vsize.cx + 2*framew > workarearc.right - workarearc.left
		|| vsize.cy +caphight+framew > workarearc.bottom-workarearc.top)
	{
		MoveWindow(&workarearc);
	}
	else
	{
		ShowWindow(SW_HIDE);
		MoveWindow(0,0,vsize.cx + 2*framew,vsize.cy+caphight+2*framew);
		CenterWindow();
		ShowWindow(SW_SHOW);
	}
	m_pMediaControl->Play();
	//�򲥷��б�Ϳ�������֮��ǰ�����ļ���ʱ��������Ϊ��λ
	LONGLONG times = m_pMediaControl->GetRuntime();//��ý���ļ������������ӿ�
	int timesec = times/10000000;//����100����Ϊ��λ������Ϊ��λ
	::PostMessage(m_PlaylistDlg.GetSafeHwnd(),WM_RUNTIME,(WPARAM)timesec,0);
	::PostMessage(m_ControlPanelDlg.GetSafeHwnd(),WM_RUNTIME,(WPARAM)timesec,0);
	//�������ö�ʱ��
	KillTimer(CURRENT_TIMER);
	SetTimer(CURRENT_TIMER,1000,NULL);
	return 0;
}


afx_msg LRESULT CToyPlayerDlg::OnScreenshot(WPARAM wParam, LPARAM lParam)
{
	if (m_pMediaControl)
	{
		m_pMediaControl->GetCueentImage();
	}
	return 0;
}


void CToyPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == CURRENT_TIMER)
	{
		int curtime = m_pMediaControl->GetCurrentTime()/10000000;
		
		::PostMessage(m_ControlPanelDlg.GetSafeHwnd(),WM_CURENT_TIME,(WPARAM)curtime,0);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CToyPlayerDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ClientToScreen(&point);
	CMenu *pPopup = m_Menu.GetSubMenu(0);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y,this);

	CDialogEx::OnRButtonDown(nFlags, point);
}


// ����CFileDlg��ý���ļ�
BOOL CToyPlayerDlg::OpenMediaFile(void)
{
	CString strFilter = _T("ALL File (*.*) | *.*|");
	strFilter += "AVI File (*.avi) | *.avi|";
	strFilter += "MPEG File (*.mpg;*.mpeg) | *.mpg;*.mpeg|";
	strFilter += "MP3 File (*.mp3) | *.mp3|";
	strFilter += "WMA File (*.wma;*.wmv) | *.wma;*.wmv|";
	strFilter += "MP4 File (*.mp4) | *.mp4|";
	strFilter += "MKV File (*.mkv) | *.mkv|";
	strFilter += "RMVB File (*.rmvb)| *.rmvb|";
	strFilter += "3GP File (*.3gp) | *.3gp|";

	CFileDialog dlg(TRUE,NULL,NULL,
		OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		strFilter,this);
	if (dlg.DoModal() == IDOK)
	{
		GetDlgItem(IDC_OPEN_FILE)->ShowWindow(SW_HIDE);

		m_pMediaControl->OpenMediaFile(dlg.GetPathName());

		//�����Ƶͼ���С
		SIZE vsize = m_pMediaControl->GetVideSize();
		//������Ƶ��С�����湤������С���ò��Ŵ��ڴ�С
		RECT workarearc;//��������С
		SystemParametersInfo(SPI_GETWORKAREA,0,&workarearc,0);
		int caphight = GetSystemMetrics(SM_CYCAPTION);//�������߶�
		int framew = GetSystemMetrics(SM_CYFRAME);	//�߿�߶Ȼ���
		if (vsize.cx + 2*framew > workarearc.right - workarearc.left
			|| vsize.cy +caphight+framew > workarearc.bottom-workarearc.top)
		{
			MoveWindow(&workarearc);
		}
		else
		{
			ShowWindow(SW_HIDE);
			MoveWindow(0,0,vsize.cx + 2*framew,vsize.cy +caphight+2*framew);
			CenterWindow();
			ShowWindow(SW_SHOW);
		}

		//�����ļ�
		m_pMediaControl->SetVolume(90);
		m_pMediaControl->Play();

		//�����Ƶ��Ϣ��ʱ��
		LONGLONG times = m_pMediaControl->GetRuntime();//��ý���ļ������������ӿ�
		times /= 10000000;//��100����Ϊ��λת��Ϊ����Ϊ��λ
		int hours = times/3600;	//ʱ
		int min = times%3600/60;//��
		int sec = times%60;		//��
		CString timesCStr;
		timesCStr.Format(L"%02d:%02d:%02d",hours,min,sec);
		//�����ļ���Ϣ�������б�
		m_PlaylistDlg.InsertFileInfo(dlg.GetPathName().GetBuffer(),
			dlg.GetFileName().GetBuffer(),timesCStr.GetBuffer());
		//֪ͨ�������ʱ��
		::PostMessage(m_ControlPanelDlg.GetSafeHwnd(),WM_RUNTIME,(WPARAM)times,0);
		//������ʱ��
		KillTimer(CURRENT_TIMER);
		SetTimer(CURRENT_TIMER,1000,NULL);
	}
	return 0;
}


void CToyPlayerDlg::OnOpen()
{
	// TODO: �ڴ���������������
	OpenMediaFile();
}


void CToyPlayerDlg::OnClose()
{
	// TODO: �ڴ���������������
	if (m_pMediaControl)
	{
		m_pMediaControl->Pause();
	}
}


void CToyPlayerDlg::OnPlayPause()
{
	// TODO: �ڴ���������������
	static BOOL bplay = TRUE;
	if (bplay)
	{
		m_pMediaControl->Pause();
		bplay = FALSE;
	}
	else
	{
		m_pMediaControl->Play();
		bplay = TRUE;
	}
}


void CToyPlayerDlg::OnFullscreen()
{
	FullScreen();
}


// ִ��ȫ��or�˳�ȫ��
void CToyPlayerDlg::FullScreen(void)
{
	static int iScreenX= GetSystemMetrics(SM_CXSCREEN);    // X�ֱ���
	static int iScreenY= GetSystemMetrics(SM_CYSCREEN);    // Y�ֱ���
	static BOOL full = FALSE;//�Ƿ���ȫ��״̬
	if (!full)
	{
		ModifyStyle(WS_CAPTION|WS_THICKFRAME,0,0); 
		ShowWindow(SW_SHOWMAXIMIZED);
	}
	else
	{
		ModifyStyle(0,WS_CAPTION|WS_THICKFRAME,0); 
		//MoveWindow(&rc);
		//CenterWindow();
		ShowWindow(SW_NORMAL);
	}
	full = !full;
}


void CToyPlayerDlg::OnFullScreen()
{
	// TODO: �ڴ���������������
	FullScreen();
}


void CToyPlayerDlg::OnMaxScreen()
{
	// TODO: �ڴ���������������
	static BOOL bMax = FALSE;
	if (bMax)
	{
		ModifyStyle(0,WS_CAPTION|WS_THICKFRAME,0); 
		ShowWindow(SW_NORMAL);
	}
	else
	{
		ShowWindow(SW_MAXIMIZE);
	}
	bMax = !bMax;
}


void CToyPlayerDlg::OnDoubleScreen()
{
	// TODO: �ڴ���������������
	if (m_pMediaControl == NULL)
	{
		return;
	}
	SIZE videoSize = m_pMediaControl->GetVideSize();
	static int iScreenX= GetSystemMetrics(SM_CXSCREEN);    // X�ֱ���
	static int iScreenY= GetSystemMetrics(SM_CYSCREEN);    // Y�ֱ���
	if (2*videoSize.cx >= iScreenX || 2*videoSize.cy >= iScreenY)
	{
		FullScreen();
	}
	else
	{
		ShowWindow(SW_HIDE);
		MoveWindow(0,0,2*videoSize.cx,2*videoSize.cy);
		CenterWindow();
		ShowWindow(SW_SHOW);
	}
}


void CToyPlayerDlg::OnRawScreen()
{
	// TODO: �ڴ���������������
	if (m_pMediaControl == NULL)
	{
		return;
	}
	SIZE videoSize = m_pMediaControl->GetVideSize();
	static int iScreenX= GetSystemMetrics(SM_CXSCREEN);    // X�ֱ���
	static int iScreenY= GetSystemMetrics(SM_CYSCREEN);    // Y�ֱ���
	if (videoSize.cx >= iScreenX || videoSize.cy >= iScreenY)
	{
		FullScreen();
	}
	else
	{
		ShowWindow(SW_HIDE);
		MoveWindow(0,0,videoSize.cx,videoSize.cy);
		CenterWindow();
		ShowWindow(SW_SHOW);
	}
}


void CToyPlayerDlg::OnOneAndHalfScreen()
{
	// TODO: �ڴ���������������
	if (m_pMediaControl == NULL)
	{
		return;
	}
	SIZE videoSize = m_pMediaControl->GetVideSize();
	static int iScreenX= GetSystemMetrics(SM_CXSCREEN);    // X�ֱ���
	static int iScreenY= GetSystemMetrics(SM_CYSCREEN);    // Y�ֱ���
	if (videoSize.cx*1.5 >= iScreenX || videoSize.cy*1.5 >= iScreenY)
	{
		FullScreen();
	}
	else
	{
		ShowWindow(SW_HIDE);
		MoveWindow(0,0,1.5*videoSize.cx,1.5*videoSize.cy);
		CenterWindow();
		ShowWindow(SW_SHOW);
	}
}


void CToyPlayerDlg::OnHalfScreen()
{
	// TODO: �ڴ���������������
	if (m_pMediaControl == NULL)
	{
		return;
	}
	SIZE videoSize = m_pMediaControl->GetVideSize();
	static int iScreenX= GetSystemMetrics(SM_CXSCREEN);    // X�ֱ���
	static int iScreenY= GetSystemMetrics(SM_CYSCREEN);    // Y�ֱ���
	if (videoSize.cx/2 >= iScreenX || videoSize.cy/2 >= iScreenY)
	{
		FullScreen();
	}
	else
	{
		ShowWindow(SW_HIDE);
		MoveWindow(0,0,videoSize.cx/2,videoSize.cy/2);
		CenterWindow();
		ShowWindow(SW_SHOW);
	}
}


void CToyPlayerDlg::OnScreenshot()
{
	// TODO: �ڴ���������������
	if (m_pMediaControl)
	{
		m_pMediaControl->GetCueentImage();
	}
}


void CToyPlayerDlg::OnMuteUnmute()
{
	// TODO: �ڴ���������������
	if (m_pMediaControl == NULL)
	{
		return;
	}

	if (m_bMute == true)
	{
		m_pMediaControl->Unmute();
	}
	else
	{
		m_pMediaControl->Mute();
	}
	m_bMute = !m_bMute;
}


void CToyPlayerDlg::OnListdlg()
{
	// TODO: �ڴ���������������
	if (!m_PlaylistDlg.IsWindowVisible())
	{
		//���ò����б�λ��
		RECT rc;
		GetWindowRect(&rc);
		m_PlaylistDlg.MoveWindow(rc.right,rc.top,250,rc.bottom - rc.top-20);
		m_PlaylistDlg.ShowWindow(SW_SHOW);
	}
	else
	{
		m_PlaylistDlg.ShowWindow(SW_HIDE);
	}
}


void CToyPlayerDlg::OnQuit()
{
	// TODO: �ڴ���������������
	SendMessage(WM_CLOSE);
}


void CToyPlayerDlg::OnTopWind()
{
	// TODO: �ڴ���������������
	static BOOL bTop = FALSE;
	if (bTop)
	{//�����ǰ�����ö�״̬����ȡ���ö�
		::SetWindowPos(GetSafeHwnd(),HWND_NOTOPMOST,0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	}
	else
	{//���û�д����ö�״̬�����ö�
		::SetWindowPos(GetSafeHwnd(),HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE); 
	}
	bTop = !bTop;
}


void CToyPlayerDlg::OnPreFile()
{
	m_PlaylistDlg.PostMessage(WM_PRE,0,0);
}


void CToyPlayerDlg::OnNext()
{
	m_PlaylistDlg.PostMessage(WM_NEXT,0,0);
}


void CToyPlayerDlg::OnForward()
{
	// TODO: �ڴ���������������	
	OnForword(0,0);
}


void CToyPlayerDlg::OnBackward()
{
	// TODO: �ڴ���������������
	OnRetreat(0,0);
}


void CToyPlayerDlg::OnReplay()
{
	// TODO: �ڴ���������������
	if (m_pMediaControl)
	{
		m_pMediaControl->Restart();
	}
}


void CToyPlayerDlg::OnAcceleratorPlay()
{
	// TODO: �ڴ���������������
	OnPlayPause();
}


void CToyPlayerDlg::OnAcceleratorForward()
{
	// TODO: �ڴ���������������
	OnForword(0,0);
}


void CToyPlayerDlg::OnAcceleratorBackward()
{
	// TODO: �ڴ���������������
	OnRetreat(0,0);
}


void CToyPlayerDlg::OnAcceleratorVolumeUp()
{
	// TODO: �ڴ���������������
	OnVolumeUp(0,0);
}


void CToyPlayerDlg::OnAcceleratorVolumeDown()
{
	// TODO: �ڴ���������������
	OnVolumeDown(0,0);
}
