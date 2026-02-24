/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Real.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:45:40 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/24 13:19:12 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_computor.hpp"

class Real
{
public:
	Real(void);
	Real(const Real &);
	Real &operator=(const Real &);
	~Real();

	bool operator>(const Real &) const;
	bool operator<(const Real &) const;
	bool operator>=(const Real &) const;
	bool operator<=(const Real &) const;
	bool operator==(const Real &) const;
	bool operator!=(const Real &) const;
	bool operator!(void) const;

	Real operator-(void) const;

	Real operator+(const Real &) const;
	Real operator-(const Real &) const;
	Real operator*(const Real &) const;
	Real operator/(const Real &) const;

	Real &operator+=(const Real &);
	Real &operator-=(const Real &);
	Real &operator*=(const Real &);
	Real &operator/=(const Real &);

	friend std::istream &operator>>(std::istream &,
									Real &);

	friend std::ostream &operator<<(std::ostream &,
									const Real &);

private:
	static const std::size_t __precision;
	std::pair<std::vector<int>, std::vector<int>> __digits;
	bool __isNegative;

	void __simplify(const bool &);

	static std::pair<std::vector<int>, std::vector<int>> __computeDigitSum(const std::pair<std::vector<int>, std::vector<int>> &,
																		   const std::pair<std::vector<int>, std::vector<int>> &);

	static std::pair<std::vector<int>, std::vector<int>> __computeDigitDif(const std::pair<std::vector<int>, std::vector<int>> &,
																		   const std::pair<std::vector<int>, std::vector<int>> &);

	static std::pair<std::vector<int>, std::vector<int>> __computeDigitMul(const std::pair<std::vector<int>, std::vector<int>> &,
																		   const std::pair<std::vector<int>, std::vector<int>> &);

	Real __sqrt(void) const;

	bool __hasExactSqrt(void) const;

	friend class Fraction;
	friend class Solver;
};
