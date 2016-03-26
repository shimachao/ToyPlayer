#include "StdAfx.h"
#include "VMR9.h"
#pragma comment(lib,"D3d9.lib")

CVMR9::CVMR9() : m_pWindowless(NULL)
{

}

BOOL CVMR9::HasVideo() const 
{ 
	return (m_pWindowless != NULL); 
}

CVMR9::~CVMR9()
{
	SafeRelease(&m_pWindowless);
}

// Initialize the VMR-9 for windowless mode. 
HRESULT InitWindowlessVMR9( 
	IBaseFilter *pVMR,              // Pointer to the VMR
	HWND hwnd,                      // Clipping window
	IVMRWindowlessControl9** ppWC   // Receives a pointer to the VMR.
	) 
{ 

	IVMRFilterConfig9 * pConfig = NULL; 
	IVMRWindowlessControl9 *pWC = NULL;

	// Set the rendering mode.  

	HRESULT hr = pVMR->QueryInterface(IID_PPV_ARGS(&pConfig)); 
	if (FAILED(hr))
	{
		goto done;
	}

	hr = pConfig->SetRenderingMode(VMR9Mode_Windowless); 
	if (FAILED(hr))
	{
		goto done;
	}

	// Query for the windowless control interface.
	hr = pVMR->QueryInterface(IID_PPV_ARGS(&pWC));
	if (FAILED(hr))
	{
		goto done;
	}

	// Set the clipping window.
	hr = pWC->SetVideoClippingWindow(hwnd);
	if (FAILED(hr))
	{
		goto done;
	}

	// Preserve aspect ratio by letter-boxing
	hr = pWC->SetAspectRatioMode(VMR9ARMode_LetterBox);
	if (FAILED(hr))
	{
		goto done;
	}

	// Return the IVMRWindowlessControl pointer to the caller.

	*ppWC = pWC;
	(*ppWC)->AddRef();

done:
	SafeRelease(&pConfig);
	SafeRelease(&pWC);
	return hr; 
} 

HRESULT CVMR9::AddToGraph(IGraphBuilder *pGraph, HWND hwnd)
{
	IBaseFilter *pVMR = NULL;

	HRESULT hr = AddFilterByCLSID(pGraph, CLSID_VideoMixingRenderer9, 
		&pVMR, L"VMR-9");
	if (SUCCEEDED(hr))
	{
		// Set windowless mode on the VMR. This must be done before the VMR 

		// is connected.

		hr = InitWindowlessVMR9(pVMR, hwnd, &m_pWindowless);
	}
	SafeRelease(&pVMR);
	return hr;
}

HRESULT CVMR9::FinalizeGraph(IGraphBuilder *pGraph)
{
	if (m_pWindowless == NULL)
	{
		return S_OK;
	}

	IBaseFilter *pFilter = NULL;

	HRESULT hr = m_pWindowless->QueryInterface(IID_PPV_ARGS(&pFilter));
	if (FAILED(hr))
	{
		goto done;
	}

	BOOL bRemoved;
	hr = RemoveUnconnectedRenderer(pGraph, pFilter, &bRemoved);

	// If we removed the VMR, then we also need to release our 

	// pointer to the VMR's windowless control interface.

	if (bRemoved)
	{
		SafeRelease(&m_pWindowless);
	}

done:
	SafeRelease(&pFilter);
	return hr;
}


HRESULT CVMR9::UpdateVideoWindow(HWND hwnd, const LPRECT prc)
{
	if (m_pWindowless == NULL)
	{
		return S_OK; // no-op

	}

	if (prc)
	{
		return m_pWindowless->SetVideoPosition(NULL, prc);
	}
	else
	{

		RECT rc;
		GetClientRect(hwnd, &rc);
		return m_pWindowless->SetVideoPosition(NULL, &rc);
	}
}

HRESULT CVMR9::Repaint(HWND hwnd, HDC hdc)
{
	if (m_pWindowless)
	{
		return m_pWindowless->RepaintVideo(hwnd, hdc);
	}
	else
	{
		return S_OK;
	}
}

HRESULT CVMR9::DisplayModeChanged()
{
	if (m_pWindowless)
	{
		return m_pWindowless->DisplayModeChanged();
	}
	else
	{
		return S_OK;
	}
}

HRESULT CVMR9::SetFullscreen(BOOL)
{
	return FALSE;
}

SIZE CVMR9::GetVideoSize()
{
	SIZE vsize;
	m_pWindowless->GetNativeVideoSize(&vsize.cx,&vsize.cy,NULL,NULL);
	return vsize;
}

HRESULT CVMR9::GetCurrentImage(LPCTSTR path)
{

	return S_OK;
}