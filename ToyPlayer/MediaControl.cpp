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
	//初始化com库
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		OutputDebugString(L"\n\n-->初始化com库失败!\n\n");
		return;
	}
	m_Volume = 0;
}

CMediaControl::~CMediaControl(void)
{
	//释放com库
	DestroyGraph();
	CoUninitialize();
}

HRESULT CMediaControl::CreateGraph()
{
	DestroyGraph();
	//创建filter graph管理器
	HRESULT hr = CoCreateInstance(CLSID_FilterGraph, NULL, 
					CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&m_pGraph);
	if (FAILED(hr))
	{
		OutputDebugString(L"\n\n-->创建filter graph管理器失败！\n\n");
		return hr;
	}
	//申请IMediaControl和IMediaEventEx接口
	hr = m_pGraph->QueryInterface(IID_IMediaControl, (void **)&m_pControl);
	hr |= m_pGraph->QueryInterface(IID_IMediaEventEx, (void **)&m_pEvent);
	hr |= m_pGraph->QueryInterface(IID_IMediaSeeking,(void**)&m_pSeeking);
	hr |= m_pGraph->QueryInterface(IID_IBasicAudio,(void**)&m_pBasicAudio);
	hr |= m_pGraph->QueryInterface(IID_IBasicVideo,(void**)&m_pBasicVideo);
	if (FAILED(hr))
	{
		TRACE(L"\n-->%d",__LINE__);
		OutputDebugString(L"\n\n-->申请IMediaControl,IMediaEventEx,IMediaSeeking接口失败！\n\n");
		return hr;
	}
	//设置消息通知窗口句柄
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
			OutputDebugString(L"\n\n-->render为EVR\n\n");
			break;

		case Try_VMR9:
			m_pVideo = new (std::nothrow) CVMR9();
			OutputDebugString(L"\n\n-->render为VMR9\n\n");
			break;

		case Try_VMR7:
			m_pVideo = new (std::nothrow) CVMR7();
			OutputDebugString(L"\n\n-->render为VMR7\n\n");
			break;
		}//switch

		if (m_pVideo == NULL)
		{
			hr = E_OUTOFMEMORY;
			OutputDebugString(L"\n\n-->render创建失败\n\n");
			break;//跳出for
		}

		hr = m_pVideo->AddToGraph(m_pGraph, m_VideoHwnd);
		if (SUCCEEDED(hr))
		{
			break;//跳出for
		}

		OutputDebugString(L"\n\n-->将render添加到graph失败\n\n");
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

//设置待播放的媒体文件名，包含路径
void CMediaControl::OpenMediaFile(LPCTSTR filename)
{
	HRESULT hr = CreateGraph();
	if (FAILED(hr))
	{
		OutputDebugString(L"\n\n-->CreteGraph失败！\n\n");
		goto done;
	}
	//创建并添加source filter到graph中
	hr = m_pGraph->AddSourceFilter(filename,NULL,&m_pSourceFilter);
	if (FAILED(hr))
	{
		OutputDebugString(L"\n\n-->AddAddSourceFilter失败\n\n");
		goto done;
	}
	// Try to render the streams.
	hr = RenderStreams();
	if (FAILED(hr))
	{
		OutputDebugString(L"\n\n-->RenderStream失败\n\n");
	}

done:
	if (FAILED(hr))
	{
		DestroyGraph();
		OutputDebugString(L"\n\n-->打开媒体文件失败!\n\n");
	}
	//SafeRelease(&m_pSourceFilter);
	//通过查询初始化媒体的时长
	InitRuntiems();
}

//设置视频显示窗口句柄
void CMediaControl::SetVideoWnd(HWND hwnd)
{
	m_VideoHwnd = hwnd;
}

//设置接收graph消息通知的窗口
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
			//通知播放器窗口，出现了错误,操作中止了
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
		{//如果时长大于两个小时，步进设为5分钟
			m_Step = 3000000000;
		}
		else if (m_RunTimes > 36000000000)
		{//如果时长大于1个小时，步进设为2分钟
			m_Step = 1200000000;
		}
		else
		{//步进设为5秒
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

//前进
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

//后退
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

//重新开始播放
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
{//最大化，不需要特别的操作吧，这里只是记录下最大化后窗口的位置大小
	::GetClientRect(m_VideoHwnd,&m_Size);
}

void CMediaControl::Minimize()
{
	//不需要CMediaControl插手，播放器窗口自己搞定
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
	//vo的范围是0到100，要映射到-10000到0
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
