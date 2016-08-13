#include "stdafx.h"
#include "Tree.h"
#include "Compiler.h"
#include "Identificator.h"

TNode* TNode::FindTheOperand(List* list, int left, int right, int& MinPriorityOperIndex)
{
	// найти и убрать окаймляющие скобки
	Lexem* templex = (Lexem*)list->get(left);
	if (templex->GetState()[0] == '(')
	{
		// это окаймляющая скобка?
		int unclosedBracketCounter = 1;
		for (int j = left + 1; j <= right; j++)
		{
			templex = (Lexem*)list->get(j);
			if (templex->GetState()[0] == '(') unclosedBracketCounter++;
			if (templex->GetState()[0] == ')') unclosedBracketCounter--;
			if (unclosedBracketCounter == 0 && j != right) 
				break;  // это не окаймляющие скобки!
			if (unclosedBracketCounter == 0 && j == right)  // это окаймляющие скобки! 
			{
				return FindTheOperand(list, left + 1, right - 1, MinPriorityOperIndex);
			}
			if (unclosedBracketCounter < 0)
			{
				ReportError(templex->charNumInLine, templex->charNumInLine, "Overclosed bracket");
				system("pause");
				exit(0);
			}
		}
		if (unclosedBracketCounter > 0)
		{
			ReportError(templex->charNumInLine, templex->charNumInLine, "Unclosed bracket");
			system("pause");
			exit(0);
		}
	}
	Lexem* lexe = RecursiveTreeer(list, left, right, MinPriorityOperIndex);
	TNode* operand = NULL;
	int doubleDotIndex = MinPriorityOperIndex;
	switch (lexe->GetLexemType())
	{
		case lt_variable:
			operand = new TVariable(lexe->GetKeyword());
			break;
		case lt_const: 
			operand = new TConst(lexe);
			break;
		case lt_operator:
			switch (lexe->GetOperTyp())
			{
			case ot_leftunar:
				operand = new TUnaryOperation(lexe, list, left, MinPriorityOperIndex - 1);
				break;
			case ot_rightunar:
				operand = new TUnaryOperation(lexe, list, MinPriorityOperIndex + 1, right);
				break;
			case ot_binar:
				operand = new TBinaryOperation(lexe, list, left, MinPriorityOperIndex - 1, MinPriorityOperIndex + 1, right);
				break;
			case ot_ternar:
				while (((Lexem*)list->get(doubleDotIndex))->GetName()[0] != ':' && doubleDotIndex <= right) doubleDotIndex++;
				operand = new TernarOperation(lexe, list, left, MinPriorityOperIndex - 1, MinPriorityOperIndex + 1, doubleDotIndex - 1, doubleDotIndex + 1, right);
				break;
			}
			break;
		/*default:
			ReportError(templex->charNumInLine, templex->charNumInLine, "Variable, const or operator expected");
			return NULL;*/
	}
	if (operand == NULL)
	{
		ReportError(templex->charNumInLine, templex->charNumInLine, "Bad syntax");
		system("pause");
		exit(0);
	}
	return operand;
}

TConst::TConst(Lexem* key)
{
	m_const.setType(key->GetConstTyp());//Base->find(key->GetKeyword())->GetVarTypeNum());
	m_const.setValue(key->GetNumericConstValue());
	keyWord = key->GetKeyword();
}

//ct_double, ct_int, ct_bool, ct_char

void TConst::print()
{
	switch (m_const.type())
	{
	case ct_double:
		cout << m_const.value();
		break;
	case ct_int:
		cout << (int)m_const.value();
		break;
	case ct_bool:
		cout << (bool)m_const.value();
		break;
	case ct_char:
		cout << (char)m_const.value();
		break;
	}
}

TVariable::TVariable(char* key)
{
	keyWord = (char*)heap->get_mem(sizeof(char)*(strlen(key) + 1));
	strcpy(keyWord, key);
}

TVariable::~TVariable()
{
}

