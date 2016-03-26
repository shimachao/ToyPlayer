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
	����������������ý���������ɫ��ǰ��ɫ��
	@para	bk��������ɫֵ
	@para	fore��ǰ��ɫ
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


