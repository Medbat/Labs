#include <stdio.h>

class Time
{
	int hours, minutes, seconds;
	int months, days;
	int year; // ~(~@.@)
	static int daysInMonth[13];
public:
	// конструктор по умолчанию
	Time()
	{
		setTime(0, 0, 0, 1, 1, 1970);
	}
	// конструктор с параметрами времени в виде чисел
	Time(int h, int min, int s, int d, int mon, int year)
	{
		setTime(h, min, s, d, mon, year);
	}
	// коррекция времени
	void validate()
	{
		if (seconds > 60)
		{
			minutes += seconds / 60;
			seconds %= 60;
		}
		if (minutes > 60)
		{
			hours += minutes / 60;
			minutes %= 60;
		}
		if (hours > 24)
		{
			days += hours / 24;
			hours %=24;
		}
		while (days > daysInMonth[months])
		{
			days -= daysInMonth[months];
			months++;
			if (months == 12)
				months = 1;
		}
	}
	// установка времени с чисел
	void setTime(int h, int min, int s, int d, int mon, int year)
	{
		hours = h;	
		minutes = min;
		seconds = s;
		days = d;
		months = mon;
		validate();
	}
	// установка времени из строки. часы, минуты и секунды разделены двоеточием, через пробел идут день и месяц
	void setTime(char *string)
	{
		int h, min, s, d, mon, year;
		sscanf(string, "%d:%d:%d %d.%d.%d", &h, &min, &s, &d, &mon, &year);
		setTime(h, min, s, d, mon, year);
	}
	// геттер часов
	int getHours()
	{
		return hours;
	}
	// геттер минут
	int getMinutes()
	{
		return minutes;
	}
	// геттер секунд
	int getSeconds()
	{
		return seconds;
	}
	// геттер дней
	int getDays()
	{
		return days;
	}
	// геттер месяца
	int getMonths()
	{
		return months;
	}
	// добавление секунд
	void addSec(int s)
	{
		seconds += s;
		validate();
	}
	// добавление дней
	void addDays(int d)
	{
		days += d;
		validate();
	}
	// добавление месяцев
	void addMonths(int mon)
	{
		months += mon;
		validate();
	}
};

int Time::daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
