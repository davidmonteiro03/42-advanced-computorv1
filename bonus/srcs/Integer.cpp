/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Integer.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:40:55 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/24 07:12:29 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

Integer::Integer(void) : __digits(),
						 __isNegative(false) { this->__simplify(); }

Integer::Integer(const Integer &copy) : __digits(copy.__digits),
										__isNegative(copy.__isNegative) { this->__simplify(); }

Integer &Integer::operator=(const Integer &other)
{
	if (this != &other)
	{
		this->__digits = other.__digits;
		this->__isNegative = other.__isNegative;
		this->__simplify();
	}
	return *this;
}

Integer::~Integer() {}

bool Integer::operator>(const Integer &other) const
{
	if (this->__isNegative != other.__isNegative)
		return other.__isNegative;
	if (this->__digits.size() != other.__digits.size())
		return this->__isNegative == false ? this->__digits.size() > other.__digits.size()
										   : this->__digits.size() < other.__digits.size();
	for (std::size_t i = 0; i < this->__digits.size(); i++)
		if (this->__digits[i] != other.__digits[i])
			return this->__isNegative == false ? this->__digits[i] > other.__digits[i]
											   : this->__digits[i] < other.__digits[i];
	return false;
}

bool Integer::operator<(const Integer &other) const
{
	if (this->__isNegative != other.__isNegative)
		return this->__isNegative;
	if (this->__digits.size() != other.__digits.size())
		return this->__isNegative == false ? this->__digits.size() < other.__digits.size()
										   : this->__digits.size() > other.__digits.size();
	for (std::size_t i = 0; i < this->__digits.size(); i++)
		if (this->__digits[i] != other.__digits[i])
			return this->__isNegative == false ? this->__digits[i] < other.__digits[i]
											   : this->__digits[i] > other.__digits[i];
	return false;
}

bool Integer::operator>=(const Integer &other) const
{
	if (this->__isNegative != other.__isNegative)
		return other.__isNegative;
	if (this->__digits.size() != other.__digits.size())
		return this->__isNegative == false ? this->__digits.size() > other.__digits.size()
										   : this->__digits.size() < other.__digits.size();
	for (std::size_t i = 0; i < this->__digits.size(); i++)
		if (this->__digits[i] != other.__digits[i])
			return this->__isNegative == false ? this->__digits[i] > other.__digits[i]
											   : this->__digits[i] < other.__digits[i];
	return true;
}

bool Integer::operator<=(const Integer &other) const
{
	if (this->__isNegative != other.__isNegative)
		return this->__isNegative;
	if (this->__digits.size() != other.__digits.size())
		return this->__isNegative == false ? this->__digits.size() < other.__digits.size()
										   : this->__digits.size() > other.__digits.size();
	for (std::size_t i = 0; i < this->__digits.size(); i++)
		if (this->__digits[i] != other.__digits[i])
			return this->__isNegative == false ? this->__digits[i] < other.__digits[i]
											   : this->__digits[i] > other.__digits[i];
	return true;
}

bool Integer::operator==(const Integer &other) const { return this->__digits == other.__digits &&
															  this->__isNegative == other.__isNegative; }

bool Integer::operator!=(const Integer &other) const { return this->__digits != other.__digits ||
															  this->__isNegative != other.__isNegative; }

bool Integer::operator!(void) const
{
	if (this->__digits.empty() == true)
		return true;
	for (std::vector<int>::const_iterator d = this->__digits.begin(); d != this->__digits.end(); d++)
		if (*d != 0)
			return false;
	return true;
}

Integer Integer::operator-(void) const
{
	Integer tmp(*this);
	tmp.__isNegative = !tmp.__isNegative;
	return tmp;
}

Integer Integer::operator+(const Integer &other) const
{
	Integer result;
	Integer absA(*this), absB(other);
	absA.__isNegative = false;
	absB.__isNegative = false;
	if (this->__isNegative == other.__isNegative)
	{
		result.__digits = Integer::__computeDigitSum(this->__digits, other.__digits);
		result.__isNegative = this->__isNegative;
	}
	else
	{
		Integer top = this->__isNegative == false ? absA : absB, bottom = this->__isNegative == false ? absB : absA;
		if (top >= bottom)
			result.__digits = Integer::__computeDigitDif(top.__digits, bottom.__digits);
		else
			result.__digits = Integer::__computeDigitDif(bottom.__digits, top.__digits);
		result.__isNegative = top < bottom;
	}
	result.__simplify();
	return result;
}