TValue TVariable::exec() 
{
	TValue res;
	/*Lexem* vari = ((Lexem_List*)Base->find_list(lexem->GetKeyword()))->find(lexem->GetKeyword());*/
	Lexem* vari = Base->find(GetKeyWord());
	if (vari)
	{
		res.setType(vari->GetVarTypeNum());
		if (vari->GetVarPointCounter() == 0)
		{
			switch (res.type())
			{
			case ct_bool:
				res.setValue((double)*((bool*)(vari->GetVarAdress())));
				break;
			case ct_int:
				res.setValue((double)*((int*)(vari->GetVarAdress())));
				break;
			case ct_char:
				res.setValue((double)*((char*)(vari->GetVarAdress())));
				break;
			case ct_double:
				res.setValue(*((double*)(vari->GetVarAdress())));
				break;
			default:
				break;
			}
		}
		else if (vari->GetVarPointCounter() > 0)
		{
			res.setValuePointer(vari->GetVarAdress());
			res.setPointerLevel(vari->GetVarPointCounter());
		}
		else
		{//throw КОЛИЧЕСТВО ЗВЕЗДОЧЕК >0
		}
	}
	else; //throw типа ошибка, но вроде оно не должно вывалиться, если наша прога норм работает
	return res;
}

void TValue::print()
{
	cout << m_value;
}

void TVariable::print()
{
	Lexem* vari = Base->find(keyWord);
	if(vari->GetVarPointCounter()>0)
	{
		cout << vari->GetVarAdress();
		return;
	}
	cout << "(value: ";
	switch (vari->GetVarTypeNum())
	{
	case ct_double:
		cout << *((double*)(vari->GetVarAdress()));
		break;
	case ct_int:
		cout << *(int*)((double*)(vari->GetVarAdress()));
		break;
	case ct_bool:
		cout << *(bool*)((double*)(vari->GetVarAdress()));
		break;
	case ct_char:
		cout << *(char*)((double*)(vari->GetVarAdress()));
		break;
	}
	cout << ")" << GetLexem()->GetName();
}

TUnaryOperation::TUnaryOperation(Lexem* operat, List* list, int left, int right)
{
	int MinPriorityOperIndex = 0;
	keyWord = (char*)heap->get_mem(sizeof(char)*(strlen(operat->GetKeyword()) + 1));
	strcpy(keyWord, operat->GetKeyword());
	isPostfix = operat->GetOperTyp() == ot_rightunar;
	m_operand = FindTheOperand(list, left, right, MinPriorityOperIndex);
}

TUnaryOperation::~TUnaryOperation()
{
}

