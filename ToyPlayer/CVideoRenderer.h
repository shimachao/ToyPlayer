// Abstract class to manage the video renderer filter.
// Specific implementations handle the VMR-7, VMR-9, or EVR filter.
#pragma once

#include <DShow.h>

class CVideoRenderer
{
public:
	virtual ~CVideoRenderer() {};

	virtual BOOL    HasVideo() const = 0;
	virtual HRESULT AddToGraph(IGraphBuilder *pGraph, HWND hwnd) = 0;
	virtual HRESULT FinalizeGraph(IGraphBuilder *pGraph) = 0;
	virtual HRESULT UpdateVideoWindow(HWND hwnd, const LPRECT prc) = 0;
	virtual HRESULT Repaint(HWND hwnd, HDC hdc) = 0;
	virtual HRESULT DisplayModeChanged() = 0;
	virtual HRESULT SetFullscreen(BOOL) =0;
	virtual SIZE GetVideoSize() =0;
	virtual	HRESULT	GetCurrentImage(LPCTSTR) =0;//参数为文件要保存的路径和文件名
};


