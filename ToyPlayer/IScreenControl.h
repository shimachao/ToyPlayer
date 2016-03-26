//��Ƶ���Ż�����ƽӿڣ������ࣩ

#pragma once

class IScreenControl
{
public:
	virtual ~IScreenControl(){}

	virtual void Maximize(void) =0;	//���
	virtual void Minimize(void) =0;	//��С��

	virtual void FullScreen() =0;	//ȫ��or�˳�ȫ��
	virtual void RestoreSize(void) =0;	//�ظ�֮ǰ�����С

	virtual void SetScreenSize(LPRECT) =0;	//ֱ��������Ƶ���Ż����С

protected:
	RECT	m_Size;			//ȫ��֮ǰ�Ĵ���λ�ô�С��left��right��top��bottom��
};
