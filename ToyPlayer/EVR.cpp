#include "StdAfx.h"
#include "EVR.h"


CEVR::CEVR() : m_pEVR(NULL), m_pVideoDisplay(NULL)
{

}

CEVR::~CEVR()
{
	SafeRelease(&m_pEVR);
	SafeRelease(&m_pVideoDisplay);
}

BOOL CEVR::HasVideo() const 
{ 
	return (m_pVideoDisplay != NULL); 
}


HRESULT InitializeEVR( 
	IBaseFilter *pEVR,              // Pointer to the EVR
	HWND hwnd,                      // Clipping window
	IMFVideoDisplayControl** ppDisplayControl
	) 
{ 
	IMFGetService *pGS = NULL;
	IMFVideoDisplayControl *pDisplay = NULL;

	HRESULT hr = pEVR->QueryInterface(IID_PPV_ARGS(&pGS)); 
	if (FAILED(hr))
	{
		goto done;
	}

	hr = pGS->GetService(MR_VIDEO_RENDER_SERVICE, IID_PPV_ARGS(&pDisplay));
	if (FAILED(hr))
	{
		goto done;
	}

	// Set the clipping window.
	hr = pDisplay->SetVideoWindow(hwnd);
	if (FAILED(hr))
	{
		goto done;
	}

	// Preserve aspect ratio by letter-boxing
	hr = pDisplay->SetAspectRatioMode(MFVideoARMode_PreservePicture);
	if (FAILED(hr))
	{
		goto done;
	}

	// Return the IMFVideoDisplayControl pointer to the caller.
	*ppDisplayControl = pDisplay;
	(*ppDisplayControl)->AddRef();

done:
	SafeRelease(&pGS);
	SafeRelease(&pDisplay);
	return hr; 
} 

HRESULT CEVR::AddToGraph(IGraphBuilder *pGraph, HWND hwnd)
{
	IBaseFilter *pEVR = NULL;
	HRESULT hr = AddFilterByCLSID(pGraph, CLSID_EnhancedVideoRenderer, 
		&pEVR, L"EVR");

	if (FAILED(hr))
	{
		goto done;
	}

	hr = InitializeEVR(pEVR, hwnd, &m_pVideoDisplay);
	if (FAILED(hr))
	{
		goto done;
	}
	UpdateVideoWindow(hwnd,NULL);

	// Note: Because IMFVideoDisplayControl is a service interface,
	// you cannot QI the pointer to get back the IBaseFilter pointer.
	// Therefore, we need to cache the IBaseFilter pointer.
	m_pEVR = pEVR;
	m_pEVR->AddRef();

done:
	SafeRelease(&pEVR);
	return hr;
}


HRESULT CEVR::FinalizeGraph(IGraphBuilder *pGraph)
{
	if (m_pEVR == NULL)
	{
		return S_OK;
	}

	BOOL bRemoved;
	HRESULT hr = RemoveUnconnectedRenderer(pGraph, m_pEVR, &bRemoved);
	if (bRemoved)
	{
		SafeRelease(&m_pEVR);
		SafeRelease(&m_pVideoDisplay);
	}
	return hr;
}


HRESULT CEVR::UpdateVideoWindow(HWND hwnd, const LPRECT prc)
{
	if (m_pVideoDisplay == NULL)
	{
		return S_OK; // no-op

	}

	if (prc)
	{
		return m_pVideoDisplay->SetVideoPosition(NULL, prc);
	}
	else
	{

		RECT rc;
		GetClientRect(hwnd, &rc);
		return m_pVideoDisplay->SetVideoPosition(NULL, &rc);
	}
}

HRESULT CEVR::Repaint(HWND hwnd, HDC hdc)
{
	if (m_pVideoDisplay)
	{
		return m_pVideoDisplay->RepaintVideo();
	}
	else
	{
		return S_OK;
	}
}

HRESULT CEVR::DisplayModeChanged()
{
	// The EVR does not require any action in response to WM_DISPLAYCHANGE.
	return S_OK;
}

HRESULT CEVR::SetFullscreen(BOOL fFullscreen)
{
	return m_pVideoDisplay->SetFullscreen(fFullscreen);
}

SIZE CEVR::GetVideoSize()
{
	SIZE vsize;
	m_pVideoDisplay->GetNativeVideoSize(&vsize,NULL);
	return vsize;
}

HRESULT CEVR::GetCurrentImage(LPCTSTR path)
{
	HRESULT hr = S_FALSE;

	BITMAPINFOHEADER bih;
	ZeroMemory(&bih,sizeof(BITMAPINFOHEADER));
	bih.biSize = sizeof(BITMAPINFOHEADER);
	BYTE *pDib = NULL;
	DWORD cbDib = 0;
	LONGLONG TimeStamp = 0;
	hr = m_pVideoDisplay->GetCurrentImage(&bih,(BYTE**)&pDib,&cbDib,&TimeStamp);

	BITMAPFILEHEADER bFh;
	ZeroMemory(&bFh,sizeof(BITMAPFILEHEADER));
	bFh.bfType = ((WORD) ('M' << 8) | 'B');     //always is "BM" 
	bFh.bfSize = sizeof(BITMAPFILEHEADER) + cbDib;
	int nPolette = 0;//调色板大小
	nPolette = (1 << bih.biBitCount);
	if (bih.biBitCount >= 24)
	{
		nPolette = 0;
	}
	nPolette*=4;
	bFh.bfOffBits = sizeof(BITMAPFILEHEADER) + bih.biSize + nPolette;
	//保存到文件
	CFile bitmapFile(L".\\test.bmp", CFile::modeNoTruncate|
		CFile::modeReadWrite | CFile::modeCreate | CFile::typeBinary); 
	bitmapFile.Write(&bFh, sizeof(BITMAPFILEHEADER)); 
	bitmapFile.Write(&bih,sizeof(bih));
	bitmapFile.Write(pDib, cbDib); 
	bitmapFile.Close();
	CoTaskMemFree(pDib);
	return hr;
}
