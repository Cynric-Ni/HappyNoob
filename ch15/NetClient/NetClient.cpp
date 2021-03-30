// NetClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")

int main()
{
   //加载套接字库
	WORD  wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return -1;
	}
  //创建套接字
	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN addrSrv;
	inet_pton(AF_INET, "127.0.0.1", &addrSrv.sin_addr);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	char recvBuf[100];
	char sendBuf[100];
	char tempBuf[200];
	char str[INET_ADDRSTRLEN];

	int len = sizeof(SOCKADDR);

	while (1) {
	 //发送数据
		printf("Please input data:\n");
		gets_s(sendBuf);
		sendto(sockClient, sendBuf, strlen(sendBuf) + 1, 0,
			(SOCKADDR*)&addrSrv, len);
	 //等待并接收数据
		recvfrom(sockClient, recvBuf, 100, 0, (SOCKADDR*)&addrSrv, &len);
		if ('q' == recvBuf[0]) {
			sendto(sockClient, "q", strlen("q") + 1, 0,
				(SOCKADDR*)&addrSrv, len);
			printf("Chat end!\n");
			break;
		}
		sprintf_s(tempBuf, 200, "%s say: %s",
			inet_ntop(AF_INET, &addrSrv.sin_addr, str, sizeof(str)), recvBuf);
		printf("%s\n", tempBuf);
	}
	//关闭套接字
	closesocket(sockClient);
	WSACleanup();

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
