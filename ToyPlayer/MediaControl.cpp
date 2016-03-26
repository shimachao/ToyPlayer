#include "StdAfx.h"
#include "MediaControl.h"
#include "EVR.h"
#include "VMR9.h"
#include "VMR7.h"
#include <Strmif.h>
#include <Mtype.h>
//#include <MMSystem.h>

#pragma comment(lib,"Strmiids.lib")
#pragma comment(lib,"Quartz.lib")
//#pragma comment(lib,"Strmbasd.lib")
//#pragma comment(lib,"winmm.lib")


CMediaControl::CMediaControl(void):m_VideoHwnd(NULL),m_PlayerbackState(STATE_NO_GRAPH),
									m_pGraph(NULL),m_pControl(NULL),m_pEvent(NULL),
									m_pSeeking(NULL),m_pVideo(NULL)
{
	//��ʼ��com��
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		OutputDebugString(L"\n\n-->��ʼ��com��ʧ��!\n\n");
		return;
	}
	m_Volume = 0;
}

CMediaControl::~CMediaControl(void)
{
	//�ͷ�com��
	DestroyGraph();
	CoUninitialize();
}

HRESULT CMediaControl::CreateGraph()
{
	DestroyGraph();
	//����filter graph������
	HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL, 
					CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&m_pGraph);
	if (FAILED(hr))
	{
		OutputDebugString(L"\n\n-->����filter graph������ʧ�ܣ�\n\n");
		return hr;
	}
	//����IMediaControl��IMediaEventEx�ӿ�
	hr = m_pGraph->QueryInterface(IID_IMediaControl, (void **)&m_pControl);
	hr |= m_pGraph->QueryInterface(IID_IMediaEventEx, (void **)&m_pEvent);
	hr |= m_pGraph->QueryInterface(IID_IMediaSeeking,(void**)&m_pSeeking);
	hr |= m_pGraph->QueryInterface(IID_IBasicAudio,(void**)&m_pBasicAudio);
	hr |= m_pGraph->QueryInterface(IID_IBasicVideo,(void**)&m_pBasicVideo);
	if (FAILED(hr))
	{
		TRACE(L"\n-->%d",__LINE__);
		OutputDebugString(L"\n\n-->����IMediaControl,IMediaEventEx,IMediaSeeking�ӿ�ʧ�ܣ�\n\n");
		return hr;
	}
	//������Ϣ֪ͨ���ھ��
	m_pEvent->SetNotifyWindow((OAHWND)m_NotifyHwnd,WM_GRAPH_EVENT,NULL);

	m_PlayerbackState = STATE_STOPPED;

	return S_OK;
}

HRESULT CMediaControl::CreateVideoRenderer()
{
	HRESULT hr = E_FAIL;
	enum { Try_EVR, Try_VMR9, Try_VMR7 };

	for (DWORD i = Try_EVR; i <= Try_VMR7; i++)
	{
		switch (i)
		{
		case Try_EVR:
			m_pVideo = new (std::nothrow) CEVR();
			OutputDebugString(L"\n\n-->renderΪEVR\n\n");
			break;

		case Try_VMR9:
			m_pVideo = new (std::nothrow) CVMR9();
			OutputDebugString(L"\n\n-->renderΪVMR9\n\n");
			break;

		case Try_VMR7:
			m_pVideo = new (std::nothrow) CVMR7();
			OutputDebugString(L"\n\n-->renderΪVMR7\n\n");
			break;
		}//switch

		if (m_pVideo == NULL)
		{
			hr = E_OUTOFMEMORY;
			OutputDebugString(L"\n\n-->render����ʧ��\n\n");
			break;//����for
		}

		hr = m_pVideo->AddToGraph(m_pGraph, m_VideoHwnd);
		if (SUCCEEDED(hr))
		{
			break;//����for
		}

		OutputDebugString(L"\n\n-->��render��ӵ�graphʧ��\n\n");
		delete m_pVideo;
		m_pVideo = NULL;
	}
	return hr;
}

