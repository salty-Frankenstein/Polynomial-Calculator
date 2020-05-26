#ifndef PARSER_H
#define PARSER_H

#include"expression.h"
#include<map>
#include<string>
#include<regex>

using ReduceRes = std::pair<std::string, std::string>;
#define OPERL(x) (x.first)
#define OPERR(x) (x.second)

using InteRes = std::pair<double, std::pair<double, std::string>>;
#define INTE_LOW(x) (x.first)
#define INTE_UP(x) (x.second.first)
#define INTE_OPER(x) (x.second.second)

enum ExprType { 
	E_DER,		//derivation
	E_INT,		//integral
	E_POL,		//polynomial
	E_PAR, 		//parentheses
	E_ADD, 		//addition
	E_MUL,		//multipication
};

class Parser{
public:
	bool BindName(std::string name, const std::vector<double> &coef);
	std::string ReadName(std::string&);
	ExprP Parse(std::string);
	static Polynomial Eval(ExprP);

	std::map<std::string, Polynomial> nameMap;
	const static std::regex patterns[];

//private:
	std::pair<ExprType, std::string> MatchPar(std::string&);
	std::pair<ExprType, std::string> MatchDer(std::string&);
	static std::string ReduceDer(std::string);
	static InteRes ReduceInte(std::string);
	static std::string ReducePar(std::string);
};

#endif //!PARSER_H

