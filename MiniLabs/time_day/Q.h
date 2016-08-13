class Q
{
	int num, denom;
public:
	// конструктор по умолчанию (дробь 1/1)
	Q()
	{
		num = denom = 1;
	}
	// конструктор с указанием числителя и знаменателя
	Q(int a, int b)
	{
		num = a;
		denom = b;
		reduction();
	}
	// возвращение числителя
	int getN()
	{
		return num;
	}
	// возвращение знаменателя
	int getD()
	{
		return denom;
	}
	// добавление целого числа ко дроби
	void addInt(int a)
	{
		num +=  a * denom;
		reduction();
	}
	// добавление дроби ко дроби
	void addQ(Q q)
	{
		num += q.num * denom;
		denom *= q.denom;
		reduction();
	}
	// умножение дроби на число
	void multiply(int a)
	{
		num *= a;
		reduction();
	}
	// сравнение двух дробей
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
	// сокращение дроби
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
	// перегрузка присваивания
	Q operator=(Q q)
	{
		num = q.num;
		denom = q.denom;
		return *this;
	}
	// перегрузка умножения на число
	Q operator*(int a)
	{
		Q temp = *this;
		temp.multiply(a);
		return temp;
	}
	// перегрузка добавления числа
	Q operator+(int a)
	{
		Q temp = *this;
		temp.addInt(a);
		return temp;
	}
	// перегрузка добавления дроби
	Q operator+(Q q)
	{
		Q temp = *this;
		temp.addQ(q);
		return temp;
	}
};