HRESULT CMediaControl::RenderStreams()
{
	BOOL bRenderedAnyPin = FALSE;

	IFilterGraph2 *pGraph2 = NULL;
	IEnumPins *pEnum = NULL;
	IBaseFilter *pAudioRenderer = NULL;
	HRESULT hr = m_pGraph->QueryInterface(IID_PPV_ARGS(&pGraph2));
	if (FAILED(hr))
	{
		goto done;
	}
	// Add the video renderer to the graph
	hr = CreateVideoRenderer();
	if (FAILED(hr))
	{
		goto done;
	}

	// Add the DSound Renderer to the graph.
	hr = AddFilterByCLSID(m_pGraph, CLSID_DSoundRender, 
		&pAudioRenderer, L"Audio Renderer");
	if (FAILED(hr))
	{
		goto done;
	}

	// Enumerate the pins on the source filter.
	hr = m_pSourceFilter->EnumPins(&pEnum);
	if (FAILED(hr))
	{
		goto done;
	}
	// Loop through all the pins
	IPin *pPin;
	while (S_OK == pEnum->Next(1, &pPin, NULL))
	{           
		// Try to render this pin. 
		// It's OK if we fail some pins, if at least one pin renders.
		HRESULT hr2 = pGraph2->RenderEx(pPin, AM_RENDEREX_RENDERTOEXISTINGRENDERERS, NULL);

		pPin->Release();
		if (SUCCEEDED(hr2))
		{
			bRenderedAnyPin = TRUE;
		}
	}

	hr = m_pVideo->FinalizeGraph(m_pGraph);
	if (FAILED(hr))
	{
		goto done;
	}

	// Remove the audio renderer, if not used.
	BOOL bRemoved;
	hr = RemoveUnconnectedRenderer(m_pGraph, pAudioRenderer, &bRemoved);

done:
	SafeRelease(&pEnum);
	SafeRelease(&pAudioRenderer);
	SafeRelease(&pGraph2);

	// If we succeeded to this point, make sure we rendered at least one 
	// stream.
	if (SUCCEEDED(hr))
	{
		if (!bRenderedAnyPin)
		{
			hr = VFW_E_CANNOT_RENDER;
		}
	}
	return hr;
}

HRESULT CMediaControl::DestroyGraph()
{
	if (m_pGraph != NULL)
	{
		if (m_pControl)
		{
			m_pControl->Stop();
		}
		if (m_pEvent)
		{
			m_pEvent->SetNotifyWindow((OAHWND)NULL, NULL, NULL);
		}
		
		SafeRelease(&m_pGraph);
		SafeRelease(&m_pSourceFilter);
		SafeRelease(&m_pControl);
		SafeRelease(&m_pEvent);
		SafeRelease(&m_pBasicAudio);
		SafeRelease(&m_pBasicVideo);

		delete m_pVideo;
		m_pVideo = NULL;

		m_PlayerbackState = STATE_NO_GRAPH;

		return S_OK;
	}
	return S_FALSE;
}

//���ô����ŵ�ý���ļ���������·��
void CMediaControl::OpenMediaFile(LPCTSTR filename)
{
	HRESULT hr = CreateGraph();
	if (FAILED(hr))
	{
		OutputDebugString(L"\n\n-->CreteGraphʧ�ܣ�\n\n");
		goto done;
	}
	//���������source filter��graph��
	hr = m_pGraph->AddSourceFilter(filename,NULL,&m_pSourceFilter);
	if (FAILED(hr))
	{
		OutputDebugString(L"\n\n-->AddAddSourceFilterʧ��\n\n");
		goto done;
	}
	// Try to render the streams.
	hr = RenderStreams();
	if (FAILED(hr))
	{
		OutputDebugString(L"\n\n-->RenderStreamʧ��\n\n");
	}

done:
	if (FAILED(hr))
	{
		DestroyGraph();
		OutputDebugString(L"\n\n-->��ý���ļ�ʧ��!\n\n");
	}
	//SafeRelease(&m_pSourceFilter);
	//ͨ����ѯ��ʼ��ý���ʱ��
	InitRuntiems();
}

