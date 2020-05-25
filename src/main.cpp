#include"polynomial.h"
#include"parser.h"
#include<iostream>
using namespace std;

int main(){
	auto res1 = Parser::ReduceAdd("abdj+sk3+3l");
	auto res2 = Parser::ReduceMul("anks*dfa*df");
	auto res3 = Parser::ReduceDer("djfk!");
	auto res4 = Parser::ReduceInte("$[1.234,.342](f+g)");

	cout << OPERL(res1) << ' ' << OPERR(res1) << endl;
	cout << OPERL(res2) << ' ' << OPERR(res2) << endl;
	cout << res3 << endl;
	cout << INTE_LOW(res4) << ' ' << INTE_UP(res4) << ' ' << INTE_OPER(res4) << endl;
	return 0;
	Polynomial p({2,0,-3,5,-0,-.1,-1});
	p.Show();
	std::cout << "\n";
	Polynomial p1({2,3,0,2}, 1), p2({-1,-2,3,0,1}, 1);
	auto p3 = p1 * p2;
	p1.Show();
	std::cout << std::endl;
	p2.Show();
	std::cout << std::endl;
	p3.Show();
	std::cout << std::endl;
	p1.Integral(0,5).Show();
	std::cout<<std::endl;
	return 0;
}

