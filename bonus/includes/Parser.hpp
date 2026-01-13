/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:07:37 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/13 11:21:48 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_computor.hpp"

class Parser
{
private:
	Parser(void);
	Parser(const Parser &);
	Parser &operator=(const Parser &);
	~Parser();

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

	static void __checkVocabularyNumbers(const tokens_t &);
	static void __checkVocabularyEquals(const tokens_t &);

public:
	static tokens_t tokenization(const std::string &);

	static void checkSyntax(const tokens_t &);
	static void checkVocabulary(const tokens_t &);

	Equation compute(const tokens_t &);
};
