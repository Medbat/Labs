#include "stdafx.h"
#include "Identificator.h"

Lexem::Lexem(int lengthname, char* name, char* state)
{
	this->lengthname= lengthname;

	int i;

	for (i = 0; name[i] != '\0'; i++);
	this->name = (char*)heap->get_mem(i*sizeof(char));
	strcpy(this->name, name);

	/*keyword = (char*)heap->get_mem((i + 1)*sizeof(char));
	strcpy(&keyword[1], name);*/

	for (i = 0; state[i] != '\0'; i++);
	this->state = (char*)heap->get_mem(i*sizeof(char));
	strcpy(this->state, state);
}

Lexem::~Lexem()
{
	heap->free_mem(name);
	name = NULL;
	heap->free_mem(state);
	state = NULL;
	/*heap->free_mem(keyword);
	keyword = NULL;*/
}

char* Lexem::ToCharStar()
{
	char* Result = (char*)heap->get_mem((strlen(name) + strlen(state) + 3)*sizeof(char));
	memcpy(Result, name, strlen(name));
	Result[strlen(name)] = '(';
	memcpy(&Result[strlen(name) + 1], state, strlen(state));
	Result[strlen(name) + strlen(state) + 1] = ')';
	Result[strlen(name) + strlen(state) + 2] = '\0';
	return Result;
}

char* Lexem::GetName()
{
	return name;
}

char* Lexem::GetState()
{
	return state;
}

char* Lexem::GetKeyword()
{
	if (lexTyp == lt_operator)
		return name;
	if (lexTyp == lt_interrupt)
		return name;
	if (lexTyp == lt_standardFunc)
		return name;
	char *result;
	result = (char*)heap->get_mem((strlen(name) + (nestingLevel?strlen(nestingLevel)+1:1))*sizeof(char));
	result[0] = '\0';
	if (nestingLevelLength > 0)
		strcat(result, nestingLevel);

	//if (nestingLevelLength > 0)
	//{
	//	char* temp = (char*)heap->get_mem(1024 * sizeof(char));
	//	for (int i = 0; i < nestingLevelLength; i++)
	//	{
	//		temp[0] = '\0';
	//		_itoa(nestingLevel[i], temp, 10);
	//		/*if (i != nestingLevelLength - 1)
	//			strcat(result, ".");*/
	//	}
	//	heap->free_mem(temp);
	//}
	strcat(result, name);
	return result;
}

LexemTypes Lexem::GetLexemType()
{
	return lexTyp;
}

ConstTypes Lexem::GetConstTyp()
{
	return constTyp;
}

ConditionalsTypes Lexem::GetCondTyp()
{
	return condTyp;
}

InterruptTypes Lexem::GetInterruptTyp()
{
	return interruptTyp;
}

FuncTypes Lexem::GetFuncTypes()
{
	return funcTyp;
}

double Lexem::GetNumericConstValue()
{
	return numericConstValue;
}

int Lexem::GetVarTypeNum()
{
	return varTypenum;
}

char* Lexem::GetNestingLevel()
{
	return nestingLevel;
}

int Lexem::GetNestingLevelLength()
{
	return nestingLevelLength;
}

void* Lexem::GetVarAdress()
{
	return varAddress;
}

int Lexem::GetVarPointCounter()
{
	return PointCounter;
}

void Lexem::SetVar(void* v)
{
	//switch (varTypenum)
	//{
	//	//ct_double, ct_int, ct_bool, ct_char
	//case ct_double:
	//	memcpy(varAddress, v, sizeof(double));
	//	break;
	//case ct_int:
	//	memcpy(varAddress, v, sizeof(int));
	//	break;
	//case ct_bool:
	//	memcpy(varAddress, v, sizeof(bool));
	//	break;
	//case ct_char:
	//	memcpy(varAddress, v, sizeof(char));
	//	break;
	//default:
	//	break;
	//}
	if (PointCounter == 0)
	{
		switch (varTypenum)
		{
			//ct_double, ct_int, ct_bool, ct_char
		case ct_double:
			memcpy(varAddress, v, sizeof(double));
			break;
		case ct_int:
			memcpy(varAddress, v, sizeof(int));
			break;
		case ct_bool:
			memcpy(varAddress, v, sizeof(bool));
			break;
		case ct_char:
			memcpy(varAddress, v, sizeof(char));
			break;
		default:
			break;
		}
	}
	if (PointCounter > 0)
		memcpy(varAddress, v, sizeof(void*));
}

void Lexem::SetVarAdress(void* adr)
{
	varAddress=adr;
}

void Lexem::SetVarTypeNum(int num) { varTypenum = num; }

