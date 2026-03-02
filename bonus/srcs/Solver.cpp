/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:45:50 by dcaetano          #+#    #+#             */
/*   Updated: 2026/03/02 08:52:54 by dcaetano         ###   ########.fr       */
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
		if (p_term.second < 0.0L)
			os << '-';
		if (p_term.first == 0ULL)
			os << (p_term.second >= 0.0L ? p_term.second : -p_term.second);
		else
		{
			if (p_term.second != -1.0L && p_term.second != 1.0L)
				os << (p_term.second >= 1.0L ? p_term.second : -p_term.second) << " * ";
			os << "X";
			if (p_term.first > 1ULL)
				os << "^" << p_term.first;
		}
	}
	else
	{
		os << (p_term.second >= 0.0L ? " + " : " - ");
		if (p_term.first == 0ULL)
			os << (p_term.second >= 0.0L ? p_term.second : -p_term.second);
		else
		{
			if (p_term.second != -1.0L && p_term.second != 1.0L)
				os << (p_term.second >= 0.0L ? p_term.second : -p_term.second) << " * ";
			os << "X";
			if (p_term.first > 1ULL)
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
		if (it->second == 0.0L)
		{
			reducedForm.erase(it);
			it = reducedForm.begin();
		}
		else
			++it;
	}
	std::cout << "Reduced form: " << reducedForm << std::endl;
	unsigned long long int polynomialDegree = 0ULL;
	for (std::map<unsigned long long int, long double>::const_iterator t = reducedForm.begin(); t != reducedForm.end(); t++)
		polynomialDegree = std::max(polynomialDegree, t->first);
	if (polynomialDegree == 0ULL)
		return Solver::__solveZeroDegreeEquation(reducedForm[polynomialDegree]);
	std::cout << "Polynomial degree: " << polynomialDegree << std::endl;
	if (polynomialDegree == 1ULL)
		return Solver::__solveFirstDegreeEquation(reducedForm[1ULL], reducedForm[0ULL]);
	if (polynomialDegree == 2ULL)
		return Solver::__solveSecondDegreeEquation(reducedForm[2ULL], reducedForm[1ULL], reducedForm[0ULL]);
	std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
}

void Solver::__solveZeroDegreeEquation(const long double &a) { std::cout << (a == 0.0L ? "Any real number is a solution." : "No solution.") << std::endl; }

void Solver::__solveFirstDegreeEquation(const long double &a,
										const long double &b)
{
	if (a == 0.0L)
		return Solver::__solveZeroDegreeEquation(b);
	std::cout << "The solution is: " << std::endl;
	long double x = -b / a;
	(x == 0.0L ? x = 0.0L : true);
	std::cout << x << std::endl;
}

void Solver::__solveSecondDegreeEquation(const long double &a,
										 const long double &b,
										 const long double &c)
{
	if (a == 0.0L)
		return Solver::__solveFirstDegreeEquation(b, c);
	long double disc = b * b - 4.0L * a * c;
	if (disc > 0.0L)
	{
		std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
		long double x1 = (-b + Solver::__sqrt(disc)) / (2.0L * a);
		long double x2 = (-b - Solver::__sqrt(disc)) / (2.0L * a);
		(x1 == 0.0L ? x1 = 0.0L : true);
		(x2 == 0.0L ? x2 = 0.0L : true);
		std::cout << x1 << std::endl;
		std::cout << x2 << std::endl;
		return;
	}
	if (disc < 0.0L)
	{
		std::cout << "Discriminant is strictly negative, the two complex solutions are:" << std::endl;
		long double realPart = -b / (2.0L * a);
		long double imagPart = Solver::__sqrt(-disc) / (2.0L * a);
		(realPart == 0.0L ? realPart = 0.0L : true);
		(imagPart == 0.0L ? imagPart = 0.0L : true);
		Solver::__displayComplex(realPart, imagPart);
		Solver::__displayComplex(realPart, -imagPart);
		return;
	}
	std::cout << "Discriminant is strictly zero, the solution is:" << std::endl;
	long double x = -b / (2.0L * a);
	(x == 0.0L ? x = 0.0L : true);
	std::cout << x << std::endl;
}

long double Solver::__sqrt(const long double &x)
{
	if (x < 0.0L)
		return -std::numeric_limits<long double>::quiet_NaN();
	if (x == 0.0L || x == 1.0L)
		return x;
	long double approx = x;
	long double next;
	while (true)
	{
		next = 0.5L * (approx + x / approx);
		if (next == approx)
			break;
		approx = next;
	}
	return approx;
}

void Solver::__displayComplex(const long double &realPart,
							  const long double &imagPart)
{
	if (realPart == 0.0L && imagPart == 0.0L)
	{
		std::cout << "0" << std::endl;
		return;
	}
	if (realPart == 0.0L)
	{
		if (imagPart == -1.0L)
			std::cout << "-";
		else if (imagPart != 1.0L)
			std::cout << imagPart;
		std::cout << "i" << std::endl;
		return;
	}
	if (imagPart == 0.0L)
	{
		std::cout << realPart << std::endl;
		return;
	}
	std::cout << realPart << (imagPart >= 0.0L ? " + " : " - ");
	if (imagPart != 1.0L && imagPart != -1.0L)
		std::cout << (imagPart >= 0.0L ? imagPart : -imagPart);
	std::cout << "i" << std::endl;
}
