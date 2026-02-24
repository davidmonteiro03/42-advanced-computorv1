/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fraction.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:18:02 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/24 11:46:57 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

Fraction::Fraction(void) : __numerator(),
						   __denominator() { this->__reduce(); }

Fraction::Fraction(const Real &dividend,
				   const Real &divisor)
{
	Real tmpNumerator(dividend), tmpDenominator(divisor);
	tmpNumerator.__isNegative = false;
	tmpDenominator.__isNegative = false;
	while (tmpNumerator.__digits.second.empty() == false || tmpDenominator.__digits.second.empty() == false)
	{
		int newNumeratorDigit = 0, newDenominatorDigit = 0;
		if (tmpNumerator.__digits.second.empty() == false)
		{
			newNumeratorDigit = tmpNumerator.__digits.second.front();
			tmpNumerator.__digits.second.erase(tmpNumerator.__digits.second.begin());
		}
		if (tmpDenominator.__digits.second.empty() == false)
		{
			newDenominatorDigit = tmpDenominator.__digits.second.front();
			tmpDenominator.__digits.second.erase(tmpDenominator.__digits.second.begin());
		}
		tmpNumerator.__digits.first.push_back(newNumeratorDigit);
		tmpDenominator.__digits.first.push_back(newDenominatorDigit);
	}
	std::stringstream ss;
	ss << tmpNumerator << " " << tmpDenominator;
	ss >> *this;
}

Fraction::Fraction(const Fraction &copy) : __numerator(copy.__numerator),
										   __denominator(copy.__denominator) { this->__reduce(); }

Fraction &Fraction::operator=(const Fraction &other)
{
	if (this != &other)
	{
		this->__numerator = other.__numerator;
		this->__denominator = other.__denominator;
		this->__reduce();
	}
	return *this;
}

Fraction::~Fraction() {}

Real Fraction::__round(const std::size_t &precision) const
{
	Real result;
	Integer dividend(this->__numerator), divisor(this->__denominator), remainder;
	for (std::size_t i = 0; i < dividend.__digits.size(); i++)
	{
		remainder.__digits.push_back(dividend.__digits[i]);
		int newDigit = 0;
		while (remainder >= divisor)
		{
			remainder -= divisor;
			newDigit++;
		}
		result.__digits.first.push_back(newDigit);
		remainder.__simplify();
	}
	for (std::size_t i = 0; i < precision; i++)
	{
		remainder.__digits.push_back(0);
		int newDigit = 0;
		while (remainder >= divisor)
		{
			remainder -= divisor;
			newDigit++;
		}
		result.__digits.second.push_back(newDigit);
		remainder.__simplify();
	}
	result.__simplify(true);
	return result;
}

std::istream &operator>>(std::istream &is,
						 Fraction &p_frac)
{
	is >> p_frac.__numerator >> p_frac.__denominator;
	p_frac.__reduce();
	return is;
}

std::ostream &operator<<(std::ostream &os,
						 const Fraction &p_frac)
{
	Integer one;
	std::stringstream ss("1");
	ss >> one;
	os << p_frac.__numerator;
	if (p_frac.__denominator != one)
		os << '/' << p_frac.__denominator;
	return os;
}

void Fraction::__reduce(void)
{
	this->__numerator.__isNegative = false;
	this->__denominator.__isNegative = false;
	this->__numerator.__simplify();
	this->__denominator.__simplify();
	if (!this->__denominator)
		throw std::invalid_argument("can't have fractions with denominator zero");
	Integer a(this->__numerator);
	Integer b(this->__denominator);
	if (!b)
		return;
	a.__isNegative = false;
	b.__isNegative = false;
	while (!b == false)
	{
		Integer r = a % b;
		a = b;
		b = r;
	}
	if (!a)
		return;
	this->__numerator /= a;
	this->__denominator /= a;
}
