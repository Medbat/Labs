#include "stdafx.h"
#include "Compiler.h"
#include "Heap.h"
#include "List.h"
#include "hash.h"
#include "Identificator.h"
#include <fstream>
#include <locale>
#include "Automat.h"
#include "Tree.h"

Compiler::Compiler()
{
	Initialize();
}

char* Compiler::MakeAWord(int num)
{
	char* temp = (char*)heap->get_mem(sizeof(char*));
	for (int i = 0; i<num; i++)
	{
		temp[i] = (char)heap->get_mem(sizeof(char));
	}
	temp[num] = '\0';
	return temp;
}

bool Compiler::IsConst(char* a)
{
	return a[0] == 'z' || a[0] == 'd' || a[0] == 'h' || a[0] == 'r' ||
		a[0] == 'e' || a[0] == 'o';
}

bool Compiler::IsDivisorOrBracket(char* a)
{
	return a[0] == ';' || a[0] == ',' || a[0] == '(' || a[0] == ')' || a[0] == ':' || a[0] == ']';
}

bool Compiler::IsStandardFunction(char* name)
{
	return !strcmp(name, "sin") || !strcmp(name, "cos") || !strcmp(name, "printf") || !strcmp(name, "min") || !strcmp(name, "max");
}

void Compiler::DeleteApostrophes(char* a)
{
	int length = strlen(a) - 2;
	memcpy(a, &(a)[1], length);
	a[length] = '\0';
}

bool isRightToLeftOper(Lexem* a)
{
	int num = a->OperGetPriority();
	return num == 3 || num == 15 || num == 16 || a->GetName()[0]=='[';
}

Lexem* RecursiveTreeer(List* Lexems, int leftborder, int rightborder, int& MinPriorityOperIndex)
{

	// ����� � ������ ����������� ������
	Lexem* templex = (Lexem*)Lexems->get(leftborder);
	//if ((templex->GetState())[0] == '(')
	//{
	//	// ��� ����������� ������?
	//	int unclosedBracketCounter = 1;
	//	for (int j = leftborder + 1; j <= rightborder; j++)
	//	{
	//		templex = (Lexem*)Lexems->get(j);
	//		if ((templex->GetState())[0] == '(') unclosedBracketCounter++;
	//		if ((templex->GetState())[0] == ')') unclosedBracketCounter--;
	//		if (unclosedBracketCounter == 0 && j != rightborder ) break;  // ��� �� ����������� ������!
	//		if (unclosedBracketCounter == 0 && j == rightborder )  // ��� ����������� ������! 
	//		{
	//			return RecursiveTreeer(Lexems, leftborder + 1, rightborder - 1, MinPriorityOperIndex);
	//		}
	//		if (unclosedBracketCounter < 0)
	//		{
	//			cout << "Error! Overclosed bracket!";
	//			return 0;
	//		}
	//	}
	//	if (unclosedBracketCounter > 0)
	//	{
	//		cout << "Error! Unclosed bracket!";
	//		return 0;
	//	}
	//}
	// ��� ������������ �������?
	if (leftborder == rightborder)
	{
		return templex;
	}
	// ����� �������� � ����������� �����������, �� ���� ������� �� �������� 
	Lexem* MinPriorityLexem = NULL;
	MinPriorityOperIndex = rightborder + 1;
	int unclosedBracketCounter = 0;
	for (int j = leftborder; j <= rightborder; j++)
	{
		templex = (Lexem*)Lexems->get(j);
		if (unclosedBracketCounter > 0)
		{
			if ((templex->GetState())[0] == '(') unclosedBracketCounter++;
			if ((templex->GetState())[0] == ')') unclosedBracketCounter--;
			continue; // ������� ��������� � �������
		}

		if (templex->GetLexemType() == lt_operator)
		{
			if (!MinPriorityLexem ||
				templex->OperGetPriority() > MinPriorityLexem->OperGetPriority() ||
				templex->OperGetPriority() == MinPriorityLexem->OperGetPriority() && isRightToLeftOper(templex))
			{
				MinPriorityLexem = templex;
				MinPriorityOperIndex = j;
			}
		}
		if ((templex->GetState())[0] == '(') unclosedBracketCounter++;
	}
	return MinPriorityLexem ? MinPriorityLexem : (Lexem*)Lexems->get(leftborder);
	// �������� � ������
}

void Compiler::Initialize()
{
	automatsNumber = 5;
	automats = (Automat**)heap->get_mem(automatsNumber * sizeof(Automat*));
	automats[0] = new Automat("Word.txt");
	automats[1] = new Automat("NumConst.txt");
	automats[2] = new Automat("CharStrConst.txt");
	automats[3] = new Automat("Operators.txt");
	automats[4] = new Automat("Braces.txt");

	standtypes = new Automat("StandartTypes.txt");
}

