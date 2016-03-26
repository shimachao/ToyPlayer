
// ToyPlayerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ToyPlayer.h"
#include "ToyPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CToyPlayerDlg 对话框




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


// CToyPlayerDlg 消息处理程序
HACCEL hAccel;
BOOL CToyPlayerDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_Menu.LoadMenu(IDR_PLAYDLG_MENU);
	hAccel = LoadAccelerators(theApp.m_hInstance,MAKEINTRESOURCE(IDR_PLAYDLG_ACCELERATOR));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CToyPlayerDlg::OnPaint()
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
HCURSOR CToyPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


afx_msg LRESULT CToyPlayerDlg::OnGraphEvent(WPARAM wParam, LPARAM lParam)
{
	//TODO 添加graph消息处理函数
	return 0;
}


int CToyPlayerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  在此添加您专用的创建代码
	
	m_ControlPanelDlg.Create(IDD_CONTROL_PANEL_DLG,this);
	

	m_pMediaControl->SetVideoWnd(m_hWnd);
	m_pMediaControl->SetNotifyWnd(m_hWnd);
	//初始化播放列表对话框
	m_PlaylistDlg.Create(IDD_PLAYLIST_DLG,this);
	//SetTimer(CURRENT_TIMER,1000,NULL);
	return 0;
}


void CToyPlayerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	//设置视频画面大小
	RECT rc;
	GetClientRect(&rc);
	m_pMediaControl->SetScreenSize(&rc);
	//设置控制面板的位置
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
	//SetWindowPos(&m_ControlPanelDlg,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);//保持控制面板在前
	m_ControlPanelDlg.MoveWindow(&m_ControlPanelPos);
}


void CToyPlayerDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);
	// TODO: 在此处添加消息处理程序代码
	RECT rc;
	GetClientRect(&rc);
	//设置控制面板的位置
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
		//设置播放列表位置
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
	// TODO: 在此添加控件通知处理程序代码
	OpenMediaFile();
	//GetDlgItem(IDC_OPEN_FILE)->EnableWindow(FALSE);
}


BOOL CToyPlayerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	extern HACCEL hAccel;
	if (TranslateAccelerator(m_hWnd,hAccel,pMsg))
	{
		return TRUE;
	}
	//屏蔽ESC和ENTER键
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
	//获得视频图像大小
	SIZE vsize = m_pMediaControl->GetVideSize();
	//根据视频大小和桌面工作区大小设置播放窗口大小
	RECT workarearc;//工作区大小
	SystemParametersInfo(SPI_GETWORKAREA,0,&workarearc,0);
	int caphight = GetSystemMetrics(SM_CYCAPTION);//标题栏高度
	int framew = GetSystemMetrics(SM_CYFRAME);	//边框高度或宽度
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
	//向播放列表和控制面板告之当前播放文件的时长，以秒为单位
	LONGLONG times = m_pMediaControl->GetRuntime();//打开媒体文件后才能用这个接口
	int timesec = times/10000000;//从以100纳秒为单位到以秒为单位
	::PostMessage(m_PlaylistDlg.GetSafeHwnd(),WM_RUNTIME,(WPARAM)timesec,0);
	::PostMessage(m_ControlPanelDlg.GetSafeHwnd(),WM_RUNTIME,(WPARAM)timesec,0);
	//重新设置定时器
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == CURRENT_TIMER)
	{
		int curtime = m_pMediaControl->GetCurrentTime()/10000000;
		
		::PostMessage(m_ControlPanelDlg.GetSafeHwnd(),WM_CURENT_TIME,(WPARAM)curtime,0);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CToyPlayerDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ClientToScreen(&point);
	CMenu *pPopup = m_Menu.GetSubMenu(0);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y,this);

	CDialogEx::OnRButtonDown(nFlags, point);
}


// 利用CFileDlg打开媒体文件
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

		//获得视频图像大小
		SIZE vsize = m_pMediaControl->GetVideSize();
		//根据视频大小和桌面工作区大小设置播放窗口大小
		RECT workarearc;//工作区大小
		SystemParametersInfo(SPI_GETWORKAREA,0,&workarearc,0);
		int caphight = GetSystemMetrics(SM_CYCAPTION);//标题栏高度
		int framew = GetSystemMetrics(SM_CYFRAME);	//边框高度或宽度
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

		//播放文件
		m_pMediaControl->SetVolume(90);
		m_pMediaControl->Play();

		//获得视频信息：时长
		LONGLONG times = m_pMediaControl->GetRuntime();//打开媒体文件后才能用这个接口
		times /= 10000000;//以100纳秒为单位转换为以秒为单位
		int hours = times/3600;	//时
		int min = times%3600/60;//分
		int sec = times%60;		//秒
		CString timesCStr;
		timesCStr.Format(L"%02d:%02d:%02d",hours,min,sec);
		//插入文件信息到播放列表
		m_PlaylistDlg.InsertFileInfo(dlg.GetPathName().GetBuffer(),
			dlg.GetFileName().GetBuffer(),timesCStr.GetBuffer());
		//通知控制面板时长
		::PostMessage(m_ControlPanelDlg.GetSafeHwnd(),WM_RUNTIME,(WPARAM)times,0);
		//开启定时器
		KillTimer(CURRENT_TIMER);
		SetTimer(CURRENT_TIMER,1000,NULL);
	}
	return 0;
}


