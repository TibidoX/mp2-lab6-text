#pragma once
#include <cstring>
#include "TMem.h"
#include "TText.h"

using namespace std;

struct TNode
{
	static TMem mem;
	bool flag;
	char str[81];
	TNode* pNext, * pDown;

	TNode(char* _str = nullptr, TNode* _pNext = nullptr, TNode* _pDown = nullptr)
	{
		pNext = _pNext;
		pDown = _pDown;
		if (_str == nullptr)
			str[0] = '\0';
		else
			strcpy_s(str, _str);
	}

	void* operator new(size_t size)
	{
		TNode* res = mem.pFree;
		if (mem.pFree)
			mem.pFree = mem.pFree->pNext;
		return res;
	}
	void operator delete(void* del)
	{
		if (del)
		{
			TNode* delNode = (TNode*)del;
			TNode* pLastFree = mem.pFree;
			mem.pFree = delNode;
			mem.pFree->pNext = pLastFree;
		}
	}
	static void InitMem(int s = 1000)
	{
		mem.pFirst = (TNode*) new char[sizeof(TNode) * s];
		mem.pFree = mem.pFirst;
		mem.pLast = mem.pFirst + s - 1;
		TNode* p = mem.pFirst;
		for (int i = 0; i < s - 1; i++)
		{
			p->pNext = p + 1;
			p++;
			p->str[0] = '\0';
			p->flag = false;
		}
		mem.pLast->pNext = nullptr;
	}
	static void CleanMem(TText& txt)
	{
		TNode* p = mem.pFree;
		while (p)
		{
			p->flag = true;
			p = p->pNext;
		}
		for (txt.Reset(); !txt.IsEnd(); txt.GoNext())
			txt.Setflag();
		p = mem.pFirst;
		while (p <= mem.pLast)
		{
			if (!p->flag) {
				delete p;
				p->flag = true;
			}
			p++;
		}
	}

	static void PrintFree()
	{
		TNode* p = mem.pFree;
		while (p)
		{
			cout << p;
			p++;
		}
	}

	TNode* CopyNode(TNode* p)
	{
		TNode* pN = nullptr, * pD = nullptr, * res;
		if (p->pNext)
			pN = CopyNode(p->pNext);
		if (p->pDown)
			pD = CopyNode(p->pDown);
		res = new TNode(p->str, pN, pD);
		return res;
	}
};

