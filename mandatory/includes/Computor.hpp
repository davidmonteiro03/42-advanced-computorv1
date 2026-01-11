/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:53:01 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/11 20:52:53 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../includes/ft_computor.hpp"

class Computor
{
private:
	Computor(void);
	Computor(const Computor &);
	Computor &operator=(const Computor &);
	~Computor();

	static double __sqrt(const double &);

	static void __showReducedForm(const reduced_t &);
	static term_t __getHighestDegreeTerm(const reduced_t &);

	static args_t __split(const std::string &);
	static equation_t __equation(const args_t &);
	static reduced_t __reduce(const equation_t &);

	static void __solveFirstDegreeEquation(const reduced_t &);
	static void __solveSecondDegreeEquation(const reduced_t &);
	static void __solveSecondDegreeEquationPositiveDiscriminant(const double &,
																const double &,
																const double &);
	static void __solveSecondDegreeEquationNegativeDiscriminant(const double &,
																const double &,
																const double &);

public:
	static void solve(const std::string &);
};
