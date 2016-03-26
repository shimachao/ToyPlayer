// PlaylistDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ToyPlayer.h"
#include "PlaylistDlg.h"
#include "afxdialogex.h"
#include <CdErr.h>

// CPlaylistDlg �Ի���

IMPLEMENT_DYNAMIC(CPlaylistDlg, CDialogEx)

CPlaylistDlg::CPlaylistDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPlaylistDlg::IDD, pParent),m_iCurPlaying(0)
{

}

CPlaylistDlg::~CPlaylistDlg()
{
}

void CPlaylistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLAY_LIST, m_PlaylistCtrl);
}


BEGIN_MESSAGE_MAP(CPlaylistDlg, CDialogEx)
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_ADD, &CPlaylistDlg::OnBnClickedAdd)
//	ON_NOTIFY(HDN_ITEMDBLCLICK, 0, &CPlaylistDlg::OnHdnItemdblclickPlayList)
	ON_NOTIFY(NM_DBLCLK, IDC_PLAY_LIST, &CPlaylistDlg::OnNMDblclkPlayList)
	ON_MESSAGE(WM_NEXT, &CPlaylistDlg::OnNext)
	ON_MESSAGE(WM_PRE, &CPlaylistDlg::OnPre)
	ON_MESSAGE(WM_RUNTIME, &CPlaylistDlg::OnRuntime)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_REMOVE, &CPlaylistDlg::OnBnClickedRemove)
	ON_NOTIFY(NM_RCLICK, IDC_PLAY_LIST, &CPlaylistDlg::OnNMRClickPlayList)
	ON_COMMAND(ID_PLAY, &CPlaylistDlg::OnPlay)
	ON_COMMAND(ID_ADD, &CPlaylistDlg::OnAdd)
	ON_COMMAND(ID_REMOVE, &CPlaylistDlg::OnRemove)
END_MESSAGE_MAP()


// CPlaylistDlg ��Ϣ�������
HWND PlaylistDlgHwnd;

BOOL CPlaylistDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	PlaylistDlgHwnd = GetSafeHwnd();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	TRACE(L"\n --> the init of listdlg\n");
	m_PlaylistCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_PlaylistCtrl.InsertColumn(0,L"Filename",LVCFMT_LEFT,200);
	m_PlaylistCtrl.InsertColumn(1,L"Runtime",LVCFMT_LEFT,60);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CPlaylistDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	TRACE(L"\n-->cancle\n");
	ShowWindow(SW_HIDE);
	//CDialogEx::OnCancel();
}


void CPlaylistDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	TRACE(L"\n-->ok\n");
	//CDialogEx::OnOK();
}


void CPlaylistDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	lpMMI->ptMinTrackSize = CPoint(150,00);//���ô�����С�ߴ�
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CPlaylistDlg::InsertFileInfo(LPTSTR pathName,LPTSTR fileName, LPTSTR time)
{
	int i = m_PlaylistCtrl.GetItemCount();
	m_PlaylistCtrl.InsertItem(i,fileName);
	m_PlaylistCtrl.SetItemText(i,1,time);
	//����ȫ·��
	LPTSTR pPathName = new TCHAR[_tcslen(pathName)+1];
	_tcscpy(pPathName,pathName);
	m_PlaylistCtrl.SetItemData(i,(DWORD_PTR)pPathName);
}


void CPlaylistDlg::DeleteFileInfo(int nItem)
{
	LPCTSTR pStr = (LPCTSTR)m_PlaylistCtrl.GetItemData(nItem);
	delete pStr;
	m_PlaylistCtrl.DeleteItem(nItem);
}


void CPlaylistDlg::OnBnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog  dlg( TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, NULL, NULL );
	DWORD MAXFILE = 50*MAX_PATH;
	dlg.m_ofn.nMaxFile = MAXFILE;
	TCHAR* pc = new TCHAR[MAXFILE];
	dlg.m_ofn.lpstrFile = pc;
	dlg.m_ofn.lpstrFile[0] = NULL;

	CString pathname,filename;
	int iReturn = dlg.DoModal();
	if(iReturn ==  IDOK)
	{
		POSITION pos = dlg.GetStartPosition();
		while (pos != NULL)
		{
			pathname = dlg.GetNextPathName(pos);
			//��ȡ�ļ����������������������'\'��ֹͣ��'\'���漴Ϊ�ļ���
			for (int i = pathname.GetLength()-1; i >0; i--)
			{
				if ('\\' == pathname.GetAt(i))
				{
					filename = pathname.Right(pathname.GetLength()-i-1);
					break;
				}
			}
			InsertFileInfo(pathname.GetBuffer(),filename.GetBuffer(),NULL);
		}
	}

	if(CommDlgExtendedError() == FNERR_BUFFERTOOSMALL)
		AfxMessageBox(L"�򿪵��ļ���̫��");
	delete []pc;
}


void CPlaylistDlg::OnNMDblclkPlayList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_PlaylistCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		TRACE0("No items were selected!\n");
	}
	else
	{
			int nItem = m_PlaylistCtrl.GetNextSelectedItem(pos);
			WPARAM p = m_PlaylistCtrl.GetItemData(nItem);
			GetParent()->PostMessage(WM_OPEN_FILE,p);
			m_iCurPlaying = nItem;
	}


	*pResult = 0;
}


