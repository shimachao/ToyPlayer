//�������ƽӿ�(������)

#pragma once

class IVolumeControl
{
public:
	virtual ~IVolumeControl(){};

	virtual void VolumeUp(void)=0;	//��������
	virtual void VolumeDown(void)=0;	//��С����
	virtual void Mute(void)=0;		//����
	virtual void Unmute(void)=0;		//�������
	virtual void SetVolume(int)=0;	//����������С�����ͻ���ѡ����0��100��ӳ�䵽-10000��0

protected:
	LONG	m_Volume;				//���浱ǰ��������С����-10000��0
};
