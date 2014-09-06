/*
Direct3D8 shim to replace fullscreen with windowed mode.
Confirmed to be working with Vice City
by E.Sandberg 2014

This code is released into the public domain.
Read LICENSE.TXT for license information.
*/

#include "FakeDirect3D8.h"

FakeDirect3D8::FakeDirect3D8(IDirect3D8* realD3D8){
	this->realD3D8 = realD3D8;
}

FakeDirect3D8::~FakeDirect3D8(){

}

/* IUnknown implementations */
ULONG __stdcall FakeDirect3D8::AddRef(){
	return realD3D8->AddRef();
}
HRESULT __stdcall FakeDirect3D8::QueryInterface(REFIID riid, LPVOID* ppvObj){
	return realD3D8->QueryInterface(
		riid,
		ppvObj);
}
ULONG __stdcall FakeDirect3D8::Release(){
	//return realD3D8->Release();
	return 0;
}

HRESULT __stdcall FakeDirect3D8::CreateDevice(
	UINT Adapter,
	D3DDEVTYPE DeviceType,
	HWND  hFocusWindow,
	DWORD BehaviorFlags,
	D3DPRESENT_PARAMETERS* pPresentationParameters,
	IDirect3DDevice8** ppReturnedDeviceInterface
	) {
	realD3D8->CreateDevice(
		Adapter,
		DeviceType,
		hFocusWindow,
		BehaviorFlags,
		pPresentationParameters,
		ppReturnedDeviceInterface);

	SetWindowLongPtr(pPresentationParameters->hDeviceWindow, GWL_STYLE, (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX));
	SetWindowPos(pPresentationParameters->hDeviceWindow, HWND_NOTOPMOST,
		0, 0,
		pPresentationParameters->BackBufferWidth,
		pPresentationParameters->BackBufferHeight,
		SWP_SHOWWINDOW);

	pPresentationParameters->Windowed = true;
	HRESULT result = (*ppReturnedDeviceInterface)->Reset(pPresentationParameters);
	UpdateWindow(pPresentationParameters->hDeviceWindow);
	return result;
}
HRESULT __stdcall FakeDirect3D8::EnumAdapterModes(UINT Adapter, UINT Mode, D3DDISPLAYMODE* pMode){
	return realD3D8->EnumAdapterModes(
		Adapter,
		Mode,
		pMode);
}
UINT __stdcall FakeDirect3D8::GetAdapterCount(){
	return realD3D8->GetAdapterCount();
}
HRESULT __stdcall FakeDirect3D8::GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode){
	return realD3D8->GetAdapterDisplayMode(
		Adapter,
		pMode);
}
HRESULT __stdcall FakeDirect3D8::GetAdapterIdentifier(UINT Adapter, DWORD Flags,
	D3DADAPTER_IDENTIFIER8* pIdentifier){
	return realD3D8->GetAdapterIdentifier(
		Adapter,
		Flags,
		pIdentifier);
}
UINT __stdcall FakeDirect3D8::GetAdapterModeCount(UINT Adapter){
	return realD3D8->GetAdapterModeCount(Adapter);
}
HMONITOR __stdcall FakeDirect3D8::GetAdapterMonitor(UINT Adapter){
	return realD3D8->GetAdapterMonitor(Adapter);
}
HRESULT __stdcall FakeDirect3D8::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS8* pCaps){
	return realD3D8->GetDeviceCaps(
		Adapter,
		DeviceType,
		pCaps);
}
HRESULT __stdcall FakeDirect3D8::RegisterSoftwareDevice(void* pInitializeFunction){
	return realD3D8->RegisterSoftwareDevice(pInitializeFunction);
}
HRESULT __stdcall FakeDirect3D8::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType,
	D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat,
	D3DFORMAT DepthStencilFormat){
	return realD3D8->CheckDepthStencilMatch(
		Adapter,
		DeviceType,
		AdapterFormat,
		RenderTargetFormat,
		DepthStencilFormat);
}
HRESULT __stdcall FakeDirect3D8::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType,
	D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType,
	D3DFORMAT CheckFormat){
	return realD3D8->CheckDeviceFormat(
		Adapter,
		DeviceType,
		AdapterFormat,
		Usage,
		RType,
		CheckFormat);
}
HRESULT __stdcall FakeDirect3D8::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType,
	D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType
	){
	return realD3D8->CheckDeviceMultiSampleType(
		Adapter,
		DeviceType,
		SurfaceFormat,
		Windowed,
		MultiSampleType);
}
HRESULT __stdcall FakeDirect3D8::CheckDeviceType(UINT Adapter, D3DDEVTYPE CheckType,
	D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL Windowed){
	return realD3D8->CheckDeviceType(
		Adapter,
		CheckType,
		DisplayFormat,
		BackBufferFormat,
		Windowed);
}