bool Compiler::CheckWithAutomatons(char* sourceCodeFile, List* Lexems)
{
	char* buf = (char*)heap->get_mem(1024 * sizeof(char));
	int ok = 0;
	int strNum = 1;
	int chNum = 0;
	char nextStr;
	ifstream in(sourceCodeFile);
	while (!in.eof())
	{
		ok = 0;
		in >> buf;
		int tempLen = strlen(buf);
		while (buf[0] != '\0')
		{
			for (int i = 0; i < automatsNumber; i++)
			{
				ok = automats[i]->Check(buf);
				if (ok == 0)
				{
					ReportError(strNum, chNum, automats[i]->getErrorMessage());
					return false;
				}
				if (ok == 1)
				{
					automats[i]->AddLexem(Lexems, strNum, chNum);
					chNum += tempLen - strlen(buf);
					tempLen = strlen(buf);
					break;
				}
			}
			if (ok == 2)
			{
				ReportError(strNum, chNum, "Fedor lalka is this");
				//cout << "What is this?";
				return false;
			}
		}
		in.get(nextStr);
		if (nextStr == '\n') { strNum++; chNum = 0; }
		chNum++;
	}
	return true;
}

bool Compiler::NestingLevelSearching(List* Lexems)
{
	int level = 0;// ������� (�������, �����) �����������
	int* nestingLevel = (int*)heap->get_mem(1024 * sizeof(int));//������ �����������
	for (int j = 0; j < 1024; j++)//�������� ��� ����
		nestingLevel[j] = 0;
	for (int i = 0; i < Lexems->count(); i++)// �� ���� ��������
	{

		Lexem* tempLexem = (Lexem*)Lexems->get(i);//������� �������

		if (!strcmp(tempLexem->GetState(), "{"))
			nestingLevel[level++]++;
		if (!strcmp(tempLexem->GetState(), "}"))
			level--;
		//����������� ������� ���� ���������� � ������� ���������
		if (!strcmp(tempLexem->GetState(), "var"))
		{
			char tempNestingLevel[1024] = "";
			for (int j = 0; j < level; j++)
			{
				char num[1024];
				_itoa(nestingLevel[j], num, 10);
				strcat(tempNestingLevel, num);
				strcat(tempNestingLevel, ".");
			}
			tempLexem->SetNestingLevel(tempNestingLevel, level);
		}
	}
	bool fidanLalka = true;//����� �������� ����
	heap->free_mem(nestingLevel);
	return fidanLalka;
}

bool Compiler::ClarifyLexems(List *Lexems)
{
	char* buf = (char*)heap->get_mem(1024 * sizeof(char));
	char* autobuf = (char*)heap->get_mem(1024 * sizeof(char));
	Lexem* templex;
	int ok = 0;
	bool itWillBeNewVariable = false;
	for (int i = 0; i < Lexems->count(); i++)
	{
		templex = (Lexem*)Lexems->get(i);
		strcpy(buf, templex->GetState());
		if (!strcmp(templex->GetName(), "output") || !strcmp(templex->GetName(), "input"))
		{
			templex->SwitchToStandardFunc();
			Lexems->set(i, templex);
			continue;
		}
		if (!strcmp(templex->GetState(), "charend") || !strcmp(templex->GetState(), "strend"))
		{
			
		}
		if (buf[0] == '#') // ������ ����� define
		{
			templex->SwitchToPreProc();
			Lexems->set(i, templex);
			continue;
		}
		if (buf[0] == '{' || buf[0] == '}') // �������� ������
		{
			templex->SwitchToBrace(buf[0]);
			Lexems->set(i, templex);
			continue;
		}
		if (buf[0] == '(' || buf[0] == ')') // ������� ������
		{
			templex->SwitchToPar(buf[0]);
			Lexems->set(i, templex);
			continue;
		}
		if (buf[0] == ']') // ���������� ������
		{
			templex->SwitchToSquareBracket(buf[0]);
			Lexems->set(i, templex);
			continue;
		}
		if (buf[0] == ',')
		{
			templex->SwitchToComma();
			Lexems->set(i, templex);
			continue;
		}
		if (buf[0] == 'v') // ������������� ?
		{
			strcpy(buf, templex->GetName());
			ok = standtypes->Check(buf);
			if (ok == 1)                     // ��� ����?
			{
				itWillBeNewVariable = true;
				templex->SwitchToType();
				Lexems->set(i, templex);
				continue;
			}
			// standard func
			if (IsStandardFunction(templex->GetName()))
			{
				templex->SwitchToStandardFunc();
				Lexems->set(i, templex);
				continue;
			}
			//Cond
			if (!strcmp(templex->GetName(), "if") || !strcmp(templex->GetName(), "else") || !strcmp(templex->GetName(), "while") || !strcmp(templex->GetName(), "switch") || !strcmp(templex->GetName(), "case") || !strcmp(templex->GetName(), "default"))
			{
				templex->SwitchToCond();
				Lexems->set(i, templex);
				continue;
			}
			//Interrupt
			if (!strcmp(templex->GetName(), "continue") || !strcmp(templex->GetName(), "break"))
			{
				templex->SwitchToInterrupt();
				Lexems->set(i, templex);
				continue;
			}
			if (itWillBeNewVariable == false && Base->find(templex->GetKeyword()) == NULL)
			{
				ReportError(templex->lineNumInCode, templex->charNumInLine, 
					"Variable doesn't exist in current context");
				return false;
			}
			templex->SwitchToVariable();  // ����������? �������?
			//Lexems->set(i, templex);
			Base->auto_create(templex, itWillBeNewVariable);
			if (!itWillBeNewVariable)
				Lexems->set(i, templex);
			itWillBeNewVariable = false;
			continue;
		}
		if (IsConst(buf))   // ��������� ?
		{
			strcpy(autobuf, templex->GetName());
			templex->SwitchToConst(buf, atof(autobuf));
			Lexems->set(i, templex);
			continue;
		}
		if (buf[0] == 's')  // ������?
		{
			templex->SwitchToStrConst();
		}
		if (IsDivisorOrBracket(buf))  // ������? �����������?
		{
			templex->SwitchToNothing();
			Lexems->set(i, templex);
			continue;
		}
		templex->SwitchToOper();  // ��� ��������
		Lexems->set(i, templex);
	}
	return true;
}

