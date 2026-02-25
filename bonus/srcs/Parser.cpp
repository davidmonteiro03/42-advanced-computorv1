/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:06:29 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/25 17:40:58 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

Parser::Parser(void) {}

Parser::Parser(const Parser &) {}

Parser &Parser::operator=(const Parser &) { return *this; }

Parser::~Parser() {}

std::list<std::string> Parser::tokenization(const std::string &expr)
{
	std::list<std::string> tokens;
	if (expr.empty())
		return tokens;
	for (std::string::const_iterator c = expr.begin(); c != expr.end();)
	{
		if (std::isspace(*c) != false)
		{
			c++;
			continue;
		}
		if (std::strchr(OPERATOR_CHARS, *c) != NULL)
		{
			tokens.push_back(expr.substr(std::distance(expr.begin(), c++), 1));
			continue;
		}
		std::string::const_iterator k = c;
		for (; c != expr.end() && std::isspace(*c) == false && std::strchr(OPERATOR_CHARS, *c) == NULL; c++)
			;
		tokens.push_back(expr.substr(std::distance(expr.begin(), k), std::distance(k, c)));
	}
	return tokens;
}

void Parser::checkSyntax(const std::list<std::string> &tokens)
{
	if (tokens.empty())
		throw std::invalid_argument("expression can not be empty");
	bool hasEquals = false;
	for (std::list<std::string>::const_iterator t = tokens.begin(); t != tokens.end(); t++)
	{
		if (*t == "+")
		{
			Parser::__checkSyntaxPlus(t, tokens.end());
			continue;
		}
		if (*t == "-")
		{
			Parser::__checkSyntaxMinus(t, tokens.end());
			continue;
		}
		if (*t == "*")
		{
			Parser::__checkSyntaxAsterisk(t, tokens.end());
			continue;
		}
		if (*t == "=")
		{
			if (hasEquals == true)
				throw std::invalid_argument("expression can only contain one equals sign");
			hasEquals = true;
			Parser::__checkSyntaxEquals(t, tokens.end());
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
		Parser::__checkSyntaxValue(t, tokens.end());
	}
	if (hasEquals == false)
		throw std::invalid_argument("expression must contain one equals sign");
}

void Parser::checkVocabulary(const std::list<std::string> &tokens)
{
	if (tokens.empty())
		throw std::invalid_argument("expression can not be empty");
	for (std::list<std::string>::const_iterator t = tokens.begin(); t != tokens.end();)
	{
		if (*t == "=")
		{
			t++;
			continue;
		}
		std::string valueStr = "1", degreeStr = "0";
		bool isDegreeNegative = false;
		while (t != tokens.end() && (*t == "+" || *t == "-"))
			t++;
		if (t != tokens.end() && Parser::__isOperator(*t) == false)
			valueStr = *t++;
		if (t != tokens.end() && *t == "*")
			t++;
		if (t != tokens.end() && *t == "X")
		{
			degreeStr = "1";
			if (++t != tokens.end() && *t == "^")
			{
				while (++t != tokens.end() && (*t == "+" || *t == "-"))
					if (*t == "-")
						isDegreeNegative = !isDegreeNegative;
				if (t != tokens.end() && Parser::__isOperator(*t) == false)
					degreeStr = *t++;
			}
		}
		Parser::__checkVocabularyValue(valueStr);
		Parser::__checkVocabularyDegree(degreeStr);
		if (isDegreeNegative == true)
			throw std::invalid_argument("expression degrees must be natural values");
	}
}

bool Parser::__isOperator(const std::string &token)
{
	if (token.empty() == true)
		return false;
	if (token.size() > 1)
		return false;
	return std::strchr(OPERATOR_CHARS, token[0]) != NULL;
}

void Parser::__checkSyntaxPlus(const std::list<std::string>::const_iterator &curr,
							   const std::list<std::string>::const_iterator &end)
{
	const std::list<std::string>::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (next == end)
		throw std::invalid_argument("+ operator must contain something after it");
	if (prev != end && *prev == "*")
		throw std::invalid_argument("+ operator can not contain * operator before it");
	if (next != end && (*next == "*" || *next == "=" || *next == "^"))
		throw std::invalid_argument("+ operator can not contain " + *next + " operator after it");
}

void Parser::__checkSyntaxMinus(const std::list<std::string>::const_iterator &curr,
								const std::list<std::string>::const_iterator &end)
{
	const std::list<std::string>::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (next == end)
		throw std::invalid_argument("- operator must contain something after it");
	if (prev != end && *prev == "*")
		throw std::invalid_argument("- operator can not contain * operator before it");
	if (next != end && (*next == "*" || *next == "=" || *next == "^"))
		throw std::invalid_argument("- operator can not contain " + *next + " operator after it");
	if (prev != end && next != end)
		if (*prev == "^" && (*next == "X" || Parser::__isOperator(*next) == false))
			throw std::invalid_argument("expression degrees must be natural values");
}

void Parser::__checkSyntaxAsterisk(const std::list<std::string>::const_iterator &curr,
								   const std::list<std::string>::const_iterator &end)
{
	const std::list<std::string>::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (prev == end)
		throw std::invalid_argument("* operator must contain something before it");
	if (next == end)
		throw std::invalid_argument("* operator must contain something after it");
	if (prev != end && Parser::__isOperator(*prev) == true)
		throw std::invalid_argument("* operator must contain values before it");
	if (next != end && *next != "X")
		throw std::invalid_argument("* operator must contain variable X after it");
}

void Parser::__checkSyntaxEquals(const std::list<std::string>::const_iterator &curr,
								 const std::list<std::string>::const_iterator &end)
{
	const std::list<std::string>::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (prev == end)
		throw std::invalid_argument("= operator must contain something before it");
	if (next == end)
		throw std::invalid_argument("= operator must contain something after it");
	if (prev != end && *prev != "X" && Parser::__isOperator(*prev) == true)
		throw std::invalid_argument("= operator must contain values or variable X before it");
	if (next != end && (*next == "*" || *next == "=" || *next == "^"))
		throw std::invalid_argument("= operator must contain values, variable X or +/- operators after it");
}

void Parser::__checkSyntaxCaret(const std::list<std::string>::const_iterator &curr,
								const std::list<std::string>::const_iterator &end)
{
	const std::list<std::string>::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (prev == end)
		throw std::invalid_argument("^ operator must contain something before it");
	if (next == end)
		throw std::invalid_argument("^ operator must contain something after it");
	if (prev != end && *prev != "X")
		throw std::invalid_argument("^ operator must contain variable X before it");
	if (next != end && *next != "+" && *next != "-" && Parser::__isOperator(*next) == true)
		throw std::invalid_argument("^ operator must contain values after it");
}

void Parser::__checkSyntaxVariableX(const std::list<std::string>::const_iterator &curr,
									const std::list<std::string>::const_iterator &end)
{
	const std::list<std::string>::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (prev != end && (*prev == "^" || *prev == "X"))
		throw std::invalid_argument("variable X can not contain ^ operator neither variable X before it");
	if (next != end && (*next == "*" || *next == "X" || Parser::__isOperator(*next) == false))
		throw std::invalid_argument("variable X can not contain * operator neither variable X neither values before it");
	if (prev != end && next != end)
		if (*prev == "=" && *next == "=")
			throw std::invalid_argument("variable X can not contain = operator before and other = operator after it");
}

void Parser::__checkSyntaxValue(const std::list<std::string>::const_iterator &curr,
								const std::list<std::string>::const_iterator &end)
{
	const std::list<std::string>::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (prev != end && (*prev == "*" || *prev == "X" || Parser::__isOperator(*prev) == false))
		throw std::invalid_argument("values can not contain * operator neither variable X neither values before it");
	if (next != end && *next == "^")
		throw std::invalid_argument("values can not contain ^ operator after it");
	if (prev != end && next != end)
	{
		if (*prev == "=" && *next == "=")
			throw std::invalid_argument("values can not contain = operator before and other = operator after it");
		if (*prev == "^" && (*next == "*" || *next == "X"))
			throw std::invalid_argument("values can not contain ^ operator before and * operator or variable X after it");
	}
}

void Parser::__checkVocabularyValue(const std::string &token)
{
	if (token.empty() == true)
		throw std::invalid_argument("value \"" + token + "\" can not be empty");
	std::string::const_iterator c = token.begin();
	while (c != token.end() && std::isspace(*c) != 0)
		c++;
	if (c != token.end() && (*c == '+' || *c == '-'))
		c++;
	bool hasIntegerPart = false, hasDecimalPart = false;
	while (c != token.end() && std::isdigit(*c) != 0)
	{
		hasIntegerPart = true;
		c++;
	}
	if (c != token.end() && *c == '.')
	{
		c++;
		while (c != token.end() && std::isdigit(*c) != 0)
		{
			hasDecimalPart = true;
			c++;
		}
	}
	while (c != token.end() && std::isspace(*c) != 0)
		c++;
	if (c != token.end())
		throw std::invalid_argument("value \"" + token + "\" contains invalid characters");
	if (hasIntegerPart == false && hasDecimalPart == false)
		throw std::invalid_argument("value \"" + token + "\" must have digits");
}

void Parser::__checkVocabularyDegree(const std::string &token)
{
	if (token.empty() == true)
		throw std::invalid_argument("degree \"" + token + "\" can not be empty");
	std::string::const_iterator c = token.begin();
	while (c != token.end() && std::isspace(*c) != 0)
		c++;
	if (c != token.end() && (*c == '+' || *c == '-'))
		c++;
	bool hasDigits = false;
	while (c != token.end() && std::isdigit(*c) != 0)
	{
		hasDigits = true;
		c++;
	}
	while (c != token.end() && std::isspace(*c) != 0)
		c++;
	if (c != token.end())
		throw std::invalid_argument("degree \"" + token + "\" contains invalid characters");
	if (hasDigits == false)
		throw std::invalid_argument("degree \"" + token + "\" must have digits");
}
