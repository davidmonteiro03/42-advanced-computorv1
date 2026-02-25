/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Real.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:50:11 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/25 15:22:09 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

const std::size_t Real::__precision = 16;

Real::Real(void) : __digits(),
				   __isNegative(false) { this->__simplify(false); }

Real::Real(const Real &copy) : __digits(copy.__digits),
							   __isNegative(copy.__isNegative) { this->__simplify(false); }

Real &Real::operator=(const Real &other)
{
	if (this != &other)
	{
		this->__digits = other.__digits;
		this->__isNegative = other.__isNegative;
		this->__simplify(false);
	}
	return *this;
}

Real::~Real() {}

bool Real::operator>(const Real &other) const
{
	if (this->__isNegative != other.__isNegative)
		return other.__isNegative;
	if (this->__digits.first.size() != other.__digits.first.size())
		return this->__isNegative == false ? this->__digits.first.size() > other.__digits.first.size()
										   : this->__digits.first.size() < other.__digits.first.size();
	for (std::size_t i = 0; i < this->__digits.first.size(); i++)
		if (this->__digits.first[i] != other.__digits.first[i])
			return this->__isNegative == false ? this->__digits.first[i] > other.__digits.first[i]
											   : this->__digits.first[i] < other.__digits.first[i];
	Real a(*this), b(other);
	const std::size_t aSize = a.__digits.second.size(), bSize = b.__digits.second.size();
	const std::size_t maxSize = std::max(aSize, bSize);
	for (std::size_t i = aSize; i < maxSize; i++)
		a.__digits.second.push_back(0);
	for (std::size_t i = bSize; i < maxSize; i++)
		b.__digits.second.push_back(0);
	for (std::size_t i = 0; i < maxSize; i++)
		if (a.__digits.second[i] != b.__digits.second[i])
			return a.__isNegative == false ? a.__digits.second[i] > b.__digits.second[i]
										   : a.__digits.second[i] < b.__digits.second[i];
	return false;
}

bool Real::operator<(const Real &other) const
{
	if (this->__isNegative != other.__isNegative)
		return this->__isNegative;
	if (this->__digits.first.size() != other.__digits.first.size())
		return this->__isNegative == false ? this->__digits.first.size() < other.__digits.first.size()
										   : this->__digits.first.size() > other.__digits.first.size();
	for (std::size_t i = 0; i < this->__digits.first.size(); i++)
		if (this->__digits.first[i] != other.__digits.first[i])
			return this->__isNegative == false ? this->__digits.first[i] < other.__digits.first[i]
											   : this->__digits.first[i] > other.__digits.first[i];
	Real a(*this), b(other);
	const std::size_t aSize = a.__digits.second.size(), bSize = b.__digits.second.size();
	const std::size_t maxSize = std::max(aSize, bSize);
	for (std::size_t i = aSize; i < maxSize; i++)
		a.__digits.second.push_back(0);
	for (std::size_t i = bSize; i < maxSize; i++)
		b.__digits.second.push_back(0);
	for (std::size_t i = 0; i < maxSize; i++)
		if (a.__digits.second[i] != b.__digits.second[i])
			return a.__isNegative == false ? a.__digits.second[i] < b.__digits.second[i]
										   : a.__digits.second[i] > b.__digits.second[i];
	return false;
}

bool Real::operator>=(const Real &other) const
{
	if (this->__isNegative != other.__isNegative)
		return other.__isNegative;
	if (this->__digits.first.size() != other.__digits.first.size())
		return this->__isNegative == false ? this->__digits.first.size() > other.__digits.first.size()
										   : this->__digits.first.size() < other.__digits.first.size();
	for (std::size_t i = 0; i < this->__digits.first.size(); i++)
		if (this->__digits.first[i] != other.__digits.first[i])
			return this->__isNegative == false ? this->__digits.first[i] > other.__digits.first[i]
											   : this->__digits.first[i] < other.__digits.first[i];
	Real a(*this), b(other);
	const std::size_t aSize = a.__digits.second.size(), bSize = b.__digits.second.size();
	const std::size_t maxSize = std::max(aSize, bSize);
	for (std::size_t i = aSize; i < maxSize; i++)
		a.__digits.second.push_back(0);
	for (std::size_t i = bSize; i < maxSize; i++)
		b.__digits.second.push_back(0);
	for (std::size_t i = 0; i < maxSize; i++)
		if (a.__digits.second[i] != b.__digits.second[i])
			return a.__isNegative == false ? a.__digits.second[i] > b.__digits.second[i]
										   : a.__digits.second[i] < b.__digits.second[i];
	return true;
}

