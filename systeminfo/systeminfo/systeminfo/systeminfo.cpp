// systeminfo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <atlbase.h>

BOOL GetVersionEx2(LPOSVERSIONINFOW lpVersionInformation)
{
    HMODULE hNtDll = GetModuleHandleW(L"NTDLL"); // 获取ntdll.dll的句柄
    typedef NTSTATUS(NTAPI* tRtlGetVersion)(PRTL_OSVERSIONINFOW povi); // RtlGetVersion的原型
    tRtlGetVersion pRtlGetVersion = NULL;
    if (hNtDll)
    {
        pRtlGetVersion = (tRtlGetVersion)GetProcAddress(hNtDll, "RtlGetVersion"); // 获取RtlGetVersion地址
    }
    if (pRtlGetVersion)
    {
        return pRtlGetVersion((PRTL_OSVERSIONINFOW)lpVersionInformation) >= 0; // 调用RtlGetVersion
    }
    return FALSE;
}
int main()
{
    OSVERSIONINFOEXW ovi = { sizeof ovi };
    GetVersionEx2((LPOSVERSIONINFOW)&ovi);
    printf("使用NTDLL->RtlGetVersion获取的信息：\n");
    printf("dwMajorVersion: %08x %d\n", ovi.dwMajorVersion, ovi.dwMajorVersion);
    printf("dwMinorVersion: %08x %d\n", ovi.dwMinorVersion, ovi.dwMinorVersion);
    printf("dwBuildNumber: %08x %d\n", ovi.dwBuildNumber, ovi.dwBuildNumber);
    printf("dwPlatformID: %08x %d\n", ovi.dwPlatformId, ovi.dwPlatformId);
    printf("szCSDVersion: %s\n", (char*)CW2A(ovi.szCSDVersion, 1));
    printf("wServicePackMajor: %04x %d\n", ovi.wServicePackMajor, ovi.wServicePackMajor);
    printf("wServicePackMinor: %04x %d\n", ovi.wServicePackMinor, ovi.wServicePackMinor);
    printf("wSuitMask: %04x %d\n", ovi.wSuiteMask, ovi.wSuiteMask);
    printf("wProductType: %02x %d\n", ovi.wProductType, ovi.wProductType);
    printf("wReserved: %02x %d\n", ovi.wReserved, ovi.wReserved);

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