bool Compiler::ClarifyOperators(List* Lexems)
{
	Lexem *prevlex, *nextlex, *templex;
	bool isleftoperand, isrightoperand;
	bool isBinar = false;
	for (int i = 0; i < Lexems->count(); i++)
	{
		templex = (Lexem*)Lexems->get(i);
		if (templex->GetLexemType() == lt_operator)
		{
			isleftoperand = isrightoperand = false;
			if (!strcmp(templex->GetName(), "/")
				|| !strcmp(templex->GetName(), "==")
				|| !strcmp(templex->GetName(), ">=")
				|| !strcmp(templex->GetName(), "<=")
				|| !strcmp(templex->GetName(), "<<")
				|| !strcmp(templex->GetName(), ">>")
				|| !strcmp(templex->GetName(), ">")
				|| !strcmp(templex->GetName(), "<")
				|| !strcmp(templex->GetName(), "=")
				|| !strcmp(templex->GetName(), "!=")
				|| !strcmp(templex->GetName(), "&&")
				|| !strcmp(templex->GetName(), "||"))
			{
				if (isBinar)
				{
					ReportError(templex->GetLineNumInCode(), templex->charNumInLine, "Operand expected.");
					return false;
				}
				else
				{
					isBinar = true;
					templex->OperSwitchToBinar();
					continue;
				}
			}
			else
				isBinar = false;
			if (i == 0)
				prevlex = NULL;                    // ���������� - �������� ��������
			else
				prevlex = (Lexem*)Lexems->get(i - 1);
			if (i == Lexems->count() - 1)
				nextlex = NULL;
			else
				nextlex = (Lexem*)Lexems->get(i + 1);

			if (prevlex->GetLexemType() == lt_variable || prevlex->GetLexemType() == lt_const ||
				prevlex->GetName()[0] == ')' || prevlex->GetName()[0] == ']')
				isleftoperand = true;

			if (nextlex->GetLexemType() == lt_variable || nextlex->GetLexemType() == lt_const ||
				nextlex->GetName()[0] == '(' || nextlex->GetName()[0] == '+' || (nextlex->GetName())[0] == '-' ||
				nextlex->GetName()[0] == '*' || (nextlex->GetName())[0] == '&')
				isrightoperand = true;

			// ��������� ��������
			if (isleftoperand && !isrightoperand)
				templex->OperSwitchToLeftunar();
			else
				if (!isleftoperand && isrightoperand)
				templex->OperSwitchToRightunar();
				else
					if (isleftoperand && isrightoperand)
					{
						if ((templex->GetName())[0] == '?')
							templex->OperSwitchToTernar();
						else
							templex->OperSwitchToBinar();
					}
					else
					{
						ReportError(templex->lineNumInCode, templex->charNumInLine, "Wrong operator");
						return false;
					}

			// ��������� ��������
			if (!templex->CheckOper())
			{
				ReportError(templex->lineNumInCode, templex->charNumInLine, "Wrong operator");
				return false;
			}

			templex->OperAssignPriority();
		}
		else
			isBinar = false;
	}
	return true;
}

void ReportError(int lineNum, int charNum, char* message)
{
	cout << "Error (line " << lineNum << ", char " << charNum << "): \n" << message << endl;
}

bool Compiler::Compile(char* sourceCodeFile)
{
	/*
	int line;
	char ch;
	bool flag = ValidateBraces(sourceCodeFile, line, ch);
	if (!flag)
	{
		cout << "error in line " << line << " brace " << ch << endl;
	}
	*/

	List* Lexems = new List(sizeof(Lexem));
	TList* tree;
	if (!CheckWithAutomatons(sourceCodeFile, Lexems)             // ����������� ������ ����������
		|| !ValidateBraces(sourceCodeFile)						 // ��������� ��� ������
		|| !NestingLevelSearching(Lexems)                        // ������� ����������� ����������
		|| !ClarifyLexems(Lexems)                                // �������� �������
		|| !ClarifyOperators(Lexems)                             // ���������� ��������
		|| !FindNoOperation(Lexems)                              // ���� �� ������ ��� ����������/���������
		|| !DefineReplacement(Lexems)                            // ��� #define
		|| !(tree = BuildTree(Lexems, 0, Lexems->count() - 1))   // �������� ������� ������
		)
		return false;

	cout << "\n���������� ������\n";
	tree->exec();
	return true;
}

