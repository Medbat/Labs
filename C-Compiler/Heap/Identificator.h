#pragma once
#include "Heap.h"

enum LexemTypes
{
	lt_null,// НИЧЕГО 
	lt_nothing,// То что не обработано
	lt_brace,// Фигурная скобка 
	lt_parenthesis,// Круглая скобка
	lt_squarebracket,
	lt_variable,
	lt_type,
	lt_const,
	lt_strConst,
	lt_operator,
	lt_standardFunc,
	lt_cond,
	lt_interrupt,
	lt_comma,
	lt_preproc,
	lt_printf
};

enum BraceTypes
{
	brace_null,
	brace_open,
	brace_close
};
enum ParenthesisTypes
{
	par_null,
	par_open,
	par_close
};
enum SquareBracketTypes
{
	sbt_null,
	sbt_open,
	sbt_close
};
enum ConditionalsTypes
{
	condt_null,
	ct_if,
	ct_else,
	ct_while,
	ct_switch,
	ct_case,
	ct_default
};
enum InterruptTypes
{
	it_null,
	it_continue,
	it_break
};
enum FuncTypes
{
	ft_null,
	ft_max,
	ft_min
};

enum ConstTypes
{
	const_null,
	ct_double = 1,
	ct_int = 2,
	ct_bool = 3,
	ct_char = 4,
	ct_string = 5
};

enum OperTypes
{
	ot_null,
	ot_leftunar,
	ot_rightunar,
	ot_binar,
	ot_ternar
};

enum TypTypes
{
	tt_null, 
	tt_double, 
	tt_int, 
	tt_bool, 
	tt_char
};

class Lexem // СуперКласс
{
	LexemTypes lexTyp; // лексема
	
	int lengthname; // длина имени лексемы
	char* name; // имя лексемы
	char* state; // значение из автомата
	
	int varTypenum; // переменная
	void* varAddress; // место хранения переменной
	int PointCounter; // Сколько указателей
	char* nestingLevel; // уровень вложенности
	int nestingLevelLength; // Длина nestingLevel

	TypTypes typTyp; // тип

	ConstTypes constTyp; // константа (не строковая)
	double numericConstValue;



	OperTypes operTyp;               // операция
	int operPriority;					//приоритет операции

	FuncTypes funcTyp;				//min или max, иди что там еще есть
	
	ConditionalsTypes condTyp;		//всякая шняга с условием
	InterruptTypes interruptTyp;

	BraceTypes braceType; // фигурная скобка
	ParenthesisTypes parType; // круглая скобка
	SquareBracketTypes sbType; // квадратная скобка

public:

	// для отладки программы
	int lineNumInCode; // номер строки
	int charNumInLine; // номер символа (в строке)

	Lexem(int a = 0, char* b = NULL, char* c = NULL);
	~Lexem();
	char* ToCharStar();
	char* GetName();
	char* GetState();
	char* GetKeyword();
	LexemTypes GetLexemType();
	int GetVarTypeNum();
	char* GetNestingLevel();
	int GetNestingLevelLength();
	void* GetVarAdress();
	int GetVarPointCounter();

	int GetLineNumInCode();// номер строки
	int GetCharNumInLine(); // номер символа (в строке)
	void SetVar(void* anotherVarAdress); // поменять содержимое varAddress. Подразумеваемый тип совпадает со старый
	void SetVarAdress(void*);
	void SetVarTypeNum(int);
	void SetVarPointCounter(int);
	void SetNestingLevel(char*, int);//принимает массив и длину, отдельно задать длину нельзя
	TypTypes GetTypTyp();
	double GetNumericConstValue();
	ConstTypes GetConstTyp();
	OperTypes GetOperTyp();
	InterruptTypes GetInterruptTyp();
	ConditionalsTypes GetCondTyp();
	BraceTypes GetBraceTyp();
	ParenthesisTypes GetParTyp();
	SquareBracketTypes GetSquareBracketTyp();

	FuncTypes GetFuncTypes();

	//добавить nestinglevel
	void SwitchToVariable();
	///////////////////////////////////

	void SwitchToCond();
	void SwitchToInterrupt();
	void SwitchToStandardFunc();
	void SwitchToType();
	void SwitchToConst(char* d, double val);
	void SwitchToNothing();
	void SwitchToOper();
	void SwitchToComma();
	void SwitchToPreProc();
	void SwitchToFunc();
	void SwitchToBrace(char brace);
	void SwitchToPar(char par);
	void SwitchToSquareBracket(char sqbr);
	/////////////////////////////////

	void OperSwitchToLeftunar();
	void OperSwitchToRightunar();
	void OperSwitchToBinar();
	void OperSwitchToTernar();
	bool CheckOper();
	void OperAssignPriority();
	int OperGetPriority();
	void SwitchToStrConst();
};


class Variable : public Lexem
{
	int typenum;
	void* address;
public: 
	Variable(int a, char* b, char* c)
	{
		//keyword[0] = 'v';
		typenum = 0;
		address = NULL;
	}

	~Variable() 
	{
		Lexem::~Lexem();
		heap->free_mem(address);
	}
};

class Const : public Lexem
{
	ConstTypes typ;

	double value;
public:
	Const(Lexem a, char* d = NULL, double val = 0) : Lexem(a)
	{
		if (d[0] == 'd' || d[0] == 'z' || d[0] == 'o' || d[0] == 'h')
		{
			typ = ct_int;
		}
		if (d[0] == 'r' || d[0] == 'e')
		{
			typ = ct_double;
		}
		if (d[0] == 'c')
		{
			typ = ct_char;
		}
		value = val;
	}

	~Const();
};


class Oper : public Lexem
{
	enum Types
	{
		t_null,
		t_unar,
		t_binar,
		t_ternar
	} typ;

	int priority;
public:
	Oper();
	~Oper();
};