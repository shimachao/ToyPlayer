// NewButon.cpp : ʵ���ļ�
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



// CNewButton ��Ϣ�������




void CNewButton::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CButton::OnPaint()
	/*CBrush backgroundBrush;
	backgroundBrush.CreateSolidBrush(RGB(240,240,240));
	CRect rect;
	this->GetClientRect(&rect);
	dc.FillRect(&rect,&backgroundBrush);*/
	//SetBkColor(dc,RGB(255,255,255));
}
