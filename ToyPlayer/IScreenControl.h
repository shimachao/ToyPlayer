//视频播放画面控制接口（纯虚类）

#pragma once

class IScreenControl
{
public:
	virtual ~IScreenControl(){}

	virtual void Maximize(void) =0;	//最大化
	virtual void Minimize(void) =0;	//最小化

	virtual void FullScreen() =0;	//全屏or退出全屏
	virtual void RestoreSize(void) =0;	//回复之前画面大小

	virtual void SetScreenSize(LPRECT) =0;	//直接设置视频播放画面大小

protected:
	RECT	m_Size;			//全屏之前的窗口位置大小（left、right、top、bottom）
};
