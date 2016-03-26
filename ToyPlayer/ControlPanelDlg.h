#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "NewProgressCtrl.h"
#include "NewButon.h"

// CControlPanelDlg 对话框

class CControlPanelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CControlPanelDlg)

public:
	CControlPanelDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CControlPanelDlg();

// 对话框数据
	enum { IDD = IDD_CONTROL_PANEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnNcHitTest(CPoint point);
	virtual void OnOK();
	virtual void OnCancel();
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedForword();
	afx_msg void OnBnClickedRetreat();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	// 音量控制
	CSliderCtrl m_VolumeSliderCtrl;
public:
	afx_msg void OnBnClickedMuteCheck();
private:
	CButton m_MuteCheckBox;
	int m_TotalTime;		//当前播放文件的时长，以秒为单位
public:
	afx_msg void OnBnClickedShowList();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedPre();
	afx_msg void OnBnClickedScreenshot();
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	afx_msg LRESULT OnRuntime(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCurentTime(WPARAM wParam, LPARAM lParam);
private:
	// 时间进度条
	//CProgressCtrl m_TimeProgressCtrl;
	CNewProgressCtrl m_TimeProgressCtrl;
public:
private:
	//CNewButton m_PreBtn;
};
