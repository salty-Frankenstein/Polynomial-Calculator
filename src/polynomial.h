#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include<vector>

bool Feq(double a, double b);

class Polynomial{
public:
	Polynomial(const std::vector<double>& p, bool high = false);
	Polynomial operator+(const Polynomial&)const;
	Polynomial operator-()const;
	Polynomial operator-(const Polynomial&)const;
	//Polynomial operator*(const Polynomial&)const;
	void Show();
private:
	void Standardize();

	std::vector<double> coef;
	int maxTerm;
};

#endif //!POLYNOMIAL_H

