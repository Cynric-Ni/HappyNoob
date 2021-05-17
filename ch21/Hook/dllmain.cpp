// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <Windows.h>
#include <stdio.h>
#include <TlHelp32.h>
#include <debugapi.h>

HINSTANCE g_hInst;
HHOOK g_hMouse = NULL;
HHOOK g_hKeyboard = NULL;
HWND g_hWnd;
_declspec(dllexport) void SetHook(HWND hwnd);
_declspec(dllexport) void Show();

void Show() {
   
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    return 1;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (VK_F4 == wParam) {
        
        MessageBox(NULL, TEXT("111"), TEXT("222"),0);
        //OutputDebugString(L"退出");
    }
    if (VK_F2 == wParam) {
       
        SendMessage(g_hWnd, WM_CLOSE, 0, 0);
        UnhookWindowsHookEx(g_hMouse);
        UnhookWindowsHookEx(g_hKeyboard);
    }
    return 1;
}

void SetHook(HWND hwnd) {
    g_hWnd = hwnd;
    //g_hMouse = SetWindowsHookEx(WH_MOUSE, MouseProc, g_hInst, 0);
    g_hKeyboard = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, g_hInst, 0);
}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    g_hInst = hModule;
   /* switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }*/
   

    return TRUE;
}

