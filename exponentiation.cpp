#include<iostream>  
using namespace std;

int yici(int store[], int lenth, int n)
{
	int i = 0, j = 0, jieguo = 0, jinwei1 = 0, jinwei2 = 0, zanshizong = lenth, k = 0, zanshi = lenth;
	int b[1000] = { 0 }, c[9] = { 0 };
	for (i = 0; i<9; i++)
	{
		c[i] = store[999 - i];
	}
	for (k = 1; k<n; k++)
	{
		for (i = 0; i<5; i++)
		{
			for (j = 0; j<zanshi; j++)
			{
				jieguo = store[999 - j] * c[i] + jinwei2;
				jinwei2 = jieguo / 10;
				jieguo = jieguo % 10;
				b[999 - i - j] += jieguo + jinwei1;
				if (b[999 - i - j] >= 10)
				{
					jinwei1 = b[999 - i - j] / 10;
					b[999 - i - j] = b[999 - i - j] % 10;
				}
				else
				{
					jinwei1 = 0;
				}
			}
			if (i + j>zanshizong)
			{
				zanshizong = i + j;
			}
			if (jinwei1 || jinwei2)
			{
				zanshizong++;
				b[1000 - zanshizong] = +jinwei1 + jinwei2;
			}
			jinwei1 = 0, jinwei2 = 0;
		}
		for (i = 0; i<zanshizong; i++)
		{
			store[999 - i] = b[999 - i];
			b[999 - i] = 0;
		}
		zanshi = zanshizong;
	}
	return zanshizong;
}
int main()
{
	char r[6] = { 0 };
	int store[1000] = { 0 }, i = 0, n = 0, point = 0, lenth = 0, sin = 0, j = 0, k = 0, z = 0;
	while (cin >> r >> n)
	{
		lenth = 5;
		for (i = 0; r[i] != '.'&&i<6; i++)
		{
			store[995 + i] = r[i] - '0';
		}
		point = 5 - i;
		for (i++; i<6; i++)
		{
			store[994 + i] = r[i] - '0';
		}
		lenth = yici(store, lenth, n);
		point = point*n;
		for (i = 0; i<lenth - point; i++)
		{
			if (store[1000 - lenth] != 0)
			{
				cout << store[1000 - lenth + i];
			}
		}
		for (j = 999; j>1000 - lenth; j--)
		{
			if (store[j] != 0)
				break;
		}
		j = 999 - j;
		if (j<point)
		{
			cout << '.';
		}
		if (lenth<point)
		{
			for (z = i; z + lenth<point; z++)
			{
				cout << '0';
			}
		}
		for (; i<lenth; i++)
		{
			if (lenth - i - j>0)
				cout << store[1000 - lenth + i];
		}
		cout << endl;
	}
}