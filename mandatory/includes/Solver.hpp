/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:43:43 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/25 17:51:18 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_computor.hpp"

class Solver
{
public:
	friend std::ostream &operator<<(std::ostream &,
									const std::map<unsigned long long int, long double> &);

	static void solve(const Equation &);

private:
	Solver(void);
	Solver(const Solver &);
	Solver &operator=(const Solver &);
	~Solver();

	static void __solveZeroDegreeEquation(const long double &);
	static void __solveFirstDegreeEquation(const long double &,
										   const long double &);
	static void __solveSecondDegreeEquation(const long double &,
											const long double &,
											const long double &);

	static long double __sqrt(const long double &);

	static void __displayComplex(const long double &,
								 const long double &);
};
