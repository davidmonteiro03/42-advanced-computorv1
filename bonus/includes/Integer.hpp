/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Integer.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:22:05 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/23 15:38:00 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_computor.hpp"

class Integer
{
public:
	Integer(void);
	Integer(const Integer &);
	Integer &operator=(const Integer &);
	~Integer();

	bool operator>(const Integer &) const;
	bool operator<(const Integer &) const;
	bool operator>=(const Integer &) const;
	bool operator<=(const Integer &) const;
	bool operator==(const Integer &) const;
	bool operator!=(const Integer &) const;
	bool operator!(void) const;

	Integer operator-(void) const;

	Integer operator+(const Integer &) const;
	Integer operator-(const Integer &) const;
	Integer operator*(const Integer &) const;
	Integer operator/(const Integer &) const;
	Integer operator%(const Integer &) const;

	Integer &operator+=(const Integer &);
	Integer &operator-=(const Integer &);
	Integer &operator*=(const Integer &);
	Integer &operator/=(const Integer &);
	Integer &operator%=(const Integer &);

	Integer &operator++(void);
	Integer &operator--(void);

	Integer operator++(int);
	Integer operator--(int);

	friend std::istream &operator>>(std::istream &,
									Integer &);

	friend std::ostream &operator<<(std::ostream &,
									const Integer &);

private:
	std::vector<int> __digits;
	bool __isNegative;

	void __simplify(void);

	static std::vector<int> __computeDigitSum(const std::vector<int> &,
											  const std::vector<int> &);
	static std::vector<int> __computeDigitDif(const std::vector<int> &,
											  const std::vector<int> &);
	static std::vector<int> __computeDigitMul(const std::vector<int> &,
											  const std::vector<int> &);

	static std::vector<int> __computeDigitIncrement(const std::vector<int> &);
	static std::vector<int> __computeDigitDecrement(const std::vector<int> &);

	friend class Real;
	friend class Fraction;
};
