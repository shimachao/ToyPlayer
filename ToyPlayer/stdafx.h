
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持
#include "SkinH.h"
#pragma comment (lib,"SkinHu.lib")

#include "DSAssist.h"
#define WM_GRAPH_EVENT WM_APP + 1
#define WM_PLAY		WM_USER + 1
#define WM_PAUSE	WM_USER + 2
#define WM_FORWORD	WM_USER + 3//快进消息
#define WM_RETREAT	WM_USER + 4//后退

#define WM_VOLUME_UP	WM_USER + 5		//音量增大
#define WM_VOLUME_DOWN	WM_USER + 6		//音量减小
#define WM_SET_VOLUME	WM_USER + 7		//设置音量
#define WM_MUTE			WM_USER + 8		//静音
#define WM_UNMUTE		WM_USER + 9		//解除静音
#define WM_SHOW_LIST	WM_USER + 10	//显示列表

#define WM_OPEN_FILE	WM_USER + 11	//打开文件，播放列表-->播放dlg
#define WM_NEXT			WM_USER + 12	//请求播放列表中的下一个媒体文件
#define WM_PRE			WM_USER + 13	//请求播放列表中的上一个文件
#define WM_RUNTIME		WM_USER + 14	//告知播放列表一个文件的时长：playerDlg-->PlaylistDlg

#define WM_SCREENSHOT	WM_USER + 15	//截图

#define WM_CURENT_TIME WM_USER + 16	//播放器主窗口向控制面板报告当前播放位置




#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


