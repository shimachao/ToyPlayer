#pragma once
#include "afxcmn.h"


// CPlaylistDlg 对话框

class CPlaylistDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPlaylistDlg)

public:
	CPlaylistDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPlaylistDlg();

// 对话框数据
	enum { IDD = IDD_PLAYLIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_PlaylistCtrl;
	int	m_iCurPlaying;			//当前正在播放的文件序号
public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	void InsertFileInfo(LPTSTR pathName,LPTSTR fileName, LPTSTR time);
	void DeleteFileInfo(int nItem);
	afx_msg void OnBnClickedAdd();
	afx_msg void OnNMDblclkPlayList(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	afx_msg LRESULT OnNext(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPre(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRuntime(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedRemove();
	afx_msg void OnNMRClickPlayList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPlay();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
};
