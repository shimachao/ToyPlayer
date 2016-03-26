#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "NewProgressCtrl.h"
#include "NewButon.h"

// CControlPanelDlg �Ի���

class CControlPanelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CControlPanelDlg)

public:
	CControlPanelDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CControlPanelDlg();

// �Ի�������
	enum { IDD = IDD_CONTROL_PANEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	// ��������
	CSliderCtrl m_VolumeSliderCtrl;
public:
	afx_msg void OnBnClickedMuteCheck();
private:
	CButton m_MuteCheckBox;
	int m_TotalTime;		//��ǰ�����ļ���ʱ��������Ϊ��λ
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
	// ʱ�������
	//CProgressCtrl m_TimeProgressCtrl;
	CNewProgressCtrl m_TimeProgressCtrl;
public:
private:
	//CNewButton m_PreBtn;
};
