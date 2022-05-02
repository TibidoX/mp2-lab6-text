#pragma once

#include <iostream>
#include <fstream>
#include "TNode.h"
#include "TStack.h"
using namespace std;

class TText
{
	TNode* pFirst, * pCurr;
	TStack<TNode*> st;
	//int count = 0;
public:
	TText(TNode* p) { pFirst = p; }
	void SetFirst(TNode* p){ pFirst = p; }
	TText() { pFirst = nullptr; pCurr = nullptr; }
	TText* Copy()
	{
		return new TText(pFirst->CopyNode(pFirst));
	}
	void Pointer()
	{
		TNode* tmpP = pCurr;
		TStack<TNode*> tmpS = st;
		for (Reset(); !IsEnd(); GoNext())
		{
			int j = 0;
			while (pCurr->str[j] != '\0') {
				if (pCurr->str[j] == '<')
					pCurr->str[j] = '\0';
				j++;
			}
		}
		pCurr = tmpP;
		st = tmpS;
		int i = 0;
		while (pCurr->str[i] != '\0')
			i++;
		pCurr->str[i] = '<';
		pCurr->str[i + 1] = '\0';
	}
	void GoNextLine()
	{
		if (pCurr != nullptr) {
			st.Push(pCurr);
			pCurr = pCurr->pNext;
			//
			Pointer();
		}
		else throw - 1;
	}
	void GoDownLine()
	{
		if (pCurr != nullptr)
		{
			st.Push(pCurr);
			pCurr = pCurr->pDown;
			//
			/*int i = 0;
			while (pCurr->str[i] != '\0')
				i++;
			pCurr->str[i] = '<';
			pCurr->str[i + 1] = '\0';*/
			Pointer();
		}
		else throw - 1;
	}
	void GoFirstLine()
	{
		if (pCurr != nullptr)
		{
			pCurr = pFirst;
			st.Clear();
			//
			Pointer();
		}
		else throw - 1;
	}

	void GoPrevLine()
	{
		if (pCurr)
			pCurr = st.Pop();
		else throw - 1;
		//
		Pointer();
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
		TNode* pHead = nullptr, * tmp = nullptr;
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
	void PrintRec(TNode* p, int c)
	{
		if (p) {
			cout << p->str << endl;
			if (p->pDown) {
				c++;
				for (int i = 0; i < c - 1; i++)
				{
					cout << "  ";
				}
				cout << '{' << endl;
				for (int i = 0; i < c; i++)
				{
					cout << "  ";
				}
				PrintRec(p->pDown, c);
				for (int i = 0; i < c - 1; i++)
				{
					cout << "  ";
				}
				cout << '}' << endl;
				c--;
			}
			if (p->pNext) {
				for (int i = 0; i < c; i++)
				{
					cout << "  ";
				}
				PrintRec(p->pNext, c);
			}
		}
	}
	void SaveRec(ofstream& os, TNode* p, int c)
	{
		TNode* tmpP = pCurr;
		TStack<TNode*> tmpS = st;
		for (Reset(); !IsEnd(); GoNext())
		{
			int j = 0;
			while (pCurr->str[j] != '\0') {
				if (pCurr->str[j] == '<')
					pCurr->str[j] = '\0';
				j++;
			}
		}
		pCurr = tmpP;
		st = tmpS;
		//
		if (p) {
			os << p->str << endl;
			if (p->pDown) {
				c++;
				for (int i = 0; i < c - 1; i++)
				{
					os << "  ";
				}
				os << '{' << endl;
				for (int i = 0; i < c; i++)
				{
					os << "  ";
				}
				SaveRec(os, p->pDown, c);
				for (int i = 0; i < c - 1; i++)
				{
					os << "  ";
				}
				os << '}' << endl;
				c--;
			}
			if (p->pNext) {
				for (int i = 0; i < c; i++)
				{
					os << "  ";
				}
				SaveRec(os, p->pNext, c);
			}
		}
	}
	void Save(char* fn)
	{
		ofstream os(fn);
		SaveRec(os, pFirst, 0);
	}
	void Print()
	{
		//count = 0;
		PrintRec(pFirst, 0);
		
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
		//Pointer();
		int i = 0;
		while (pCurr->str[i] != '\0')
			i++;
		pCurr->str[i] = '<';
		pCurr->str[i + 1] = '\0';
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