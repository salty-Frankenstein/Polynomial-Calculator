#include"polynomial.h"
#include<iostream>

int main(){
	Polynomial p({2,0,-3,5,-0,-.1,-1});
	p.Show();
	std::cout << "\n";
	Polynomial p1({1,2,3,0,2}, 1), p2({-1,-2,3,0,1}, 1);
	auto p3 = p1 - p2;
	p3.Show();
	std::cout << std::endl;
	return 0;
}

