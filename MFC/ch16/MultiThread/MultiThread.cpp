// MultiThread.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

using std::cout;

//int index = 0;
int tickets = 100;
HANDLE hMutex;
DWORD WINAPI Fun1Proc(
    LPVOID lpParameter //thread data
);
DWORD WINAPI Fun2Proc(
    LPVOID lpParameter
);
int main()
{
    HANDLE hThread1;
    HANDLE hThread2;

    //创建互斥对象
    hMutex = CreateMutex(NULL, FALSE, L"tickets");
    if (hMutex) {
        if (ERROR_ALREADY_EXISTS == GetLastError()) {
            cout << "only one instance can run!\n";
            system("pause");
            return -1;
        }
    }
    //创建线程
    hThread1 = CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
    hThread2 = CreateThread(NULL, 0, Fun2Proc, NULL, 0, NULL);
    CloseHandle(hThread1);
    CloseHandle(hThread2);
  /*  while (index++ < 1000)
    cout << "main thread is running\n";
    //Sleep(10);*/
    Sleep(40000);
    return 0;
}

//线程1的入口函数
DWORD WINAPI Fun1Proc(
    LPVOID lpParameter  // thread data
)
{
 /*   while(index++<1000)
    cout << "thread1 is running\n";*/
   
    char buf[100] = { 0 };
    while (TRUE)
    {
        WaitForSingleObject(hMutex, INFINITE);
        if (tickets > 0) {
            //Sleep(10);
            sprintf_s(buf, "thread1 sell ticket:%d\n", tickets);
            cout << buf;
            tickets--;
            ReleaseMutex(hMutex);
        }else{
            ReleaseMutex(hMutex);
            break;
        }
        //ReleaseMutex(hMutex);
    }
    return 0;
}

//线程2的入口函数
DWORD WINAPI Fun2Proc(
    LPVOID lpParameter
)
{
    char buf[100] = { 0 };
    while (TRUE) {
        WaitForSingleObject(hMutex, INFINITE);
        if (tickets > 0) {
            //Sleep(10);
            sprintf_s(buf, "thread2 sell ticket :%d\n", tickets);
            cout << buf;
            tickets--;
            ReleaseMutex(hMutex);
        }else{
            ReleaseMutex(hMutex);
            break;     
        }
        //ReleaseMutex(hMutex);
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
