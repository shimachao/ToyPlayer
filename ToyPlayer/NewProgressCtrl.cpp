// NewProgressCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ToyPlayer.h"
#include "NewProgressCtrl.h"


// CNewProgressCtrl

IMPLEMENT_DYNAMIC(CNewProgressCtrl, CProgressCtrl)

CNewProgressCtrl::CNewProgressCtrl()
{
	m_BackgroundColor = RGB(136,136,136);
	m_ForegroundColor = RGB(32,32,32);
}

CNewProgressCtrl::~CNewProgressCtrl()
{
}

void CNewProgressCtrl::SetBkForeColor(COLORREF bk,COLORREF fore)
{
	m_BackgroundColor = bk;
	m_ForegroundColor = fore;
}

BEGIN_MESSAGE_MAP(CNewProgressCtrl, CProgressCtrl)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CNewProgressCtrl 消息处理程序




void CNewProgressCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CProgressCtrl::OnPaint()
	CBrush backgroundBrush;
	backgroundBrush.CreateSolidBrush(m_BackgroundColor);
	CBrush foreBrush;
	foreBrush.CreateSolidBrush(m_ForegroundColor);
	CRect rect;
	this->GetClientRect(&rect);

	double with = rect.Width();

	int min,max;
	this->GetRange(min,max);

	int pos = this->GetPos();
	double unit = (double)rect.Width()/(max - min);

	dc.FillRect(&rect,&backgroundBrush);

	rect.right = pos*unit;
	dc.FillRect(&rect,&foreBrush);
}


void CNewProgressCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect r;
	this->GetClientRect(&r);

	double with = r.Width();

	int min,max;
	this->GetRange(min,max);

	double unit = (double)(max-min)/r.Width();

	int pos = point.x*unit;

	this->SetPos(pos);
	CProgressCtrl::OnLButtonDown(nFlags, point);
}
