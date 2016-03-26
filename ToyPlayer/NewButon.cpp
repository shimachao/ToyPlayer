// NewButon.cpp : 实现文件
//

#include "stdafx.h"
#include "ToyPlayer.h"
#include "NewButon.h"


// CNewButton

IMPLEMENT_DYNAMIC(CNewButton, CButton)

CNewButton::CNewButton()
{

}

CNewButton::~CNewButton()
{
}


BEGIN_MESSAGE_MAP(CNewButton, CButton)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CNewButton 消息处理程序




void CNewButton::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CButton::OnPaint()
	/*CBrush backgroundBrush;
	backgroundBrush.CreateSolidBrush(RGB(240,240,240));
	CRect rect;
	this->GetClientRect(&rect);
	dc.FillRect(&rect,&backgroundBrush);*/
	//SetBkColor(dc,RGB(255,255,255));
}
