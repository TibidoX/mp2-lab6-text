#define HOME	71
#define DOWN	80
#define NEXT	77
#define UP	72
#define ESC	27
#define INS	82
#define DEL	83
#define ENTER	13

#include "TText.h"
#include <iostream>
#include "conio.h"
using namespace std;


TMem TNode::mem;
void main()
{
	char ch;
	TText text;
	do {
		cout << ">,v,^, Home, Ins, Del, Enter, Esc";
		ch = _getch();
		if (ch == 0xE0) ch = _getch();
		if (ch == ESC) break;
		if (ch != ENTER) ch = _getch();
		switch (ch) {
		case ENTER:
			break;
		case HOME: text.GoFirstLine(); break;
		case DOWN:text.GoDownLine(); break;
		case NEXT:text.GoNextLine(); break;
		case UP:  text.GoPrevLine(); break;
		case INS:
			break;
		case DEL:
			break;

		}
	} while (ch != ESC);

}