#include"parser.h"
#include<sstream>
#include<stack>
using namespace std;

const regex Parser::patterns[] = {
	regex("\\(.+\\)"),			//parentheses
	regex(".*[^\\!]\\!"),		//derivation
	regex("\\$\\[.+,.+\\][^\\+\\*\\(]+"
		"|\\$\\[.+,.+\\]\\(.+\\)"),	//integral
	//regex("[^\\+]+\\+"),		//add
	//regex("[^\\*]+\\*"),		//multiply
};

bool Parser::BindName(string name, const vector<double> &coef){
	auto i = nameMap.find(name);
	if(i == nameMap.end()){
		nameMap[name] = Polynomial(coef, 1);
		return false;
	}
	nameMap[name] = Polynomial(coef, 1);
	return true;
}


ExprP Parser::Parse(string str){
	if(str.empty())throw "syntax error";
	
	stack<ExprP> valSt;		//stack of sub-expressions
	stack<ExprType> symSt;	//stack of symbols
	
	ExprType type = E_POL;
	smatch s;
	bool matched;
	while(!str.empty()){
		//matching all patterns from the head of the string
		for(int i = 0; i < 3; i++){
			matched = regex_search(str, s, patterns[i]);
			if(matched && s[0].first == str.begin() && s.str().size() != 0){
				type = ExprType(i);
				break;
			}
		}
		
		//if matched
		ExprP sub_expr;
		//get sub-expressions
		switch(type){
		case E_PAR:	//parentheses
			sub_expr = Parse(ReducePar(s.str()));
			break;
		case E_DER:	//derivation
			sub_expr = ExprP(new Derivation(Parse(ReduceDer(s.str()))));
			break;
		case E_INT:	//integral
			{
			auto res = ReduceInte(s.str());
			sub_expr = ExprP(new Integral(Parse(INTE_OPER(res)), INTE_LOW(res), INTE_UP(res)));
			}
			break;
		}
		
		//if symbol is multiply, then combine
		if(!symSt.empty() && symSt.top() == E_MUL){
			if(valSt.empty())throw "syntax error";
			auto t = valSt.top();
			valSt.pop();
			symSt.pop();
			valSt.push(ExprP(new Multipication(t, sub_expr)));
		}
		else valSt.push(sub_expr);


		//if not matched, then process symbols
		if(type == E_POL){
			switch(str[0]){
			case '+':
				type = E_ADD;
				symSt.push(type);
				break;
			case '*':
				type = E_MUL;
				symSt.push(type);
				break;
			}
		}

		//if none of these, it's a name binding
		if(type == E_POL){
			auto name = ReadName(str);
			auto i = nameMap.find(name);
			//name not found
			if(i == nameMap.end())throw "syntax error";
			//processing multiply
			if(!symSt.empty() && symSt.top() == E_MUL){
				if(valSt.empty())throw "syntax error";
				auto t = valSt.top();
				valSt.pop();
				symSt.pop();
				valSt.push(ExprP(new Multipication(t, ExprP(new PolynomialExPr(i->second)))));
			}
			else valSt.push(ExprP(new PolynomialExPr(i->second)));
		}
		else{	//delete the first sub-expression
			if(type == E_ADD || type == E_MUL)
				str.erase(str.begin());
			else str.erase(s[0].first, s[0].second);
		}
		
	}

	//end of parsing, pop all the stacks to get the final expression
	//there should be only E_ADD in the stack
	ExprP res;
	while(!symSt.empty()){
		if(symSt.top() == E_MUL)throw "syntax error";
		if(valSt.empty())throw "syntax error";
		res = ExprP(new Addition(res, valSt.top()));
		valSt.pop();
		symSt.pop();
	}

	if(valSt.empty())throw "syntax error";
	res = ExprP(new Addition(res, valSt.top()));
	return res;
}


string Parser::ReadName(string& s){
	auto isAlpha = [](char c){
		return c >= 'a' && c <= 'z'
			|| c >= 'A' && c <= 'Z';};
	string res;
	for(auto i = s.begin(); i != s.end(); i++){
		if(!isAlpha(*i))break;
		res += *i;
		s.erase(i);
		i--;
	}
	return res;
}

ReduceRes Parser::ReduceAdd(string s){
	string opl, opr;
	bool isl = true;
	for(auto c : s){
		if(c == '+' && isl){
			isl = false;
			continue;
		}
		if(isl)opl += c;
		else opr += c;
	}
	return {opl, opr};
}

ReduceRes Parser::ReduceMul(string s){
	string opl, opr;
	bool isl = true;
	for(auto c : s){
		if(c == '*' && isl){
			isl = false;
			continue;
		}
		if(isl)opl += c;
		else opr += c;
	}
	return {opl, opr};
}

string Parser::ReduceDer(string s){
	s.pop_back();
	return s;
}

InteRes Parser::ReduceInte(string s){
	string sup, slow, sres;
	int state = 0;
	for(auto c : s){
		if(c == '[' || c == ',' || c == ']'){
			state++;
			continue;
		}
		if(state == 1)slow += c;
		else if(state == 2)sup += c;
		else if(state == 3)sres += c;
	}
	istringstream ssup(sup), sslow(slow);
	double up, low;
	ssup >> up;
	sslow >> low;
	return {low, {up, sres}};
}

string Parser::ReducePar(string s){
	s.erase(s.begin());
	s.pop_back();
	return s;
}