void Lexem::SetVarPointCounter(int num) { PointCounter = num; }

void Lexem::SetNestingLevel(char* nestLevel, int length) 
{	
	nestingLevelLength = length;
	if (length == 0)
	{
		nestingLevel = NULL;
		return;
	}
	nestingLevel = (char*)heap->get_mem(sizeof(nestLevel));
	strcpy(nestingLevel, nestLevel);
}

TypTypes Lexem::GetTypTyp()
{
	return typTyp;
}

OperTypes Lexem::GetOperTyp()
{
	return operTyp;
}

BraceTypes Lexem::GetBraceTyp()
{
	return braceType;
}
ParenthesisTypes Lexem::GetParTyp()
{
	return parType;
}
SquareBracketTypes Lexem::GetSquareBracketTyp()
{
	return sbType;
}
void Lexem::SwitchToBrace(char brace)
{
	lexTyp = lt_brace;
	braceType = brace == '{' ? brace_open : brace_close;
}
void Lexem::SwitchToPar(char par)
{
	lexTyp = lt_parenthesis;
	parType = par == '(' ? par_open : par_close;
}
void Lexem::SwitchToSquareBracket(char sqbr)
{
	lexTyp = lt_squarebracket;
	sbType = sqbr == '[' ? sbt_open : sbt_close;
}


void Lexem::SwitchToVariable()
{
	lexTyp = lt_variable;
	//keyword[0] = 'v';
	varTypenum = -1;
	varAddress = NULL;
}

void Lexem::SwitchToCond()
{
	lexTyp = lt_cond;
	switch (name[0])
	{
	case 'w':
		strcpy(state, "while");
		condTyp = ct_while;
		return;
	case 'i':
		strcpy(state, "if");
		condTyp = ct_if;
		return;
	case 'e':
		strcpy(state, "else");
		condTyp = ct_else;
		return;
	case 's':
		strcpy(state, "switch");
		condTyp = ct_switch;
		return;
	case 'c':
		strcpy(state, "case");
		condTyp = ct_case;
		return;
	case 'd':
		strcpy(state, "default");
		condTyp = ct_default;
		return;
	default:
		return;
	}
}

void Lexem::SwitchToInterrupt()
{
	lexTyp = lt_interrupt;
	switch (name[0])
	{
	case 'c':
		strcpy(state, "continue");
		interruptTyp = it_continue;
		return;
	case 'b':
		strcpy(state, "break");
		interruptTyp = it_break;
		return;
	default:
		return;
	}
}

void Lexem::SwitchToStandardFunc()
{
	lexTyp = lt_standardFunc;
}

void Lexem::SwitchToType()
{
	lexTyp = lt_type;
	switch (name[0])
	{
	case 'i':
		strcpy(state, "int");
		typTyp = tt_int;
		return;
	case 'd':
		heap->free_mem(state);
		state = (char*)heap->get_mem(7*sizeof(char));
		strcpy(state, "double");
		typTyp = tt_double;
		return;
	case 'c':
		heap->free_mem(state);
		state = (char*)heap->get_mem(5 * sizeof(char));
		strcpy(state, "char");
		typTyp = tt_char;
		return;
	case 'b':
		heap->free_mem(state);
		state = (char*)heap->get_mem(5 * sizeof(char));
		strcpy(state, "bool");
		typTyp = tt_bool;
		return;
	default:
		return;
	}
};

void Lexem::SwitchToConst(char* d = NULL, double val = 0)
{
	lexTyp = lt_const;
	if (d[0] == 'd' || d[0] == 'z' || d[0] == 'o' || d[0] == 'h')
	{
		constTyp = ct_int;
		numericConstValue = val;
	}
	if (d[0] == 'r' || d[0] == 'e')
	{
		constTyp = ct_double;
		numericConstValue = val;
	}
}

void Lexem::SwitchToNothing() { lexTyp = lt_nothing; }

void Lexem::SwitchToOper() { lexTyp = lt_operator; }

void Lexem::SwitchToComma() { lexTyp = lt_comma; }

void Lexem::SwitchToPreProc() { lexTyp = lt_preproc; }

void Lexem::SwitchToFunc()
{
	lexTyp = lt_standardFunc;
}

