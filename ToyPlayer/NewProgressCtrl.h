#pragma once


// CNewProgressCtrl

class CNewProgressCtrl : public CProgressCtrl
{
	DECLARE_DYNAMIC(CNewProgressCtrl)

public:
	CNewProgressCtrl();
	virtual ~CNewProgressCtrl();
	void SetBkForeColor(COLORREF bk,COLORREF fore);
	/*
	这个函数是用来设置进度条背景色和前景色的
	@para	bk：背景颜色值
	@para	fore：前景色
	*/

protected:
	DECLARE_MESSAGE_MAP()

private:
	COLORREF m_BackgroundColor;
	COLORREF m_ForegroundColor;
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