Integer Integer::operator-(const Integer &other) const { return *this + -other; }

Integer Integer::operator*(const Integer &other) const
{
	Integer result;
	result.__digits = Integer::__computeDigitMul(this->__digits, other.__digits);
	result.__isNegative = this->__isNegative != other.__isNegative;
	result.__simplify();
	return result;
}

Integer Integer::operator/(const Integer &other) const
{
	if (!other)
		throw std::invalid_argument("can't compute division by zero");
	Integer result;
	Integer dividend(*this), divisor(other), remainder;
	dividend.__isNegative = false;
	divisor.__isNegative = false;
	for (std::size_t i = 0; i < dividend.__digits.size(); i++)
	{
		remainder.__digits.push_back(dividend.__digits[i]);
		int newDigit = 0;
		while (remainder >= divisor)
		{
			remainder -= divisor;
			newDigit++;
		}
		result.__digits.push_back(newDigit);
		remainder.__simplify();
	}
	result.__isNegative = this->__isNegative != other.__isNegative;
	result.__simplify();
	return result;
}

Integer Integer::operator%(const Integer &other) const
{
	if (!other)
		throw std::invalid_argument("can't compute modulo by zero");
	Integer result;
	Integer dividend(*this), divisor(other);
	dividend.__isNegative = false;
	divisor.__isNegative = false;
	for (std::size_t i = 0; i < dividend.__digits.size(); i++)
	{
		result.__digits.push_back(dividend.__digits[i]);
		while (result >= divisor)
			result -= divisor;
		result.__simplify();
	}
	result.__isNegative = this->__isNegative;
	result.__simplify();
	return result;
}

Integer &Integer::operator+=(const Integer &other)
{
	*this = *this + other;
	return *this;
}

Integer &Integer::operator-=(const Integer &other)
{
	*this = *this - other;
	return *this;
}

Integer &Integer::operator*=(const Integer &other)
{
	*this = *this * other;
	return *this;
}

Integer &Integer::operator/=(const Integer &other)
{
	*this = *this / other;
	return *this;
}

Integer &Integer::operator%=(const Integer &other)
{
	*this = *this % other;
	return *this;
}

Integer &Integer::operator++(void)
{
	if (!*this)
	{
		this->__digits.push_back(1);
		this->__isNegative = false;
		this->__simplify();
		return *this;
	}
	if (this->__isNegative == false)
		this->__digits = Integer::__computeDigitIncrement(this->__digits);
	else
		this->__digits = Integer::__computeDigitDecrement(this->__digits);
	this->__simplify();
	return *this;
}

Integer Integer::operator++(int)
{
	Integer tmp(*this);
	++(*this);
	return tmp;
}

Integer &Integer::operator--(void)
{
	if (!*this)
	{
		this->__digits.push_back(1);
		this->__isNegative = true;
		this->__simplify();
		return *this;
	}
	if (this->__isNegative == false)
		this->__digits = Integer::__computeDigitDecrement(this->__digits);
	else
		this->__digits = Integer::__computeDigitIncrement(this->__digits);
	this->__simplify();
	return *this;
}

Integer Integer::operator--(int)
{
	Integer tmp(*this);
	--(*this);
	return tmp;
}

std::istream &operator>>(std::istream &is,
						 Integer &p_int)
{
	std::string buffer;
	is >> buffer;
	if (buffer.empty() == true)
		return is;
	p_int.__digits.clear();
	p_int.__isNegative = false;
	std::string::iterator c = buffer.begin();
	while (c != buffer.end() && std::isspace(*c) != 0)
		c++;
	if (c != buffer.end() && (*c == '+' || *c == '-'))
		if (*c++ == '-')
			p_int.__isNegative = true;
	while (c != buffer.end() && std::isdigit(*c) != 0)
		p_int.__digits.push_back(static_cast<int>(*c++ - '0'));
	p_int.__simplify();
	return is;
}

std::ostream &operator<<(std::ostream &os,
						 const Integer &p_int)
{
	if (!p_int)
		return os << '0';
	if (p_int.__isNegative == true)
		os << '-';
	for (std::vector<int>::const_iterator d = p_int.__digits.begin(); d != p_int.__digits.end(); d++)
		os << *d;
	return os;
}

void Integer::__simplify(void)
{
	while (this->__digits.empty() == false && this->__digits.front() == 0)
		this->__digits.erase(this->__digits.begin());
	if (this->__digits.empty() == true)
		this->__isNegative = false;
}

