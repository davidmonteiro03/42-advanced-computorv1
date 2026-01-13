/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Equation.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:22:47 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/13 11:31:27 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

Equation::Equation(void) : __leftSide(terms_t()),
						   __rightSide(terms_t()) {}

Equation::Equation(const tokens_t &tokens)
{
	double sign = 1;
	bool switchSide = false;
	for (tokens_t::const_iterator t = tokens.begin(); t != tokens.end(); t++)
	{
		terms_t &side = (switchSide == false ? this->__leftSide : this->__rightSide);
		if (Equation::__isOperator(*t) == false)
		{
			tokens_t::const_iterator v = t, next = std::next(t);
			double value = 0;
			std::stringstream vSs(*v);
			vSs >> value;
			if (next == tokens.end())
			{
				if (value != 0)
					side.push_back(Term(0, value * sign));
				sign = 1;
				break;
			}
			if (*next != "*" && *next != "X")
			{
				if (value != 0)
					side.push_back(Term(0, value * sign));
				sign = 1;
				continue;
			}
			if (*next == "*")
				next = std::next(++t);
			next = std::next(++t);
			if (next == tokens.end())
			{
				if (value != 0)
					side.push_back(Term(1, value * sign));
				sign = 1;
				break;
			}
			if (*next != "^")
			{
				if (value != 0)
					side.push_back(Term(1, value * sign));
				sign = 1;
				continue;
			}
			next = std::next(++t);
			long long int degree = 0;
			std::stringstream dSs(*next);
			dSs >> degree;
			if (value != 0)
				side.push_back(Term(degree, value * sign));
			sign = 1;
			++t;
		}
		else if (*t == "X")
		{
			tokens_t::const_iterator next = std::next(t);
			if (next == tokens.end())
			{
				side.push_back(Term(1, sign));
				sign = 1;
				break;
			}
			if (*next != "^")
			{
				side.push_back(Term(1, sign));
				sign = 1;
				continue;
			}
			next = std::next(++t);
			long long int degree = 0;
			std::stringstream dSs(*next);
			dSs >> degree;
			side.push_back(Term(degree, sign));
			sign = 1;
			++t;
		}
		else if (*t == "-")
			sign = -sign;
		else if (*t == "=")
			switchSide = !switchSide;
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

const terms_t &Equation::getLeftSide(void) const { return this->__leftSide; }

const terms_t &Equation::getRightSide(void) const { return this->__rightSide; }

Equation Equation::moveAllToOneSide(void) const
{
	Equation allInOneSide(*this);
	while (allInOneSide.__rightSide.empty() == false)
	{
		Term elementToMove = allInOneSide.__rightSide.front();
		allInOneSide.__leftSide.push_back(Term(elementToMove.getDegree(), -elementToMove.getValue()));
		allInOneSide.__rightSide.erase(allInOneSide.__rightSide.begin());
	}
	return allInOneSide;
}

reduced_t Equation::reduce(void) const
{
	reduced_t reducedForm;
	for (terms_t::const_iterator t = this->__leftSide.begin(); t != this->__leftSide.end(); t++)
		reducedForm[t->getDegree()] += t->getValue();
	for (reduced_t::iterator t = reducedForm.begin(); t != reducedForm.end();)
	{
		if (t->second == 0)
			t = reducedForm.erase(t);
		else
			++t;
	}
	return reducedForm;
}
