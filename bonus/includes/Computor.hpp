/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:53:01 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/13 13:27:57 by dcaetano         ###   ########.fr       */
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

	static void __displayComplex(const double &,
								 const double &);

	static bool __isOperator(const std::string &);

	static Term __getHighestDegreeTerm(const reduced_t &);

	static void __displayValue(const double &);

	static void __displayTerm(const long long int &,
							  const double &,
							  const bool &);
	static void __displayTerms(const terms_t &);
	static void __displayReducedForm(const reduced_t &);

	static void __actualSolve(const reduced_t &);

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
