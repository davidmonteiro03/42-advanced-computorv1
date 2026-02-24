/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Equation.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:50:59 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/24 11:23:59 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

Equation::Equation(void) : __leftSide(),
						   __rightSide() {}

Equation::Equation(const std::list<std::string> &tokens) : __leftSide(),
														   __rightSide()
{
	if (tokens.empty())
		return;
	bool sideFlag = false;
	for (std::list<std::string>::const_iterator t = tokens.begin(); t != tokens.end();)
	{
		if (*t == "=")
		{
			sideFlag = !sideFlag;
			t++;
			continue;
		}
		std::string valueStr = "1", degreeStr = "0";
		bool isValueNegative = false, isDegreeNegative = false;
		while (t != tokens.end() && (*t == "+" || *t == "-"))
			if (*t++ == "-")
				isValueNegative = !isValueNegative;
		if (t != tokens.end() && Equation::__isOperator(*t) == false)
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
				if (t != tokens.end() && Equation::__isOperator(*t) == false)
					degreeStr = *t++;
			}
		}
		std::stringstream ss;
		ss << (isValueNegative == true ? "-" : "") << valueStr << " ";
		ss << (isDegreeNegative == true ? "-" : "") << degreeStr;
		Real value;
		Integer degree;
		ss >> value >> degree;
		std::vector<Term> &side = sideFlag == false ? this->__leftSide : this->__rightSide;
		side.push_back(Term(value, degree));
	}
}

Equation::Equation(const Equation &copy) : __leftSide(copy.__leftSide),
										   __rightSide(copy.__rightSide) {}

Equation &Equation::operator=(const Equation &other)
{
	if (this != &other)
	{
		this->__leftSide = other.__leftSide;
		this->__rightSide = other.__rightSide;
	}
	return *this;
}

Equation::~Equation() {}

bool Equation::__isOperator(const std::string &s)
{
	if (s.empty() != false)
		return false;
	if (s.size() != 1)
		return false;
	return std::strchr("+-*=^X", s[0]) != NULL;
}
