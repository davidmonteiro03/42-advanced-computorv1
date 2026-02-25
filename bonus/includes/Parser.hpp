/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 07:15:40 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/25 17:40:39 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_computor.hpp"

#define OPERATOR_CHARS "+-*=^X"

class Parser
{
public:
	static std::list<std::string> tokenization(const std::string &);

	static void checkSyntax(const std::list<std::string> &);
	static void checkVocabulary(const std::list<std::string> &);

private:
	Parser(void);
	Parser(const Parser &);
	Parser &operator=(const Parser &);
	~Parser();

	static bool __isOperator(const std::string &);

	static void __checkSyntaxPlus(const std::list<std::string>::const_iterator &,
								  const std::list<std::string>::const_iterator &);
	static void __checkSyntaxMinus(const std::list<std::string>::const_iterator &,
								   const std::list<std::string>::const_iterator &);
	static void __checkSyntaxAsterisk(const std::list<std::string>::const_iterator &,
									  const std::list<std::string>::const_iterator &);
	static void __checkSyntaxEquals(const std::list<std::string>::const_iterator &,
									const std::list<std::string>::const_iterator &);
	static void __checkSyntaxCaret(const std::list<std::string>::const_iterator &,
								   const std::list<std::string>::const_iterator &);
	static void __checkSyntaxVariableX(const std::list<std::string>::const_iterator &,
									   const std::list<std::string>::const_iterator &);
	static void __checkSyntaxValue(const std::list<std::string>::const_iterator &,
								   const std::list<std::string>::const_iterator &);

	static void __checkVocabularyValue(const std::string &);
	static void __checkVocabularyDegree(const std::string &);
};
