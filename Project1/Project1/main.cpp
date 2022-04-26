#define HOME	71
#define DOWN	100
#define NEXT	110
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
	//TNode::InitMem();
	//ifstream ifs("TestText.txt");
	//TText text;

	//text.SetFirst(text.ReadRec(ifs));
	//text.ReadRec(ifs);
	//text.Reset();
	//char ch;
	//char* s = new char[100];
	////TText text;
	//do {
	//	cout << "n - Insert next line" << endl;
	//	cout << "d - Insert down line" << endl;
	//	cout << "p - Print" << endl;
	//	ch = _getch();
	//	//if (ch == 0xE0) ch = _getch();
	//	if (ch == ESC) break;
	//	//if (ch != ENTER) ch = _getch();
	//	switch (ch) {
	//	case ENTER:
	//		break;
	//	case HOME: {text.GoFirstLine(); break; }
	//	case DOWN: {cin >> s; text.InsDownLine(s); text.GoDownLine(); break; }
	//	case NEXT: {cin >> s; text.InsNextLine(s); text.GoNextLine(); break; }
	//	case UP:  text.GoPrevLine(); break;
	//	case INS:
	//		break;
	//	case DEL:
	//		break;
	//	case 49:text.Print(); break;
	//	}
	//} while (ch != ESC);

	//TNode::PrintFree();
	TNode::InitMem();
	ifstream ifs("TestText.txt");
	TText text;

	text.SetFirst(text.ReadRec(ifs));
	text.ReadRec(ifs);
	text.Reset();
	text.InsDownLine((char*)"First.First");
	text.GoDownLine();
	text.InsDownLine((char*)"First.First.First");
	text.GoDownLine();
	text.InsDownLine((char*)"First.First.Second");
	text.GoDownLine();
	text.InsDownSec((char*)"oooooooooooooooooooooooooooooo");
	text.GoDownLine();
	text.InsNextLine((char*)"rrrrrrrrrrrrrrr");
	text.GoFirstLine();
	text.DelDownLine();
	//text.DelNextLine();


	TNode::CleanMem(text);

	text.Print();

	cout << "Gtddd"<<endl;
	TNode::PrintFree();
}