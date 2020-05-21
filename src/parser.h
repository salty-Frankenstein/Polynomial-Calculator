#ifndef PARSER_H
#define PARSER_H

#include"expression.h"
#include<map>
#include<string>
#include<regex>


class Parser{
public:

private:
	std::map<std::string, Polynomial> nameMap;
	const static std::regex patterns[];
};

const std::regex Parser::patterns[] = {
	std::regex("")
};

#endif //!PARSER_H

