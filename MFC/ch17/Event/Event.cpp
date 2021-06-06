// Event.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

using std::cout;
DWORD WINAPI Fun1Proc(LPVOID lpParameter);
DWORD WINAPI Fun2Proc(LPVOID lpParameter);

int tickets = 100;
HANDLE g_hEvent;

int main()
{
    HANDLE hThread1;
    HANDLE hThread2;
    //创建人工重置事件内核对象
    g_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    SetEvent(g_hEvent);
    //创建线程
    hThread1 = CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
    hThread2 = CreateThread(NULL, 0, Fun2Proc, NULL, 0, NULL);
    CloseHandle(hThread1);
    CloseHandle(hThread2);

    //让主线程睡眠4秒
    Sleep(4000);
    //关闭事件对象句柄
    CloseHandle(g_hEvent);
    return 0;
}


//线程1的入口函数
DWORD WINAPI Fun1Proc(LPVOID lpParameter) {
    char buf[100] = { 0 };
    while (TRUE) {
        //请求事件对象
        WaitForSingleObject(g_hEvent, INFINITE);
        if (tickets > 0) {
            sprintf_s(buf, "thread1 sell ticket: %d\n", tickets);
            cout << buf;
            tickets--;
            SetEvent(g_hEvent);
        }else{
            SetEvent(g_hEvent);
            break;
        }
    }
    return 0;
}

//线程2的入口函数
DWORD WINAPI Fun2Proc(LPVOID lpParameter) {
    char buf[100] = { 0 };
    while (TRUE) {
        //请求事件对象
        WaitForSingleObject(g_hEvent, INFINITE);
        if (tickets > 0) {
            sprintf_s(buf, "thread2 sell ticket: %d\n", tickets);
            cout << buf;
            tickets--;
            SetEvent(g_hEvent);
        }else{
            SetEvent(g_hEvent);
            break;
        }
    }
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
