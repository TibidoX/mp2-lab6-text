#include "TText.h"
#include <iostream>
#include "conio.h"
using namespace std;

TMem TNode::mem;
void main()
{
	TNode::InitMem();
	TText text;
	int c, n;
	char* s = new char[100];
	text.Read((char*)"TestText.txt");
	text.Reset();
	do {
		cout << "1. Go next line" << endl;
		cout << "2. Go down line" << endl;
		cout << "3. Go previous line" << endl;
		cout << "4. Go first line" << endl;
		cout << "5. Insert next line" << endl;
		cout << "6. Insert down line" << endl;
		cout << "7. Insert next section" << endl;
		cout << "8. Insert down section" << endl;
		cout << "9. Delete next line" << endl;
		cout << "10. Delete down line" << endl;
		cout << "11. Print Free" << endl;
		cout << "12. Print" << endl;
		cout << "13. Save" << endl;
		cout << "14. Clean memory" << endl;
		cout << "0. Exit" << endl;

		cin >> c;
		switch (c) {
		case 1: {text.GoNextLine(); break; }
		case 2: {text.GoDownLine(); break; }
		case 3: {text.GoPrevLine(); break; }
		case 4: {text.GoFirstLine(); break; }
		case 5: {cin >> s; text.InsNextLine(s); break; }
		case 6: {cin >> s; text.InsDownLine(s); break; }
		case 7: {cin >> s; text.InsNextSec(s); break; }
		case 8: {cin >> s; text.InsDownSec(s); break; }
		case 9: {          text.DelNextLine(); break; }
		case 10:{	       text.DelDownLine(); break; }
		case 11:{cout << endl; TNode::PrintFree(); cout << endl; break; }
		case 12:{cout << endl; text.Print(); cout << endl; break; }
		case 13: {text.Save((char*)"TestText.txt"); break; }
		case 14: {TNode::CleanMem(text); break; }
		}
	} while (c != 0);

	//TNode::PrintFree();
	//TNode::InitMem();
	////ifstream ifs("TestText.txt");
	//
	//TText text;
	//text.Read((char*)"TestText.txt");
	////text.SetFirst(text.ReadRec(ifs));
	////text.ReadRec(ifs);
	//text.Reset();
	//text.InsDownLine((char*)"First.First");
	//text.GoDownLine();
	//text.InsDownLine((char*)"First.First.First");
	//text.GoDownLine();
	//text.InsDownLine((char*)"First.First.Second");
	//text.GoDownLine();
	//text.InsDownSec((char*)"oooooooooooooooooooooooooooooo");
	//text.GoDownLine();
	//text.InsNextLine((char*)"rrrrrrrrrrrrrrr");
	//text.GoFirstLine();
	////text.DelDownLine();
	////text.DelNextLine();


	//TNode::CleanMem(text);

	//text.Print();

	//cout << "Udalennoe"<<endl;
	//TNode::PrintFree();
}