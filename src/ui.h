#ifndef UI_H
#define UI_H

#include"parser.h"

enum State { MENU, INPUT, CALCULATE, INVERSE, ROOT, SHOW, EXIT};

class UI{
public:
	UI();
	void Run();	
private:
	Parser parser;
	bool CheckCin();
	void ShowUI();
	void GetCommand();
	void GetInput();
	void ShowPoly();
	void Calculate();
	void Root();
	void Inverse();
	State state;
};

#endif //!UI_H

