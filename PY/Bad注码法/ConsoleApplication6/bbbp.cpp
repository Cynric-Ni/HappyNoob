#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "_bbbp_h.h"
#define random(x) (rand()%x)
int jp, jb,lb;
int loop;                           //�غ�ͳ��
int vloop, bloop;                   //�غ���Ӯ
//int thirbp;                       //BBBPͳ��
int F;                     //�����
int i = 0;
double M = 400;                  //Ǯ
bool lz;                 //�Ƿ���Ҫ����
int lzs;
int bz = 0;                      //����
//bool Pthirbp;
bool ds = 0;                                   //0�ǵ���1��˫��
double peilv = 1.98;

using namespace std;




bool jsbp(int f)                            //0�ǵ���1��˫��
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
	cout << "��ʼ��ע1��" << endl;
	loop++;
    M-=1;
	F=random(10);
	i++;
	cout << "�������:" << F << endl;
	
	if (jsbp(F)==ds)
	{
		cout << "�н�" << endl;
		M+=(1*peilv);
		vloop++;
		lz = 0;
		bz = 0;
		cout << "Ǯ��" << M << endl;
		return M;

	}
	else
	{
		cout << "A1��1��û��" << endl;
		cout << "Ǯ��" << M << endl;
		bz++;
		return A2();
	}
	
};

  double A2()
{
	cout << "A��2����ע2��" << endl;
	M-=2;
	F = random(10);
	i++;
	cout << "�������:" << F << endl;
	if (jsbp(F) == ds)
	{
		cout << "�н�" << endl;
		M += (2 * peilv);
		cout << "Ǯ��" << M << endl;
		vloop++;
		lz = 0;
		lb = 0;
		
		return M;
	}
	else
	{
		cout << "A��2��û��" << endl;
		bz++;
		return A3();

	}
};

  double   A3()
{
	cout << "A��3����ע4��" << endl;
	M-=4;
	F = random(10);
	i++;
	cout << "�������" << F << endl;
	if (jsbp(F) == ds)
	{
		cout << "�н�" << endl;
		bz = 0;
		lz = 0;
		lb = 0;
		M +=(4 * peilv);
		cout << "Ǯ��" << M << endl;
		return M;
	}
	else
	{
		cout << "A��3��û��" << endl;
		cout << "Ǯ��" << M << endl;
		bz++;
		lz = 1;
		return B1();

	}
};

  double  B1()
{
	if (bz == 3)
		forxunh();

	     cout << "B��1�ο�ʼ��ע6��" << endl;
	     M-=6;
	     F = random(10);
	     i++;
	     cout << "B��1�ο������" << F << endl;
		 if (jsbp(F) == ds)
	     {
		  cout << "�н�" << endl;
		  M +=(6 * peilv);
		  if (lz)
		  {
			  bz=0;
			  cout << "Ǯ��" << M << endl;
			  return B2();

		  }
		  else
		  {
			  lz = 0;
			  vloop++;
			  cout << "Ǯ��" << M << endl;
			  return M;
		  }
     	 } 
	   else
	   {
		  cout << "b��1��û��׼��������" << endl;
		  cout << "Ǯ��" << M << endl;
		  return C1();
	    }
};

  double  B2()
{
	cout << "B��2����ע2��" << endl;
	M =M- 2;
	F = random(10);
	if (jsbp(F) == ds)
	{
		cout << "�н�" << endl;
		M = M+(2 * peilv);
		vloop++;
		lz = 0;
		lb = 0;
		bz = 0;
		cout << "Ǯ��" << M << endl;
        return M;
	}
	else
	{
		bz++;
		cout << "B��2��û��" << endl;
		return B3();
	}
};

  double  B3()
{
	cout << "B�ڵ�3����ע4��" << endl;
	M-= 4;
	F = random(10);
	if (jsbp(F) == ds)
	{
		cout << "�н�" << endl;
		M +=(4 * peilv);
		vloop++;
		lz = 0;
		lb = 0;
		bz = 0;
		cout << "Ǯ��" << M << endl;
		return M;
	}
	else
	{
		bz++;
		cout << "B��3��û��" << endl;
		return B1();
	}
};

  double  C1()
{
	if (bz == 3)
		forxunh();
	cout << "C��1����ע11��" << endl;
	M-= 11;
	F = random(10);
	i++;
	cout << "c��1�ο������" << F << endl;
	if (jsbp(F) == ds)
	{
		cout << "�н�" << endl;
		M +=(11 * peilv);
		if (lz == 1)
		{
			bz = 0;
			cout << "Ǯ��" << M << endl;
			return C2();
		}
		else
		{
			lz = 0;
			vloop++;
			cout << "Ǯ��" << M << endl;
			return M;
		}
	}
	else
	{
		cout << "c1��1��û��" << endl;
		return D1();
	}
};

  double   C2()
{
	cout << "C��2����ע3��" << endl;
	M-= 3;
	F = random(10);
	if (jsbp(F) == ds)
	{
		cout << "�н�" << endl;
		M +=(3 * peilv);
		vloop++;
		lz = 0;
		lb = 0;
		bz = 0;
		cout << "Ǯ��" << M << endl;
		return M;
	}
	else
	{
		bz++;
		cout << "Ǯ��" << M << endl;
		return C3();
	}
};

  double C3()
{
	cout << "C��3����ע4��" << endl;
	M -= 6;
	F = random(10);
	if (jsbp(F) == ds)
	{
		cout << "�н�" << endl;
		M +=(6 * peilv);
		vloop++;
		lz = 0;
		lb = 0;
		bz = 0;
		cout << "Ǯ��" << M << endl;
		return M;
	}
	else
	{
		bz++;
		cout << "C��3��û��" << endl;
		cout << "Ǯ��" << M << endl;
		return C1();
	}
};
  
  double  D1()
  {
	  if (bz == 3)
		  forxunh();

	  cout << "C��1�ο�ʼ��ע19��" << endl;
	  M -= 19;
	  F = random(10);
	  i++;
	  cout << "��1�ο������" << F << endl;
	  if (jsbp(F) == ds)
	  {
		  cout << "�н�" << endl;
		  M += (19 * peilv);
		  if (lz)
		  {
			  bz = 0;
			  cout << "Ǯ��" << M << endl;
			  return D2();

		  }
		  else
		  {
			  lz = 0;
			  vloop++;
			  cout << "Ǯ��" << M << endl;
			  return M;
		  }
	  }
	  else
	  {
		  cout << "Cû��׼����D��" << endl;
		  cout << "Ǯ��" << M << endl;
		  return E1();
	  }
  };

  double  D2()
  {
	  cout << "D��2����ע6��" << endl;
	  M -= 6;
	  F = random(10);
	  if (jsbp(F) == ds)
	  {
		  cout << "�н�" << endl;
		  M += (6 * peilv);
		  vloop++;
		  lz = 0;
		  lb = 0;
		  bz = 0;
		  cout << "Ǯ��" << M << endl;
		  return M;
	  }
	  else
	  {
		  bz++;
		  cout << "D��2��û��" << endl;
		  cout << "Ǯ��" << M << endl;
		  return D3();
	  }
  };

  double  D3()
  {
	  cout << "D��3����ע4��" << endl;
	  M -= 4;
	  F = random(10);
	  if (jsbp(F) == ds)
	  {
		  cout << "��D����3����ע�н�" << endl;
		  M += (4 * peilv);
		  vloop++;
		  lz = 0;
		  lb = 0;
		  bz = 0;
		  cout << "Ǯ��" << M << endl;
		  return M;
	  }
	  else
	  {
		  bz++;
		  cout << "D��3��û��" << endl;
		  cout << "Ǯ��" << M << endl;
		  return D1();
	  }
  };


  double  E1()
  {
	  if (bz == 3)
		  forxunh();

	  cout << "��E����ʼ��ע19��" << endl;
	  M -= 33;
	  F = random(10);
	  i++;
	  cout << "��E���������" << F << endl;
	  if (jsbp(F) == ds)
	  {
		  cout << "��E��19�н�" << endl;
		  M += (33 * peilv);
		  if (lz)
		  {
			  bz = 0;
			  cout << "Ǯ��" << M << endl;
			  return E2();

		  }
		  else
		  {
			  lz = 0;
			  vloop++;
			  cout << "Ǯ��" << M << endl;
			  return M;
		  }
	  }
	  else
	  {
		  cout << "E��1��û��" << endl;
		  cout << "Ǯ��" << M << endl;
		  return F1();
	  }
  };

  double   E2()
  {
	  cout << "��������3����ע11��" << endl;
	  M -= 11;
	  F = random(10);
	  if (jsbp(F) == ds)
	  {
		  cout << "��������2����ע�н�" << endl;
		  M += (11 * peilv);
		  vloop++;
		  lz = 0;
		  lb = 0;
		  bz = 0;
		  cout << "Ǯ��" << M << endl;
		  return M;
	  }
	  else
	  {
		  bz++;
		  cout << "E��2��û��" << endl;
		  cout << "Ǯ��" << M << endl;
		  return E3();
	  }
  };

  double   E3()
  {
	  cout << "��E����3����ע4��" << endl;
	  M -= 33;
	  F = random(10);
	  if (jsbp(F) == ds)
	  {
		  cout << "��E����3����ע�н�" << endl;
		  M += (33 * peilv);
		  vloop++;
		  lz = 0;
		  lb = 0;
		  bz = 0;
		  cout << "Ǯ��" << M << endl;
		  return M;
	  }
	  else
	  {
		  bz++;
		  cout << "Ǯ��" << M << endl;
		  return E1();
	  }
  };

  double F1()
  {
	  if (bz == 3)
		  forxunh();

	  cout << "F��1�ο�ʼ��ע57��" << endl;
	  M -= 57;
	  F = random(10);
	  i++;
	  cout << "F��1�ο������" << F << endl;
	  if (jsbp(F) == ds)
	  {
		  cout << "�н�" << endl;
		  M = M + (57 * peilv);
		  if (lz)
		  {
			  bz = 0;
			  cout << "Ǯ��" << M << endl;
			  return F2();

		  }
		  else
		  {
			  lz = 0;
			  vloop++;
			  cout << "Ǯ��" << M << endl;
			  return M;
		  }
	  }
	  else
	  {
		  cout << "F��1��û��" << endl;
		  return G1();
	  }
  };

  double  F2()
  {
	  cout << "��������3����ע19��" << endl;
	  M -= 19;
	  F = random(10);
	  if (jsbp(F) == ds)
	  {
		  cout << "��������2����ע�н�" << endl;
		  M += (19 * peilv);
		  vloop++;
		  lz = 0;
		  lb = 0;
		  bz = 0;
		  cout << "Ǯ��" << M << endl;
		  return M;
	  }
	  else
	  {
		  bz++;
		  cout << "F2��2��û��" << endl;
		  cout << "Ǯ��" << M << endl;
		  return F3();
	  }
  };

  double   F3()
  {
	  cout << "F��3����ע33��" << endl;
	  M -=33;
	  F = random(10);
	  if (jsbp(F) == ds)
	  {
		  cout << "F��3����ע�н�" << endl;
		  M+= (33 * peilv);
		  vloop++;
		  lz = 0;
		  lb = 0;
		  bz = 0;
		  cout << "Ǯ��" << M << endl;
		  return M;
	  }
	  else
	  {
		  bz++;
		  cout << "F3û��" << endl;
		  cout << "Ǯ��" << M << endl;
		  return F1();
	  }
  };

  double   G1()
  {
	  if (bz == 3)
		  forxunh();

	  cout << "G1��1�ο�ʼ��ע100��" << endl;
	  M -= 100;
	  F = random(10);
	  i++;
	  cout << "G��1�ο������" << F << endl;
	  if (jsbp(F) == ds)
	  {
		  cout << "��E��19�н�" << endl;
		  M +=(100 * peilv);
		  if (lz)
		  {
			  bz = 0;
			  cout << "Ǯ��" << M << endl;
			  return F2();

		  }
		  else
		  {
			  lz = 0;
			  vloop++;
			  cout << "Ǯ��" << M << endl;
			  return M;
		  }
	  }
	  else
	  {
		  cout << "�غ���" << endl;
		  bloop++;
		  cout << "Ǯ��" << M << endl;
		  return M;
	  }
  };

  double  G2()
  {
	  cout << "��������3����ע34��" << endl;
	  M -= 34;
	  F = random(10);
	  if (jsbp(F) == ds)
	  {
		  cout << "�н�" << endl;
		  M += (34 * peilv);
		  vloop++;
		  lz = 0;
		  lb = 0;
		  bz = 0;
		  cout << "Ǯ��" << M << endl;
		  return M;
	  }
	  else
	  {
		  bz++;
		  cout << "G2û��" << endl;
		  cout << "Ǯ��" << M << endl;
		  return G3();
	  }
  };

  double  G3()
  {
	  cout << "G��3����ע66��" << endl;
	  M -= 66;
	  F = random(10);
	  if (jsbp(F) == ds)
	  {
		  cout << "G��3����ע�н�" << endl;
		  M += (66* peilv);
		  vloop++;
		  lz = 0;
		  lb = 0;
		  bz = 0;
		  cout << "Ǯ��" << M << endl;
		  return M;
	  }
	  else
	  {
		  cout << "G��3��û��" << endl;
		  bz=0;
		  cout << "Ǯ��" << M << endl;
		  return G1();
	  }
  };