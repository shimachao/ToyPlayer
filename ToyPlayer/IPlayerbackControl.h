//媒体回放控制接口（纯虚类）
#include "stdafx.h"
#pragma once

class IPlayerbackControl
{
public:
	virtual ~IPlayerbackControl(){}

	virtual HRESULT Play(void) =0;		//播放
	virtual HRESULT Pause(void) =0;		//暂停
	virtual HRESULT Restart(void) =0;	//重头开始播放
	virtual HRESULT Forword(void) =0;	//快进一段
	virtual HRESULT Retreat(void) =0;	//后退一段
	virtual HRESULT SkipTo(LONGLONG) =0;	//跳转到指定位置播放

	virtual HRESULT InitRuntiems(void) =0;	//初始化时长和步进时间，以100纳秒为单位
protected:
	LONGLONG	m_RunTimes;				//时长，以100纳秒为单位
	LONGLONG	m_Step;					//快进或后退的步长，以100纳秒为单位
};
