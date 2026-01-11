/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:54:03 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/11 21:44:35 by dcaetano         ###   ########.fr       */
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

term_t Computor::__getHighestDegreeTerm(const reduced_t &reduced)
{
	term_t highestDegreeTerm;
	if (reduced.empty() != false)
		return highestDegreeTerm;
	highestDegreeTerm = *reduced.begin();
	for (reduced_t::const_iterator r = reduced.begin(); r != reduced.end(); r++)
		if (r->first > highestDegreeTerm.first)
			highestDegreeTerm = *r;
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

equation_t Computor::__equation(const args_t &args)
{
	equation_t eq;
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
			double degree = 0;
			ssDegree >> degree;
			terms_t &side = (sideOfEquation == false ? eq.first : eq.second);
			side.push_back(std::make_pair(degree, value * signal));
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
	return eq;
}

reduced_t Computor::__reduce(const equation_t &eq)
{
	equation_t tmp(eq);
	while (tmp.second.empty() == false)
	{
		term_t term = tmp.second.front();
		tmp.first.push_back(std::make_pair(term.first, -term.second));
		tmp.second.erase(tmp.second.begin());
	}
	reduced_t reduced;
	for (terms_t::iterator t = tmp.first.begin(); t != tmp.first.end(); t++)
		reduced[t->first] += t->second;
	return reduced;
}

void Computor::__solveFirstDegreeEquation(const reduced_t &reduced)
{
	reduced_t tmp(reduced);
	double a = tmp[1], b = tmp[0];
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
		std::cout << "The solution is:" << std::endl;
		std::cout << -c / b << std::endl;
		return;
	}
	double disc = b * b - 4 * a * c;
	if (disc > 0)
		return __solveSecondDegreeEquationPositiveDiscriminant(a, b, disc);
	if (disc < 0)
		return __solveSecondDegreeEquationNegativeDiscriminant(a, b, disc);
	std::cout << "The solution is:" << std::endl;
	std::cout << -b / (2 * a) << std::endl;
}

void Computor::__solveSecondDegreeEquationPositiveDiscriminant(const double &a,
															   const double &b,
															   const double &disc)
{
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
	std::cout << "Discriminant is strictly negative, the two complex solutions are:" << std::endl;
	std::cout << -b << "/" << 2 * a << " + " << Computor::__sqrt(-disc) << "i/" << 2 * a << std::endl;
	std::cout << -b << "/" << 2 * a << " - " << Computor::__sqrt(-disc) << "i/" << 2 * a << std::endl;
}

void Computor::solve(const std::string &expr)
{
	args_t args = Computor::__split(expr);
	equation_t eq = Computor::__equation(args);
	reduced_t reduced = Computor::__reduce(eq);
	Computor::__showReducedForm(reduced);
	term_t highestDegreeTerm = Computor::__getHighestDegreeTerm(reduced);
	if (highestDegreeTerm.first < 1)
	{
		std::cout << (highestDegreeTerm.second == 0 ? "Any real number is a solution." : "No solution.") << std::endl;
		return;
	}
	std::cout << "Polynomial degree: " << highestDegreeTerm.first << std::endl;
	if (highestDegreeTerm.first == 1)
		return Computor::__solveFirstDegreeEquation(reduced);
	if (highestDegreeTerm.first == 2)
		return Computor::__solveSecondDegreeEquation(reduced);
	std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
}