void Lexem::OperSwitchToLeftunar() 
{
	if (lexTyp == lt_operator)
	{
		operTyp = ot_leftunar;
		heap->free_mem(state);
		state = (char*)heap->get_mem(9 * sizeof(char));
		strcpy(state, "leftUnar");
	}
}
void Lexem::OperSwitchToRightunar()
{
	if (lexTyp == lt_operator)
	{
		operTyp = ot_rightunar;
		heap->free_mem(state);
		state = (char*)heap->get_mem(10 * sizeof(char));
		strcpy(state, "rightUnar");
	}
}
void Lexem::OperSwitchToBinar()
{
	if (lexTyp == lt_operator)
	{
		operTyp = ot_binar;
		heap->free_mem(state);
		state = (char*)heap->get_mem(6 * sizeof(char));
		strcpy(state, "Binar");
	}
}
void Lexem::OperSwitchToTernar() 
{ 
	if (lexTyp == lt_operator)
	{
		operTyp = ot_ternar;
		heap->free_mem(state);
		state = (char*)heap->get_mem(7 * sizeof(char));
		strcpy(state, "Ternar");
	}
}

bool Lexem::CheckOper()
{
	if (lexTyp != lt_operator) return false;
	switch (operTyp)
	{
	case ot_leftunar:
		if ((name[0] == '+' && name[1] == '+') ||
			(name[0] == '-' && name[1] == '-')) return true;
		
		else return false;
		break;
	case ot_rightunar:
		if ((name[0] == '+' && name[1] == '+') ||
			(name[0] == '-' && name[1] == '-') ||
			(name[0] == '+' && name[1] == '\0') ||
			(name[0] == '-' && name[1] == '\0') ||
			(name[0] == '!' && name[1] == '\0') || 
			(name[0] == '*' && name[1] == '\0') ||
			(name[0] == '&' && name[1] == '\0')) return true;
		else return false;
		break;
	case ot_binar:
		if ((name[0] == '+' && name[1] == '\0') ||
			(name[0] == '-' && name[1] == '\0') ||
			(name[0] == '*' && name[1] == '\0') ||
			(name[0] == '/' && name[1] == '\0') ||
			(name[0] == '&' && name[1] == '\0') ||
			(name[0] == '|' && name[1] == '\0') ||
			(name[0] == '<' && name[1] == '<') ||
			(name[0] == '>' && name[1] == '>') ||
			(name[0] == '&' && name[1] == '&') ||
			(name[0] == '|' && name[1] == '|') ||
			(name[0] == '=' && name[1] == '=') ||
			(name[0] == '!' && name[1] == '=') ||
			(name[0] == '<' && name[1] == '=') ||
			(name[0] == '>' && name[1] == '=') ||
			(name[0] == '<' && name[1] == '\0') ||
			(name[0] == '>' && name[1] == '\0') ||
			(name[0] == '+' && name[1] == '\0') ||
			(name[0] == '=' && name[1] == '\0') ||
			(name[0] == '[' && name[1] == '\0') ||
			(name[0] == '(' && name[1] == '\0')) return true;
		else return false;
		break;
	case ot_ternar:
		return true;
		break;
	default:
		return false;
		break;
	}
}

void Lexem::OperAssignPriority() // уже проверено, назначить приоритет
{
	switch (operTyp)
	{
	case ot_leftunar:
		operPriority = 2;
		break;
	case ot_rightunar:
		operPriority = 3;
		break;
	case ot_binar:
		if (name[0] == '[' && name[1] == '\0') operPriority = 2;
		else if	((name[0] == '*' && name[1] == '\0') ||
			(name[0] == '/' && name[1] == '\0')) operPriority = 5;
		else if ((name[0] == '+' && name[1] == '\0') ||
			(name[0] == '-' && name[1] == '\0')) operPriority = 6;
		else if ((name[0] == '<' && name[1] == '<') ||
			(name[0] == '>' && name[1] == '>')) operPriority = 7;
		else if ((name[0] == '<' && name[1] == '=') ||
			(name[0] == '>' && name[1] == '=') ||
			(name[0] == '<' && name[1] == '\0') ||
			(name[0] == '>' && name[1] == '\0')) operPriority = 8;
		else if ((name[0] == '=' && name[1] == '=') ||
			(name[0] == '!' && name[1] == '=')) operPriority = 9;
		else if ((name[0] == '&' && name[1] == '\0')) operPriority = 10;
		else if ((name[0] == '|' && name[1] == '\0')) operPriority = 12;
		else if ((name[0] == '&' && name[1] == '&')) operPriority = 13;
		else if ((name[0] == '|' && name[1] == '|')) operPriority = 14;
		else if ((name[0] == '=' && name[1] == '\0')) operPriority = 16;
		break;
	case ot_ternar:
		operPriority = 15;
		break;
	default:
		break;
	}
}

int Lexem::OperGetPriority() {	return operPriority; }

void Lexem::SwitchToStrConst() { lexTyp = lt_strConst; }


int Lexem::GetLineNumInCode()
{
	return lineNumInCode;
}
int Lexem::GetCharNumInLine()
{
	return charNumInLine;
}