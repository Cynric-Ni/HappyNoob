// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#define DLL1_API _declspec(dllexport)
#include "Dll1.h"
#include <tchar.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

//_declspec(dllexport) int add(int a, int b)
 int add(int a, int b) {
    return a + b;
}

 //_declspec(dllexport) int subtract(int a, int b)
 int subtract(int a, int b) {
    return a - b;
}

 void Point::output(int x, int y)
 {
     //返回调用者进程当前正在使用的那个窗口的句柄
     HWND hwnd = GetForegroundWindow();
     //获取DC
     HDC hdc = GetDC(hwnd);
     TCHAR buf[20] = { 0 };

     _stprintf_s(buf,L"x=%d,y=%d",x,y);
     //输出坐标
     TextOut(hdc, 0, 0, buf, _tcslen(buf));
     //释放DC
     ReleaseDC(hwnd, hdc);

 }