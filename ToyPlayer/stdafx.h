
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��
#include "SkinH.h"
#pragma comment (lib,"SkinHu.lib")

#include "DSAssist.h"
#define WM_GRAPH_EVENT WM_APP + 1
#define WM_PLAY		WM_USER + 1
#define WM_PAUSE	WM_USER + 2
#define WM_FORWORD	WM_USER + 3//�����Ϣ
#define WM_RETREAT	WM_USER + 4//����

#define WM_VOLUME_UP	WM_USER + 5		//��������
#define WM_VOLUME_DOWN	WM_USER + 6		//������С
#define WM_SET_VOLUME	WM_USER + 7		//��������
#define WM_MUTE			WM_USER + 8		//����
#define WM_UNMUTE		WM_USER + 9		//�������
#define WM_SHOW_LIST	WM_USER + 10	//��ʾ�б�

#define WM_OPEN_FILE	WM_USER + 11	//���ļ��������б�-->����dlg
#define WM_NEXT			WM_USER + 12	//���󲥷��б��е���һ��ý���ļ�
#define WM_PRE			WM_USER + 13	//���󲥷��б��е���һ���ļ�
#define WM_RUNTIME		WM_USER + 14	//��֪�����б�һ���ļ���ʱ����playerDlg-->PlaylistDlg

#define WM_SCREENSHOT	WM_USER + 15	//��ͼ

#define WM_CURENT_TIME WM_USER + 16	//�������������������屨�浱ǰ����λ��




#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


