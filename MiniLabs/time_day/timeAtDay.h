class timeAtDay
{
	int seconds, minutes, hours;
public:
	timeAtDay(int h, int m, int s)
	{
		set(h, m, s);
	}
	void set(int h, int m, int s)
	{
		hours = h;
		minutes = m;
		seconds = s;
	}
	int getS()
	{
		return seconds;
	}
	int getM()
	{
		return minutes;
	}
	int getH()
	{
		return hours;
	}
	void addS(int s)
	{
		seconds += s;
		minutes += seconds / 60;
		seconds %= 60;
		hours += minutes / 60;
		minutes %= 60;
		hours %= 60;
	}
};
