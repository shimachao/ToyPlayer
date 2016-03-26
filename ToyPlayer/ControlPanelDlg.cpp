// ControlPanelDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ToyPlayer.h"
#include "ControlPanelDlg.h"
#include "afxdialogex.h"
#include   <dwmapi.h> 
#pragma comment (lib , "dwmapi.lib" ) 

// CControlPanelDlg �Ի���

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


// CControlPanelDlg ��Ϣ�������


LRESULT CControlPanelDlg::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// ȡ��������ڵĴ�������
	UINT nHitTest = CDialog::OnNcHitTest(point);

	// �������ڴ��ڿͻ������򷵻ر��������Ÿ�Windows
	// ʹWindows������ڱ�����������д������ɵ����ƶ�����
	return (nHitTest==HTCLIENT) ? HTCAPTION : nHitTest;
	//return CDialogEx::OnNcHitTest(point);
}


void CControlPanelDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();
}


void CControlPanelDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialogEx::OnCancel();
}



BOOL CControlPanelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_VolumeSliderCtrl.SetRange(0,100);
	m_VolumeSliderCtrl.SetPos(100);
	m_TimeProgressCtrl.SetBarColor(RGB(0,0,255));
	m_TimeProgressCtrl.SetBkColor(RGB(40,40,40));

	//SetBackgroundColor(RGB(160,160,160));
	SkinH_Attach();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CControlPanelDlg::OnBnClickedPlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetParent()->PostMessage(WM_FORWORD);
}


void CControlPanelDlg::OnBnClickedRetreat()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetParent()->PostMessage(WM_RETREAT);
}


void CControlPanelDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if ((CSliderCtrl*)pScrollBar == &m_VolumeSliderCtrl)
	{//�ж��Ƿ�Ϊ�������ƻ��鵼�µ���Ϣ
		int pos = m_VolumeSliderCtrl.GetPos();
		GetParent()->PostMessage(WM_SET_VOLUME,(WPARAM)pos);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CControlPanelDlg::OnBnClickedMuteCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CControlPanelDlg::OnBnClickedNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	extern HWND PlaylistDlgHwnd;
	::PostMessage(PlaylistDlgHwnd,WM_NEXT,0,0);
}


void CControlPanelDlg::OnBnClickedPre()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	extern HWND PlaylistDlgHwnd;
	::PostMessage(PlaylistDlgHwnd,WM_PRE,0,0);
}


void CControlPanelDlg::OnBnClickedScreenshot()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetParent()->PostMessage(WM_SCREENSHOT);
}


void CControlPanelDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	//���ݿ�������С��������ؼ��Ĵ�С
	CProgressCtrl* pProgress = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS);
	//����ʱ���������С��λ��
	if (pProgress != NULL)
	{
		pProgress->MoveWindow(50,10,cx - 100,10);
	}
	//���õ�ǰʱ�����ʱ�侲̬���ֿؼ���λ��
	GetDlgItem(IDC_CURRENT_TIME)->MoveWindow(5,8,50,15);
	GetDlgItem(IDC_TOTAL_TIME)->MoveWindow(cx - 55,8,50,15);
	//���������ؼ���λ��
}


afx_msg LRESULT CControlPanelDlg::OnRuntime(WPARAM wParam, LPARAM lParam)
{
	m_TotalTime = (int)wParam;
	//����ʱ��
	CString str;
	str.Format(L"%02d:%02d:%02d",m_TotalTime/3600,m_TotalTime%3600/60,m_TotalTime%60);
	SetDlgItemText(IDC_TOTAL_TIME,str.GetBuffer());
	//���ý�������Χ
	m_TimeProgressCtrl.SetRange32(0,m_TotalTime);
	return 0;
}


afx_msg LRESULT CControlPanelDlg::OnCurentTime(WPARAM wParam, LPARAM lParam)
{
	
	int curtime = (int)wParam;
	//TODO:���ݵ�ǰʱ�����ý������Ľ���
	m_TimeProgressCtrl.SetPos(curtime);
	//���õ�ǰʱ�侲̬�ı��ؼ�
	CString str;
	str.Format(L"%02d:%02d:%02d",curtime/3600,curtime%3600/60,curtime%60);
	SetDlgItemText(IDC_CURRENT_TIME,str.GetBuffer());
	return 0;
}

