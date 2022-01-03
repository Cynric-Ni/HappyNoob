#include "stdafx.h"
#include "Test.h"

typedef  int (WINAPI * SendCmd)(int Add_num);

CTest::CTest(void)
{

}


CTest::~CTest(void)
{
}

int CTest::Testcall(SendCmd Sd,int add_num)
{
	return Sd(add_num);
}
