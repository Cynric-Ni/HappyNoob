#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "_bbbp_h.h"
#define random(x) (rand()%x)
int jp, jb,lb;
int loop;                           //回合统计
int vloop, bloop;                   //回合输赢
//int thirbp;                       //BBBP统计
int F;                     //随机数
int i = 0;
double M = 400;                  //钱
bool lz;                 //是否需要连中
int lzs;
int bz = 0;                      //不中
//bool Pthirbp;
bool ds = 0;                                   //0是单，1是双。
double peilv = 1.98;

using namespace std;




bool jsbp(int f)                            //0是单，1是双。
{
	f = F;
	if (f != 0)
	{
		if (f % 2 == 0)
		{
			jp++;
			return 1;
		}
		else
		{
			jb++;
			lb++;
			return 0;
		}
	}
	else
	{
		jp++;
		return 1;
	}
};

void forxunh()
{   
	for (int ls=0,flag=0; i < 2000; i++)
	{   
		F = random(10);
		jsbp(F);
		cout<<i <<"   "<< F << endl;
		if (F % 2 == 0)
		{
			ls++;
		}
		else
		{
			ls = 0;
		}

		while (ls >= 3)
		{

			F = random(10);
			jsbp(F);
			cout << i <<"   "<< F << endl;
			i++;
			if (F % 2 == 0)
				flag = 0;
			else
			{
				flag = 1;
				ls = 0;
			}
		}

		if (flag==1)
		  break;

	}
};




  double  A1()
{
	forxunh();
	cout << "开始下注1码" << endl;
	loop++;
    M-=1;
	F=random(10);
	i++;
	cout << "开奖结果:" << F << endl;
	
	if (jsbp(F)==ds)
	{
		cout << "中奖" << endl;
		M+=(1*peilv);
		vloop++;
		lz = 0;
		bz = 0;
		cout << "钱数" << M << endl;
		return M;

	}
	else
	{
		cout << "A1第1次没中" << endl;
		cout << "钱数" << M << endl;
		bz++;
		return A2();
	}
	
};

  double A2()
{
	cout << "A第2次下注2码" << endl;
	M-=2;
	F = random(10);
	i++;
	cout << "开奖结果:" << F << endl;
	if (jsbp(F) == ds)
	{
		cout << "中奖" << endl;
		M += (2 * peilv);
		cout << "钱数" << M << endl;
		vloop++;
		lz = 0;
		lb = 0;
		
		return M;
	}
	else
	{
		cout << "A第2次没中" << endl;
		bz++;
		return A3();

	}
};

  double   A3()
{
	cout << "A第3次下注4码" << endl;
	M-=4;
	F = random(10);
	i++;
	cout << "开奖结果" << F << endl;
	if (jsbp(F) == ds)
	{
		cout << "中奖" << endl;
		bz = 0;
		lz = 0;
		lb = 0;
		M +=(4 * peilv);
		cout << "钱数" << M << endl;
		return M;
	}
	else
	{
		cout << "A第3次没中" << endl;
		cout << "钱数" << M << endl;
		bz++;
		lz = 1;
		return B1();

	}
};

  double  B1()
{
	if (bz == 3)
		forxunh();

	     cout << "B第1次开始下注6码" << endl;
	     M-=6;
	     F = random(10);
	     i++;
	     cout << "B第1次开奖结果" << F << endl;
		 if (jsbp(F) == ds)
	     {
		  cout << "中奖" << endl;
		  M +=(6 * peilv);
		  if (lz)
		  {
			  bz=0;
			  cout << "钱数" << M << endl;
			  return B2();

		  }
		  else
		  {
			  lz = 0;
			  vloop++;
			  cout << "钱数" << M << endl;
			  return M;
		  }
     	 } 
	   else
	   {
		  cout << "b第1次没中准备第三档" << endl;
		  cout << "钱数" << M << endl;
		  return C1();
	    }
};

  double  B2()
{
	cout << "B第2次下注2码" << endl;
	M =M- 2;
	F = random(10);
	if (jsbp(F) == ds)
	{
		cout << "中奖" << endl;
		M = M+(2 * peilv);
		vloop++;
		lz = 0;
		lb = 0;
		bz = 0;
		cout << "钱数" << M << endl;
        return M;
	}
	else
	{
		bz++;
		cout << "B第2次没中" << endl;
		return B3();
	}
};

  double  B3()
{
	cout << "B第第3次下注4码" << endl;
	M-= 4;
	F = random(10);
	if (jsbp(F) == ds)
	{
		cout << "中奖" << endl;
		M +=(4 * peilv);
		vloop++;
		lz = 0;
		lb = 0;
		bz = 0;
		cout << "钱数" << M << endl;
		return M;
	}
	else
	{
		bz++;
		cout << "B第3次没中" << endl;
		return B1();
	}
};

  double  C1()
{
	if (bz == 3)
		forxunh();
	cout << "C第1次下注11码" << endl;
	M-= 11;
	F = random(10);
	i++;
	cout << "c第1次开奖结果" << F << endl;
	if (jsbp(F) == ds)
	{
		cout << "中奖" << endl;
		M +=(11 * peilv);
		if (lz == 1)
		{
			bz = 0;
			cout << "钱数" << M << endl;
			return C2();
		}
		else
		{
			lz = 0;
			vloop++;
			cout << "钱数" << M << endl;
			return M;
		}
	}
	else
	{
		cout << "c1第1次没中" << endl;
		return D1();
	}
};

  double   C2()
{
	cout << "C第2次下注3码" << endl;
	M-= 3;
	F = random(10);
	if (jsbp(F) == ds)
	{
		cout << "中奖" << endl;
		M +=(3 * peilv);
		vloop++;
		lz = 0;
		lb = 0;
		bz = 0;
		cout << "钱数" << M << endl;
		return M;
	}
	else
	{
		bz++;
		cout << "钱数" << M << endl;
		return C3();
	}
};

  double C3()
{
	cout << "C第3次下注4码" << endl;
	M -= 6;
	F = random(10);
	if (jsbp(F) == ds)
	{
		cout << "中奖" << endl;
		M +=(6 * peilv);
		vloop++;
		lz = 0;
		lb = 0;
		bz = 0;
		cout << "钱数" << M << endl;
		return M;
	}
	else
	{
		bz++;
		cout << "C第3次没中" << endl;
		cout << "钱数" << M << endl;
		return C1();
	}
};
  
  double  D1()
  {
	  if (bz == 3)
		  forxunh();

	  cout << "C第1次开始下注19码" << endl;
	  M -= 19;
	  F = random(10);
	  i++;
	  cout << "第1次开奖结果" << F << endl;
	  if (jsbp(F) == ds)
	  {
		  cout << "中奖" << endl;
		  M += (19 * peilv);
		  if (lz)
		  {
			  bz = 0;
			  cout << "钱数" << M << endl;
			  return D2();

		  }
		  else
		  {
			  lz = 0;
			  vloop++;
			  cout << "钱数" << M << endl;
			  return M;
		  }
	  }
	  else
	  {
		  cout << "C没中准备第D档" << endl;
		  cout << "钱数" << M << endl;
		  return E1();
	  }
  };

  double  D2()
  {
	  cout << "D第2次下注6码" << endl;
	  M -= 6;
	  F = random(10);
	  if (jsbp(F) == ds)
	  {
		  cout << "中奖" << endl;
		  M += (6 * peilv);
		  vloop++;
		  lz = 0;
		  lb = 0;
		  bz = 0;
		  cout << "钱数" << M << endl;
		  return M;
	  }
	  else
	  {
		  bz++;
		  cout << "D第2次没中" << endl;
		  cout << "钱数" << M << endl;
		  return D3();
	  }
  };

  double  D3()
  {
	  cout << "D第3次下注4码" << endl;
	  M -= 4;
	  F = random(10);
	  if (jsbp(F) == ds)
	  {
		  cout << "第D档第3次下注中奖" << endl;
		  M += (4 * peilv);
		  vloop++;
		  lz = 0;
		  lb = 0;
		  bz = 0;
		  cout << "钱数" << M << endl;
		  return M;
	  }
	  else
	  {
		  bz++;
		  cout << "D第3次没中" << endl;
		  cout << "钱数" << M << endl;
		  return D1();
	  }
  };


  double  E1()
  {
	  if (bz == 3)
		  forxunh();

	  cout << "第E档开始下注19码" << endl;
	  M -= 33;
	  F = random(10);
	  i++;
	  cout << "第E档开奖结果" << F << endl;
	  if (jsbp(F) == ds)
	  {
		  cout << "第E档19中奖" << endl;
		  M += (33 * peilv);
		  if (lz)
		  {
			  bz = 0;
			  cout << "钱数" << M << endl;
			  return E2();

		  }
		  else
		  {
			  lz = 0;
			  vloop++;
			  cout << "钱数" << M << endl;
			  return M;
		  }
	  }
	  else
	  {
		  cout << "E第1次没中" << endl;
		  cout << "钱数" << M << endl;
		  return F1();
	  }
  };

  double   E2()
  {
	  cout << "第三档第3次下注11码" << endl;
	  M -= 11;
	  F = random(10);
	  if (jsbp(F) == ds)
	  {
		  cout << "第三档第2次下注中奖" << endl;
		  M += (11 * peilv);
		  vloop++;
		  lz = 0;
		  lb = 0;
		  bz = 0;
		  cout << "钱数" << M << endl;
		  return M;
	  }
	  else
	  {
		  bz++;
		  cout << "E第2次没中" << endl;
		  cout << "钱数" << M << endl;
		  return E3();
	  }
  };

  double   E3()
  {
	  cout << "第E档第3次下注4码" << endl;
	  M -= 33;
	  F = random(10);
	  if (jsbp(F) == ds)
	  {
		  cout << "第E档第3次下注中奖" << endl;
		  M += (33 * peilv);
		  vloop++;
		  lz = 0;
		  lb = 0;
		  bz = 0;
		  cout << "钱数" << M << endl;
		  return M;
	  }
	  else
	  {
		  bz++;
		  cout << "钱数" << M << endl;
		  return E1();
	  }
  };

  double F1()
  {
	  if (bz == 3)
		  forxunh();

	  cout << "F第1次开始下注57码" << endl;
	  M -= 57;
	  F = random(10);
	  i++;
	  cout << "F第1次开奖结果" << F << endl;
	  if (jsbp(F) == ds)
	  {
		  cout << "中奖" << endl;
		  M = M + (57 * peilv);
		  if (lz)
		  {
			  bz = 0;
			  cout << "钱数" << M << endl;
			  return F2();

		  }
		  else
		  {
			  lz = 0;
			  vloop++;
			  cout << "钱数" << M << endl;
			  return M;
		  }
	  }
	  else
	  {
		  cout << "F第1次没中" << endl;
		  return G1();
	  }
  };

  double  F2()
  {
	  cout << "第三档第3次下注19码" << endl;
	  M -= 19;
	  F = random(10);
	  if (jsbp(F) == ds)
	  {
		  cout << "第三档第2次下注中奖" << endl;
		  M += (19 * peilv);
		  vloop++;
		  lz = 0;
		  lb = 0;
		  bz = 0;
		  cout << "钱数" << M << endl;
		  return M;
	  }
	  else
	  {
		  bz++;
		  cout << "F2第2次没中" << endl;
		  cout << "钱数" << M << endl;
		  return F3();
	  }
  };

  double   F3()
  {
	  cout << "F第3次下注33码" << endl;
	  M -=33;
	  F = random(10);
	  if (jsbp(F) == ds)
	  {
		  cout << "F第3次下注中奖" << endl;
		  M+= (33 * peilv);
		  vloop++;
		  lz = 0;
		  lb = 0;
		  bz = 0;
		  cout << "钱数" << M << endl;
		  return M;
	  }
	  else
	  {
		  bz++;
		  cout << "F3没中" << endl;
		  cout << "钱数" << M << endl;
		  return F1();
	  }
  };

  double   G1()
  {
	  if (bz == 3)
		  forxunh();

	  cout << "G1第1次开始下注100码" << endl;
	  M -= 100;
	  F = random(10);
	  i++;
	  cout << "G第1次开奖结果" << F << endl;
	  if (jsbp(F) == ds)
	  {
		  cout << "第E档19中奖" << endl;
		  M +=(100 * peilv);
		  if (lz)
		  {
			  bz = 0;
			  cout << "钱数" << M << endl;
			  return F2();

		  }
		  else
		  {
			  lz = 0;
			  vloop++;
			  cout << "钱数" << M << endl;
			  return M;
		  }
	  }
	  else
	  {
		  cout << "回合输" << endl;
		  bloop++;
		  cout << "钱数" << M << endl;
		  return M;
	  }
  };

  double  G2()
  {
	  cout << "第三档第3次下注34码" << endl;
	  M -= 34;
	  F = random(10);
	  if (jsbp(F) == ds)
	  {
		  cout << "中奖" << endl;
		  M += (34 * peilv);
		  vloop++;
		  lz = 0;
		  lb = 0;
		  bz = 0;
		  cout << "钱数" << M << endl;
		  return M;
	  }
	  else
	  {
		  bz++;
		  cout << "G2没中" << endl;
		  cout << "钱数" << M << endl;
		  return G3();
	  }
  };

  double  G3()
  {
	  cout << "G第3次下注66码" << endl;
	  M -= 66;
	  F = random(10);
	  if (jsbp(F) == ds)
	  {
		  cout << "G第3次下注中奖" << endl;
		  M += (66* peilv);
		  vloop++;
		  lz = 0;
		  lb = 0;
		  bz = 0;
		  cout << "钱数" << M << endl;
		  return M;
	  }
	  else
	  {
		  cout << "G第3次没中" << endl;
		  bz=0;
		  cout << "钱数" << M << endl;
		  return G1();
	  }
  };