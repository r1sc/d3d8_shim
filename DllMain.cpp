/* 
Direct3D8 shim to replace fullscreen with windowed mode.
Confirmed to be working with Vice City
by E.Sandberg 2014

This code is released into the public domain.
Read LICENSE.TXT for license information.
*/
#include <Windows.h>
#include <d3d8.h>
#include "FakeDirect3D8.h"

typedef IDirect3D8* (__stdcall *func_Direct3DCreate8)(UINT);
func_Direct3DCreate8 originalDirect3DCreate8;

IDirect3D8* realD3D8;
IDirect3D8* __stdcall myDirect3DCreate8(UINT SDKVersion){
	realD3D8 = originalDirect3DCreate8(SDKVersion);
	return new FakeDirect3D8(realD3D8);
}

HMODULE dll;
BOOL APIENTRY DllMain(
	HANDLE hModule,	// Handle to DLL module
	DWORD ul_reason_for_call,
	LPVOID lpReserved) // Reserved
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// A process is loading the DLL.
		char dllPath[256];
		GetSystemDirectory(dllPath, 256);
		strcat_s(dllPath, "\\d3d8.dll");
		dll = LoadLibrary(dllPath);
		originalDirect3DCreate8 = (func_Direct3DCreate8)GetProcAddress(dll, "Direct3DCreate8");
		break;
	case DLL_THREAD_ATTACH:
		// A process is creating a new thread.
		break;
	case DLL_THREAD_DETACH:
		// A thread exits normally.
		break;
	case DLL_PROCESS_DETACH:
		// A process unloads the DLL.
		FreeLibrary(dll);
		break;
	}
	return TRUE;
}