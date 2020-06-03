#include"parser.h"
#include<sstream>
#include<stack>
using namespace std;

const regex Parser::patterns[] = {
	regex("\\w+\\!(?!\\!)"),		//derivation
	regex("\\$\\[[^\\]]+,[^\\]]+\\][^\\+\\*\\(]+"),	//integral
	//regex("\\(.+\\)"),			//parentheses
	//regex("[^\\+]+\\+"),		//add
	//regex("[^\\*]+\\*"),		//multiply
};

pair<ExprType, string> Parser::MatchDer(string& s){
	//cout << "try match der:" << s<<endl;
	int num = 0;
	string res;
	regex pat("\\$\\[[^\\]]+,[^\\]]+\\]\\(");
	smatch sm;
	bool matched = regex_search(s, sm, pat);
	if(matched && sm[0].first == s.begin() && sm.str().size() != 0){
		res += sm.str();
		s.erase(sm[0].first, sm[0].second);
		num = 1;
		for(auto i = s.begin(); i != s.end(); i++){
			if(*i == '(')num++;
			if(*i == ')')num--;
			res += *i;
			s.erase(i);
			i--;
			if(num == 0)return {E_INT, res};
		}
	}
	return {E_POL, ""};
}

pair<ExprType, string> Parser::MatchPar(string& s){
	int num = 0;
	string res;
	if(s[0] != '('){
		return {E_POL, ""};
	}
	for(auto i = s.begin(); i != s.end(); i++){
		if(*i == '(')num++;
		if(*i == ')')num--;
		res += *i;
		s.erase(i);
		auto next = i;
		i--;
		if(num == 0){
			if(*next != '!')
				return {E_PAR, res};
			else{
				res += *next;
				s.erase(next);
				return {E_DER, res};
			}
		}
	}
	return {E_POL, ""};
}

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
	bool matched, del;
	while(!str.empty()){
		del = false;
		//cout << "now parsing: "<< str<<endl;
		type = E_POL;
		//matching all patterns from the head of the string

		//matching parentheses
		auto par = MatchPar(str);
		string strm;
		if(par.first != E_POL){
			type = par.first;
			strm = par.second;
		}
		else{
			for(int i = 0; i < 2; i++){
				matched = regex_search(str, s, patterns[i]);
				if(matched && s[0].first == str.begin() && s.str().size() != 0){
					type = ExprType(i);
					del = true;
					strm = s.str();
					//cout << "recent matched:" << s.str()<<endl;
					break;
				}
			}
		}
		//try matching derivation with parentheses
		if(type == E_POL){
			par = MatchDer(str);
			if(par.first != E_POL){
				type = par.first;
				strm = par.second;
			}
		}
		// DEBUG
		/*		
		if(type == E_POL){
			cout << "not matched" << endl;
		}
		else{
				cout << "matched:" << strm << " type:" << type << endl;
		}*/
		
		//if matched
		if(type != E_POL){
			ExprP sub_expr;
			//get sub-expressions
			switch(type){
			case E_PAR:	//parentheses
				sub_expr = Parse(ReducePar(strm));
				break;
			case E_DER:	//derivation
				sub_expr = ExprP(new Derivation(Parse(ReduceDer(strm))));
				break;
			case E_INT:	//integral
				{
				auto res = ReduceInte(strm);
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
			if(del)
				str.erase(s[0].first, s[0].second);
		}

		//if not matched, then process symbols
		if(type == E_POL){
			switch(str[0]){
			case '+':
				type = E_ADD;
				symSt.push(type);
				str.erase(str.begin());
				break;
			case '*':
				type = E_MUL;
				symSt.push(type);
				str.erase(str.begin());
				break;
			}
		}

		// DEBUG

		//cout << type << ' ' << symSt.size() << ' ' << valSt.size()<<endl;
		//if none of these, it's a name binding
		if(type == E_POL){
			auto name = ReadName(str);
			// DEBUG
			//cout << name <<' '<<str<< endl;
			//cout << "---\n";
			auto i = nameMap.find(name);
			//name not found
			if(i == nameMap.end())throw "syntax error";
			//cout << "found\n";
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
		/*
		else{	//delete the first sub-expression
			if(type == E_ADD || type == E_MUL)
				str.erase(str.begin());
			else if(type != E_PAR)
				str.erase(s[0].first, s[0].second);
		}
		*/
		
	}
	
	//	cout << type << ' ' << symSt.size() << ' ' << valSt.size()<<endl;
	
	//end of parsing, pop all the stacks to get the final expression
	//there should be only E_ADD in the stack

	if(valSt.empty())throw "syntax error";
	ExprP res = valSt.top();
	valSt.pop();
	while(!symSt.empty()){
		if(symSt.top() == E_MUL)throw "syntax error";
		if(valSt.empty())throw "syntax error";
		res = ExprP(new Addition(res, valSt.top()));
		valSt.pop();
		symSt.pop();
	}
	//cout << "arrived:";
	//res->Eval().Show();cout<<endl;
	if(!valSt.empty())throw "syntax error";
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

string Parser::ReduceDer(string s){
	s.pop_back();
	return s;
}

InteRes Parser::ReduceInte(string s){
	string sup, slow, sres;
	int state = 0;
	for(auto c : s){
		if(state < 3 && (c == '[' || c == ',' || c == ']')){
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
	if(ssup.fail() || sslow.fail())
		throw "syntax error";
	return {low, {up, sres}};
}

string Parser::ReducePar(string s){
	s.erase(s.begin());
	s.pop_back();
	return s;
}

Polynomial Parser::Eval(ExprP expr){
	return expr->Eval();
}

