/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fraction.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:13:46 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/24 12:49:18 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_computor.hpp"

class Fraction
{
public:
	Fraction(void);
	Fraction(const Real &,
			 const Real &);
	Fraction(const Fraction &);
	Fraction &operator=(const Fraction &);
	~Fraction();

	friend std::istream &operator>>(std::istream &,
									Fraction &);

	friend std::ostream &operator<<(std::ostream &,
									const Fraction &);

private:
	Integer __numerator;
	Integer __denominator;

	void __reduce(void);

	Real __round(const std::size_t &) const;

	friend class Real;
	friend class Solver;
};
