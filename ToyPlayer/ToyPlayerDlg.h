
// ToyPlayerDlg.h : 头文件
//

#pragma once
#include "MediaControl.h"
#include "ControlPanelDlg.h"
#include "PlaylistDlg.h"
#define CURRENT_TIMER	1
// CToyPlayerDlg 对话框
class CToyPlayerDlg : public CDialogEx
{
// 构造
public:
	CToyPlayerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TOYPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnGraphEvent(WPARAM wParam, LPARAM lParam);
private:
	// 媒体控制类
	CMediaControl* m_pMediaControl;
	//控制面板
	CControlPanelDlg m_ControlPanelDlg;
	//记录控制面板相对于主窗口的位置和大小
	RECT	m_ControlPanelPos;
	//右键弹出菜单
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
	// 利用CFileDlg打开媒体文件
	BOOL OpenMediaFile(void);
public:
	afx_msg void OnOpen();
	afx_msg void OnClose();
	afx_msg void OnPlayPause();
	afx_msg void OnFullscreen();
private:
	// 执行全屏or退出全屏
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
	// 是处于静音状态不
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