bool Real::operator<=(const Real &other) const
{
	if (this->__isNegative != other.__isNegative)
		return this->__isNegative;
	if (this->__digits.first.size() != other.__digits.first.size())
		return this->__isNegative == false ? this->__digits.first.size() < other.__digits.first.size()
										   : this->__digits.first.size() > other.__digits.first.size();
	for (std::size_t i = 0; i < this->__digits.first.size(); i++)
		if (this->__digits.first[i] != other.__digits.first[i])
			return this->__isNegative == false ? this->__digits.first[i] < other.__digits.first[i]
											   : this->__digits.first[i] > other.__digits.first[i];
	Real a(*this), b(other);
	const std::size_t aSize = a.__digits.second.size(), bSize = b.__digits.second.size();
	const std::size_t maxSize = std::max(aSize, bSize);
	for (std::size_t i = aSize; i < maxSize; i++)
		a.__digits.second.push_back(0);
	for (std::size_t i = bSize; i < maxSize; i++)
		b.__digits.second.push_back(0);
	for (std::size_t i = 0; i < maxSize; i++)
		if (a.__digits.second[i] != b.__digits.second[i])
			return a.__isNegative == false ? a.__digits.second[i] < b.__digits.second[i]
										   : a.__digits.second[i] > b.__digits.second[i];
	return true;
}

bool Real::operator==(const Real &other) const { return this->__digits.first == other.__digits.first &&
														this->__digits.second == other.__digits.second &&
														this->__isNegative == other.__isNegative; }

bool Real::operator!=(const Real &other) const { return this->__digits.first != other.__digits.first ||
														this->__digits.second != other.__digits.second ||
														this->__isNegative != other.__isNegative; }

bool Real::operator!(void) const
{
	if (this->__digits.first.empty() == true && this->__digits.second.empty() == true)
		return true;
	for (std::vector<int>::const_iterator d = this->__digits.first.begin(); d != this->__digits.first.end(); d++)
		if (*d != 0)
			return false;
	for (std::vector<int>::const_iterator d = this->__digits.second.begin(); d != this->__digits.second.end(); d++)
		if (*d != 0)
			return false;
	return true;
}

Real Real::operator-(void) const
{
	Real tmp(*this);
	tmp.__isNegative = !tmp.__isNegative;
	return tmp;
}

Real Real::operator+(const Real &other) const
{
	Real result;
	Real absA(*this), absB(other);
	absA.__isNegative = false;
	absB.__isNegative = false;
	if (this->__isNegative == other.__isNegative)
	{
		result.__digits = Real::__computeDigitSum(this->__digits, other.__digits);
		result.__isNegative = this->__isNegative;
	}
	else
	{
		Real top = this->__isNegative == false ? absA : absB, bottom = this->__isNegative == false ? absB : absA;
		if (top >= bottom)
			result.__digits = Real::__computeDigitDif(top.__digits, bottom.__digits);
		else
			result.__digits = Real::__computeDigitDif(bottom.__digits, top.__digits);
		result.__isNegative = top < bottom;
	}
	result.__simplify(false);
	return result;
}

Real Real::operator-(const Real &other) const { return *this + -other; }

Real Real::operator*(const Real &other) const
{
	Real result;
	result.__digits = Real::__computeDigitMul(this->__digits, other.__digits);
	result.__isNegative = this->__isNegative != other.__isNegative;
	result.__simplify(false);
	return result;
}

Real Real::operator/(const Real &other) const
{
	if (!other)
		throw std::invalid_argument("can't compute division by zero");
	Real result;
	Fraction fraction(*this, other);
	result = fraction.__round(Real::__precision);
	result.__isNegative = this->__isNegative != other.__isNegative;
	result.__simplify(true);
	return result;
}

Real &Real::operator+=(const Real &other)
{
	*this = *this + other;
	return *this;
}

Real &Real::operator-=(const Real &other)
{
	*this = *this - other;
	return *this;
}

Real &Real::operator*=(const Real &other)
{
	*this = *this * other;
	return *this;
}

