#pragma once

#include "stdafx.h"
#include <DShow.h>
#include "CVideoRenderer.h"
#include "IPlayerbackControl.h"
#include "IScreenControl.h"
#include "IVolume.h"
#include "IMediaInfo.h"

enum PlaybackState
{
	STATE_NO_GRAPH,	//filter graph还未建立
	STATE_RUNNING,	//正在播放
	STATE_PAUSED,	//暂停状态
	STATE_STOPPED,	//停止状态
};

class CMediaControl : public IPlayerbackControl,public IScreenControl,
					  public IVolumeControl
{
public:
	CMediaControl(void);
	virtual ~CMediaControl(void);
	
	//媒体回放控制接口
	virtual HRESULT Play(void);		//播放
	virtual HRESULT Pause(void);	//暂停
	virtual HRESULT Restart(void);	//重头开始播放
	virtual HRESULT Forword(void);	//快进一段
	virtual HRESULT Retreat(void);	//后退一段

	virtual HRESULT SkipTo(LONGLONG);	//跳转到指定位置播放
	virtual HRESULT InitRuntiems(void);	//初始化时长和步进时间，以100纳秒为单位
	//画面控制接口
	virtual void Maximize(void);	//最大化
	virtual void Minimize(void);	//最小化
	virtual void FullScreen();		//全屏或退出全屏
	virtual void RestoreSize(void);	//回复之前画面大小
	virtual void SetScreenSize(LPRECT);	//直接设置视频播放画面大小
	HRESULT	GetCueentImage();//截图

	//声音控制接口
	virtual void VolumeUp(void);	//音量增大
	virtual void VolumeDown(void);	//减小音量
	virtual void Mute(void);		//静音
	virtual void Unmute(void);		//解除静音
	virtual void SetVolume(int);	//设置音量大小，给客户的选择是0到100，映射到-10000到0
	
	//
	void OpenMediaFile(LPCTSTR);		//打开媒体文件，文件名包含路径
	void SetVideoWnd(HWND);				//设置视频显示窗口句柄
	void SetNotifyWnd(HWND);			//设置接收graph消息窗口
	HRESULT	HandleGraphEvent();			//graph事件处理程序

	//媒体信息查询接口
	SIZE GetVideSize();			//查询视频帧大小
	LONGLONG GetRuntime();		//查询时长
	LONGLONG GetCurrentTime();	//查询当前播放位置

private:
	HRESULT CreateGraph(void);			//创建graph
	HRESULT	DestroyGraph(void);			//销毁现有的graph
	HRESULT CreateVideoRenderer(void);	//创建
	HRESULT RenderStreams(void);		//提交媒体中的所有数据流


private:
	HWND			m_VideoHwnd;		//视频显示窗口句柄
	HWND			m_NotifyHwnd;		//接收graph的窗口
	PlaybackState	m_PlayerbackState;	//当前回放状态

	IBaseFilter		*m_pSourceFilter;	//媒体文件filter
	IGraphBuilder	*m_pGraph;			//filter管理器
	IMediaControl	*m_pControl;		//媒体回放管理器
	IBasicAudio		*m_pBasicAudio;		//音频基本接口
	IBasicVideo		*m_pBasicVideo;		//视频基本接口
	IMediaEventEx	*m_pEvent;			//媒体事件接口
	IMediaSeeking	*m_pSeeking;		//媒体定位接口
	CVideoRenderer	*m_pVideo;			//视频渲染filter的包装类
};

