/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Equation.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:12:16 by dcaetano          #+#    #+#             */
/*   Updated: 2026/03/02 09:18:50 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

Equation::Equation(void) : __leftSide(),
						   __rightSide() {}

Equation::Equation(const std::string &expr)
{
	std::vector<std::string> args = Parser::split(expr);
	long double sign = 1.0L;
	bool sideFlag = false;
	for (std::vector<std::string>::iterator a = args.begin(); a != args.end(); a++)
	{
		std::string valueStr = *a;
		if (++a == args.end())
			break;
		if (Parser::checkAsterisk(*a) == false || ++a == args.end())
			break;
		std::string variableXStr = *a;
		if (Parser::checkVariableX(*a) == false)
			break;
		std::vector<Term> &side = sideFlag == false ? this->__leftSide : this->__rightSide;
		long double value = Parser::getValue(valueStr) * sign;
		unsigned long long int degree = Parser::getDegree(variableXStr);
		side.push_back(Term(value, degree));
		sign = 1.0L;
		if (++a == args.end())
			break;
		if (Parser::checkOperator(*a) == false)
			break;
		if (*a == "-")
			sign = -1.0L;
		else if (*a == "=")
			sideFlag = !sideFlag;
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
