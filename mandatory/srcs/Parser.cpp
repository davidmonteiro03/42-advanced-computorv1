/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 07:17:17 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/23 10:16:06 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

Parser::Parser(void) {}

Parser::Parser(const Parser &) {}

Parser &Parser::operator=(const Parser &) { return *this; }

Parser::~Parser() {}

std::vector<std::string> Parser::split(const std::string &s)
{
	std::vector<std::string> words;
	std::stringstream ss(s);
	while (ss.eof() == false)
	{
		std::string word = "";
		ss >> word;
		if (word.empty() == false)
			words.push_back(word);
	}
	return words;
}

bool Parser::checkAsterisk(const std::string &s)
{
	if (s.empty() == true)
		return false;
	std::string::const_iterator c = s.begin();
	while (c != s.end() && std::isspace(*c) != 0)
		c++;
	bool hasAsterisk = false;
	if (c != s.end() && *c == '*')
	{
		hasAsterisk = true;
		c++;
	}
	while (c != s.end() && std::isspace(*c) != 0)
		c++;
	return hasAsterisk == true && c == s.end();
}

bool Parser::checkOperator(const std::string &s)
{
	if (s.empty() == true)
		return false;
	std::string::const_iterator c = s.begin();
	while (c != s.end() && std::isspace(*c) != 0)
		c++;
	bool hasOperator = false;
	if (c != s.end() && std::strchr("+-=", *c) != NULL)
	{
		hasOperator = true;
		c++;
	}
	while (c != s.end() && std::isspace(*c) != 0)
		c++;
	return hasOperator == true && c == s.end();
}

bool Parser::checkVariableX(const std::string &s)
{
	if (s.empty() == true)
		return false;
	std::string::const_iterator c = s.begin();
	while (c != s.end() && std::isspace(*c) != 0)
		c++;
	bool hasX = false;
	if (c != s.end() && *c == 'X')
	{
		hasX = true;
		c++;
	}
	bool hasCaret = false;
	if (c != s.end() && *c == '^')
	{
		hasCaret = true;
		c++;
	}
	bool hasExponent = false;
	while (c != s.end() && std::isspace(*c) == 0)
	{
		hasExponent = true;
		c++;
	}
	while (c != s.end() && std::isspace(*c) != 0)
		c++;
	return hasX == true && hasCaret == true && hasExponent == true && c == s.end();
}

double Parser::getValue(const std::string &s)
{
	double value = 0.0;
	std::stringstream ss(s);
	ss >> value;
	return value;
}

long long int Parser::getDegree(const std::string &s)
{
	if (s.empty() == true)
		return 0;
	long long int degree = 0;
	std::string::const_iterator c = s.begin();
	while (c != s.end() && std::isspace(*c) != 0)
		c++;
	if (c == s.end() || *c != 'X')
		return 0;
	c++;
	if (c == s.end() || *c != '^')
		return 0;
	c++;
	while (c != s.end() && std::isdigit(*c) != 0)
		degree = degree * 10 + *c++ - '0';
	return degree;
}
