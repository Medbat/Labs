class Modulo
{
	int osn, ch;
public:
	Modulo()
	{
		osn = 10;
		ch = 0;
	}
	Modulo(int o, int c)
	{
		osn = o;
		ch = c;
	}
	void add(int a)
	{
		ch += a;
		ch %= osn;
	}
	void dec(int a)
	{
		ch -= a;
		if (ch < 0)
			ch = -ch;
		ch %= osn;
	}
	void mult(int a)
	{
		ch *= a;
		ch %= osn;
	}
	void del(int a)
	{
		int newdel = ch;
		while ( newdel % a )
			newdel += osn;
		ch = newdel / a;
		ch %= osn;
	}
	int getCh()
	{
		return ch;
	}
};