TValue TUnaryOperation::exec()
{
	TValue res = m_operand->exec();
	char* name = GetKeyWord();
	if (name[0] == '+' && name[1] == '+')
	{
		if (m_operand->GetLexem() && m_operand->GetLexem()->GetLexemType() == lt_variable)
		{
			Lexem* vari = m_operand->GetLexem();
			if (vari->GetVarPointCounter() == 0)
			{
				res.setValue(res.value() + 1);
				bool vb;
				int vi;
				char vc;
				double vd;
				switch (vari->GetVarTypeNum())
				{
					case ct_bool:
						vb = res.value();
						vari->SetVar(&vb);
						break;
					case ct_int:
						vi = res.value();
						vari->SetVar(&vi);
						break;
					case ct_char:
						vc = res.value();
						vari->SetVar(&vc);
						break;
					case ct_double:
						vd = res.value();
						vari->SetVar(&vd);
						break;
				}
			}
			else if (vari->GetVarPointCounter() > 0)
			{
				/*switch (m_type)
				{
				case ct_bool:
					res.setValuePointer((bool*)res.valuepointer() + 1);
				case ct_char:
					res.setValuePointer((char*)res.valuepointer() + 1);
				case ct_int:
					res.setValuePointer((int*)res.valuepointer() + 1);
				case ct_double:
					res.setValuePointer((double*)res.valuepointer() + 1);
				}*/
				res.setValuePointer((double*)res.valuepointer() + 1);
				vari->SetVar(res.valuepointer());
			}
		}
	}
	if (name[0] == '-' && name[1] == '-')
	{
		if (m_operand->GetLexem()->GetLexemType() == lt_variable)
		{
			Lexem* vari = m_operand->GetLexem();
			if (vari->GetVarPointCounter() == 0)
			{
				res.setValue(res.value() - 1);
				bool vb;
				int vi;
				char vc;
				double vd;
				switch (vari->GetVarTypeNum())
				{
				case ct_bool:
					vb = res.value();
					vari->SetVar(&vb);
					break;
				case ct_int:
					vi = res.value();
					vari->SetVar(&vi);
					break;
				case ct_char:
					vc = res.value();
					vari->SetVar(&vc);
					break;
				case ct_double:
					vd = res.value();
					vari->SetVar(&vd);
					break;
				}
			}
			else if (vari->GetVarPointCounter() > 0)
			{
				/*switch (m_type)
				{
				case ct_bool:
				res.setValuePointer((bool*)res.valuepointer() - 1);
				case ct_char:
				res.setValuePointer((char*)res.valuepointer() - 1);
				case ct_int:
				res.setValuePointer((int*)res.valuepointer() - 1);
				case ct_double:
				res.setValuePointer((double*)res.valuepointer() - 1);
				}*/
				res.setValuePointer((double*)res.valuepointer() - 1);
				vari->SetVar(res.valuepointer());
			}
		}
	}
	if (name[0] == '+' && name[1] == '\0')
	{
	}
	if (name[0] == '-' && name[1] == '\0')
	{
		if (res.isPointer()) 
		{
			ReportError((m_operand->GetLexem())->GetLineNumInCode(), (m_operand->GetLexem())->GetCharNumInLine(),
				"Попытка присвоить унарный минус указателю. Ай ай ай");
			system("pause");
			exit(0);
		}
		res.setValue(-res.value());
	}
	if (name[0] == '!' && name[1] == '\0')
	{
		if (res.isPointer()) 
		{
			ReportError((m_operand->GetLexem())->GetLineNumInCode(), (m_operand->GetLexem())->GetCharNumInLine(),
				"Попытка отрицать указатель");
			system("pause");
			exit(0);
		}
		res.setType(ct_bool);
		res.setValue(res.value()==0? 1 : 0);
	}
	if (name[0] == '*' && name[1] == '\0')
	{
		if (!res.isPointer()) 
		{
			ReportError((m_operand->GetLexem())->GetLineNumInCode(), (m_operand->GetLexem())->GetCharNumInLine(),
				"Попытка разыменовать НЕуказатель");
			system("pause");
			exit(0);
		}
		Lexem* lex = m_operand->GetLexem();
		if (lex->GetVarPointCounter() == 1) // int* a; *a;
		{
			switch (res.type())
			{
			case ct_bool:
				res.setValue((double)*(bool*)(res.valuepointer()));
				break;
			case ct_char:
				res.setValue((double)*(char*)(res.valuepointer()));
				break;
			case ct_int:
				res.setValue((double)*(int*)(res.valuepointer()));
				break;
			case ct_double:
				res.setValue(*(double*)(res.valuepointer()));
				break;
			}
		}
		if (lex->GetVarPointCounter() > 1)  // int********* a; *a;
		{
			res.setPointerLevel(res.pointerlevel()-1);
		}
	}
	if (name[0] == '&' && name[1] == '\0')
	{
		Lexem* lex = m_operand->GetLexem();
		if (lex->GetLexemType() == lt_variable)
		{
			res.setValuePointer(lex->GetVarAdress());
		}
		res.setPointerLevel(res.pointerlevel() + 1);
	}
	return res;
}

void TUnaryOperation::print()
{
	char* name = GetKeyWord();
	if (isPostfix)
		{
		cout << name;
			m_operand->print();
		}
		else
		{
			m_operand->print();
		cout << name;
	}
	/*
	if (name[0] == '+' && name[1] == '\0')
	{
		cout << "+";
		m_operand->print();
	}
	if (name[0] == '-' && name[1] == '\0')
	{
		cout << "-";
		m_operand->print();
	}
	if (name[0] == '!' && name[1] == '\0')
	{
		cout << "!";
		m_operand->print();
	}
	if (name[0] == '*' && name[1] == '\0')
	{
		cout << "*";
		m_operand->print();
	}
	if(name[0] == '&' && name[1] == '\0')
	{
		cout << "&";
		m_operand->print();
	}
	*/
}

bool TUnaryOperation::operandsAreNotNull()
{
	return m_operand != NULL;
}

