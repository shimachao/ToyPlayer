// Manages the VMR-9 video renderer filter.
#pragma once
#include "cvideorenderer.h"
#include <d3d9.h>
#include <Vmr9.h>


class CVMR9 : public CVideoRenderer
{
	IVMRWindowlessControl9 *m_pWindowless;

public:
	CVMR9();
	~CVMR9();
	BOOL    HasVideo() const;
	HRESULT AddToGraph(IGraphBuilder *pGraph, HWND hwnd);
	HRESULT FinalizeGraph(IGraphBuilder *pGraph);
	HRESULT UpdateVideoWindow(HWND hwnd, const LPRECT prc);
	HRESULT Repaint(HWND hwnd, HDC hdc);
	HRESULT DisplayModeChanged();
	HRESULT SetFullscreen(BOOL);
	SIZE GetVideoSize();
	HRESULT	GetCurrentImage(LPCTSTR);
};


