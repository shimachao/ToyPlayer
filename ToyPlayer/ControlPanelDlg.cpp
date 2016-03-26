// ControlPanelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ToyPlayer.h"
#include "ControlPanelDlg.h"
#include "afxdialogex.h"
#include   <dwmapi.h> 
#pragma comment (lib , "dwmapi.lib" ) 

// CControlPanelDlg 对话框

IMPLEMENT_DYNAMIC(CControlPanelDlg, CDialogEx)

CControlPanelDlg::CControlPanelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CControlPanelDlg::IDD, pParent)
{

}

CControlPanelDlg::~CControlPanelDlg()
{
}

void CControlPanelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VOLUME_SLIDER, m_VolumeSliderCtrl);
	DDX_Control(pDX, IDC_MUTE_CHECK, m_MuteCheckBox);
	DDX_Control(pDX, IDC_PROGRESS, m_TimeProgressCtrl);
	//DDX_Control(pDX, IDC_PRE, m_PreBtn);
}


BEGIN_MESSAGE_MAP(CControlPanelDlg, CDialogEx)
	ON_WM_NCHITTEST()
//	ON_WM_MOUSEMOVE()
//ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_PLAY, &CControlPanelDlg::OnBnClickedPlay)
ON_BN_CLICKED(IDC_FORWORD, &CControlPanelDlg::OnBnClickedForword)
ON_BN_CLICKED(IDC_RETREAT, &CControlPanelDlg::OnBnClickedRetreat)
ON_WM_HSCROLL()
ON_BN_CLICKED(IDC_MUTE_CHECK, &CControlPanelDlg::OnBnClickedMuteCheck)
ON_BN_CLICKED(IDC_SHOW_LIST, &CControlPanelDlg::OnBnClickedShowList)
ON_BN_CLICKED(IDC_NEXT, &CControlPanelDlg::OnBnClickedNext)
ON_BN_CLICKED(IDC_PRE, &CControlPanelDlg::OnBnClickedPre)
ON_BN_CLICKED(IDC_SCREENSHOT, &CControlPanelDlg::OnBnClickedScreenshot)
ON_WM_SIZE()
ON_MESSAGE(WM_RUNTIME, &CControlPanelDlg::OnRuntime)
ON_MESSAGE(WM_CURENT_TIME, &CControlPanelDlg::OnCurentTime)
//ON_COMMAND(ID_MUTE_UNMUTE, &CControlPanelDlg::OnMuteUnmute)
//ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CControlPanelDlg 消息处理程序


LRESULT CControlPanelDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 取得鼠标所在的窗口区域
	UINT nHitTest = CDialog::OnNcHitTest(point);

	// 如果鼠标在窗口客户区，则返回标题条代号给Windows
	// 使Windows按鼠标在标题条上类进行处理，即可单击移动窗口
	return (nHitTest==HTCLIENT) ? HTCAPTION : nHitTest;
	//return CDialogEx::OnNcHitTest(point);
}


void CControlPanelDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CControlPanelDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}



BOOL CControlPanelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_VolumeSliderCtrl.SetRange(0,100);
	m_VolumeSliderCtrl.SetPos(100);
	m_TimeProgressCtrl.SetBarColor(RGB(0,0,255));
	m_TimeProgressCtrl.SetBkColor(RGB(40,40,40));

	//SetBackgroundColor(RGB(160,160,160));
	SkinH_Attach();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CControlPanelDlg::OnBnClickedPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	static BOOL fPlaying = TRUE;
	if (fPlaying)
	{
		GetParent()->PostMessage(WM_PAUSE);
		fPlaying = FALSE;
	}
	else
	{
		GetParent()->PostMessage(WM_PLAY);
		fPlaying = TRUE;
	}
	
}


void CControlPanelDlg::OnBnClickedForword()
{
	// TODO: 在此添加控件通知处理程序代码
	GetParent()->PostMessage(WM_FORWORD);
}


void CControlPanelDlg::OnBnClickedRetreat()
{
	// TODO: 在此添加控件通知处理程序代码
	GetParent()->PostMessage(WM_RETREAT);
}


void CControlPanelDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ((CSliderCtrl*)pScrollBar == &m_VolumeSliderCtrl)
	{//判断是否为音量控制滑块导致的消息
		int pos = m_VolumeSliderCtrl.GetPos();
		GetParent()->PostMessage(WM_SET_VOLUME,(WPARAM)pos);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CControlPanelDlg::OnBnClickedMuteCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE(L"\n\n-->check:%d\n\n",m_MuteCheckBox.GetCheck());
	if (m_MuteCheckBox.GetCheck() == BST_CHECKED)
	{
		GetParent()->PostMessage(WM_MUTE);
		TRACE(L"\n-->send MUTE\n");
	}
	else
	{
		GetParent()->PostMessage(WM_UNMUTE);
		TRACE(L"\n-->send UNMUTE\n");
	}
	
}


void CControlPanelDlg::OnBnClickedShowList()
{
	GetParent()->PostMessage(WM_SHOW_LIST);
	// TODO: 在此添加控件通知处理程序代码
}


void CControlPanelDlg::OnBnClickedNext()
{
	// TODO: 在此添加控件通知处理程序代码
	extern HWND PlaylistDlgHwnd;
	::PostMessage(PlaylistDlgHwnd,WM_NEXT,0,0);
}


void CControlPanelDlg::OnBnClickedPre()
{
	// TODO: 在此添加控件通知处理程序代码
	extern HWND PlaylistDlgHwnd;
	::PostMessage(PlaylistDlgHwnd,WM_PRE,0,0);
}


void CControlPanelDlg::OnBnClickedScreenshot()
{
	// TODO: 在此添加控件通知处理程序代码
	GetParent()->PostMessage(WM_SCREENSHOT);
}


void CControlPanelDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	//根据控制面板大小设置上面控件的大小
	CProgressCtrl* pProgress = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS);
	//设置时间进度条大小和位置
	if (pProgress != NULL)
	{
		pProgress->MoveWindow(50,10,cx - 100,10);
	}
	//设置当前时间和总时间静态文字控件的位置
	GetDlgItem(IDC_CURRENT_TIME)->MoveWindow(5,8,50,15);
	GetDlgItem(IDC_TOTAL_TIME)->MoveWindow(cx - 55,8,50,15);
	//设置其他控件的位置
}


afx_msg LRESULT CControlPanelDlg::OnRuntime(WPARAM wParam, LPARAM lParam)
{
	m_TotalTime = (int)wParam;
	//设置时长
	CString str;
	str.Format(L"%02d:%02d:%02d",m_TotalTime/3600,m_TotalTime%3600/60,m_TotalTime%60);
	SetDlgItemText(IDC_TOTAL_TIME,str.GetBuffer());
	//设置进度条范围
	m_TimeProgressCtrl.SetRange32(0,m_TotalTime);
	return 0;
}


afx_msg LRESULT CControlPanelDlg::OnCurentTime(WPARAM wParam, LPARAM lParam)
{
	
	int curtime = (int)wParam;
	//TODO:根据当前时间设置进度条的进度
	m_TimeProgressCtrl.SetPos(curtime);
	//设置当前时间静态文本控件
	CString str;
	str.Format(L"%02d:%02d:%02d",curtime/3600,curtime%3600/60,curtime%60);
	SetDlgItemText(IDC_CURRENT_TIME,str.GetBuffer());
	return 0;
}

