#include"polynomial.h"
#include<cmath>
#include<iostream>
#include<algorithm>
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

Polynomial Polynomial::operator/(const Polynomial& x)const{
	if(x.maxTerm == 0 && x.coef[0] == 0)
		throw "div by 0";
	int n = maxTerm, m = x.maxTerm;
	if(n < m){
		return Polynomial({0});
	}
	vector<double> a(maxTerm + 1), b(x.maxTerm + 1);
	reverse_copy(coef.begin(), coef.end(), a.begin());
	reverse_copy(x.coef.begin(), x.coef.end(), b.begin());
	b.resize(n - m + 1);
	Polynomial ans = Polynomial(b).Inverse() * Polynomial(a);
	ans.coef.resize(n - m + 1);
	reverse(ans.coef.begin(), ans.coef.end());
	ans.Standardize();
	return ans;
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

double Polynomial::ToNum()const{
	auto res = (*this)(0);
	return res.coef[0];
}

double Polynomial::Root(double x)const{
	double x0;
	int time = 0;
	do{
		time++;
		x0 = x;
		if(time > 10000 || Feq((this->Derivation())(x).ToNum(), 0.0))
			throw "no root";
		x = x0 - (*this)(x).ToNum() / (this->Derivation())(x).ToNum();
	}while(!Feq(x, x0));
	return x;
}

Polynomial Polynomial::Inverse()const{
	vector<double> b(maxTerm + 1);
	if(coef[0] == 0)throw "no inv";
	b[0] = 1 / coef[0];
	for(int k = 1; k <= maxTerm; k++){
		for(int i = 0; i < k; i++){
			b[k] += b[i] * (- coef[k-i] / coef[0]);
		}
	}
	return Polynomial(b);
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
		if(i == 1) cout << "x ";
		else cout << "x^" << i << ' ';
	}

	if(Feq(coef[0], 0.0))return;
	if(coef[0] > 0)cout << '+';
	cout << coef[0];
}

