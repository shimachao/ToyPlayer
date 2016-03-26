
// ToyPlayerDlg.h : ͷ�ļ�
//

#pragma once
#include "MediaControl.h"
#include "ControlPanelDlg.h"
#include "PlaylistDlg.h"
#define CURRENT_TIMER	1
// CToyPlayerDlg �Ի���
class CToyPlayerDlg : public CDialogEx
{
// ����
public:
	CToyPlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TOYPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnGraphEvent(WPARAM wParam, LPARAM lParam);
private:
	// ý�������
	CMediaControl* m_pMediaControl;
	//�������
	CControlPanelDlg m_ControlPanelDlg;
	//��¼�����������������ڵ�λ�úʹ�С
	RECT	m_ControlPanelPos;
	//�Ҽ������˵�
	CMenu m_Menu;

	CPlaylistDlg	m_PlaylistDlg;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	afx_msg LRESULT OnPlay(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPause(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnForword(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRetreat(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
protected:
	afx_msg LRESULT OnVolumeUp(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnVolumeDown(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetVolume(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMute(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUnmute(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowList(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedOpenFile();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	afx_msg LRESULT OnOpenFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnScreenshot(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
private:
	// ����CFileDlg��ý���ļ�
	BOOL OpenMediaFile(void);
public:
	afx_msg void OnOpen();
	afx_msg void OnClose();
	afx_msg void OnPlayPause();
	afx_msg void OnFullscreen();
private:
	// ִ��ȫ��or�˳�ȫ��
	void FullScreen(void);
public:
	afx_msg void OnFullScreen();
	afx_msg void OnMaxScreen();
	afx_msg void OnDoubleScreen();
	afx_msg void OnRawScreen();
	afx_msg void OnOneAndHalfScreen();
	afx_msg void OnHalfScreen();
	afx_msg void OnScreenshot();
	afx_msg void OnMuteUnmute();
private:
	// �Ǵ��ھ���״̬��
	bool m_bMute;
public:
	afx_msg void OnListdlg();
	afx_msg void OnQuit();
	afx_msg void OnTopWind();
	afx_msg void OnPreFile();
	afx_msg void OnNext();
	afx_msg void OnForward();
	afx_msg void OnBackward();
	afx_msg void OnReplay();
	afx_msg void OnAcceleratorPlay();
	afx_msg void OnAcceleratorForward();
	afx_msg void OnAcceleratorBackward();
	afx_msg void OnAcceleratorVolumeUp();
	afx_msg void OnAcceleratorVolumeDown();
};