void Compiler::PrintLexemList(List* list)
{
	for (int i = 0; i < list->count(); i++)
	{
		cout << ((Lexem*)list->get(i))->ToCharStar() << ' ';
	}
	cout << endl;
}

TList* Compiler::BuildTree(List* Lexems, int left, int right)
{
	// ��������� ������ - ���������� ������
	TList* MYSuperReadyTreeBlyat = new TList();
	TNode* curnode = NULL;
	int MinPriorityOperIndex;
	int PointCounter = 0;
	TypTypes t;
	Lexem* templex = NULL;
	int leftborder = left;
	int rightborder = right;
	for (int i = left; i <= right; i++)
	{
		templex = (Lexem*)Lexems->get(i);
		if (templex->GetLexemType() != lt_cond)
		{
			// �������� ������ �������� �� ����� � �������
			if (templex->GetLexemType() == lt_brace && (i == left || ((Lexem*)Lexems->get(i - 1))->GetName()[0] == ';'))
			{
				TList* NewList = NULL;
				// ����� ����������� �������� ������

				MYSuperReadyTreeBlyat->addNode(NewList = HandleBlockCode(Lexems, i));
				leftborder = rightborder = i + 1;
				continue;
			}


			if ((templex->GetName())[0] == ';')
			{
				templex = (Lexem*)Lexems->get(leftborder);
				if (templex->GetLexemType() == lt_type)    // ������, ����� ������ ����������� ����������.
				{
					leftborder++;
					t = templex->GetTypTyp();
					templex = (Lexem*)Lexems->get(leftborder);
					PointCounter = 0;
					while (templex->GetLexemType() == lt_operator && templex->GetName()[0] == '*')
					{
						PointCounter++;
						templex = (Lexem*)Lexems->get(++leftborder);
					}
					if (templex->GetLexemType() == lt_variable)
					{
						bool isStaticArray=false;
						if (PointCounter > 0)
						{
							templex->SetVarAdress(heap->get_mem(sizeof(void*)));
						}
						else
						{
						    //������ ����� ����� ����������� ����������� ������
							List* arraysizes = new List(sizeof(int));
							int seeker = leftborder + 1;
							Lexem* lexforindex = (Lexem*)Lexems->get(seeker);
							int* value = (int*)heap->get_mem(sizeof(int));
							while (lexforindex->GetName()[0] == '[')
							{
								lexforindex = (Lexem*)Lexems->get(++seeker);
								if (lexforindex->GetLexemType() != lt_const || lexforindex->GetConstTyp() != ct_int) 
								{
									ReportError(lexforindex->GetLineNumInCode(), lexforindex->GetCharNumInLine(),
										"��������� ��������� ��� ����� \n");
									return NULL;
								}
								*value = (int)lexforindex->GetNumericConstValue();
								arraysizes->add(value);
								lexforindex = (Lexem*)Lexems->get(++seeker);
								if (lexforindex->GetName()[0] != ']') 
									{
										ReportError(lexforindex->GetLineNumInCode(), lexforindex->GetCharNumInLine(),
											"�������� ������ ']' \n");
										return NULL;
									}
								lexforindex = (Lexem*)Lexems->get(++seeker);
							}
							PointCounter = arraysizes->count();
							heap->free_mem(value);
							// ���� ���������� �������� ������ ��� �������!!!
							/*int arrayelements = 1;
							for (size_t i = 0; i < arraysizes->count(); i++)
							{
								arrayelements *= *(int*)arraysizes->get(i);
							}*/

							if (PointCounter)
							{
								void** pointertogetmem = (void**)templex->GetVarAdress();
								GetMemForArrayR(pointertogetmem, arraysizes, 0, t);
								templex->SetVarAdress(pointertogetmem);
								isStaticArray = true;
							}
							else switch (t)
							{
							case tt_bool:
								templex->SetVarAdress((bool*)heap->get_mem(sizeof(bool)));
								break;
							case tt_int:
								templex->SetVarAdress((int*)heap->get_mem(sizeof(int)));
								break;
							case tt_double:
								templex->SetVarAdress((double*)heap->get_mem(sizeof(double)));
								break;
							case tt_char:
								templex->SetVarAdress((char*)heap->get_mem(sizeof(char)));
								break;
							default:
								break;
							}
						}
						templex->SetVarTypeNum(t);
						templex->SetVarPointCounter(PointCounter);

						if (!Base->find(templex->GetKeyword())) 
						{
							char* s = "�� �����";
							strcat(s, (char*)templex->GetKeyword());
							strcat(s, "������-��");
							ReportError(templex->GetLineNumInCode(), templex->GetCharNumInLine(), s);
							return NULL;
						}
						
						Base->find(templex->GetKeyword())->SetVarAdress(templex->GetVarAdress());
						Base->find(templex->GetKeyword())->SetVarTypeNum(t);
						Base->find(templex->GetKeyword())->SetVarPointCounter(PointCounter);

						if (isStaticArray)
						{
							leftborder = rightborder = i + 1;
							continue;
					}
					
					}



					if (!Base->find(templex->GetKeyword()))
					{
						char* s = "�� �����";
						strcat(s, (char*)templex->GetKeyword());
						strcat(s, "������-��");
						ReportError(templex->GetLineNumInCode(), templex->GetCharNumInLine(), s);
						return NULL;
					}
					Base->find(templex->GetKeyword())->SetVarAdress(templex->GetVarAdress());
					Base->find(templex->GetKeyword())->SetVarTypeNum(t);
					Base->find(templex->GetKeyword())->SetVarPointCounter(PointCounter);



					//for (int n = leftborder; n < Lexems->count(); n++)
					//{
					//	templex = (Lexem*)Lexems->get(n);
					//	if (templex->GetLexemType() == var && strcmp(templex->GetKeyword(), buf) == 0)
					//	{
					//		templex->SetVarTypeNum(t);
					//		templex->SetVarAdress(varConnector);
					//	}
					//}
				}

				rightborder = i - 1;
				MinPriorityOperIndex = 0;
				templex = RecursiveTreeer(Lexems, leftborder, rightborder, MinPriorityOperIndex);
				int doubleDotIndex = MinPriorityOperIndex;
				//TList* params = NULL;
				switch (templex->GetLexemType())
				{
				case lt_standardFunc:
					left = leftborder + 1;
					leftborder++;
					while (leftborder < Lexems->count())
					{
						if (!strcmp(((Lexem*)Lexems->get(leftborder))->GetName(), ";"))
						{
							//params = BuildTree(Lexems, left + 1, leftborder);
							// ���� ���!
							// params = params->addNode(params->FindTheOperand(Lexems, left, leftborder, 0));
							break;
						}
						leftborder++;
					}
					leftborder -= 2;
					MYSuperReadyTreeBlyat->addNode(new TStandardFunc(templex, Lexems, left + 1, leftborder));
					break;
				case lt_variable:
					MYSuperReadyTreeBlyat->addNode(new TVariable(templex->GetKeyword()));
					break;
				case lt_const:
					MYSuperReadyTreeBlyat->addNode(new TConst(templex));
					break;
				case lt_operator:
					switch (templex->GetOperTyp())
					{
					case ot_leftunar:
						MYSuperReadyTreeBlyat->addNode(new TUnaryOperation(templex, Lexems, leftborder, MinPriorityOperIndex - 1));
						break;
					case ot_rightunar:
						MYSuperReadyTreeBlyat->addNode(new TUnaryOperation(templex, Lexems, MinPriorityOperIndex + 1, rightborder));
						break;
					case ot_binar:
						MYSuperReadyTreeBlyat->addNode(new TBinaryOperation(templex, Lexems, leftborder, MinPriorityOperIndex - 1, MinPriorityOperIndex + 1, rightborder));
						break;
					case ot_ternar:
						while (((Lexem*)Lexems->get(doubleDotIndex))->GetName()[0] != ';' &&
							doubleDotIndex <= rightborder) doubleDotIndex++;
						MYSuperReadyTreeBlyat->addNode(new TernarOperation(templex, Lexems, leftborder, MinPriorityOperIndex - 1, MinPriorityOperIndex + 1, doubleDotIndex - 1, doubleDotIndex + 1, rightborder));
						break;
					default:
						break;
					}
					break;
				default:
					ReportError(templex->GetLineNumInCode(), templex->GetCharNumInLine(),
						"��� �� ����?! ���������� �������");
					system("pause");
					exit(0);
				}
				leftborder = rightborder = i + 1;
				//		// ����� � ������ ����������� ������
				//		templex = (Lexem*)Lexems->get(i);
				//		if ((templex->GetState())[0] == '(')
				//		{
				//			// ��� ����������� ������?
				//			int unclosedBracketCounter = 1;
				//			for (int j = leftborder + 1; j < rightborder; j++)
				//			{
				//				templex = (Lexem*)Lexems->get(i);
				//				if ((templex->GetState())[0] == '(') unclosedBracketCounter++;
				//				if ((templex->GetState())[0] == ')') unclosedBracketCounter--;
				//				if (unclosedBracketCounter == 0 && j != rightborder - 1) break;  // ��� �� ����������� ������!
				//				if (unclosedBracketCounter == 0 && j == rightborder - 1)  // ��� ����������� ������! 
				//				{
				//					leftborder++;
				//					rightborder--;
				//					break;
				//				}
				//				if (unclosedBracketCounter < 0)
				//				{
				//					cout << "Error! Overclosed bracket!";
				//					return - 3;
				//				}
				//			}
				//			if (unclosedBracketCounter > 0)
				//			{
				//				cout << "Error! Unclosed bracket!";
				//				return -3;
				//			}
				//		}
				//		// ��� ������������ �������?
				//		if (leftborder==rightborder)
				//		{
				//			templex = (Lexem*)Lexems->get(leftborder);
				//			if (templex->GetLexemType()==cons)  // ��� ���������? 
				//			{
				//				// �������� � ������!
				//				TConst* tcon = new TConst(templex);
				//				if (curnode == NULL) Trees->add(tcon);
				//				// ???
				//			}
				//			if (templex->GetLexemType() == var)  // ��� ����������? 
				//			{
				//				// �������� � ������!
				//				TVariable* tvar = new TVariable(templex);
				//				if (curnode == NULL) Trees->add(tvar);
				//				// ???
				//			}
				//		}
				//		// ����� �������� � ����������� �����������, �� ���� ������� �� �������� 
				//		Lexem* MinPriorityLexem = NULL;
				//		int MinPriorityLexemIndex = rightborder + 1;
				//		int unclosedBracketCounter = 0;
				//		for (int j = leftborder; j < rightborder; j++)
				//		{
				//			if (unclosedBracketCounter > 0) continue; // ������� ��������� � �������
				//			templex = (Lexem*)Lexems->get(i);
				//			
				//			if (templex->GetLexemType() == oper)
				//			{
				//				if (!MinPriorityLexem ||
				//					templex->OperGetPriority() > MinPriorityLexem->OperGetPriority() ||
				//					templex->OperGetPriority() == MinPriorityLexem->OperGetPriority() && isRightToLeftOper(templex))
				//				{
				//					MinPriorityLexem = templex;
				//					MinPriorityLexemIndex = j;
				//				}
				//			}
				//			if ((templex->GetState())[0] == '(') unclosedBracketCounter++;
				//			if ((templex->GetState())[0] == ')') unclosedBracketCounter--;
				//		}
				//		// �������� � ������
				//		switch (MinPriorityLexem->GetOperTyp())
				//		{
				//		case leftunar:
				//			Trees->add(new TUnaryOperation(MinPriorityLexem, Lexems, leftborder, MinPriorityLexemIndex - 1));
				//			break;
				//		case rightunar:
				//			Trees->add(new TUnaryOperation(MinPriorityLexem, Lexems, MinPriorityLexemIndex + 1, rightborder));
				//			break;
				//		case binar:
				//			break;
				//		case ternar:
				//			break;
				//		default:
				//			break;
				//		}
			}
		}
		//lt = lt_cond
		else
		{
			leftborder++;
			int leftCond = leftborder;
			int rightCond = rightborder - 1;
			//��������� ������� (� ������� �������)
			if (((Lexem*)(Lexems->get(leftborder)))->GetParTyp() != par_open && templex->GetCondTyp()
				!= ct_case && templex->GetCondTyp() != ct_default)
			{
				ReportError(((Lexem*)(Lexems->get(leftborder)))->GetLineNumInCode(), ((Lexem*)(Lexems->get(leftborder)))->GetCharNumInLine(), 
					"�������� ������ '('");
				return NULL;
			}
			TConst* cond_case = NULL;
			if (templex->GetCondTyp() == ct_case)
			{
				cond_case = new TConst((Lexem*)Lexems->get(leftborder));
			}
			else
				if (templex->GetCondTyp() == ct_default)
				{
				}
				else

			{
				leftborder++;
				rightborder = leftborder;
				while (rightborder < Lexems->count())
				{
					if (((Lexem*)(Lexems->get(rightborder)))->GetParTyp() == par_close)
						break;
					rightborder++;
				}
				if (((Lexem*)Lexems->get(rightborder))->GetParTyp() != par_close) 
				{
					ReportError(((Lexem*)(Lexems->get(rightborder)))->GetLineNumInCode(), ((Lexem*)(Lexems->get(rightborder)))->GetCharNumInLine(),
						"�������� ������ ')'\n");
					return NULL;
				}

				leftCond = leftborder;
				rightCond = rightborder - 1;

				rightborder++;
				leftborder = rightborder;
			}
			//��������� ����� ���� (� �������� �������)
			TList* bodyList = NULL;
			if (templex->GetCondTyp() != ct_case && templex->GetCondTyp() != ct_default)
				bodyList = HandleBlockCode(Lexems, leftborder);

			TList* elseBranchList = NULL;
			switch (templex->GetCondTyp())
			{
			case ct_if:
				if (((Lexem*)Lexems->get(leftborder + 1))->GetCondTyp() == ct_else)
				{
					leftborder++;
					leftborder++;
					elseBranchList = HandleBlockCode(Lexems, leftborder);
				}
				MYSuperReadyTreeBlyat->addNode(new TIf(Lexems, leftCond, rightCond, bodyList, elseBranchList));
				break;
			case ct_while:
				MYSuperReadyTreeBlyat->addNode(new TWhile(Lexems, leftCond, rightCond, bodyList));
				break;
			case ct_switch:
				MYSuperReadyTreeBlyat->addNode(new TSwitch(Lexems, leftCond, rightCond, bodyList));
				break;
			case ct_case:
				left = leftborder;
				while (leftborder < Lexems->count())
				{
					if (((Lexem*)Lexems->get(leftborder))->GetInterruptTyp() == it_break)
					{
						bodyList = BuildTree(Lexems, left, leftborder);
						break;
					}
					leftborder++;
				}
				if (((Lexem*)Lexems->get(leftborder))->GetInterruptTyp() != it_break)
				{
					ReportError(((Lexem*)(Lexems->get(leftborder)))->GetLineNumInCode(), ((Lexem*)(Lexems->get(leftborder)))->GetCharNumInLine(),
						"�������� \"break\"\n");
					return NULL;
				}

				MYSuperReadyTreeBlyat->addNode(new TCase(Lexems, cond_case, bodyList, ct_case));
				break;
			case ct_default:
				left = leftborder+1; 
				while (leftborder < Lexems->count())
				{
					if (((Lexem*)Lexems->get(leftborder))->GetInterruptTyp() == it_break)
					{
						bodyList = BuildTree(Lexems, left, leftborder);
						break;
					}
					leftborder++;
				}
				if (((Lexem*)Lexems->get(leftborder))->GetInterruptTyp() != it_break)
				{
					ReportError(((Lexem*)(Lexems->get(leftborder)))->GetLineNumInCode(), ((Lexem*)(Lexems->get(leftborder)))->GetCharNumInLine(),
						"�������� \"break\"\n");
					return NULL;
				}
				MYSuperReadyTreeBlyat->addNode(new TCase(Lexems, NULL, bodyList, ct_default));
				break;
			default:
				break;
			}
			leftborder++;
			i = leftborder;
		}
	}
	return MYSuperReadyTreeBlyat;
}

