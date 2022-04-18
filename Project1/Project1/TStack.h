#pragma once

#include <stdlib.h>
#include <string>

using namespace std;
template<class T>
class TStack
{
	int size;
	int NumLast;
	T* mas;
public:
	TStack(int _size = 10)
	{
		if (_size <= 0)
			throw _size;
		size = _size;
		mas = new T[size];
		NumLast = -1;
	}
	~TStack()
	{
		delete[] mas;
	}
	TStack(const TStack<T>& c)
	{
		size = c.size;
		NumLast = c.NumLast;
		delete[] mas;
		mas = new T[size];
		for (int i = 0; i <= NumLast; i++)
			mas[i] = c.mas[i];
	}

	//*вывод

	TStack& operator=(const TStack& c)
	{
		if (this != &c)
		{
			if (size != c.size)
			{
				delete[] mas;
				size = c.size;
				mas = new T[size];
			}
			NumLast = c.NumLast;
			for (int i = 0; i <= NumLast; i++)
				mas[i] = c.mas[i];
		}
		return *this;
	}

	bool operator==(const TStack& c) const
	{
		if (size != c.size || NumLast != c.NumLast)
			return false;
		for (int i = 0; i <= NumLast; i++)
			if (mas[i] != c.mas[i])
				return false;
		return true;
	}

	bool Empty() const
	{
		return (NumLast == -1);
		//if (NumLast==-1)
			//return true;
		//else return false;
	}
	bool Full() const
	{
		return (NumLast == size - 1);
		//if (NumLast==size-1)
			//return true;
		//else return false;
	}
	//push, pop, (очистка)
	void Push(const T& el)
	{
		if (this->Full())
			throw el;
		mas[NumLast + 1] = el;
		NumLast++;
	}
	T Pop()
	{
		if (this->Empty())
			throw - 1;
		NumLast--;
		return mas[NumLast + 1];
	}

	T Top()
	{
		if (this->Empty())
			throw - 1;
		return (mas[NumLast]);
	}

	void Clear()
	{NumLast = -1;}

	int GetSize() { return size; }
	/*bool Skobki(const string& c)
	{
		TStack<int> s;
		for (int i = 0; i < c.size(); i++)
		{
			if (c[i] == '(')
				s.Push(1);
			if (c[i] == ')')
			{
				if (s.Empty)
					return false;
				s.Pop();
			}
		}
		return(s.Empty);
	}*/
};

