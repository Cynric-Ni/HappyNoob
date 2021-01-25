#pragma once
typedef  int (WINAPI* SendCmd)(int Add_num);
class CTest
{
public:

	CTest(void);
	~CTest(void);
	int a;
	int  Testcall(SendCmd Sd,int add_num);
};

