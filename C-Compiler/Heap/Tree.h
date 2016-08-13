#pragma once
#include "Identificator.h"
#include "hash.h"

class TValue
{
public:
	int type()
	{
		return m_type;
	}

	void setType(int t)
	{
		m_type = t;
	}

	double value()
	{
		return m_value;
	}

	void setValue(double v)
	{
		m_value = v;
		m_pointerlevel = 0;
		ispointer = false;
	}

	void* valuepointer()
	{
		return m_valuepointer;
	}

	void setValuePointer(void* v)
	{
		m_valuepointer = v;
		ispointer = true;
	}

	int pointerlevel()
	{
		return m_pointerlevel;
	}

	void setPointerLevel(int l)
	{
		m_pointerlevel = l;
	}

	friend TValue operator +(TValue o1, TValue o2);
	friend bool operator ==(TValue o1, TValue o2);
	void print();

	bool isPointer()
	{
		return ispointer;
	}

private:
	int m_type;
	double m_value; // для int, bool, char, double
	void* m_valuepointer; // для void*
	int m_pointerlevel;
	bool ispointer;
};

class TNode
{
public:
	TNode()
	{
	}

	virtual ~TNode()
	{
	}

	virtual TValue exec()
	{
		TValue a;
		a.setType(1); 
		a.setValue(0); 
		return a; 
	}

	virtual void print()
	{
	}

	Lexem* GetLexem() 
	{
		return Base->find(keyWord);
	}

	char* GetKeyWord()
	{
		return keyWord;
	}

	virtual bool operandsAreNotNull()
	{
		return true;
	};

protected:
	char* keyWord;
	TNode* FindTheOperand(List* list, int left, int right, int& MinPriorityOperIndex);
};

class TConst : public TNode
{
public:
	TConst(Lexem* lex);

	~TConst()
	{
	}

	TValue exec() override
	{
		return m_const;
	}

	void print() override;
	
protected:
	TValue m_const;
};

class TVariable : public TNode
{
public:
	TVariable(char*);
	~TVariable();
	
	TValue exec() override;
	void print() override;
};

class TUnaryOperation : public TNode
{
public:
	TUnaryOperation(Lexem*, List*, int leftborder, int rightborder);
	~TUnaryOperation();

	TValue exec() override;
	void print() override;
	bool operandsAreNotNull() override;
protected:
	int m_type;
	TNode* m_operand;
	bool isPostfix; // 0 - prefix, 1 - postfix. set in constructor
};

class TBinaryOperation : public TNode
{
public:
	TBinaryOperation(Lexem*, List*, int leftborder1, int rightborder1, int leftborder2, int rightborder2);

	~TBinaryOperation()
	{
	}

	TValue exec() override;
	void print() override;
	bool operandsAreNotNull() override;
protected:
	int m_type;
	TNode* m_operand1;
	TNode* m_operand2;
};


class TernarOperation : public TNode
{
public:
	TernarOperation(Lexem*, List*, int leftborder1, int rightborder1,
									int leftborder2, int rightborder2,
									int leftborder3, int rightborder3);
	~TernarOperation();

	bool operandsAreNotNull() override;
	TValue exec() override;
	void print() override;
protected:

	TBinaryOperation* condition;
	TNode* branch1;
	TNode* branch2;
};


class TInterrupt : public TNode
{
public:
	TInterrupt(InterruptTypes it)
	{
		this->it = it;
	}

	~TInterrupt()
	{
	}

	void print() override
	{
		switch (it)
		{
		case it_continue:
			cout << " continue\n";
			break;
		case it_break:
			cout << " break\n";
			break;
		default:
			break;
	}
	}

protected :
	InterruptTypes it;
};

class TList : public TNode
{
public:
	TList();
	~TList();
	TValue exec() override;
	TValue exec(InterruptTypes& it);
	TValue execSwitch(char* smth);
	void print() override;
	void addNode(TNode* node);
	TNode* GetNode(int i);
	int NodeCount();
protected:
	List* Trees;
};

class TIf : public TNode
{
public:
	TIf(List* Lexems, int leftCond, int rightCond, TList* branch_then, TList* branch_else)
	{
		int min = 0;
		this->condition = FindTheOperand(Lexems, leftCond, rightCond, min);
		this->branch_then = branch_then;
		this->branch_else = branch_else;
	}

	~TIf()
	{
	}

	TValue exec() override
	{
		InterruptTypes it = it_null;
		if (condition->exec().value()) 
		return branch_then->exec(it);
		else
			if (branch_else == NULL)
				return *(new TValue());
			return branch_else->exec(it);		
	}

	void print() override
	{
		cout << " if(";
		condition->print();
		cout << ")\n{";
		branch_then->print();
		cout << "\n}\n";
		if (branch_else != NULL)
		{
			cout << " else\n{";
			branch_else->print();
			cout << "}\n";
		}		
	}

protected:
	TNode* condition;
	TList* branch_then;
	TList* branch_else;
};

class TWhile : public TNode
{
public:
	TWhile(List* Lexems, int leftCond, int rightCond, TList* body)
	{
		int min = 0;
		this->condition = FindTheOperand(Lexems, leftCond, rightCond, min);
		this->body = body;
	}

	~TWhile()
	{
	}

	TValue exec() override
	{
		TValue* res = new TValue();
		int i = 0;
		bool bbreak = false;
		bool bcontinue = false;
		InterruptTypes it;
		while (condition->exec().value())
		{ 
			it = it_null;
			res = &(body)->exec(it);
			if (it = it_continue)
				continue;
			if (it = it_break)
				break;	
		}
		return *res;		
	};

	void print() override
	{
		cout << " while(";
		condition->print();
		cout << ")\n{";
		body->print();
		cout << "\n}\n";
	}

protected:
	TNode* condition;
	TList* body;
};

class TSwitch : public TNode
{
public:
	TSwitch(List* Lexems, int leftCond, int rightCond, TList* body)
	{
		int min = 0;
		this->condition;
		this->condition = (TConst*)FindTheOperand(Lexems, leftCond, rightCond, min);
		this->body = body;
	}

	~TSwitch()
	{
	}

	TValue exec() override
	{
		return body->execSwitch(condition->GetKeyWord());
	}

	void print() override
	{
		cout << " switch(";
		condition->print();
		cout << ")\n{";
		body->print();
		cout << "\n}\n";
	}

protected:
	TConst* condition;
	TList* body;
};

class TCase : public TNode
{
public:
	TCase(List* Lexems, TConst* condition, TList* body, ConditionalsTypes ct)
	{
		int min = 0;
		this->condition = condition;
		this->body = body;
		this->ct = ct;
	}

	~TCase()
	{
	}

	TValue exec() override
	{
		InterruptTypes it = it_null;
		return body->exec(it);
	}

	void print() override
	{
		if (ct == ct_case)
		{
			cout << " case ";
			condition->print();
		}
		else 
			cout << " default ";
		cout << ":\n" ;
		body->print() ;
	}

	ConditionalsTypes GetCT()
	{
		return ct;
	}

	char* GetName()
	{
		return condition->GetKeyWord();
	}

protected:
	ConditionalsTypes ct;
	TConst* condition;
	TList* body;
};

class TStandardFunc : public TNode
{
public:
	TStandardFunc(Lexem* lex, List* Lexems, int left, int right);
	TValue exec() override;
	void print() override;
protected:
	TNode* m_param;
};
