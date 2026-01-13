/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:10:11 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/13 11:24:15 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

Parser::Parser(void) {}

Parser::Parser(const Parser &) {}

Parser &Parser::operator=(const Parser &) { return *this; }

Parser::~Parser() {}

bool Parser::__isOperator(const std::string &s)
{
	if (s.empty() != false)
		return false;
	if (s.size() != 1)
		return false;
	return std::strchr("+-*=^X", s[0]) != NULL;
}

void Parser::__checkSyntaxNumbers(const tokens_t::const_iterator &curr,
								  const tokens_t::const_iterator &end)
{
	tokens_t::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (prev != end && (*prev == "*" || *prev == "X"))
		throw std::invalid_argument("numbers can't contain '" + *prev + "' before it");
	if (prev != end && Parser::__isOperator(*prev) == false)
		throw std::invalid_argument("numbers can't contain other numbers before it");
	if (next != end && *next == "^")
		throw std::invalid_argument("numbers can't contain '" + *next + "' after it");
	if (next != end && Parser::__isOperator(*next) == false)
		throw std::invalid_argument("numbers can't contain other numbers after it");
}

void Parser::__checkSyntaxPlusMinus(const tokens_t::const_iterator &curr,
									const tokens_t::const_iterator &end)
{
	tokens_t::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (next == end)
		throw std::invalid_argument("'" + *curr + "' sign must contain something after it");
	if (prev != end && (*prev == "*" || *prev == "^"))
		throw std::invalid_argument("'" + *curr + "' sign can't contain '" + *prev + "' before it");
	if (next != end && (*next == "*" || *next == "=" || *next == "^"))
		throw std::invalid_argument("'" + *curr + "' sign can't contain '" + *next + "' after it");
	if (prev != end && next != end && ((*prev == "+" || *prev == "-") && (*next == "+" || *next == "-")))
		throw std::invalid_argument("expression can't have three '+'/'-' consecutive signs");
}

void Parser::__checkSyntaxEquals(const tokens_t::const_iterator &curr,
								 const tokens_t::const_iterator &end)
{
	tokens_t::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (prev == end)
		throw std::invalid_argument("'" + *curr + "' sign must contain something before it");
	if (next == end)
		throw std::invalid_argument("'" + *curr + "' sign must contain something after it");
	if (prev != end && Parser::__isOperator(*prev) != false && *prev != "X")
		throw std::invalid_argument("'" + *curr + "' sign can't contain '" + *prev + "' before it");
	if (next != end && (*next == "*" || *next == "=" || *next == "^"))
		throw std::invalid_argument("'" + *curr + "' sign can't contain '" + *next + "' after it");
}

void Parser::__checkSyntaxAsterik(const tokens_t::const_iterator &curr,
								  const tokens_t::const_iterator &end)
{
	tokens_t::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (prev == end)
		throw std::invalid_argument("'" + *curr + "' sign must contain something before it");
	if (next == end)
		throw std::invalid_argument("'" + *curr + "' sign must contain something after it");
	if (prev != end && Parser::__isOperator(*prev) != false)
		throw std::invalid_argument("'" + *curr + "' sign must contain numbers before it");
	if (next != end && *next != "X")
		throw std::invalid_argument("'" + *curr + "' sign must contain an 'X' after it");
}

void Parser::__checkSyntaxCaret(const tokens_t::const_iterator &curr,
								const tokens_t::const_iterator &end)
{
	tokens_t::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (prev == end)
		throw std::invalid_argument("'" + *curr + "' sign must contain something before it");
	if (next == end)
		throw std::invalid_argument("'" + *curr + "' sign must contain something after it");
	if (prev != end && *prev != "X")
		throw std::invalid_argument("'" + *curr + "' sign must contain an 'X' before it");
	if (next != end && Parser::__isOperator(*next) != false)
		throw std::invalid_argument("'" + *curr + "' sign must contain numbers after it");
}

