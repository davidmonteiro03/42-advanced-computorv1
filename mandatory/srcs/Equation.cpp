/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Equation.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:39:33 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/13 10:57:12 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

Equation::Equation(void) : __leftSide(terms_t()),
						   __rightSide(terms_t()) {}

Equation::Equation(const args_t &args)
{
	bool sideOfEquation = false;
	double signal = 1;
	for (args_t::const_iterator a = args.begin(); a != args.end();)
	{
		std::stringstream ssValue(*a);
		double value = 0;
		ssValue >> value;
		if (++a == args.end())
			break;
		if (++a == args.end())
			break;
		if (a->size() >= 3)
		{
			std::stringstream ssDegree(a->substr(2, a->size() - 2));
			long long int degree = 0;
			ssDegree >> degree;
			terms_t &side = (sideOfEquation == false ? this->__leftSide : this->__rightSide);
			side.push_back(Term(degree, value * signal));
		}
		if (++a == args.end())
			break;
		std::string op(*a);
		if (op == "+")
			signal = 1;
		else if (op == "-")
			signal = -1;
		else if (op == "=")
		{
			sideOfEquation = !sideOfEquation;
			signal = 1;
		}
		if (++a == args.end())
			break;
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

reduced_t Equation::reduce(void) const
{
	terms_t l(this->__leftSide), r(this->__rightSide);
	while (r.empty() == false)
	{
		Term term = r.front();
		l.push_back(Term(term.getDegree(), -term.getValue()));
		r.erase(r.begin());
	}
	reduced_t reduced;
	for (terms_t::iterator t = l.begin(); t != l.end(); t++)
		reduced[t->getDegree()] += t->getValue();
	return reduced;
}
