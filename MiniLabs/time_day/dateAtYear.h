class dateAtYear
{
	int days, months;
	static int daysInMonth[13];
public:
	dateAtYear(int d, int m)
	{
		set(d, m);
	}
	void set(int d, int m)
	{
		days = d;
		months = m;
	}
	int getD()
	{
		return days;
	}
	int getM()
	{
		return months;
	}
	void addDays(int d)
	{
		days += d;
		while (days > daysInMonth[months])
		{
			days -= daysInMonth[months];
			months++;
			if (months == 13)
				months = 1;
		}
	}
};


int dateAtYear::daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
