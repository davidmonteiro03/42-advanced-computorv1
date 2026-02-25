/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:45:50 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/25 19:08:44 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

Solver::Solver(void) {}

Solver::Solver(const Solver &) {}

Solver &Solver::operator=(const Solver &) { return *this; }

Solver::~Solver() {}

void Solver::__displayTerm(std::ostream &os,
						   const std::pair<unsigned long long int, long double> &p_term,
						   const bool &isFirst)
{
	if (isFirst == true)
	{
		if (p_term.second < 0.0)
			os << '-';
		if (p_term.first == 0)
			os << (p_term.second >= 0.0 ? p_term.second : -p_term.second);
		else
		{
			if (p_term.second != -1.0 && p_term.second != 1.0)
				os << (p_term.second >= 1.0 ? p_term.second : -p_term.second) << " * ";
			os << "X";
			if (p_term.first > 1)
				os << "^" << p_term.first;
		}
	}
	else
	{
		os << (p_term.second >= 0.0 ? " + " : " - ");
		if (p_term.first == 0)
			os << (p_term.second >= 0.0 ? p_term.second : -p_term.second);
		else
		{
			if (p_term.second != -1.0 && p_term.second != 1.0)
				os << (p_term.second >= 0.0 ? p_term.second : -p_term.second) << " * ";
			os << "X";
			if (p_term.first > 1)
				os << "^" << p_term.first;
		}
	}
}

std::ostream &operator<<(std::ostream &os,
						 const std::map<unsigned long long int, long double> &p_reduced)
{
	if (p_reduced.empty() == true)
		return os << "0 = 0";
	for (std::map<unsigned long long int, long double>::const_iterator t = p_reduced.begin(); t != p_reduced.end(); t++)
		Solver::__displayTerm(os, *t, t == p_reduced.begin());
	return os << " = 0";
}

void Solver::solve(const Equation &p_eq)
{
	std::map<unsigned long long int, long double> reducedForm;
	for (std::vector<Term>::const_iterator t = p_eq.__leftSide.begin(); t != p_eq.__leftSide.end(); t++)
		reducedForm[t->getDegree()] += t->getValue();
	for (std::vector<Term>::const_iterator t = p_eq.__rightSide.begin(); t != p_eq.__rightSide.end(); t++)
		reducedForm[t->getDegree()] -= t->getValue();
	for (std::map<unsigned long long int, long double>::iterator it = reducedForm.begin(); it != reducedForm.end();)
	{
		if (it->second == 0.0)
		{
			reducedForm.erase(it);
			it = reducedForm.begin();
		}
		else
			++it;
	}
	std::cout << "Reduced form: " << reducedForm << std::endl;
	unsigned long long int polynomialDegree = 0;
	for (std::map<unsigned long long int, long double>::const_iterator t = reducedForm.begin(); t != reducedForm.end(); t++)
		polynomialDegree = std::max(polynomialDegree, t->first);
	if (polynomialDegree == 0)
		return Solver::__solveZeroDegreeEquation(reducedForm[polynomialDegree]);
	std::cout << "Polynomial degree: " << polynomialDegree << std::endl;
	if (polynomialDegree == 1)
		return Solver::__solveFirstDegreeEquation(reducedForm[1], reducedForm[0]);
	if (polynomialDegree == 2)
		return Solver::__solveSecondDegreeEquation(reducedForm[2], reducedForm[1], reducedForm[0]);
	std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
}

void Solver::__solveZeroDegreeEquation(const long double &a) { std::cout << (a == 0 ? "Any real number is a solution." : "No solution.") << std::endl; }

void Solver::__solveFirstDegreeEquation(const long double &a,
										const long double &b)
{
	if (a == 0)
		return Solver::__solveZeroDegreeEquation(b);
	std::cout << "The solution is: " << std::endl;
	std::cout << (b == 0.0 ? 0.0 : -b / a) << std::endl;
}

void Solver::__solveSecondDegreeEquation(const long double &a,
										 const long double &b,
										 const long double &c)
{
	if (a == 0.0)
		return Solver::__solveFirstDegreeEquation(b, c);
	long double disc = b * b - 4.0 * a * c;
	if (disc > 0)
	{
		std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
		long double x1 = (-b + Solver::__sqrt(disc)) / (2.0 * a);
		long double x2 = (-b - Solver::__sqrt(disc)) / (2.0 * a);
		if (x1 == 0.0)
			std::cout << 0.0 << std::endl;
		else
			std::cout << x1 << std::endl;
		if (x2 == 0.0)
			std::cout << 0.0 << std::endl;
		else
			std::cout << x2 << std::endl;
		return;
	}
	if (disc < 0.0)
	{
		std::cout << "Discriminant is strictly negative, the two complex solutions are:" << std::endl;
		double realPart = -b / (2.0 * a), imagPart = Solver::__sqrt(-disc) / (2.0 * a);
		Solver::__displayComplex(realPart, imagPart);
		Solver::__displayComplex(realPart, -imagPart);
		return;
	}
	std::cout << "Discriminant is strictly zero, the solution is:" << std::endl;
	std::cout << (b == 0.0 ? 0.0 : -b / (2.0 * a)) << std::endl;
}

long double Solver::__sqrt(const long double &x)
{
	if (x < 0.0)
		return -std::numeric_limits<long double>::quiet_NaN();
	if (x == 0.0 || x == 1.0)
		return x;
	long double approx = x;
	long double next;
	while (true)
	{
		next = 0.5 * (approx + x / approx);
		if (next == approx)
			break;
		approx = next;
	}
	return approx;
}

void Solver::__displayComplex(const long double &realPart,
							  const long double &imagPart)
{
	if (realPart == 0.0 && imagPart == 0.0)
	{
		std::cout << "0" << std::endl;
		return;
	}
	if (realPart == 0.0)
	{
		if (imagPart == -1.0)
			std::cout << "-";
		else if (imagPart != 1.0)
			std::cout << imagPart;
		std::cout << "i" << std::endl;
		return;
	}
	if (imagPart == 0.0)
	{
		std::cout << realPart << std::endl;
		return;
	}
	std::cout << realPart << (imagPart >= 0.0 ? " + " : " - ");
	if (imagPart != 1.0 && imagPart != -1.0)
		std::cout << (imagPart >= 0.0 ? imagPart : -imagPart);
	std::cout << "i" << std::endl;
}
