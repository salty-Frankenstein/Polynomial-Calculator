#include"parser.h"
#include<sstream>
using namespace std;

const regex Parser::patterns[] = {
	regex("")
};

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

