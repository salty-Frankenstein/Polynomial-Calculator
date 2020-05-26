#include"polynomial.h"
#include"parser.h"
#include<iostream>
using namespace std;

int main(){
	Parser parser;
	int num;
	string name;
	vector<double> v;
	while(1){
		v.clear();
		cin >> num;
		if(num == 0)break;
		cin >> name;
		for(int i = 1;i <= num; i++){
			int t;
			cin >> t;
			v.push_back(t);
		}
		cout << parser.BindName(name, v) << endl;
		parser.nameMap[name].Show();
		cout << endl;
	}
	while(1){
	string expr;
	cin >> expr;
	try{
		parser.Parse(expr)->Eval().Show();
		cout << endl;
	}
	catch(char const* c){
		cerr << c << endl;
	}
	cin.clear();
	}
	return 0;
	
	auto res3 = Parser::ReduceDer("djfk!");
	auto res4 = Parser::ReduceInte("$[1.234,.342](f+g)");
	auto res5 = Parser::ReducePar("(djdjdjd)");
	cout << res3 << endl;
	cout << INTE_LOW(res4) << ' ' << INTE_UP(res4) << ' ' << INTE_OPER(res4) << endl;
	cout << res5 << endl;
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

