#include <iostream>
using namespace std;

class Polynomial
{
	double *factor;
	int power;
public:

	Polynomial()
	{
		power = 0;
		factor = 0;
	}

	Polynomial(int n)
	{
		power = n;
		factor = new double[n + 1];
		for (int i = 0; i <= n; i++)
			factor[i] = 0;
	}

	Polynomial(double *f, int n)
	{
		power = n;
		factor = new double[n + 1];
		for (int i = 0; i <= n; i++)
			factor[i] = f[i];
	}

	void getPower(int power)
	{
		double *temp = new double[power + 1];
		if (this -> power != 0)
		{
			for (int i = 0; i <= this -> power; i++)
				temp[i] = factor[i];
			for (int i = this -> power + 1; i <= power; i++)
				temp[i] = 0;
			this -> power = power;
			return;
		}
		for (int i = 0; i <= power; i++)
			temp[i] = 0;
		this -> power = power;
		this -> factor = temp;
	}

	void set(int power, double value)
	{
		factor[power] = value;
	}

	char *output()
	{
		char *buf = new char[1024], *buf1 = new char[1024];
		char *lilBuf = new char[128];
		sprintf(lilBuf, "%s%.3f", (factor[0]>0?"+":""), factor[0]);
		strcpy(buf, lilBuf);
		for (int i = 1; i <= power; i++)
		{
			if (factor[i] == 0)
				continue;
			sprintf(lilBuf, "%s%.3fx^%d", (factor[i]>0?"+":""), factor[i], i);
			sprintf(buf1, "%s%s", lilBuf, buf);
			strcpy(buf, buf1);
		}
		return buf;
	}

	void read()
	{
		cout << "¬ведите максимальную степень: ";
		int power;
		cin >> power;
		getPower(power);
		for (int i = 0; i <= power; i++)
		{
			float v;
			cout << "x^" << i << ": ";
			cin >> v;
			set(i, v);
		}
	}
	
	Polynomial operator=(Polynomial q)
	{
		if (power > 0)
			delete [] this -> factor;
		power = q.power;
		factor = new double[q.power];
		for (int i = 0; i <= power; i++)
			factor[i] = q.factor[i];
		return *this;
	}

	Polynomial operator+(Polynomial q)
	{
		int n = power>q.power?power:q.power;
		double *temp = new double[n];
		for (int i = 0; i <= n; i++)
			temp[i] = ((power>=i)?factor[i]:0) + ((q.power>=i)?q.factor[i]:0);
		return Polynomial(temp, n);
	}

	Polynomial operator*(Polynomial q)
	{
		int n = power + q.power;
		double *temp = new double[n + 1];
		for (int i = 0; i <= n; i++)
			temp[i] = 0;
		for (int i = 0; i <= power; i++)
			for (int j = 0; j <= q.power; j++)
			{
				temp[i + j] += factor[i] * q.factor[j];
			}
		return Polynomial(temp, n);
	}

	void minus()
	{
		for (int i = 0; i <= power; i++)
			factor[i] = -factor[i];
	}

	Polynomial operator%(const Polynomial& q)
	{
		if (power < q.power)
			return Polynomial(factor, power);
        if (q.power == 0)
            return Polynomial(0);
        Polynomial A(power-q.power);
        Polynomial B(factor, power);
        for (int i = power; i >= q.power; i--)
        {
            if (q.factor[q.power])
            {
				A.factor[i - q.power] = B.factor[i] / q.factor[q.power];
                for (int t = 0; t <= q.power; t++) 
					B.factor [i-t] -= A.factor[i - q.power] * q.factor[q.power-t];
			}
		}
		return B;
	}

	Polynomial NOD (const Polynomial& P)
    {
		Polynomial a(*this);
		Polynomial c, d;
		Polynomial b(P);
		if (a.power < b. power)
		{
			c = a;
			a = b;
			b = c;
		}
		do
		{
			d = c;
			c = a % b;
			a = c;
		}
		while (c.power != 1);
		return d;
    }

};
