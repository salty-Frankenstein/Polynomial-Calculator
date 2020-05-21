#include"polynomial.h"
#include<cmath>
#include<iostream>
using namespace std;

bool Feq(double a, double b){
	return fabs(a - b) < 1e-6;
}

Polynomial::Polynomial(const vector<double>& p, bool high) {
	if(high){
		for(auto i = p.rbegin(); i != p.rend(); i++)
			coef.push_back(*i);
	}
	else{
		coef = p;
	}
	Standardize();
}

void Polynomial::Standardize(){
	maxTerm = coef.size() - 1;
	while(Feq(coef[maxTerm], 0.0)){
		if(maxTerm == 0)break;
		maxTerm--;
		coef.pop_back();
	}
}

Polynomial Polynomial::operator+(const Polynomial& x)const{
	vector<double> ans;
	int mi = min(maxTerm, x.maxTerm);
	for(int i = 0; i <= mi; i++)
		ans.push_back(coef[i] + x.coef[i]);
	if(maxTerm > x.maxTerm){
		for(int i = mi + 1; i <= maxTerm; i++)
			ans.push_back(coef[i]);
	}
	else{
		for(int i = mi + 1; i <= x.maxTerm; i++)
			ans.push_back(x.coef[i]);
	}
	return Polynomial(ans);
}

Polynomial Polynomial::operator-()const{
	vector<double> ans;
	for(auto i : coef)
		ans.push_back(-i);
	return Polynomial(ans);
}

Polynomial Polynomial::operator-(const Polynomial& x)const{
	return (*this) + (-x);
}

void Polynomial::Show(){
	if(maxTerm == 0){
		cout << coef[0];
		return;
	}

	for(int i = maxTerm; i > 0; i--){
		if(Feq(coef[i], 0.0))continue;
		if(i != maxTerm){
			if(coef[i] > 0)cout << '+';
		}
		if(!Feq(coef[i], 1.0)){
			cout << coef[i];
		}
		cout << "x^" << i << ' ';
	}
	if(Feq(coef[0], 0.0))return;
	if(coef[0] > 0)cout << '+';
	cout << coef[0];
}

