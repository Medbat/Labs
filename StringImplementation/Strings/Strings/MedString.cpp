
#include "headers.h"

int CharLen(char *s)
{
	if (!s)
		return 0;
	int i = 0;
	while (s[i++] != '\0');
	return --i;
}
void CharCpy(char *&Dest, char *Source)
{
	int i;
	for (i = 0; i < CharLen(Source); i++)
		Dest[i] = Source[i];
	Dest[i] = '\0';
}
char* validDouble(char *s)
{
	int i = CharLen(s) - 1;
	while (s[i] == '0')
		i--;
	s[i + 1] = '\0';
	return s;
}
int Tlen(MedString& Copy)
{
	int i = 0;
	while (Copy.String[i++] != '\0');
	return --i;
}
void Copy(MedString& Dest, MedString& Source)
{
	if (!Dest.String)
		delete [] Dest.String;
	Dest.String = new char[Tlen(Source) + 1];
	int i;
	for (i = 0; i < Tlen(Source); i++)
		Dest.String[i] = Source.String[i];
	Dest.String[i] = '\0';
}
MedString :: MedString()
{
	String = NULL;
}
MedString :: MedString(MedString &From)
{
	String = new char[Tlen(From) + 1];
	int i;
	for (i = 0; i < Tlen(From); i++)
		String[i] = From.String[i];
	String[i] = '\0';
}
MedString :: MedString(char *From)
{
	String = new char[CharLen(From) + 1];
	int i;
	for (i = 0; i < CharLen(From); i++)
		String[i] = From[i];
	String[i] = '\0';
}
MedString :: MedString(int From)
{
	char *buf = new char[1024];
	itoa(From, buf, 10);
	String = new char[CharLen(buf) + 1];
	CharCpy(String, buf);
}
MedString :: MedString(double from)
{
	char *buf = new char[1024];
	sprintf(buf, "%f", from);
	buf = validDouble(buf);
	String = new char[CharLen(buf) + 1];
	CharCpy(String, buf);
}
MedString::~MedString()
{
	if (String)
		delete [] String;
}
MedString & MedString :: operator = (char *add)
{
	if (String)
		delete String;
	String = new char[CharLen(add) + 1];
	CharCpy(String, add);
	return *this;
}
MedString & MedString :: operator = (int add)
{
	if (String)
		delete String;
	char *buf = new char[1024];
	itoa(add, buf, 10);
	String = new char[CharLen(buf) + 1];
	CharCpy(String, buf);
	return *this;
}
MedString & MedString :: operator = (MedString add)
{
	*this = add.String;
	String[Tlen(add)] = '\0';
	return *this;
}
MedString & MedString :: operator = (double add)
{
	if (String)
		delete String;
	char *buf = new char[1024];
	sprintf(buf, "%f", add);
	buf = validDouble(buf);
	String = new char[CharLen(buf) + 1];
	CharCpy(String, buf);
	return *this;
}
MedString & MedString :: operator += (char *add)
{
	char *buf = new char[CharLen(String) + 1 + CharLen(add)];
	CharCpy(buf, String);
	int i;
	for (i = 0; i < CharLen(add); i++)
		buf[CharLen(String) + i] = add[i];
	buf[CharLen(String) + i] = '\0';
	if (String)
		delete [] String;
	String = buf;
	return *this;
}
MedString & MedString :: operator += (int add)
{
	char *buf = new char[1024];
	return *this += itoa(add, buf, 10);
}
MedString & MedString :: operator += (MedString add)
{
	return *this += add.String;
}
MedString & MedString :: operator += (double add)
{
	char *buf = new char[1024];
	sprintf(buf, "%f", add);
	buf = validDouble(buf);
	return *this += buf;
}
char& MedString :: operator[](int count) throw(...)
{
	if (count < 0 || count > Tlen(*this) - 1)
		throw "Out of range";
	return String[count];
}
void MedString :: Tcopy(char *Source)
{
	Copy(*this, MedString(Source));
}
int MedString :: len()
{
	return Tlen(*this);
}
MedString operator+(MedString& first, MedString& second)
{
	return MedString(first) += second;
}
void MedSwap(MedString& first, MedString &second)
{
	MedString t(first);
	first = second;
	second = t;
}
MedString Ttrim(MedString& from)
{
	int i = Tlen(from) - 1;
	char *buf = new char[Tlen(from) + 1];
	CharCpy(buf, from.String);
	while (buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n')
		i--;
	int j = 0;
	while (buf[j] == ' ' || buf[j] == '\t' || buf[j] == '\n')
		j++;
	char *buf2 = new char[Tlen(from) + 1 - j - (Tlen(from) + 1 - i)];
	int q = 0;
	for (int k = j; k < i + 1; k++)
		buf2[q++] = buf[k];
	buf2[q] = '\0';
	delete [] buf;
	return buf2;
}
bool operator>(MedString& first, MedString& second)
{
	int min;
	if (Tlen(second) > Tlen(first))
		min = Tlen(first);
	else
		min = Tlen(second);
	for (int i = 0; i < min; i++)
	{
		if (first[i] == second[i])
			continue;
		if (first[i] > second[i])
			return true;
		else
			return false;
	}
	return false;
}
bool operator<(MedString& first, MedString& second)
{
	int min;
	if (Tlen(second) > Tlen(first))
		min = Tlen(first);
	else
		min = Tlen(second);
	for (int i = 0; i < min; i++)
	{
		if (first[i] == second[i])
			continue;
		if (first[i] < second[i])
			return true;
		else
			return false;
	}
	return false;
}
bool operator==(MedString& first, MedString& second)
{
	if (Tlen(first) != Tlen(second))
		return false;
	for (int i = 0; i < Tlen(first); i++)
		if (first[i] != second[i])
			return false;
	return true;
}
int MedString :: pos(MedString& what)
{
	char *buf = new char[Tlen(what) + 1];
	buf[Tlen(what)] = '\0';
	for (int i = 0; i < Tlen(*this) - Tlen(what) + 1; i++)
	{
		if (String[i] != what[0])
			continue;
		else
		{
			for (int j = 0; j < Tlen(what); j++)
				buf[j] = String[i + j];
			if (MedString(buf) == what)
				return i;
		}
	}
	return -1;
}
void MedString :: del(MedString& what)
{
	int d = pos(what);
	char *buf = new char[Tlen(*this) + 1 - Tlen(what)];
	int j;
	for (j = 0; j < d; j++)
		buf[j] = String[j];
	for (int i = d + Tlen(what); i < CharLen(String); i++)
		buf[j++] = String[i];
	buf[j] = '\0';
	delete [] String;
	String = buf;
}
int MedString :: nextpos(MedString& what)
{
	MedString t(*this);
	if (t.pos(what) == -1)
		return -1;
	t.del(what);
	return t.pos(what) + Tlen(what);
}
void MedString :: del(int begin, int length) throw(...)
{
	if (begin + length > len())
		throw "Out of range";
	char *buf = new char[len() + 1 - length];
	int j = 0;
	for (int i = 0; i < begin; i++)
		buf[j++] = String[i];
	for (int i = begin + length; i < len(); i++)
		buf[j++] = String[i];
	buf[j] = '\0';
	delete [] String;
	String = buf;
}
void MedString :: delall(MedString &what)
{
	while (pos(what) != -1)
		del(what);
}
void MedString :: ins(MedString& what, int whereto) throw(...)
{
	if (whereto > len())
		throw "Out of range";
	char *buf = new char[len() + 1 + Tlen(what)];
	int i;
	for (i = 0; i < whereto; i++)
		buf[i] = String[i];
	buf[i] = '\0';
	MedString t(buf);
	t = t + what + MedString(&String[whereto]);
	delete [] String;
	String = NULL;
	*this = t;
}
void MedString :: replace(MedString& what, MedString& replace_with)
{
	if (pos(what) == -1)
		return;
	int a = pos(what);
	del(what);
	ins(replace_with, a);
}
void MedString :: replaceall(MedString& what, MedString& replace_with)
{
	while (pos(what) != -1)
		replace(what, replace_with);
}
void MedString :: trim()
{
	*this = Ttrim(*this);
}
void MedString :: lower()
{
	for (int i = 0; i < len(); i++)
	{
		if (String[i] >= 'A' && String[i] <= 'Z')
			String[i] += 32;
		/*if (String[i] <= -128 && String[i] >= -143)
			String[i] += 64;*/
	}
}
void MedString :: upper()
{
	for (int i = 0; i < len(); i++)
	{
		if (String[i] >= 'a' && String[i] <= 'z')
			String[i] -= 32;
	}
}
int MedString :: to_int() throw(...)
{
	return atoi(String);
}
double MedString :: to_double() throw(...)
{
	return atof(String);
}
void MedString :: reverse()
{
	char ch;
	for (int i = 0; i < len() / 2; i++)
	{
		ch = String[i];
		String[i] = String[len() - i - 1];
		String[len() - i - 1] = ch;
	}
}
ostream& operator<<(ostream& out, MedString& p)
{
	if (p.String)
		out << p.String;
	else
		out << "";
	return out;
}