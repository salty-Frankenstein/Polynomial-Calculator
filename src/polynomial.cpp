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

Polynomial Polynomial::operator()(double x)const{
	double ans = 0;
	for(int i = 0; i <= maxTerm; i++)
		ans += coef[i] * pow(x, i);
	return Polynomial({ans});
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

Polynomial Polynomial::operator*(const Polynomial& x)const{
	vector<double> ans(maxTerm + x.maxTerm + 3);
	for(int i = 0; i <= maxTerm; i++){
		for(int j = 0; j <= x.maxTerm; j++)
			ans[i + j] += coef[i] * x.coef[j];
	}
	return Polynomial(ans);
}

Polynomial Polynomial::Derivation()const{
	Polynomial p = (*this);
	for(int i = 0; i <= p.maxTerm; i++){
		p.coef[i] *= i;
	}
	for(int i = 1; i <= p.maxTerm; i++){
		p.coef[i - 1] = p.coef[i];
	}
	p.coef[p.maxTerm] = 0;
	p.Standardize();
	return p;
}

Polynomial Polynomial::Integral(double low, double up)const{
	vector<double> ans(maxTerm + 2);
	for(int i = 0; i <= maxTerm; i++)
		ans[i + 1] = coef[i] / (i + 1);
	Polynomial p(ans);
	return Polynomial({p(up) - p(low)});
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
		if(Feq(coef[i], -1.0)){
			cout << '-';
		}
		else if(!Feq(coef[i], 1.0)){
			cout << coef[i];
		}
		cout << "x^" << i << ' ';
	}
	if(Feq(coef[0], 0.0))return;
	if(coef[0] > 0)cout << '+';
	cout << coef[0];
}

