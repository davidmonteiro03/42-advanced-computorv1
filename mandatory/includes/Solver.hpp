/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:43:43 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/23 10:06:55 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_computor.hpp"

class Solver
{
public:
	friend std::ostream &operator<<(std::ostream &,
									const std::map<long long int, double> &);

	static void solve(const Equation &);

private:
	Solver(void);
	Solver(const Solver &);
	Solver &operator=(const Solver &);
	~Solver();

	static void __solveZeroDegreeEquation(const double &);
	static void __solveFirstDegreeEquation(const double &,
										   const double &);
	static void __solveSecondDegreeEquation(const double &,
											const double &,
											const double &);

	static double __sqrt(const double &);

	static void __displayComplex(const double &,
								 const double &);
};
