/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:19:42 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/25 14:00:50 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

Solver::Solver(void) {}

Solver::Solver(const Solver &) {}

Solver &Solver::operator=(const Solver &) { return *this; }

Solver::~Solver() {}

void Solver::__displayTerm(std::ostream &os,
						   const std::pair<Integer, Real> &p_term,
						   const bool &isFirst)
{
	Real zeroReal, oneReal;
	Integer zeroInt, oneInt;
	std::stringstream ss("1 1");
	ss >> oneReal >> oneInt;
	if (isFirst == true)
	{
		if (p_term.second < zeroReal)
			os << '-';
		if (p_term.first == zeroInt)
			os << (p_term.second >= zeroReal ? p_term.second : -p_term.second);
		else
		{
			if (p_term.second != -oneReal && p_term.second != oneReal)
				os << (p_term.second >= oneReal ? p_term.second : -p_term.second) << " * ";
			os << "X";
			if (p_term.first > oneInt)
				os << "^" << p_term.first;
		}
	}
	else
	{
		os << (p_term.second >= zeroReal ? " + " : " - ");
		if (p_term.first == zeroInt)
			os << (p_term.second >= zeroReal ? p_term.second : -p_term.second);
		else
		{
			if (p_term.second != -oneReal && p_term.second != oneReal)
				os << (p_term.second >= zeroReal ? p_term.second : -p_term.second) << " * ";
			os << "X";
			if (p_term.first > oneInt)
				os << "^" << p_term.first;
		}
	}
}

std::ostream &operator<<(std::ostream &os,
						 const std::map<Integer, Real> &p_reduced)
{
	if (p_reduced.empty() == true)
		return os << "0 = 0";
	Real zero;
	for (std::map<Integer, Real>::const_iterator t = p_reduced.begin(); t != p_reduced.end(); t++)
		Solver::__displayTerm(os, *t, t == p_reduced.begin());
	return os << " = 0";
}

void Solver::solve(const Equation &p_eq)
{
	Integer zero, one, two;
	std::stringstream ss("0 1 2");
	ss >> zero >> one >> two;
	std::map<Integer, Real> reducedForm;
	for (std::vector<Term>::const_iterator t = p_eq.__leftSide.begin(); t != p_eq.__leftSide.end(); t++)
		reducedForm[t->getDegree()] += t->getValue();
	for (std::vector<Term>::const_iterator t = p_eq.__rightSide.begin(); t != p_eq.__rightSide.end(); t++)
		reducedForm[t->getDegree()] -= t->getValue();
	for (std::map<Integer, Real>::iterator it = reducedForm.begin(); it != reducedForm.end();)
	{
		if (it->second == Real())
		{
			reducedForm.erase(it);
			it = reducedForm.begin();
		}
		else
			++it;
	}
	std::cout << "Reduced form: " << reducedForm << std::endl;
	Integer polynomialDegree;
	for (std::map<Integer, Real>::const_iterator t = reducedForm.begin(); t != reducedForm.end(); t++)
		polynomialDegree = std::max(polynomialDegree, t->first);
	if (polynomialDegree == zero)
		return Solver::__solveZeroDegreeEquation(reducedForm[polynomialDegree]);
	std::cout << "Polynomial degree: " << polynomialDegree << std::endl;
	if (polynomialDegree == one)
		return Solver::__solveFirstDegreeEquation(reducedForm[one], reducedForm[zero]);
	if (polynomialDegree == two)
		return Solver::__solveSecondDegreeEquation(reducedForm[two], reducedForm[one], reducedForm[zero]);
	std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
}

void Solver::__solveZeroDegreeEquation(const Real &a) { std::cout << (!a ? "Any real number is a solution." : "No solution.") << std::endl; }

void Solver::__solveFirstDegreeEquation(const Real &a,
										const Real &b)
{
	if (!a)
		return Solver::__solveZeroDegreeEquation(b);
	Real numerator = -b, denominator = a;
	bool isNegative = numerator.__isNegative != denominator.__isNegative;
	Fraction frac(numerator, denominator);
	std::cout << "The solution is: " << std::endl;
	if (!numerator)
		std::cout << "0";
	else
		std::cout << (isNegative == true ? "-" : "") << frac;
	std::cout << std::endl;
}

