/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:18:05 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/24 16:08:38 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_computor.hpp"

class Solver
{
public:
	static void solve(const Equation &);

	friend std::ostream &operator<<(std::ostream &,
									const std::map<Integer, Real> &);

private:
	Solver(void);
	Solver(const Solver &);
	Solver &operator=(const Solver &);
	~Solver();

	static void __displayTerm(std::ostream &,
							  const std::pair<Integer, Real> &,
							  const bool &);

	static void __solveZeroDegreeEquation(const Real &);
	static void __solveFirstDegreeEquation(const Real &,
										   const Real &);
	static void __solveSecondDegreeEquation(const Real &,
											const Real &,
											const Real &);

	static void __displayComplex(const Real &,
								 const Real &);

	static void __displayComplexFractions(const Fraction &,
										  const Fraction &,
										  const bool &,
										  const bool &,
										  const bool &);
};