void Parser::__checkSyntaxVariableX(const tokens_t::const_iterator &curr,
									const tokens_t::const_iterator &end)
{
	tokens_t::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (prev != end && (*prev == "^" || *prev == "X"))
		throw std::invalid_argument("'" + *curr + "' sign must contain an '" + *prev + "' before it");
	if (next != end && (*next == "*" || *next == "X"))
		throw std::invalid_argument("'" + *curr + "' sign must contain an '" + *next + "' after it");
}

void Parser::__checkVocabularyEquals(const tokens_t &tokens)
{
	bool hasEquals = false;
	for (tokens_t::const_iterator t = tokens.begin(); t != tokens.end(); t++)
	{
		if (*t == "=")
		{
			if (hasEquals == true)
				throw std::invalid_argument("expression must have only one '=' sign");
			hasEquals = true;
		}
	}
	if (hasEquals == false)
		throw std::invalid_argument("expression must have a '=' sign");
}

void Parser::__checkVocabularyNumbers(const tokens_t &tokens)
{
	for (tokens_t::const_iterator t = tokens.begin(); t != tokens.end(); t++)
	{
		if (Parser::__isOperator(*t) == false)
		{
			tokens_t::const_iterator prev = std::prev(t);
			if (prev != tokens.end() && *prev == "^")
			{
				double dDouble = 0;
				long long int dInt = 0;
				std::stringstream ssDouble(*t), ssInt(*t);
				ssDouble >> dDouble;
				ssInt >> dInt;
				double check = static_cast<double>(dInt);
				if (dDouble != check)
					throw std::invalid_argument("'X' exponents must be integer");
			}
		}
	}
}

tokens_t Parser::tokenization(const std::string &expr)
{
	for (std::string::const_iterator c = expr.begin(); c != expr.end(); c++)
		if (std::strchr("0123456789+-*=.X^", *c) == NULL && std::isspace(*c) == false)
			throw std::invalid_argument("expression contains invalid characters");
	tokens_t tokens;
	for (std::string::const_iterator c = expr.begin(); c != expr.end();)
	{
		if (std::isspace(*c) != false)
		{
			c++;
			continue;
		}
		if (std::strchr("+-*=^X", *c) != NULL)
		{
			tokens.push_back(expr.substr(std::distance(expr.begin(), c++), 1));
			continue;
		}
		std::string::const_iterator start = c;
		for (; c != expr.end() && std::isspace(*c) == false && std::strchr("+-*=^X", *c) == NULL; c++)
			;
		std::string::const_iterator end = c;
		tokens.push_back(expr.substr(std::distance(expr.begin(), start), std::distance(start, end)));
	}
	return tokens;
}

void Parser::checkSyntax(const tokens_t &tokens)
{
	if (tokens.empty() != false)
		return;
	for (tokens_t::const_iterator t = tokens.begin(); t != tokens.end(); t++)
	{
		if (Parser::__isOperator(*t) == false)
		{
			Parser::__checkSyntaxNumbers(t, tokens.end());
			continue;
		}
		if (*t == "+" || *t == "-")
		{
			Parser::__checkSyntaxPlusMinus(t, tokens.end());
			continue;
		}
		if (*t == "=")
		{
			Parser::__checkSyntaxEquals(t, tokens.end());
			continue;
		}
		if (*t == "*")
		{
			Parser::__checkSyntaxAsterik(t, tokens.end());
			continue;
		}
		if (*t == "^")
		{
			Parser::__checkSyntaxCaret(t, tokens.end());
			continue;
		}
		if (*t == "X")
		{
			Parser::__checkSyntaxVariableX(t, tokens.end());
			continue;
		}
	}
}

void Parser::checkVocabulary(const tokens_t &tokens)
{
	if (tokens.empty() != false)
		throw std::invalid_argument("expression must not be empty");
	Parser::__checkVocabularyNumbers(tokens);
	Parser::__checkVocabularyEquals(tokens);
}
