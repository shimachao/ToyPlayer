//ý��طſ��ƽӿڣ������ࣩ
#include "stdafx.h"
#pragma once

class IPlayerbackControl
{
public:
	virtual ~IPlayerbackControl(){}

	virtual HRESULT Play(void) =0;		//����
	virtual HRESULT Pause(void) =0;		//��ͣ
	virtual HRESULT Restart(void) =0;	//��ͷ��ʼ����
	virtual HRESULT Forword(void) =0;	//���һ��
	virtual HRESULT Retreat(void) =0;	//����һ��
	virtual HRESULT SkipTo(LONGLONG) =0;	//��ת��ָ��λ�ò���

	virtual HRESULT InitRuntiems(void) =0;	//��ʼ��ʱ���Ͳ���ʱ�䣬��100����Ϊ��λ
protected:
	LONGLONG	m_RunTimes;				//ʱ������100����Ϊ��λ
	LONGLONG	m_Step;					//�������˵Ĳ�������100����Ϊ��λ
};