afx_msg LRESULT CPlaylistDlg::OnNext(WPARAM wParam, LPARAM lParam)
{
	int num = m_PlaylistCtrl.GetItemCount();
	if (num <= 0)
	{
		return 0;
	}
	m_iCurPlaying = (m_iCurPlaying+1)%num;
	m_PlaylistCtrl.SetItemState(m_iCurPlaying,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|																				LVIS_FOCUSED);
	WPARAM p = m_PlaylistCtrl.GetItemData(m_iCurPlaying);
	GetParent()->PostMessage(WM_OPEN_FILE,p);
		
	return 0;
}


afx_msg LRESULT CPlaylistDlg::OnPre(WPARAM wParam, LPARAM lParam)
{
	int num = m_PlaylistCtrl.GetItemCount();
	if (num <= 0)
	{
		return 0;
	}
	m_iCurPlaying = (m_iCurPlaying+num -1)%num;
	m_PlaylistCtrl.SetItemState(m_iCurPlaying,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
	WPARAM p = m_PlaylistCtrl.GetItemData(m_iCurPlaying);
	GetParent()->PostMessage(WM_OPEN_FILE,p);
	return 0;
}


afx_msg LRESULT CPlaylistDlg::OnRuntime(WPARAM wParam, LPARAM lParam)
{
	//��õ�ǰ����ѡ��״̬����Ŀ
	POSITION pos = m_PlaylistCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		TRACE0("No items were selected!\n");
	}
	else
	{
		int nItem = m_PlaylistCtrl.GetNextSelectedItem(pos);
		int runtime = (int)wParam;
		int hours = runtime/3600;
		int min = runtime%3600/60;
		int sec = runtime%60;
		CString runtimeStr;
		runtimeStr.Format(L"%02d:%02d:%02d",hours,min,sec);
		m_PlaylistCtrl.SetItemText(nItem,1,runtimeStr.GetBuffer());
	}
	//������ʱ��
	return 0;
}


void CPlaylistDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	//����listctrol�Ĵ�С
	CListCtrl*plist = NULL;
	plist = (CListCtrl*)GetDlgItem(IDC_PLAY_LIST);
	if (plist != NULL && nType == SIZE_RESTORED)
	{
		m_PlaylistCtrl.MoveWindow(0,0,cx,cy-30);
		m_PlaylistCtrl.SetColumnWidth(0,cx-80);//�ļ����п�ȱ仯
		m_PlaylistCtrl.SetColumnWidth(1,60);//ʱ���п�Ȳ���
		GetDlgItem(IDC_REMOVE)->SetWindowPos(NULL,cx-35,cy-25,0,0,SWP_NOSIZE);
		GetDlgItem(IDC_ADD)->SetWindowPos(NULL,cx-70,cy-25,0,0,SWP_NOSIZE);
	}
	
}


void CPlaylistDlg::OnBnClickedRemove()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��õ�ǰ����ѡ��״̬����Ŀ
	POSITION pos = m_PlaylistCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		TRACE0("No items were selected!\n");
		return;
	}
	int nItem = m_PlaylistCtrl.GetNextSelectedItem(pos);
	
	//�Ƴ���ǰѡ�е���
	m_PlaylistCtrl.DeleteItem(nItem);
	//���õ�ǰѡ����Ϊ��һ��
	int sum = m_PlaylistCtrl.GetItemCount();
	if (sum > 0)
	{
		//���Ҫ�Ƴ����ǵ�ǰ���ڲ��ŵ���
		if (nItem == m_iCurPlaying)
		{
			m_iCurPlaying = m_iCurPlaying%sum;
			WPARAM p = m_PlaylistCtrl.GetItemData(m_iCurPlaying);
			GetParent()->PostMessage(WM_OPEN_FILE,p);
		}
		nItem = nItem%sum;
		m_PlaylistCtrl.SetItemState(nItem,LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
	}
	else
	{
		m_iCurPlaying = -1;
	}
}


void CPlaylistDlg::OnNMRClickPlayList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//�ڴ���ӿؼ�֪ͨ����������
	if (pNMItemActivate->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		CMenu menu;
		VERIFY( menu.LoadMenu(IDR_PLAY_LISTDLG_MENU) );
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
	}
	*pResult = 0;
}


void CPlaylistDlg::OnPlay()
{
	POSITION pos = m_PlaylistCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		TRACE0("No items were selected!\n");
	}
	else
	{
		int nItem = m_PlaylistCtrl.GetNextSelectedItem(pos);
		WPARAM p = m_PlaylistCtrl.GetItemData(nItem);
		GetParent()->PostMessage(WM_OPEN_FILE,p);
		m_iCurPlaying = nItem;
	}

}


void CPlaylistDlg::OnAdd()
{
	// TODO: �ڴ���������������
	OnBnClickedAdd();
}


void CPlaylistDlg::OnRemove()
{
	// TODO: �ڴ���������������
	OnBnClickedRemove();
}