TList* Compiler::HandleBlockCode(List* Lexems, int &leftborder)
{
	int left = leftborder + 1;
	if (((Lexem*)Lexems->get(leftborder))->GetBraceTyp() == brace_open)
	{
		leftborder++;
		int counter = 1;
		while (leftborder < Lexems->count())
		{
			if (((Lexem*)Lexems->get(leftborder))->GetBraceTyp() == brace_close)
				counter--;
			if (((Lexem*)Lexems->get(leftborder))->GetBraceTyp() == brace_open)
				counter++;
			if (counter == 0)
				break;
			leftborder++;
		}
		if (((Lexem*)Lexems->get(leftborder))->GetBraceTyp() != brace_close)
		{
			ReportError(((Lexem*)(Lexems->get(leftborder)))->GetLineNumInCode(), ((Lexem*)(Lexems->get(leftborder)))->GetCharNumInLine(),
				"�������� ������ ')'");
			return NULL;
		}
		return BuildTree(Lexems, left, leftborder - 1);
	}
	else
	{
		left = leftborder;
		if (((Lexem*)Lexems->get(leftborder))->GetCondTyp() == ct_switch)
		{
			ReportError(((Lexem*)(Lexems->get(leftborder)))->GetLineNumInCode(), ((Lexem*)(Lexems->get(leftborder)))->GetCharNumInLine(),
				"�� �������� switch");
			return NULL;
		}
		while (leftborder < Lexems->count())
		{
			if (((Lexem*)Lexems->get(leftborder))->GetName()[0] == ';')
				return BuildTree(Lexems, left, leftborder);
			leftborder++;
		}
	}
	if (((Lexem*)Lexems->get(leftborder))->GetName()[0] != ';')
	{
		ReportError(((Lexem*)(Lexems->get(leftborder)))->GetLineNumInCode(), ((Lexem*)(Lexems->get(leftborder)))->GetCharNumInLine(),
			"�������� ������ ';'");
		return NULL;
	}
	return NULL;
}

