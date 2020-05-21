#include"expression.h"
using namespace std;

Addition::Addition(ExprP _operL, ExprP _operR)
	: operL(_operL), operR(_operR) {}

Polynomial Addition::Eval(){
	return operL->Eval() + operR->Eval();
}


Multipication::Multipication(ExprP _operL, ExprP _operR)
	: operL(_operL), operR(_operR) {}

Polynomial Multipication::Eval(){
	return operL->Eval() * operR->Eval();
}


Derivation::Derivation(ExprP _oper)
	: oper(_oper) {}

Polynomial Derivation::Eval(){
	return oper->Eval().Derivation();
}


Integral::Integral(ExprP _oper, double _low, double _up)
	: oper(_oper), low(_low), up(_up) {}

Polynomial Integral::Eval(){
	return oper->Eval().Integral(low, up);
}


PolynomialExPr::PolynomialExPr(const Polynomial& p)
	: oper(p) {}

Polynomial PolynomialExPr::Eval(){
	return oper;
}

