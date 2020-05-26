#ifndef UI_H
#define UI_H

#include"parser.h"

enum State { MENU, INPUT, CALCULATE, SHOW, EXIT};

class UI{
public:
	UI();
	void Run();	
private:
	Parser parser;
	void ShowUI();
	void GetCommand();
	void GetInput();
	void ShowPoly();
	void Calculate();
	State state;
};

#endif //!UI_H