TList* Compiler::CaseBody(List* Lexems, int &leftborder)
{
	return NULL;
}

bool Compiler::ValidateBraces(char* sourceCodeFile)
{
	int line = 1;
	int chNum = 0;
	char brace;
	char ch;
	char* stack = (char*)heap->get_mem(1024 * sizeof(char));
	int stackLength = 0;
	ifstream in(sourceCodeFile);
	while (!in.eof())
	{
		ch = 0;
		in.get(ch);
		chNum++;
		if (ch == '\n') { line++; chNum = 0; }

		if (ch == '[' || ch == '{' || ch == '(')
			stack[stackLength++] = ch;

		if (ch == ']' || ch == '}' || ch == ')')
		{
			if (stackLength == 0)
			{
				brace = ch;
				char* tempBrace = (char*)heap->get_mem(2 * sizeof(char));
				char* message = (char*)heap->get_mem(40 * sizeof(char));
				if (brace == ']') strcpy(tempBrace, "]");
				if (brace == '}') strcpy(tempBrace, "}");
				if (brace == ')') strcpy(tempBrace, ")");
				strcpy(message, "����������� ����������� ������ � ");
				strcat(message, tempBrace);
				ReportError(line, chNum, message);
				return false;
			}

			if (stack[stackLength - 1] == '[' && ch != ']' ||
				stack[stackLength - 1] == '{' && ch != '}' || stack[stackLength - 1] == '(' && ch != ')')
			{

				brace = stack[stackLength - 1];//=ch;
				char* tempBrace = (char*)heap->get_mem(2 * sizeof(char));
				char* message = (char*)heap->get_mem(15 * sizeof(char));
				if (brace == '[') strcpy(tempBrace, "]");
				if (brace == '{') strcpy(tempBrace, "}");
				if (brace == '(') strcpy(tempBrace, ")");
				strcpy(message, "��������� ");
				strcat(message,tempBrace);
				ReportError(line, chNum, message);
				return false;
			}
			stackLength--;
		}
	}
	return stackLength == 0;
}

