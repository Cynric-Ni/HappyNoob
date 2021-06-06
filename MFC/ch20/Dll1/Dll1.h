#pragma once

#ifdef DLL1_API
#else
#define DLL1_API _declspec(dllimport)
#endif

DLL1_API int add(int a, int b);
DLL1_API int subtract(int a, int b);

class DLL1_API Point
{
public:
	void output(int x, int y);
};

//_declspec(dllimport) int add(int a, int b);
//_declspec(dllimport) int subtract(int a, int b);