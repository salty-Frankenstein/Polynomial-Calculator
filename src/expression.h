#ifndef EXPRESSION_H
#define EXPRESSION_H

#include"polynomial.h"
#include<memory>

class Expression{
public:
	virtual Polynomial Eval() = 0;
};

using ExprP = std::shared_ptr<Expression>;


class Addition: public Expression{
public:
	Addition(ExprP operL, ExprP operR);
	Polynomial Eval();
private:
	ExprP operL, operR;
};


class Multipication: public Expression{
public:
	Multipication(ExprP operL, ExprP operR);
	Polynomial Eval();
private:
	ExprP operL, operR;
};


class Derivation: public Expression{
public:
	Derivation(ExprP oper);
	Polynomial Eval();
private:
	ExprP oper;
};


class Integral: public Expression{
public:
	Integral(ExprP oper, double low, double up);
	Polynomial Eval();
private:
	ExprP oper;
	double low, up;
};


class PolynomialExPr: public Expression{
public:
	PolynomialExPr(const Polynomial&);
	Polynomial Eval();
private:
	Polynomial oper;
};

#endif //!EXPRESSION_H