//������Ƶ��ʾ���ھ��
void CMediaControl::SetVideoWnd(HWND hwnd)
{
	m_VideoHwnd = hwnd;
}

//���ý���graph��Ϣ֪ͨ�Ĵ���
void CMediaControl::SetNotifyWnd(HWND hwnd)
{
	m_NotifyHwnd = hwnd;
}

HRESULT CMediaControl::HandleGraphEvent()
{
	if (!m_pEvent)
	{
		return E_UNEXPECTED;
	}

	long evCode = 0;
	LONG_PTR param1 = 0, param2 = 0;

	HRESULT hr = S_OK;

	// Get the events from the queue.
	while (SUCCEEDED(m_pEvent->GetEvent(&evCode, &param1, &param2, 0)))
	{
		switch (evCode)
		{
		case EC_COMPLETE:
		case EC_USERABORT:
			m_pControl->Stop();
			m_PlayerbackState =  STATE_STOPPED;
			break;

		case EC_ERRORABORT:
			//֪ͨ���������ڣ������˴���,������ֹ��
			m_pControl->Stop();
			m_PlayerbackState =  STATE_STOPPED;
			break;
		default:
			break;
		}

		hr = m_pEvent->FreeEventParams(evCode, param1, param2);
		if (FAILED(hr))
		{
			break;
		}
	}
	return hr;
}

HRESULT CMediaControl::InitRuntiems()
{
	HRESULT hr = m_pSeeking->GetDuration(&m_RunTimes);
	if (SUCCEEDED(hr))
	{
		if (m_RunTimes > 72000000000)
		{//���ʱ����������Сʱ��������Ϊ5����
			m_Step = 3000000000;
		}
		else if (m_RunTimes > 36000000000)
		{//���ʱ������1��Сʱ��������Ϊ2����
			m_Step = 1200000000;
		}
		else
		{//������Ϊ5��
			m_Step = 50000000;
		}
	}//if
	return hr;
}

HRESULT CMediaControl::Play()
{
	HRESULT hr = S_FALSE;
	if ((m_PlayerbackState == STATE_STOPPED || m_PlayerbackState == STATE_PAUSED)
		&& m_pControl != NULL)
	{
		hr = m_pControl->Run();
		m_PlayerbackState = STATE_RUNNING;
	}
	return hr;
}

HRESULT CMediaControl::Pause()
{
	HRESULT hr = S_FALSE;
	if (m_PlayerbackState == STATE_RUNNING && m_pControl != NULL)
	{
		hr = m_pControl->Pause();
		m_PlayerbackState = STATE_PAUSED;
	}
	return hr;
}

//ǰ��
HRESULT CMediaControl::Forword()
{
	if (m_PlayerbackState == STATE_NO_GRAPH || m_PlayerbackState == STATE_STOPPED)
	{
		return S_FALSE;
	}

	HRESULT hr = S_FALSE;
	LONGLONG curtimes;
	hr = m_pSeeking->GetCurrentPosition(&curtimes);
	if (SUCCEEDED(hr))
	{
		LONGLONG newtime = curtimes + m_Step;
		if (newtime <= m_RunTimes)
		{
			hr |= m_pSeeking->SetPositions(&newtime,AM_SEEKING_AbsolutePositioning|
				AM_SEEKING_SeekToKeyFrame,
				NULL,AM_SEEKING_NoPositioning);
		}
	}
	return hr;
}

//����
HRESULT CMediaControl::Retreat()
{
	if (m_PlayerbackState == STATE_NO_GRAPH || m_PlayerbackState == STATE_STOPPED)
	{
		return S_FALSE;
	}

	LONGLONG curtimes;
	HRESULT hr = m_pSeeking->GetCurrentPosition(&curtimes);
	LONGLONG newtime = curtimes - m_Step;
	if (newtime >= 0)
	{
		hr = m_pSeeking->SetPositions(&newtime,AM_SEEKING_AbsolutePositioning |
			AM_SEEKING_SeekToKeyFrame,NULL,
			AM_SEEKING_NoPositioning);
	}
	return hr;
}