TBinaryOperation::TBinaryOperation(Lexem* operat, List* list, int leftborder1, int rightborder1, int leftborder2, int rightborder2)
{
	int MinPriorityOperIndex = 0;
	keyWord = (char*)heap->get_mem(sizeof(char)*strlen(operat->GetKeyword()) + 1);
	strcpy(keyWord, operat->GetKeyword());
	m_operand1 = FindTheOperand(list, leftborder1, rightborder1, MinPriorityOperIndex);
	m_operand2 = FindTheOperand(list, leftborder2, rightborder2, MinPriorityOperIndex);
}

TValue TBinaryOperation::exec()
{
	TValue res1 = m_operand1->exec();
	TValue res2 = m_operand2->exec();
	TValue res;
	char* name = GetKeyWord();
	if (name[0] == '+' && name[1] == '\0')
	{
		if (!res1.isPointer() && !res2.isPointer())
		{
			res.setType(ct_double);
			res.setValue(res1.value() + res2.value());
		}
		if (res1.isPointer() && !res2.isPointer())
		{
			res.setType(ct_double);
			res.setValuePointer((double*)res1.valuepointer() + (int)res2.value());
		}
		if (!res1.isPointer() && res2.isPointer())
		{
			res.setType(ct_double);
			res.setValuePointer((int)res1.value() + (double*)res2.valuepointer());
		}
		if (res1.isPointer() && res2.isPointer()) 
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Попытка сложить указатели");
			system("pause");
			exit(0);
		}
	}
	if (name[0] == '-' && name[1] == '\0')
	{
		if (!res1.isPointer() && !res2.isPointer())
		{
			res.setType(ct_double);
			res.setValue(res1.value() - res2.value());
		}
		if (res1.isPointer() && !res2.isPointer())
		{
			res.setType(ct_double);
			res.setValuePointer((double*)res1.valuepointer() - (int)res2.value());
		}
		if (!res1.isPointer() && res2.isPointer() || (res1.isPointer() && res2.isPointer()) )
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Нельзя производить арифметические операции между указателем и НЕуказателем");
			system("pause");
			exit(0);
		}
	}
	if (name[0] == '*' && name[1] == '\0')
	{
		if (res1.isPointer() || res2.isPointer()) 
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Попытка умножать указатели");
			system("pause");
			exit(0);
		}
		res.setType(ct_double);
		res.setValue(res1.value() * res2.value());
	}
	if (name[0] == '/' && name[1] == '\0')
	{
		if (res1.isPointer() || res2.isPointer()) 
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Попытка делить указатели");
			system("pause");
			exit(0);
		}
		res.setType(ct_double);
		res.setValue(res1.value() / res2.value());
	}
	if (name[0] == '&' && name[1] == '\0')
	{
		if (res1.isPointer() || res2.isPointer()) 
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Попытка побитово умножать указатели");
			system("pause");
			exit(0);
		}
		res.setType(ct_int);
		if (res1.type() == ct_int && res2.type() == ct_int)
			res.setValue((int)res1.value() & (int)res2.value());
		else 
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Попытка производить операции побитового умножения НЕ с int");
			system("pause");
			exit(0);
		}
	}
	if (name[0] == '|' && name[1] == '\0')
	{
		if (res1.isPointer() || res2.isPointer()) 
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Попытка побитово складывать указатели");
			system("pause");
			exit(0);
		}
		res.setType(ct_int);
		if (res1.type() == ct_int && res2.type() == ct_int)
			res.setValue((int)res1.value() | (int)res2.value());
		else 
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Попытка производить операции побитового сложения НЕ с int");
			system("pause");
			exit(0);
		}
	}
	if (name[0] == '<' && name[1] == '<')
	{
		if (res1.isPointer() || res2.isPointer()) 
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Попытка побитового сдвига указателя");
			system("pause");
			exit(0);
		}
		res.setType(ct_int);
		if (res1.type() == ct_int && res2.type() == ct_int)
			res.setValue((int)res1.value() << (int)res2.value());
		else 
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Попытка производить операции побитового сдвига НЕ с int");
			system("pause");
			exit(0);
		}
	}
	if (name[0] == '>' && name[1] == '>')
	{
		if (res1.isPointer() || res2.isPointer()) 
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Попытка производить операции побитового сдвиг с указателями");
			system("pause");
			exit(0);
		}
		res.setType(ct_int);
		if (res1.type() == ct_int && res2.type() == ct_int)
			res.setValue((int)res1.value() >> (int)res2.value());
		else
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Попытка производить операции побитового сдвига НЕ с int");
			system("pause");
			exit(0);
		}
	}
	if (name[0] == '&' && name[1] == '&')
	{
		if (res1.isPointer() || res2.isPointer()) 
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Попытка применения операции логического умножения на указатели");
			system("pause");
			exit(0);
		}
		res.setType(ct_bool);
		if (res1.type() == ct_bool && res2.type() == ct_bool)
			res.setValue((bool)res1.value() && (bool)res2.value());
		else
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Попытка производить операции логического умножения НЕ с bool");
			system("pause");
			exit(0);
		}
	}
	if (name[0] == '|' && name[1] == '|')
	{
		if (res1.isPointer() || res2.isPointer()) 
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Попытка применения операции логического сложения на указатели");
			system("pause");
			exit(0);
		}
		res.setType(ct_bool);
		if (res1.type() == ct_bool && res2.type() == ct_bool)
			res.setValue((bool)res1.value() || (bool)res2.value());
		else 
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Попытка производить операции логического сложения НЕ с bool");
			system("pause");
			exit(0);
		}

	}
	if (name[0] == '=' && name[1] == '=')
	{
		res.setType(ct_bool);
		if (!res1.isPointer() && !res2.isPointer())
		{
			if (res1.type() != ct_bool && res2.type() != ct_bool)
				res.setValue(res1.value() == res2.value());
			else res.setValue((bool)res1.value() == (bool)res2.value());
		}
		if (res1.isPointer() && res2.isPointer())
		{
			res.setValue(res1.valuepointer() == res2.valuepointer());
		}
	}
	if (name[0] == '!' && name[1] == '=')
	{
		res.setType(ct_bool);
		if (!res1.isPointer() && !res2.isPointer())
		{
			if (res1.type() != ct_bool && res2.type() != ct_bool)
				res.setValue(res1.value() != res2.value());
			else res.setValue((bool)res1.value() != (bool)res2.value());
		}
		if (res1.isPointer() && res2.isPointer())
		{
			res.setValue(res1.valuepointer() != res2.valuepointer());
		}
	}
	if (name[0] == '<' && name[1] == '=')
	{
		if (res1.isPointer() || res2.isPointer()) 
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Нельзя сравнивать указатели");
			system("pause");
			exit(0);
		}
		res.setType(ct_bool);
		if (res1.type() != ct_bool && res2.type() != ct_bool)
			res.setValue(res1.value() <= res2.value());
		else res.setValue((bool)res1.value() <= (bool)res2.value());
	}
	if (name[0] == '>' && name[1] == '=')
	{
		if (res1.isPointer() || res2.isPointer()) 
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Нельзя сравнивать указатели");
			system("pause");
			exit(0);
		}
		res.setType(ct_bool);
		if (res1.type() != ct_bool && res2.type() != ct_bool)
			res.setValue(res1.value() >= res2.value());
		else res.setValue((bool)res1.value() >= (bool)res2.value());
	}
	if (name[0] == '>' && name[1] == '\0')
	{
		if (res1.isPointer() || res2.isPointer()) 
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Нельзя сравнивать указатели");
			system("pause");
			exit(0);
		}
		res.setType(ct_bool);
		if (res1.type() != ct_bool && res2.type() != ct_bool)
			res.setValue(res1.value() > res2.value());
		else res.setValue((bool)res1.value() > (bool)res2.value());
	}
	if (name[0] == '<' && name[1] == '\0')
	{
		if (res1.isPointer() || res2.isPointer()) 
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Нельзя сравнивать указатели");
			system("pause");
			exit(0);
		}
		res.setType(ct_bool);
		if (res1.type() != ct_bool && res2.type() != ct_bool)
			res.setValue(res1.value() < res2.value());
		else res.setValue((bool)res1.value() < (bool)res2.value());
	}
	if (name[0] == '=' && name[1] == '\0')
	{
		res.setType(res1.type());
		Lexem* vari = m_operand1->GetLexem();
		if (!res1.isPointer() && !res2.isPointer())
		{
			if (vari && vari->GetLexemType() == lt_variable)
			{
				res.setValue(res2.value());
				switch (res.type())
				{
				case ct_bool:
				{
					bool v = (bool)res2.value();
					vari->SetVar(&v);
					break;
				}
				case ct_int:
				{
					int v = (int)res2.value();
					vari->SetVar(&v);
					break;
				}
				case ct_char:
				{
					char v = (char)res2.value();
					vari->SetVar(&v);
					break;
				}
				case ct_double:
				{
					double v = res2.value();
					vari->SetVar(&v);
					break;
				}
				default:
					break;
				}
			}
			if (m_operand1->GetKeyWord()[0] == '*' || m_operand1->GetKeyWord()[0] == '[')
			{
				switch (res1.type())
				{
					//ct_double, ct_int, ct_bool, ct_char
				case ct_double:
				{
					double v = res2.value();
					memcpy(res1.valuepointer(), &v, sizeof(double));
					break;
				}
				case ct_int:
				{
					int v = res2.value();
					memcpy(res1.valuepointer(), &v, sizeof(int));
					break;
				}
				case ct_bool:
				{
					bool v = res2.value();
					memcpy(res1.valuepointer(), &v, sizeof(bool));
					break;
				}
				case ct_char:
				{
					char v = res2.value();
					memcpy(res1.valuepointer(), &v, sizeof(char));
					break;
				}
				default:
					break;
				}
			}
		}
		if (res1.isPointer() && res2.isPointer())
		{
			if (res1.pointerlevel() != res2.pointerlevel()) 
			{
				ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
					"Попытка присвоить указатели, не одинакового уровня");
				system("pause");
				exit(0);
			}
			res.setValuePointer(res2.valuepointer());
			res.setPointerLevel(res2.pointerlevel());
			vari->SetVar(res2.valuepointer());
		}
		if (!res1.isPointer() && res2.isPointer() || res1.isPointer() && !res2.isPointer())
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Попытка присвоить указатели, не одинакового уровня");
			system("pause");
			exit(0);
		}
	}
	if (name[0] == '[' && name[1] == '\0')
	{ 
		if (!res.isPointer()) 
		{
			ReportError((m_operand1->GetLexem())->GetLineNumInCode(), (m_operand1->GetLexem())->GetCharNumInLine(),
				"Попытка взять значение по индексу у НЕуказателя");
			system("pause");
			exit(0);
		}
		res.setType(res1.type());
		Lexem* lex = m_operand1->GetLexem();
		if (res1.pointerlevel() == 1 || lex->GetVarPointCounter() == 1) // int* a; *a;
		{
			res.setValuePointer((void**)res1.valuepointer() + (int)res2.value());
			switch (res1.type())
			{
			case ct_bool:
				res.setValue((double)*((bool*)res1.valuepointer() + (int)res2.value()));
				break;
			case ct_char:
				res.setValue((double)*((char*)res1.valuepointer() + (int)res2.value()));
				break;
			case ct_int:
				res.setValue((double)*((int*)res1.valuepointer() + (int)res2.value()));
				break;
			case ct_double:
				res.setValue(*((double*)res1.valuepointer() + (int)res2.value()));
				break;
			}
		}
		if (res1.pointerlevel() > 1)  // int********* a; *a;
		{
			void** kostyl = (void**)res1.valuepointer() + (int)res2.value();
			void* secondkostyl = *kostyl;
			res.setValuePointer(secondkostyl);
			res.setPointerLevel(res1.pointerlevel() - 1);
		}
	}
	return res;
}

