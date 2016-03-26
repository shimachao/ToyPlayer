//本头文件收集一些directshow编程中用到的辅助函数
#pragma once

#include <DShow.h>

template <class T> void SafeRelease(T **ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

HRESULT FindConnectedPin(IBaseFilter *pFilter, PIN_DIRECTION PinDir, IPin **ppPin);

HRESULT RemoveUnconnectedRenderer(IGraphBuilder *pGraph, IBaseFilter *pRenderer, BOOL *pbRemoved);

HRESULT AddFilterByCLSID(IGraphBuilder *pGraph,REFGUID clsid,IBaseFilter **ppF,LPCWSTR wszName);