void Compiler::ReplaceAll(char* sourceString, int lenOfSourceStr, char* oldValue, int lenOfOV, char* newValue, int lenOfNV)
{
	if (lenOfSourceStr == 0) return; // ������� �� ��������� ������
	char* buf = (char*)heap->get_mem(1024 * sizeof(char));
	int bufLength = 0;
	for (int i = 0; i < lenOfSourceStr; i++)
	{
		if (sourceString[i] != oldValue[0])
			buf[bufLength++] = sourceString[i];
		else
		{
			bool isEqual = true;
			for (int j = 0; j < lenOfOV; j++)
				if (sourceString[i + j] != oldValue[j])
				{
					isEqual = false;
					break;
				}
			if (isEqual)
			{
				for (int j = 0; j < lenOfNV; j++)
					buf[bufLength++] = newValue[j];
				i += lenOfOV - 1;
			}
			else
				buf[bufLength++] = sourceString[i];
		}
	}
	heap->free_mem(sourceString);
	sourceString = (char*)heap->get_mem(bufLength*sizeof(char));
	for (int i = 0; i < bufLength; i++)
		sourceString[i] = buf[i];
	heap->free_mem(buf);
}

bool Compiler::DefineReplacement(List* Lexems)
{
	for (int i = 0; i < Lexems->count(); i++)
	{
		Lexem* curLexem = (Lexem*)Lexems->get(i);
		if (curLexem->GetLexemType() == lt_preproc)
			if (!strcmp(((Lexem*)Lexems->get(i + 1))->GetName(), "define"))//���� ����� # ���� ������
			{
				Lexem* oldValue = (Lexem*)Lexems->get(i + 2);//��������� ��� � �� ��� ���� ��������
				Lexem* newValue = (Lexem*)Lexems->get(i + 3);

				for (int j = i + 4; j < Lexems->count(); j++)
					if (!strcmp(((Lexem*)Lexems->get(j))->GetName(), oldValue->GetName()))
						Lexems->set(j, newValue);

				Lexem* temp = (Lexem*)heap->get_mem(sizeof(Lexem));
				Lexems->take(i, temp);// ����������� ������� ��������� � ��������
				Lexems->take(i, temp);
				Lexems->take(i, temp);
				Lexems->take(i, temp);
				heap->free_mem(temp);
			}
	}
	return true;
}

