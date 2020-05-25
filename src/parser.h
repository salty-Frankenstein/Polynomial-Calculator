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

class Parser{
public:
	static ExprP Parse(std::string);
	static Polynomial Eval(ExprP);

	static ReduceRes ReduceAdd(std::string);
	static ReduceRes ReduceMul(std::string);
	static std::string ReduceDer(std::string);
	static InteRes ReduceInte(std::string);
	static std::string ReducePar(std::string);
private:
	std::map<std::string, Polynomial> nameMap;
	const static std::regex patterns[];
};

#endif //!PARSER_H

