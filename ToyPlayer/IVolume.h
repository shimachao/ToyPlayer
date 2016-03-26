//声音控制接口(纯虚类)

#pragma once

class IVolumeControl
{
public:
	virtual ~IVolumeControl(){};

	virtual void VolumeUp(void)=0;	//音量增大
	virtual void VolumeDown(void)=0;	//减小音量
	virtual void Mute(void)=0;		//静音
	virtual void Unmute(void)=0;		//解除静音
	virtual void SetVolume(int)=0;	//设置音量大小，给客户的选择是0到100，映射到-10000到0

protected:
	LONG	m_Volume;				//保存当前的音量大小，从-10000到0
};
