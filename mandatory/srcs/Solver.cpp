/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:45:50 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/24 13:06:26 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

Solver::Solver(void) {}

Solver::Solver(const Solver &) {}

Solver &Solver::operator=(const Solver &) { return *this; }

Solver::~Solver() {}

std::ostream &operator<<(std::ostream &os,
						 const std::map<long long int, double> &p_reduced)
{
	if (p_reduced.empty() == true)
		return os << "0 = 0";
	for (std::map<long long int, double>::const_iterator t = p_reduced.begin(); t != p_reduced.end(); t++)
	{
		if (t != p_reduced.begin())
		{
			os << (t->second >= 0 ? " + " : " - ");
			os << (t->second >= 0 ? t->second : -t->second);
			os << " * X^" << t->first;
		}
		else
			os << t->second << " * X^" << t->first;
	}
	return os << " = 0";
}

void Solver::solve(const Equation &p_eq)
{
	std::map<long long int, double> reducedForm;
	for (std::vector<Term>::const_iterator t = p_eq.__leftSide.begin(); t != p_eq.__leftSide.end(); t++)
		reducedForm[t->getDegree()] += t->getValue();
	for (std::vector<Term>::const_iterator t = p_eq.__rightSide.begin(); t != p_eq.__rightSide.end(); t++)
		reducedForm[t->getDegree()] -= t->getValue();
	std::cout << "Reduced form: " << reducedForm << std::endl;
	long long int polynomialDegree = 0;
	for (std::map<long long int, double>::const_iterator t = reducedForm.begin(); t != reducedForm.end(); t++)
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

void Solver::__solveZeroDegreeEquation(const double &a) { std::cout << (a == 0 ? "Any real number is a solution." : "No solution.") << std::endl; }

void Solver::__solveFirstDegreeEquation(const double &a,
										const double &b)
{
	if (a == 0)
		return Solver::__solveZeroDegreeEquation(b);
	std::cout << "The solution is: " << std::endl;
	std::cout << (b == 0.0 ? 0.0 : -b / a) << std::endl;
}

void Solver::__solveSecondDegreeEquation(const double &a,
										 const double &b,
										 const double &c)
{
	if (a == 0.0)
		return Solver::__solveFirstDegreeEquation(b, c);
	double disc = b * b - 4.0 * a * c;
	if (disc > 0)
	{
		std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
		std::cout << (-b + Solver::__sqrt(disc)) / (2.0 * a) << std::endl;
		std::cout << (-b - Solver::__sqrt(disc)) / (2.0 * a) << std::endl;
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

double Solver::__sqrt(const double &x)
{
	if (x < 0.0)
		return -std::numeric_limits<double>::quiet_NaN();
	if (x == 0.0 || x == 1.0)
		return x;
	double approx = x;
	double next;
	while (true)
	{
		next = 0.5 * (approx + x / approx);
		if (next == approx)
			break;
		approx = next;
	}
	return approx;
}

void Solver::__displayComplex(const double &realPart,
							  const double &imagPart)
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