void Solver::__solveSecondDegreeEquation(const Real &a,
										 const Real &b,
										 const Real &c)
{
	if (!a)
		return Solver::__solveFirstDegreeEquation(b, c);
	Real zero, two, four;
	std::stringstream ss("0 2 4");
	ss >> zero >> two >> four;
	Real disc = b * b - four * a * c;
	if (disc > zero)
	{
		std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
		if (disc.__hasExactSqrt() == true)
		{
			Real discSqrt = disc.__sqrt();
			Real numX1 = -b + discSqrt, numX2 = -b - discSqrt, denX = two * a;
			Fraction x1(numX1, denX), x2(numX2, denX);
			std::cout << (numX1.__isNegative != denX.__isNegative ? "-" : "") << x1 << std::endl;
			std::cout << (numX2.__isNegative != denX.__isNegative ? "-" : "") << x2 << std::endl;
		}
		else
		{
			std::cout << (-b + disc.__sqrt()) / (two * a) << std::endl;
			std::cout << (-b - disc.__sqrt()) / (two * a) << std::endl;
		}
		return;
	}
	if (disc < zero)
	{
		std::cout << "Discriminant is strictly negative, the complex two solutions are:" << std::endl;
		Real tmpDisc(-disc);
		if (tmpDisc.__hasExactSqrt() == true)
		{
			Real realPartNum = -b, realPartDen = two * a;
			bool realPartIsNegative = realPartNum.__isNegative != realPartDen.__isNegative;
			Fraction realPart(realPartNum, realPartDen);

			Real imagPartNum = tmpDisc.__sqrt(), imagPartDen = two * a;
			bool imagPartIsNegative = imagPartNum.__isNegative != imagPartDen.__isNegative;
			Fraction imagPart(imagPartNum, imagPartDen);

			Solver::__displayComplexFractions(realPart, imagPart, realPartIsNegative, imagPartIsNegative, true);
			Solver::__displayComplexFractions(realPart, imagPart, realPartIsNegative, imagPartIsNegative, false);
		}
		else
		{
			Real realPart = -b / (two * a), imagPart = tmpDisc.__sqrt() / (two * a);
			Solver::__displayComplex(realPart, imagPart);
			Solver::__displayComplex(realPart, -imagPart);
		}
		return;
	}
	std::cout << "Discriminant is strictly zero, the solution is:" << std::endl;
	Real numerator = -b, denominator = two * a;
	bool isNegative = numerator.__isNegative != denominator.__isNegative;
	Fraction frac(numerator, denominator);
	if (!numerator)
		std::cout << "0";
	else
		std::cout << (isNegative == true ? "-" : "") << frac;
	std::cout << std::endl;
}

void Solver::__displayComplex(const Real &realPart,
							  const Real &imagPart)
{
	Real zero, one;
	std::stringstream ss("0 1");
	ss >> zero >> one;
	if (realPart == zero && imagPart == zero)
	{
		std::cout << "0" << std::endl;
		return;
	}
	if (realPart == zero)
	{
		if (imagPart == -one)
			std::cout << "-";
		else if (imagPart != one)
			std::cout << imagPart;
		std::cout << "i" << std::endl;
		return;
	}
	if (imagPart == zero)
	{
		std::cout << realPart << std::endl;
		return;
	}
	std::cout << realPart << (imagPart >= zero ? " + " : " - ");
	if (imagPart != one && imagPart != -one)
		std::cout << (imagPart >= zero ? imagPart : -imagPart);
	std::cout << "i" << std::endl;
}

void Solver::__displayComplexFractions(const Fraction &realPart,
									   const Fraction &imagPart,
									   const bool &realPartIsNegative,
									   const bool &imagPartIsNegative,
									   const bool &isOperationNegative)
{
	Integer oneInt;
	std::stringstream ss("1");
	ss >> oneInt;
	if (!realPart.__numerator && !imagPart.__numerator)
		std::cout << "0";
	else if (!realPart.__numerator)
	{
		std::cout << (imagPartIsNegative == isOperationNegative ? "-" : "");
		if (imagPart.__numerator != oneInt)
			std::cout << imagPart.__numerator;
		std::cout << "i";
		if (imagPart.__denominator != oneInt)
			std::cout << "/" << imagPart.__denominator;
	}
	else if (!imagPart.__numerator)
		std::cout << (realPartIsNegative == true ? "-" : "") << realPart;
	else
	{
		std::cout << (realPartIsNegative == true ? "-" : "") << realPart;
		std::cout << (imagPartIsNegative == isOperationNegative ? " - " : " + ");
		if (imagPart.__numerator != oneInt)
			std::cout << imagPart.__numerator;
		std::cout << "i";
		if (imagPart.__denominator != oneInt)
			std::cout << "/" << imagPart.__denominator;
	}
	std::cout << std::endl;
}
