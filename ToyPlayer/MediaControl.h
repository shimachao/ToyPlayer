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
	STATE_NO_GRAPH,	//filter graph��δ����
	STATE_RUNNING,	//���ڲ���
	STATE_PAUSED,	//��ͣ״̬
	STATE_STOPPED,	//ֹͣ״̬
};

class CMediaControl : public IPlayerbackControl,public IScreenControl,
					  public IVolumeControl
{
public:
	CMediaControl(void);
	virtual ~CMediaControl(void);
	
	//ý��طſ��ƽӿ�
	virtual HRESULT Play(void);		//����
	virtual HRESULT Pause(void);	//��ͣ
	virtual HRESULT Restart(void);	//��ͷ��ʼ����
	virtual HRESULT Forword(void);	//���һ��
	virtual HRESULT Retreat(void);	//����һ��

	virtual HRESULT SkipTo(LONGLONG);	//��ת��ָ��λ�ò���
	virtual HRESULT InitRuntiems(void);	//��ʼ��ʱ���Ͳ���ʱ�䣬��100����Ϊ��λ
	//������ƽӿ�
	virtual void Maximize(void);	//���
	virtual void Minimize(void);	//��С��
	virtual void FullScreen();		//ȫ�����˳�ȫ��
	virtual void RestoreSize(void);	//�ظ�֮ǰ�����С
	virtual void SetScreenSize(LPRECT);	//ֱ��������Ƶ���Ż����С
	HRESULT	GetCueentImage();//��ͼ

	//�������ƽӿ�
	virtual void VolumeUp(void);	//��������
	virtual void VolumeDown(void);	//��С����
	virtual void Mute(void);		//����
	virtual void Unmute(void);		//�������
	virtual void SetVolume(int);	//����������С�����ͻ���ѡ����0��100��ӳ�䵽-10000��0
	
	//
	void OpenMediaFile(LPCTSTR);		//��ý���ļ����ļ�������·��
	void SetVideoWnd(HWND);				//������Ƶ��ʾ���ھ��
	void SetNotifyWnd(HWND);			//���ý���graph��Ϣ����
	HRESULT	HandleGraphEvent();			//graph�¼��������

	//ý����Ϣ��ѯ�ӿ�
	SIZE GetVideSize();			//��ѯ��Ƶ֡��С
	LONGLONG GetRuntime();		//��ѯʱ��
	LONGLONG GetCurrentTime();	//��ѯ��ǰ����λ��

private:
	HRESULT CreateGraph(void);			//����graph
	HRESULT	DestroyGraph(void);			//�������е�graph
	HRESULT CreateVideoRenderer(void);	//����
	HRESULT RenderStreams(void);		//�ύý���е�����������


private:
	HWND			m_VideoHwnd;		//��Ƶ��ʾ���ھ��
	HWND			m_NotifyHwnd;		//����graph�Ĵ���
	PlaybackState	m_PlayerbackState;	//��ǰ�ط�״̬

	IBaseFilter		*m_pSourceFilter;	//ý���ļ�filter
	IGraphBuilder	*m_pGraph;			//filter������
	IMediaControl	*m_pControl;		//ý��طŹ�����
	IBasicAudio		*m_pBasicAudio;		//��Ƶ�����ӿ�
	IBasicVideo		*m_pBasicVideo;		//��Ƶ�����ӿ�
	IMediaEventEx	*m_pEvent;			//ý���¼��ӿ�
	IMediaSeeking	*m_pSeeking;		//ý�嶨λ�ӿ�
	CVideoRenderer	*m_pVideo;			//��Ƶ��Ⱦfilter�İ�װ��
};