//���¿�ʼ����
HRESULT CMediaControl::Restart()
{
	LONGLONG times = 0;
	return m_pSeeking->SetPositions(&times,AM_SEEKING_AbsolutePositioning,
									NULL,AM_SEEKING_NoPositioning);
}

HRESULT CMediaControl::SkipTo(LONGLONG pos)
{
	if (m_PlayerbackState == STATE_NO_GRAPH)
	{
		return S_FALSE;
	}
	else
		return m_pSeeking->SetPositions(&pos,AM_SEEKING_AbsolutePositioning,
									NULL,AM_SEEKING_NoPositioning);
}

void CMediaControl::Maximize()
{//��󻯣�����Ҫ�ر�Ĳ����ɣ�����ֻ�Ǽ�¼����󻯺󴰿ڵ�λ�ô�С
	::GetClientRect(m_VideoHwnd,&m_Size);
}

void CMediaControl::Minimize()
{
	//����ҪCMediaControl���֣������������Լ��㶨
}

void CMediaControl::RestoreSize()
{
	m_pVideo->UpdateVideoWindow(m_VideoHwnd,&m_Size);
}

void CMediaControl::FullScreen()
{
	static BOOL bfull = TRUE;
	if (bfull)
	{
		m_pVideo->SetFullscreen(bfull);
		bfull = !bfull;
	}
}

void CMediaControl::SetScreenSize(LPRECT prc)
{
	if (m_pVideo)
	{
		m_pVideo->UpdateVideoWindow(m_VideoHwnd,prc);
		m_Size = *prc;
	}
}

HRESULT CMediaControl::GetCueentImage()
{
	HRESULT hr = S_FALSE;
	if (m_pVideo)
	{
		hr = m_pVideo->GetCurrentImage(NULL);
	}
	
	return hr;
}

void CMediaControl::VolumeUp()
{
	if (m_pBasicAudio != NULL)
	{
		m_Volume += 100;
		m_pBasicAudio->put_Volume(m_Volume);
	}
}

void CMediaControl::VolumeDown()
{
	if (m_pBasicAudio != NULL)
	{
		m_Volume -= 100;
		if (m_Volume < -10000)
		{
			m_Volume = -10000;
		}
		m_pBasicAudio->put_Volume(m_Volume);
	}
}

void CMediaControl::SetVolume(int vo)
{
	//vo�ķ�Χ��0��100��Ҫӳ�䵽-10000��0
	if (m_pBasicAudio != NULL && vo >= 0 && vo <= 100)
	{
		m_Volume = (vo - 100)*100;
		m_pBasicAudio->put_Volume(m_Volume);
	}
}

void CMediaControl::Mute()
{
	if (m_pBasicAudio != NULL)
	{
		m_pBasicAudio->put_Volume(-10000);
	}
}

void CMediaControl::Unmute()
{
	if (m_pBasicAudio != NULL)
	{
		if (m_Volume == -10000)
		{
			m_Volume = -5000;
		}
		m_pBasicAudio->put_Volume(m_Volume);
	}
}

SIZE CMediaControl::GetVideSize()
{
	if (m_pVideo == NULL)
	{
		SIZE _size;
		_size.cx = 0;
		_size.cy = 0;
		return _size;
	}
	return m_pVideo->GetVideoSize();
}

LONGLONG CMediaControl::GetRuntime()
{
	LONGLONG times = 0;
	if (m_pSeeking)
	{
		m_pSeeking->GetDuration(&times);
	}
	return times;
}

LONGLONG CMediaControl::GetCurrentTime()
{
	LONGLONG times = 0;
	if (m_pSeeking)
	{
		m_pSeeking->GetCurrentPosition(&times);
	}
	return times;
}
