/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:54:03 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/20 20:09:35 by dcaetano         ###   ########.fr       */
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

void Computor::__showReducedForm(const reduced_t &reduced)
{
	std::cout << "Reduced form: ";
	for (reduced_t::const_iterator r = reduced.begin(); r != reduced.end(); r++)
	{
		if (r == reduced.begin())
		{
			std::cout << r->second << " * X^" << r->first;
			continue;
		}
		std::cout << (r->second >= 0 ? " + " : " - ");
		std::cout << (r->second >= 0 ? r->second : -r->second);
		std::cout << " * X^" << r->first;
	}
	std::cout << " = 0" << std::endl;
}

Term Computor::__getHighestDegreeTerm(const reduced_t &reduced)
{
	Term highestDegreeTerm;
	if (reduced.empty() != false)
		return highestDegreeTerm;
	reduced_t::const_iterator r = reduced.begin();
	highestDegreeTerm.setDegree(r->first);
	highestDegreeTerm.setValue(r->second);
	for (reduced_t::const_iterator r = reduced.begin(); r != reduced.end(); r++)
	{
		if (r->first > highestDegreeTerm.getDegree())
		{
			highestDegreeTerm.setDegree(r->first);
			highestDegreeTerm.setValue(r->second);
		}
	}
	return highestDegreeTerm;
}

args_t Computor::__split(const std::string &s)
{
	args_t words;
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

void Computor::__solveFirstDegreeEquation(const reduced_t &reduced)
{
	reduced_t tmp(reduced);
	double a = tmp[1], b = tmp[0];
	if (a == 0)
	{
		std::cout << (b == 0 ? "Any real number is a solution." : "No solution.") << std::endl;
		return;
	}
	double x = (b == 0 ? 0 : -b / a);
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
		std::cout << "Discriminant is zero, the solution is:" << std::endl;
		std::cout << (c != 0 ? -c / b : 0) << std::endl;
		return;
	}
	double disc = b * b - 4 * a * c;
	if (disc > 0)
		return __solveSecondDegreeEquationPositiveDiscriminant(a, b, disc);
	if (disc < 0)
		return __solveSecondDegreeEquationNegativeDiscriminant(a, b, disc);
	std::cout << "Discriminant is zero, the solution is:" << std::endl;
	std::cout << (b == 0 ? 0 : -b / (2 * a)) << std::endl;
}

void Computor::__solveSecondDegreeEquationPositiveDiscriminant(const double &a,
															   const double &b,
															   const double &disc)
{
	if (disc <= 0)
		return;
	std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
	double x1 = (-b + Computor::__sqrt(disc)) / (2 * a);
	double x2 = (-b - Computor::__sqrt(disc)) / (2 * a);
	std::cout << (std::max(x1, x2) != 0 ? std::max(x1, x2) : 0) << std::endl;
	std::cout << (std::min(x1, x2) != 0 ? std::min(x1, x2) : 0) << std::endl;
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
	args_t args = Computor::__split(expr);
	Equation eq(args);
	reduced_t reduced = eq.reduce();
	Computor::__showReducedForm(reduced);
	Term highestDegreeTerm = Computor::__getHighestDegreeTerm(reduced);
	if (highestDegreeTerm.getDegree() < 1)
	{
		std::cout << (highestDegreeTerm.getValue() == 0 ? "Any real number is a solution." : "No solution.") << std::endl;
		return;
	}
	std::cout << "Polynomial degree: " << highestDegreeTerm.getDegree() << std::endl;
	if (highestDegreeTerm.getDegree() == 1)
		return Computor::__solveFirstDegreeEquation(reduced);
	if (highestDegreeTerm.getDegree() == 2)
		return Computor::__solveSecondDegreeEquation(reduced);
	std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
}