void CToyPlayerDlg::OnOpen()
{
	// TODO: 在此添加命令处理程序代码
	OpenMediaFile();
}


void CToyPlayerDlg::OnClose()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pMediaControl)
	{
		m_pMediaControl->Pause();
	}
}


void CToyPlayerDlg::OnPlayPause()
{
	// TODO: 在此添加命令处理程序代码
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


// 执行全屏or退出全屏
void CToyPlayerDlg::FullScreen(void)
{
	static int iScreenX= GetSystemMetrics(SM_CXSCREEN);    // X分辨率
	static int iScreenY= GetSystemMetrics(SM_CYSCREEN);    // Y分辨率
	static BOOL full = FALSE;//是否处于全屏状态
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
	// TODO: 在此添加命令处理程序代码
	FullScreen();
}


void CToyPlayerDlg::OnMaxScreen()
{
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
	if (m_pMediaControl == NULL)
	{
		return;
	}
	SIZE videoSize = m_pMediaControl->GetVideSize();
	static int iScreenX= GetSystemMetrics(SM_CXSCREEN);    // X分辨率
	static int iScreenY= GetSystemMetrics(SM_CYSCREEN);    // Y分辨率
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
	// TODO: 在此添加命令处理程序代码
	if (m_pMediaControl == NULL)
	{
		return;
	}
	SIZE videoSize = m_pMediaControl->GetVideSize();
	static int iScreenX= GetSystemMetrics(SM_CXSCREEN);    // X分辨率
	static int iScreenY= GetSystemMetrics(SM_CYSCREEN);    // Y分辨率
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
	// TODO: 在此添加命令处理程序代码
	if (m_pMediaControl == NULL)
	{
		return;
	}
	SIZE videoSize = m_pMediaControl->GetVideSize();
	static int iScreenX= GetSystemMetrics(SM_CXSCREEN);    // X分辨率
	static int iScreenY= GetSystemMetrics(SM_CYSCREEN);    // Y分辨率
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
	// TODO: 在此添加命令处理程序代码
	if (m_pMediaControl == NULL)
	{
		return;
	}
	SIZE videoSize = m_pMediaControl->GetVideSize();
	static int iScreenX= GetSystemMetrics(SM_CXSCREEN);    // X分辨率
	static int iScreenY= GetSystemMetrics(SM_CYSCREEN);    // Y分辨率
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
	// TODO: 在此添加命令处理程序代码
	if (m_pMediaControl)
	{
		m_pMediaControl->GetCueentImage();
	}
}


void CToyPlayerDlg::OnMuteUnmute()
{
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
	if (!m_PlaylistDlg.IsWindowVisible())
	{
		//设置播放列表位置
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
	// TODO: 在此添加命令处理程序代码
	SendMessage(WM_CLOSE);
}


void CToyPlayerDlg::OnTopWind()
{
	// TODO: 在此添加命令处理程序代码
	static BOOL bTop = FALSE;
	if (bTop)
	{//如果当前处于置顶状态，则取消置顶
		::SetWindowPos(GetSafeHwnd(),HWND_NOTOPMOST,0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	}
	else
	{//如果没有处于置顶状态，则置顶
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
	// TODO: 在此添加命令处理程序代码	
	OnForword(0,0);
}


void CToyPlayerDlg::OnBackward()
{
	// TODO: 在此添加命令处理程序代码
	OnRetreat(0,0);
}


void CToyPlayerDlg::OnReplay()
{
	// TODO: 在此添加命令处理程序代码
	if (m_pMediaControl)
	{
		m_pMediaControl->Restart();
	}
}


void CToyPlayerDlg::OnAcceleratorPlay()
{
	// TODO: 在此添加命令处理程序代码
	OnPlayPause();
}


void CToyPlayerDlg::OnAcceleratorForward()
{
	// TODO: 在此添加命令处理程序代码
	OnForword(0,0);
}


void CToyPlayerDlg::OnAcceleratorBackward()
{
	// TODO: 在此添加命令处理程序代码
	OnRetreat(0,0);
}


void CToyPlayerDlg::OnAcceleratorVolumeUp()
{
	// TODO: 在此添加命令处理程序代码
	OnVolumeUp(0,0);
}


void CToyPlayerDlg::OnAcceleratorVolumeDown()
{
	// TODO: 在此添加命令处理程序代码
	OnVolumeDown(0,0);
}
