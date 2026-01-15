/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:54:03 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/15 14:52:31 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

Computor::Computor(void) {}

Computor::Computor(const Computor &) {}

Computor &Computor::operator=(const Computor &) { return *this; }

Computor::~Computor() {}

double Computor::__sqrt(const double &x)
{
	if (x < 0.0)
		return -std::numeric_limits<double>::quiet_NaN();
	if (x == 0.0 || x == 1.0)
		return x;
	double approx = x;
	double next;
	do
	{
		next = 0.5 * (approx + x / approx);
		if (next == approx)
			break;
		approx = next;
	} while (true);
	return approx;
}

void Computor::__displayComplex(const double &a,
								const double &b)
{
	if (a == 0 && b == 0)
	{
		std::cout << "0" << std::endl;
		return;
	}
	if (a == 0)
	{
		if (b == -1)
			std::cout << "-";
		else if (b != 1)
			std::cout << b;
		std::cout << "i" << std::endl;
		return;
	}
	if (b == 0)
	{
		std::cout << a << std::endl;
		return;
	}
	std::cout << a << (b >= 0 ? " + " : " - ");
	if (b != 1 && b != -1)
		std::cout << (b >= 0 ? b : -b);
	std::cout << "i" << std::endl;
}

bool Computor::__isOperator(const std::string &s)
{
	if (s.empty() != false)
		return false;
	if (s.size() != 1)
		return false;
	return std::strchr("+-*=^X", s[0]) != NULL;
}

Term Computor::__getHighestDegreeTerm(const reduced_t &p)
{
	Term highestDegreeTerm;
	if (p.empty() != false)
		return highestDegreeTerm;
	reduced_t::const_iterator r = p.begin();
	highestDegreeTerm.setDegree(r->first);
	highestDegreeTerm.setValue(r->second);
	for (reduced_t::const_iterator r = p.begin(); r != p.end(); r++)
	{
		if (r->first > highestDegreeTerm.getDegree())
		{
			highestDegreeTerm.setDegree(r->first);
			highestDegreeTerm.setValue(r->second);
		}
	}
	return highestDegreeTerm;
}

void Computor::__displayTerm(const long long int &degree,
							 const double &value,
							 const bool &isFirst)
{
	if (isFirst == true)
	{
		if (value < 0)
			std::cout << '-';
		if (degree == 0)
			std::cout << (value >= 0 ? value : -value);
		else
		{
			if (value != -1 && value != 1)
				std::cout << (value >= 0 ? value : -value) << " * ";
			std::cout << "X";
			if (degree > 1)
				std::cout << "^" << degree;
		}
	}
	else
	{
		std::cout << (value >= 0 ? " + " : " - ");
		if (degree == 0)
			std::cout << (value >= 0 ? value : -value);
		else
		{
			if (value != -1 && value != 1)
				std::cout << (value >= 0 ? value : -value) << " * ";
			std::cout << "X";
			if (degree > 1)
				std::cout << "^" << degree;
		}
	}
}

void Computor::__displayValue(const double &v)
{
	if (v >= 0)
		std::cout << v;
	else
		std::cout << "(" << v << ")";
}

void Computor::__displayTerms(const terms_t &terms)
{
	if (terms.empty() != false)
	{
		std::cout << '0';
		return;
	}
	for (terms_t::const_iterator t = terms.begin(); t != terms.end(); t++)
	{
		if (t == terms.begin())
			Computor::__displayTerm(t->getDegree(), t->getValue(), true);
		else
			Computor::__displayTerm(t->getDegree(), t->getValue(), false);
	}
}

void Computor::__displayReducedForm(const reduced_t &reduced)
{
	if (reduced.empty() != false)
	{
		std::cout << '0';
		return;
	}
	for (reduced_t::const_iterator t = reduced.begin(); t != reduced.end(); t++)
	{
		if (t == reduced.begin())
			Computor::__displayTerm(t->first, t->second, true);
		else
			Computor::__displayTerm(t->first, t->second, false);
	}
}

void Computor::__actualSolve(const reduced_t &reducedForm)
{
	std::cout << "Reduced form: ";
	Computor::__displayReducedForm(reducedForm);
	std::cout << " = 0" << std::endl;
	if (reducedForm.empty())
	{
		std::cout << "Any real number is a solution." << std::endl;
		return;
	}
	Term highestDegreeTerm = Computor::__getHighestDegreeTerm(reducedForm);
	if (highestDegreeTerm.getDegree() == 0)
	{
		std::cout << (highestDegreeTerm.getValue() == 0 ? "Any real number is a solution." : "No solution.") << std::endl;
		return;
	}
	std::cout << "Polynomial degree: " << highestDegreeTerm.getDegree() << std::endl;
	if (highestDegreeTerm.getDegree() == 1)
	{
		Computor::__solveFirstDegreeEquation(reducedForm);
		return;
	}
	if (highestDegreeTerm.getDegree() == 2)
	{
		Computor::__solveSecondDegreeEquation(reducedForm);
		return;
	}
	std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
}

void Computor::__solveFirstDegreeEquation(const reduced_t &eq)
{
	reduced_t tmp(eq);
	double a = tmp[1], b = tmp[0];
	if (a == 0)
	{
		std::cout << (b == 0 ? "Any real number is a solution." : "No solution.") << std::endl;
		return;
	}
	double x = -b / a;
	std::cout << "The solution is:" << std::endl;
	std::cout << x << std::endl;
}

void Computor::__solveSecondDegreeEquation(const reduced_t &reduced)
{
	reduced_t tmp(reduced);
	double a = tmp[2], b = tmp[1], c = tmp[0];
	if (a == 0)
	{
		if (b == 0)
		{
			std::cout << (c == 0 ? "Any real number is a solution." : "No solution.") << std::endl;
			return;
		}
		std::cout << "The solution is:" << std::endl;
		std::cout << -c / b << std::endl;
		return;
	}
	double disc = b * b - 4 * a * c;
	if (disc > 0)
		return __solveSecondDegreeEquationPositiveDiscriminant(a, b, disc);
	if (disc < 0)
		return __solveSecondDegreeEquationNegativeDiscriminant(a, b, disc);
	std::cout << "Discriminant is strictly zero, the solution is:" << std::endl;
	std::cout << (b == 0 ? 0 : -b / (2 * a)) << std::endl;
}

void Computor::__solveSecondDegreeEquationPositiveDiscriminant(const double &a,
															   const double &b,
															   const double &disc)
{
	if (disc <= 0)
		return;
	double x1 = (-b + Computor::__sqrt(disc)) / (2 * a);
	double x2 = (-b - Computor::__sqrt(disc)) / (2 * a);
	std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
	std::cout << std::max(x1, x2) << std::endl;
	std::cout << std::min(x1, x2) << std::endl;
}

void Computor::__solveSecondDegreeEquationNegativeDiscriminant(const double &a,
															   const double &b,
															   const double &disc)
{
	if (disc >= 0)
		return;
	std::cout << "Discriminant is strictly negative, the two complex solutions are:" << std::endl;
	double complexA = -b / (2 * a), complexB = Computor::__sqrt(-disc) / (2 * a);
	Computor::__displayComplex(complexA, complexB);
	Computor::__displayComplex(complexA, -complexB);
}

void Computor::solve(const std::string &expr)
{
	tokens_t tokens = Parser::tokenization(expr);
	Parser::checkSyntax(tokens);
	Parser::checkVocabulary(tokens);
	Equation equation(tokens);
	Equation allInOneSide = equation.moveAllToOneSide();
	reduced_t reducedForm = allInOneSide.reduce();
	Computor::__actualSolve(reducedForm);
}