void TBinaryOperation::print()
{
	char* name = GetKeyWord();
	m_operand1->print();
	cout << name;
	m_operand2->print();
}

bool TBinaryOperation::operandsAreNotNull()
{
	return m_operand1 != NULL && m_operand2 != NULL;
}

TernarOperation::TernarOperation(Lexem* operat, List* list, int leftborder1, int rightborder1,
												int leftborder2, int rightborder2,
												int leftborder3, int rightborder3)
{
	int MinPriorityOperIndex = 0;
	keyWord = (char*)heap->get_mem(sizeof(char)*(strlen(operat->GetKeyword()) + 1));
	strcpy(keyWord, operat->GetKeyword());
	condition = (TBinaryOperation*)FindTheOperand(list, leftborder1, rightborder1, MinPriorityOperIndex);
	branch1 = FindTheOperand(list, leftborder2, rightborder2, MinPriorityOperIndex);
	branch2 = FindTheOperand(list, leftborder3, rightborder3, MinPriorityOperIndex);
}

TernarOperation::~TernarOperation()
{
}

bool TernarOperation::operandsAreNotNull()
{
	return condition != NULL;
}

TValue TernarOperation::exec()
{
	if (condition->exec().value()) return branch1->exec();
	else return branch2->exec();
}

void TernarOperation::print()
{
	condition->print();
	cout << '?';
	branch1->print();
	cout << ':';
	branch2->print();
}

