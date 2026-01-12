/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:53:01 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/12 17:54:57 by dcaetano         ###   ########.fr       */
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

	static bool __isOperator(const std::string &);

	static void __checkSyntaxNumbers(const tokens_t::const_iterator &,
									 const tokens_t::const_iterator &);
	static void __checkSyntaxPlusMinus(const tokens_t::const_iterator &,
									   const tokens_t::const_iterator &);
	static void __checkSyntaxEquals(const tokens_t::const_iterator &,
									const tokens_t::const_iterator &);
	static void __checkSyntaxAsterik(const tokens_t::const_iterator &,
									 const tokens_t::const_iterator &);
	static void __checkSyntaxCaret(const tokens_t::const_iterator &,
								   const tokens_t::const_iterator &);
	static void __checkSyntaxVariableX(const tokens_t::const_iterator &,
									   const tokens_t::const_iterator &);
	static void __checkSyntax(const tokens_t &);

	static void __checkVocabularyNumbers(const tokens_t &);
	static void __checkVocabularyEquals(const tokens_t &);
	static void __checkVocabulary(const tokens_t &);

	static tokens_t __tokenization(const std::string &);
	static equation_t __parse(const tokens_t &);
	static equation_t __moveAllToOneSide(const equation_t &);
	static reduced_t __reduce(const equation_t &);

	static term_t __getHighestDegreeTerm(const reduced_t &);

	static void __displayTerm(const long long int &,
							  const double &,
							  const bool &);
	static void __displayTerms(const terms_t &);
	static void __displayReducedForm(const reduced_t &);

	static equation_t __solveStep1(const tokens_t &);
	static equation_t __solveStep2(const equation_t &);
	static reduced_t __solveStep3(const equation_t &);
	static void __solveStep4(const reduced_t &);

	static void __solveFirstDegreeEquation(const reduced_t &);
	static void __solveSecondDegreeEquation(const reduced_t &);
	static void __solveSecondDegreeEquationPositiveDiscriminant(const double &,
																const double &,
																const double &);

public:
	static void solve(const std::string &);
};
