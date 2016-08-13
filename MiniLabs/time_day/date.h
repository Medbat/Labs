class date
{
	int days, months, years;
	static int daysInMonth[13];
public:
	date(int d, int m, int y)
	{
		set(d, m, y);
	}
	void set(int d, int m, int y)
	{
		days = d;
		months = m;
		years = y;
	}
	void setFromDays(int add)
	{
		int d = 1, m = 1, y = 1970;
		d += add;
		while (d > daysInMonth[m])
		{
			if ((!(y%400)||!(y%4)&&(y%100)) && m == 2)
				d -= 29;
			else
				d -= daysInMonth[m];
			m++;
			if (m == 13)
			{
				m = 1;
				y++;
			}
		}
		set(d, m, y);
	}
	int getD()
	{
		return days;
	}
	int getM()
	{
		return months;
	}
	int getY()
	{
		return years;
	}
	// asdkajshdgbjlahsdfashjdfvlasdf
	int getDaysFromStart()
	{
		int y = years;
		int d = days;
		int m = months;
		int counter = 0;
		while (m != 1 && y != 1970)
		{
			if ((!(y%400)||!(y%4)&&(y%100)) && m == 2)
			{
				d -= 29;
				counter += 29;
			}
			else
			{
				d -= daysInMonth[m];
				counter += daysInMonth[m];
			}
			m--;
			if (m == 0)
			{
				m = 12;
				y--;
			}
		}
		while (d > 1)
		{
			d--;
			counter++;
		}
		return counter;
	}
};

int date::daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
