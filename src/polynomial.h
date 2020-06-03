#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include<vector>

bool Feq(double a, double b);

class Polynomial{
public:
	Polynomial() = default;
	Polynomial(const std::vector<double>& p, bool high = false);
	Polynomial operator()(double)const;
	Polynomial operator+(const Polynomial&)const;
	Polynomial operator-()const;
	Polynomial operator-(const Polynomial&)const;
	Polynomial operator*(const Polynomial&)const;
	Polynomial Derivation()const;
	Polynomial Integral(double low, double up)const;

	double ToNum()const;
	double Root(double x0)const;
	Polynomial Inverse()const;
	void Show();
private:
	void Standardize();

	std::vector<double> coef;
	int maxTerm;
};

#endif //!POLYNOMIAL_H