TStandardFunc::TStandardFunc(Lexem* lex, List* Lexems, int left, int right)
{
	keyWord = (char*)heap->get_mem(sizeof(char)*strlen(lex->GetKeyword()) + 1);
	strcpy(keyWord, lex->GetKeyword());
	int min = 0;
	m_param = FindTheOperand(Lexems, left, right, min);
}

TValue TStandardFunc::exec()
{
	TValue result = *new TValue();
	if (!strcmp(keyWord, "output"))
	{
		m_param->exec().print();
		cout << endl;
	}
	if (!strcmp(keyWord, "input"))
	{
		double d;
		cin >> d;
		bool ba;
		int ia;
		char ich;
		switch ((TypTypes)m_param->GetLexem()->GetVarTypeNum())
		{
		case tt_bool:
			ba = (bool)d;
			((TVariable*)m_param)->GetLexem()->SetVar(&ba);
			break;
		case tt_int:
			ia = (int)d;
			((TVariable*)m_param)->GetLexem()->SetVar(&ia);
			break;
		case tt_double:
			((TVariable*)m_param)->GetLexem()->SetVar(&d);
			break;
		case 4:
			ich = (char)d;
			((TVariable*)m_param)->GetLexem()->SetVar(&ich);
			break;
		}
	}
	return result;
}

