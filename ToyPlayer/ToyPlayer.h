
// ToyPlayer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CToyPlayerApp:
// �йش����ʵ�֣������ ToyPlayer.cpp
//

class CToyPlayerApp : public CWinApp
{
public:
	CToyPlayerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CToyPlayerApp theApp;