Real &Real::operator/=(const Real &other)
{
	*this = *this / other;
	return *this;
}

std::istream &operator>>(std::istream &is,
						 Real &p_real)
{
	std::string buffer;
	is >> buffer;
	if (buffer.empty() == true)
		return is;
	p_real.__digits.first.clear();
	p_real.__digits.second.clear();
	p_real.__isNegative = false;
	std::string::iterator c = buffer.begin();
	while (c != buffer.end() && std::isspace(*c) != 0)
		c++;
	if (c != buffer.end() && (*c == '+' || *c == '-'))
		if (*c++ == '-')
			p_real.__isNegative = true;
	while (c != buffer.end() && std::isdigit(*c) != 0)
		p_real.__digits.first.push_back(static_cast<int>(*c++ - '0'));
	if (c != buffer.end() && *c == '.')
		c++;
	while (c != buffer.end() && std::isdigit(*c) != 0)
		p_real.__digits.second.push_back(static_cast<int>(*c++ - '0'));
	p_real.__simplify(false);
	return is;
}

std::ostream &operator<<(std::ostream &os,
						 const Real &p_real)
{
	if (!p_real)
		return os << '0';
	if (p_real.__isNegative == true)
		os << '-';
	if (p_real.__digits.first.empty() == true)
		os << '0';
	for (std::vector<int>::const_iterator d = p_real.__digits.first.begin(); d != p_real.__digits.first.end(); d++)
		os << *d;
	if (p_real.__digits.second.empty() == false)
		os << '.';
	for (std::vector<int>::const_iterator d = p_real.__digits.second.begin(); d != p_real.__digits.second.end(); d++)
		os << *d;
	return os;
}

void Real::__simplify(const bool &fixPrecision)
{
	if (fixPrecision == true)
		while (this->__digits.second.size() > Real::__precision)
			this->__digits.second.pop_back();
	while (this->__digits.first.empty() == false && this->__digits.first.front() == 0)
		this->__digits.first.erase(this->__digits.first.begin());
	while (this->__digits.second.empty() == false && this->__digits.second.back() == 0)
		this->__digits.second.pop_back();
	if (this->__digits.first.empty() == true && this->__digits.second.empty() == true)
		this->__isNegative = false;
}

std::pair<std::vector<int>, std::vector<int>> Real::__computeDigitSum(const std::pair<std::vector<int>, std::vector<int>> &digitsA,
																	  const std::pair<std::vector<int>, std::vector<int>> &digitsB)
{
	std::pair<std::vector<int>, std::vector<int>> result;
	std::pair<std::vector<int>, std::vector<int>> a(digitsA), b(digitsB);
	const std::size_t aDecSize = a.second.size(), bDecSize = b.second.size();
	const std::size_t maxDecSize = std::max(aDecSize, bDecSize);
	for (std::size_t i = aDecSize; i < maxDecSize; i++)
		a.second.push_back(0);
	for (std::size_t i = bDecSize; i < maxDecSize; i++)
		b.second.push_back(0);
	const std::size_t aIntSize = a.first.size(), bIntSize = b.first.size();
	const std::size_t maxIntSize = std::max(aIntSize, bIntSize);
	for (std::size_t i = aIntSize; i < maxIntSize; i++)
		a.first.insert(a.first.begin(), 0);
	for (std::size_t i = bIntSize; i < maxIntSize; i++)
		b.first.insert(b.first.begin(), 0);
	int carry = 0;
	for (std::size_t i = 0; i < maxDecSize; i++)
	{
		int digitA = a.second[maxDecSize - i - 1], digitB = b.second[maxDecSize - i - 1];
		int digitSum = digitA + digitB + carry;
		carry = digitSum > 9 ? 1 : 0;
		result.second.insert(result.second.begin(), carry == 1 ? digitSum - 10 : digitSum);
	}
	for (std::size_t i = 0; i < maxIntSize; i++)
	{
		int digitA = a.first[maxIntSize - i - 1], digitB = b.first[maxIntSize - i - 1];
		int digitSum = digitA + digitB + carry;
		carry = digitSum > 9 ? 1 : 0;
		result.first.insert(result.first.begin(), carry == 1 ? digitSum - 10 : digitSum);
	}
	if (carry > 0)
		result.first.insert(result.first.begin(), 1);
	return result;
}