std::vector<int> Integer::__computeDigitSum(const std::vector<int> &digitsA,
											const std::vector<int> &digitsB)
{
	std::vector<int> result;
	std::vector<int> a(digitsA), b(digitsB);
	const std::size_t aSize = a.size(), bSize = b.size();
	const std::size_t maxSize = std::max(aSize, bSize);
	for (std::size_t i = aSize; i < maxSize; i++)
		a.insert(a.begin(), 0);
	for (std::size_t i = bSize; i < maxSize; i++)
		b.insert(b.begin(), 0);
	int carry = 0;
	for (std::size_t i = 0; i < maxSize; i++)
	{
		int digitA = a[maxSize - i - 1], digitB = b[maxSize - i - 1];
		int digitSum = digitA + digitB + carry;
		carry = digitSum > 9 ? 1 : 0;
		result.insert(result.begin(), carry == 1 ? digitSum - 10 : digitSum);
	}
	if (carry == 1)
		result.insert(result.begin(), 1);
	return result;
}

std::vector<int> Integer::__computeDigitDif(const std::vector<int> &digitsA,
											const std::vector<int> &digitsB)
{
	std::vector<int> result;
	std::vector<int> a(digitsA), b(digitsB);
	const std::size_t aSize = a.size(), bSize = b.size();
	const std::size_t maxSize = std::max(aSize, bSize);
	for (std::size_t i = aSize; i < maxSize; i++)
		a.insert(a.begin(), 0);
	for (std::size_t i = bSize; i < maxSize; i++)
		b.insert(b.begin(), 0);
	int borrow = 0;
	for (std::size_t i = 0; i < maxSize; i++)
	{
		int digitA = a[maxSize - i - 1], digitB = b[maxSize - i - 1];
		int digitDif = digitA - digitB - borrow;
		borrow = digitDif < 0 ? 1 : 0;
		result.insert(result.begin(), borrow == 1 ? digitDif + 10 : digitDif);
	}
	return result;
}

std::vector<int> Integer::__computeDigitMul(const std::vector<int> &digitsA,
											const std::vector<int> &digitsB)
{
	std::vector<int> result;
	std::vector<int> a(digitsA), b(digitsB);
	const std::size_t aSize = a.size(), bSize = b.size();
	for (std::size_t i = 0; i < aSize; i++)
	{
		std::vector<int> tmpResult;
		int carry = 0;
		for (std::size_t k = 0; k < bSize; k++)
		{
			int digitA = a[aSize - i - 1], digitB = b[bSize - k - 1];
			int digitProd = digitA * digitB + carry;
			carry = digitProd > 9 ? digitProd / 10 : 0;
			tmpResult.insert(tmpResult.begin(), carry > 0 ? digitProd % 10 : digitProd);
		}
		if (carry > 0)
			tmpResult.insert(tmpResult.begin(), carry);
		for (std::size_t k = 0; k < i; k++)
			tmpResult.push_back(0);
		result = Integer::__computeDigitSum(result, tmpResult);
	}
	return result;
}

std::vector<int> Integer::__computeDigitIncrement(const std::vector<int> &digits)
{
	std::vector<int> result(digits);
	const std::size_t digitsSize = digits.size();
	int carry = 0;
	for (std::size_t i = 0; i < digitsSize; i++)
	{
		int lastDigit = result[digitsSize - i - 1];
		int newDigit = lastDigit + (i == 0 ? 1 : 0) + carry;
		carry = newDigit > 9 ? 1 : 0;
		result[digitsSize - i - 1] = newDigit > 9 ? newDigit - 10 : newDigit;
		if (carry == 0)
			break;
	}
	if (carry > 0)
		result.insert(result.begin(), 1);
	return result;
}

std::vector<int> Integer::__computeDigitDecrement(const std::vector<int> &digits)
{
	std::vector<int> result(digits);
	const std::size_t digitsSize = digits.size();
	int borrow = 0;
	for (std::size_t i = 0; i < digitsSize; i++)
	{
		int lastDigit = result[digitsSize - i - 1];
		int newDigit = lastDigit - (i == 0 ? 1 : 0) - borrow;
		borrow = newDigit < 0 ? 1 : 0;
		result[digitsSize - i - 1] = newDigit < 0 ? newDigit + 10 : newDigit;
		if (borrow == 0)
			break;
	}
	return result;
}
