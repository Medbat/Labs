class Q
{
	int num, denom;
public:
	// ����������� �� ��������� (����� 1/1)
	Q()
	{
		num = denom = 1;
	}
	// ����������� � ��������� ��������� � �����������
	Q(int a, int b)
	{
		num = a;
		denom = b;
		reduction();
	}
	// ����������� ���������
	int getN()
	{
		return num;
	}
	// ����������� �����������
	int getD()
	{
		return denom;
	}
	// ���������� ������ ����� �� �����
	void addInt(int a)
	{
		num +=  a * denom;
		reduction();
	}
	// ���������� ����� �� �����
	void addQ(Q q)
	{
		num += q.num * denom;
		denom *= q.denom;
		reduction();
	}
	// ��������� ����� �� �����
	void multiply(int a)
	{
		num *= a;
		reduction();
	}
	// ��������� ���� ������
	int compare(Q q)
	{
		int a = num * q.denom;
		int b = q.num * denom;
		if (denom * q.denom < 0)
		{
			a = -a;
			b = -b;
		}
		if (a > b)
			return 1;
		if (a == b)
			return 0;
		else
			return -1;
	}
	// ���������� �����
	void reduction()
	{
		for (int i = (num>denom?num:denom); i > 1; i--)
			if (num % i == 0 && denom % i == 0)
			{
				num /= i;
				denom /= i;
				break;
			}
		if (num < 0 && denom < 0)
		{
			num = - num;
			denom = -denom;
		}
	}
	// ���������� ������������
	Q operator=(Q q)
	{
		num = q.num;
		denom = q.denom;
		return *this;
	}
	// ���������� ��������� �� �����
	Q operator*(int a)
	{
		Q temp = *this;
		temp.multiply(a);
		return temp;
	}
	// ���������� ���������� �����
	Q operator+(int a)
	{
		Q temp = *this;
		temp.addInt(a);
		return temp;
	}
	// ���������� ���������� �����
	Q operator+(Q q)
	{
		Q temp = *this;
		temp.addQ(q);
		return temp;
	}
};