std::pair<std::vector<int>, std::vector<int>> Real::__computeDigitDif(const std::pair<std::vector<int>, std::vector<int>> &digitsA,
																	  const std::pair<std::vector<int>, std::vector<int>> &digitsB)
{
	std::pair<std::vector<int>, std::vector<int>> result;
	std::pair<std::vector<int>, std::vector<int>> a(digitsA), b(digitsB);
	const std::size_t aDecSize = a.second.size(), bDecSize = b.second.size();
	const std::size_t maxDecSize = std::max(aDecSize, bDecSize);
	for (std::size_t i = aDecSize; i < maxDecSize; i++)
		a.second.push_back(0);
	for (std::size_t i = bDecSize; i < maxDecSize; i++)
		b.second.push_back(0);
	const std::size_t aIntSize = a.first.size(), bIntSize = b.first.size();
	const std::size_t maxIntSize = std::max(aIntSize, bIntSize);
	for (std::size_t i = aIntSize; i < maxIntSize; i++)
		a.first.insert(a.first.begin(), 0);
	for (std::size_t i = bIntSize; i < maxIntSize; i++)
		b.first.insert(b.first.begin(), 0);
	int borrow = 0;
	for (std::size_t i = 0; i < maxDecSize; i++)
	{
		int digitA = a.second[maxDecSize - i - 1], digitB = b.second[maxDecSize - i - 1];
		int digitDif = digitA - digitB - borrow;
		borrow = digitDif < 0 ? 1 : 0;
		result.second.insert(result.second.begin(), borrow == 1 ? digitDif + 10 : digitDif);
	}
	for (std::size_t i = 0; i < maxIntSize; i++)
	{
		int digitA = a.first[maxIntSize - i - 1], digitB = b.first[maxIntSize - i - 1];
		int digitDif = digitA - digitB - borrow;
		borrow = digitDif < 0 ? 1 : 0;
		result.first.insert(result.first.begin(), borrow == 1 ? digitDif + 10 : digitDif);
	}
	return result;
}

std::pair<std::vector<int>, std::vector<int>> Real::__computeDigitMul(const std::pair<std::vector<int>, std::vector<int>> &digitsA,
																	  const std::pair<std::vector<int>, std::vector<int>> &digitsB)
{
	std::pair<std::vector<int>, std::vector<int>> result;
	std::pair<std::vector<int>, std::vector<int>> a(digitsA), b(digitsB);
	std::vector<int> fullA, fullB, tmpResult;
	for (std::size_t i = 0; i < a.first.size(); i++)
		fullA.push_back(a.first[i]);
	for (std::size_t i = 0; i < a.second.size(); i++)
		fullA.push_back(a.second[i]);
	for (std::size_t i = 0; i < b.first.size(); i++)
		fullB.push_back(b.first[i]);
	for (std::size_t i = 0; i < b.second.size(); i++)
		fullB.push_back(b.second[i]);
	tmpResult = Integer::__computeDigitMul(fullA, fullB);
	const std::size_t decPartSize = a.second.size() + b.second.size();
	const std::size_t intPartSize = tmpResult.size() > decPartSize ? tmpResult.size() - decPartSize : 0;
	for (std::size_t i = 0; i < intPartSize; i++)
		result.first.push_back(tmpResult[i]);
	for (std::size_t i = intPartSize; i < tmpResult.size(); i++)
		result.second.push_back(tmpResult[i]);
	return result;
}

Real Real::__sqrt(void) const
{
	Real zero, one, two;
	std::stringstream ss("0 1 2");
	ss >> zero >> one >> two;
	if (*this < zero)
		return Real();
	if (*this == zero || *this == one)
		return *this;
	Real approx(*this);
	Real next;
	while (true)
	{
		next = (approx + *this / approx) / two;
		if (next.__digits.second.size() >= Real::__precision || next == approx)
			break;
		approx = next;
	}
	return approx;
}

bool Real::__hasExactSqrt(void) const
{
	Real hundred;
	std::stringstream ss("100");
	ss >> hundred;
	Real tmp(*this);
	while (tmp.__digits.second.empty() == false)
		tmp *= hundred;
	Real squareRoot = tmp.__sqrt();
	return squareRoot.__digits.second.empty();
}