void TStandardFunc::print()
{
	cout << "throw new NotImplementedException(\"void TStandardFunc::print()\");\n";
}

TList::TList()
{
	Trees = new List(32);
}

TList::~TList()
{

}

TValue TList::exec()
{

	TValue* res = new TValue();
	TNode* node;
	for (size_t i = 0; i < Trees->count(); i++)
	{
		node = (TNode*)Trees->get(i);
		res = &(node)->exec();
	}
	return *res;
}

TValue TList::exec(InterruptTypes &it)

{
	TValue* res = new TValue();
	TNode* node;
	for (size_t i = 0; i < Trees->count(); i++)
	{
		node = (TNode*)Trees->get(i);
		if (node->GetKeyWord() != NULL)
		{
			if (!strcmp(node->GetKeyWord(), "break"))
			{
				it = it_break;
				break;
			}
			if (!strcmp(node->GetKeyWord(), "continue"))
			{
				it = it_continue;
				break;
			}
		}
		res = &(node)->exec();
	}
	return *res;
}

TValue TList::execSwitch(char* smth)
{
	TValue* res = new TValue;
	TCase* node;
	for (size_t i = 0; i < Trees->count(); i++)
	{
		node = (TCase*)Trees->get(i);
		if (node->GetCT() == ct_case && (!strcmp(node->GetName(), smth)) || node->GetCT() == ct_default)
		{
			res = &(node)->exec();
			return *res;
		}
	}
	return *res;
}

void TList::print()
{
	for (size_t i = 0; i < Trees->count(); i++)
	{
		((TNode*)Trees->get(i))->print();
		cout << endl;
	}
}

void TList::addNode(TNode* node)
{
	Trees->add(node);
}

TNode* TList::GetNode(int i)
{
	return (TNode*)Trees->get(i);
}

int TList::NodeCount()
{
	return Trees->count();
}