/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Equation.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:12:16 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/24 11:24:12 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

Equation::Equation(void) : __leftSide(),
						   __rightSide() {}

Equation::Equation(const std::string &expr)
{
	std::vector<std::string> args = Parser::split(expr);
	double sign = 1.0;
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
		double value = Parser::getValue(valueStr) * sign;
		long long int degree = Parser::getDegree(variableXStr);
		side.push_back(Term(value, degree));
		if (++a == args.end())
			break;
		if (Parser::checkOperator(*a) == false)
			break;
		if (*a == "-")
			sign = -1.0;
		else if (*a == "=")
		{
			sign = 1.0;
			sideFlag = !sideFlag;
		}
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
