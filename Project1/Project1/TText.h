#pragma once

#include <iostream>
#include <fstream>
#include "TNode.h"
#include "TMem.h"
#include "TStack.h"
using namespace std;

class TText
{
	TNode* pFirst, * pCurr;
	TStack<TNode*> st;
	int count;
public:
	TText(TNode* p) { pFirst = p; }
	TText() { pFirst = nullptr; pCurr = nullptr; }
	TText* Copy()
	{
		return new TText(pFirst->CopyNode(pFirst));
	}
	void GoNextLine()
	{
		if (pCurr != nullptr) {
			st.Push(pCurr);
			pCurr = pCurr->pNext;
		}
		else throw - 1;
	}
	void GoDownLine()
	{
		if (pCurr != nullptr)
		{
			st.Push(pCurr);
			pCurr = pCurr->pDown;
		}
		else throw - 1;
	}
	void GoFirstLine()
	{
		if (pCurr != nullptr)
		{
			pCurr = pFirst;
			st.Clear();
		}
		else throw - 1;
	}

	void GoPrevLine()
	{
		if (pCurr)
			pCurr = st.Pop();
		else throw - 1;
	}

	void InsNextLine(char str[])
	{
		if (pCurr != nullptr)
		{
			TNode* newstr = new TNode(str);
			newstr->pNext = pCurr->pNext;
			pCurr->pNext = newstr;
		}
		else throw - 1;
	}
	void InsNextSec(char str[])
	{
		if (pCurr != nullptr)
		{
			TNode* newstr = new TNode(str);
			newstr->pDown = pCurr->pNext;
			pCurr->pNext = newstr;
		}
		else throw - 1;
	}
	void InsDownLine(char str[])
	{
		TNode* newstr = new TNode(str);
		newstr->pNext = pCurr->pDown;
		pCurr->pDown = newstr;
	}
	void InsDownSec(char str[])
	{
		TNode* newstr = new TNode(str);
		newstr->pDown = pCurr->pDown;
		pCurr->pDown = newstr;
	}
	void DelNextLine()
	{
		if (pCurr != nullptr) {
			if (pCurr->pNext != nullptr)
			{
				TNode* pDel = pCurr->pNext;
				pCurr->pNext = pDel->pNext;
				delete pDel;
			}
		}
		else throw - 1;
	}
	void DelDownLine()
	{
		if (pCurr != nullptr) {
			if (pCurr->pDown != nullptr)
			{
				TNode* pDel = pCurr->pDown;
				pCurr->pDown = pDel->pNext;
				delete pDel;
			}
		}
		else throw - 1;
	}

	TNode* ReadRec(ifstream& ifs)
	{
		TNode* pHead, * tmp;
		char buf[81];

		while (!ifs.eof())
		{
			//ifs.getLine(buf, 80, '\n');
			ifs.getline(buf, 80, '\n');
			if (buf[0] == '}')
				break;
			else if (buf[0] == '{')
				tmp->pDown = ReadRec(ifs);
			else
			{
				TNode* p = new TNode(buf);
				if (pHead == nullptr)
					pHead = tmp = p;
				else
				{
					tmp->pNext = p;
					tmp = p;
				}
			}
		}
		return pHead;
	}
	void Read(char* fn)
	{
		ifstream ifs(fn);
		pFirst = ReadRec(ifs);
	}
	void PrintRec(TNode* p)
	{
		if (p)
		{
			cout << p->str << endl;
			PrintRec(p->pDown);
			PrintRec(p->pNext);
		}
	}
	void Print()
	{
		count = 0;
		PrintRec(pFirst);
	}
	bool IsEnd() { return st.Empty(); }
	void Reset()
	{
		st.Clear();
		pCurr = pFirst;
		st.Push(pCurr);
		if (pCurr->pNext)
			st.Push(pCurr->pNext);
		if (pCurr->pDown)
			st.Push(pCurr->pDown);
	}
	void GoNext()
	{
		pCurr = st.Pop();
		if (pCurr != pFirst)
			if (pCurr->pNext)
				st.Push(pCurr->pNext);
		if (pCurr->pDown)
			st.Push(pCurr->pDown);
	}
	void Setflag()
	{
		pCurr->flag = true;
	}
};