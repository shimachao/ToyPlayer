// Manages the EVR video renderer filter

#pragma once

#include <evr.h>
#include "cvideorenderer.h"

// Manages the EVR video renderer filter.

class CEVR : public CVideoRenderer
{
	IBaseFilter            *m_pEVR;
	IMFVideoDisplayControl *m_pVideoDisplay;

public:
	CEVR();
	~CEVR();
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

