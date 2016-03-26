#pragma once
#include "cvideorenderer.h"
// Manages the VMR-7 video renderer filter.

class CVMR7 : public CVideoRenderer
{
	IVMRWindowlessControl   *m_pWindowless;

public:
	CVMR7();
	~CVMR7();
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

