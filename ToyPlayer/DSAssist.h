//��ͷ�ļ��ռ�һЩdirectshow������õ��ĸ�������
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