void Compiler::GetMemForArrayR(void**& place, List* dimensionssizes, int dimension, TypTypes t)
{
	if (dimension != dimensionssizes->count() - 1)
	{
		place = (void**)heap->get_mem(*(int*)dimensionssizes->get(dimension)*sizeof(void*));
		void** pointertogetmem;
		for (size_t i = 0; i < *(int*)dimensionssizes->get(dimension); i++)
		{
			pointertogetmem = (void**)place[i];
			GetMemForArrayR(pointertogetmem, dimensionssizes, dimension + 1, t);
			place[i] = pointertogetmem;
		}
	}
	else
	{
		switch (t)
		{
		case tt_null:
			break;
		case tt_double:
			place = (void**)heap->get_mem(*(int*)dimensionssizes->get(dimension)*sizeof(double));
			break;
		case tt_int:
			place = (void**)heap->get_mem(*(int*)dimensionssizes->get(dimension)*sizeof(int));
			break;
		case tt_bool:
			place = (void**)heap->get_mem(*(int*)dimensionssizes->get(dimension)*sizeof(bool));
			break;
		case tt_char:
			place = (void**)heap->get_mem(*(int*)dimensionssizes->get(dimension)*sizeof(char));
			break;
		default:
			break;
		}
	}
}

bool Compiler::FindNoOperation(List* Lexems)
{
	bool operationFlag = false;
	bool operandFlag = false;
	for (int i = 0; i < Lexems->count(); i++)
	{
		auto templex = ((Lexem*)Lexems->get(i));
		auto templexType = templex->GetLexemType();
		if (templexType == ot_binar)
		{
			if (operandFlag)
			{
				ReportError(templex->lineNumInCode, templex->charNumInLine, "Operand expected.");
				return false;
			}
			else
				operandFlag = true;
		}
		else
			operandFlag = false;
		if (templexType == lt_variable || templexType == lt_const)
		{
			if (operationFlag)
			{
				ReportError(templex->lineNumInCode, templex->charNumInLine, "Operation expected.");
				return false;
			}
			else
				operationFlag = true;
		}
		else
			operationFlag = false;
	}
	return true;
}
