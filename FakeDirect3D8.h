/*
Direct3D8 shim to replace fullscreen with windowed mode.
Confirmed to be working with Vice City
by E.Sandberg 2014

This code is released into the public domain.
Read LICENSE.TXT for license information.
*/

#pragma once
#include <d3d8.h>

class FakeDirect3D8 : public IDirect3D8
{
private:
	IDirect3D8* realD3D8;
public:
	FakeDirect3D8(IDirect3D8* realD3D8);
	~FakeDirect3D8();

	/* IUnknown methods */
	ULONG __stdcall AddRef();
	HRESULT __stdcall QueryInterface(REFIID riid, LPVOID* ppvObj);
	ULONG __stdcall Release();

	/* IDirect3D8 methods */
	HRESULT __stdcall CreateDevice(
		UINT Adapter,
		D3DDEVTYPE DeviceType,
		HWND  hFocusWindow,
		DWORD BehaviorFlags,
		D3DPRESENT_PARAMETERS* pPresentationParameters,
		IDirect3DDevice8** ppReturnedDeviceInterface
		);
	HRESULT __stdcall EnumAdapterModes(UINT Adapter, UINT Mode, D3DDISPLAYMODE* pMode);
	UINT __stdcall GetAdapterCount();
	HRESULT __stdcall GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode);
	HRESULT __stdcall GetAdapterIdentifier(UINT Adapter, DWORD Flags,
		D3DADAPTER_IDENTIFIER8* pIdentifier);
	UINT __stdcall GetAdapterModeCount(UINT Adapter);
	HMONITOR __stdcall GetAdapterMonitor(UINT Adapter);
	HRESULT __stdcall GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS8* pCaps);
	HRESULT __stdcall RegisterSoftwareDevice(void* pInitializeFunction);
	HRESULT __stdcall CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType,
		D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat,
		D3DFORMAT DepthStencilFormat);
	HRESULT __stdcall CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType,
		D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType,
		D3DFORMAT CheckFormat);
	HRESULT __stdcall CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType,
		D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType
		);
	HRESULT __stdcall CheckDeviceType(UINT Adapter, D3DDEVTYPE CheckType,
		D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL Windowed);
};

