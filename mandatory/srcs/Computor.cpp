/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:54:03 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/09 18:05:37 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

static double ft_sqrt(double x)
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

Computor::Computor(void) {}

Computor::Computor(const Computor &) {}

Computor &Computor::operator=(const Computor &) { return *this; }

Computor::~Computor() {}

Term Computor::__strtoterm(const std::string &str)
{
	Term term;
	if (str.empty() != false)
		return term;
	std::size_t i = 0;
	for (; i < str.size() && std::isspace(str[i]) != false; i++)
		;
	std::size_t startV = i;
	for (; i < str.size() && std::isdigit(str[i]) != false; i++)
		;
	if (i < str.size() && str[i] == '.')
	{
		i++;
		for (; i < str.size() && std::isdigit(str[i]) != false; i++)
			;
	}
	std::size_t endV = i;
	for (; i < str.size() && std::isspace(str[i]) != false; i++)
		;
	if (i < str.size() && str[i] == '*')
		i++;
	for (; i < str.size() && std::isspace(str[i]) != false; i++)
		;
	if (i < str.size() && str[i] == 'X')
		i++;
	if (i < str.size() && str[i] == '^')
		i++;
	std::size_t startD = i;
	for (; i < str.size() && std::isdigit(str[i]) != false; i++)
		;
	std::size_t endD = i;
	for (; i < str.size() && std::isspace(str[i]) != false; i++)
		;
	if (i != str.size())
		return term;

	double value = 0, degree = 0;
	std::string valueStr = str.substr(startV, endV - startV), degreeStr = str.substr(startD, endD - startD);
	std::stringstream valueSs(valueStr), degreeSs(degreeStr);
	if (valueSs >> value && degreeSs >> degree)
	{
		term.setValue(value);
		term.setDegree(degree);
	}
	return term;
}

std::vector<Token> Computor::__parse(const std::string &expr)
{
	std::vector<Token> tokens;
	for (std::size_t i = 0; i < expr.size();)
	{
		if (std::strchr("+-=", expr[i]) != NULL)
		{
			switch (expr[i])
			{
			case '+':
				tokens.push_back(Token("+", PLUS));
				break;
			case '-':
				tokens.push_back(Token("-", MINUS));
				break;
			case '=':
				tokens.push_back(Token("=", EQUAL));
				break;
			default:
				break;
			}
			i++;
			continue;
		}
		for (; i < expr.size() && std::isspace(expr[i]) != false; i++)
			;
		std::size_t start = i;
		for (; i < expr.size() && std::strchr("+-=", expr[i]) == NULL; i++)
			;
		std::size_t end = i;
		std::string token = expr.substr(start, end - start);
		if (token.empty() == false)
			tokens.push_back(Token(token, TERM));
		for (; i < expr.size() && std::isspace(expr[i]) != false; i++)
			;
	}
	return tokens;
}

std::map<double, double> Computor::__reduce(const std::vector<Token> &tokens)
{
	std::map<double, double> vars;
	double signal = 1;
	bool switchSignal = false;
	for (std::vector<Token>::const_iterator t = tokens.begin(); t != tokens.end(); t++)
	{
		if (t->getType() == TERM)
		{
			Term term = Computor::__strtoterm(t->getToken());
			vars[term.getDegree()] += term.getValue() * signal;
		}
		else if (t->getType() == EQUAL)
		{
			switchSignal = !switchSignal;
			if (switchSignal == true)
				signal = -1;
			else
				signal = 1;
		}
		else if (t->getType() == PLUS)
		{
			if (switchSignal == true)
				signal = -1;
			else
				signal = 1;
		}
		else if (t->getType() == MINUS)
		{
			if (switchSignal == true)
				signal = 1;
			else
				signal = -1;
		}
	}
	return vars;
}

std::pair<double, double> Computor::__getHighestDegreeTerm(const std::map<double, double> &vars)
{
	std::pair<double, double> highestDegreeTerm;
	if (vars.size() < 1)
		return highestDegreeTerm;
	highestDegreeTerm = *vars.begin();
	for (std::map<double, double>::const_iterator v = vars.begin(); v != vars.end(); v++)
		if (v->first > highestDegreeTerm.first)
			highestDegreeTerm = *v;
	return highestDegreeTerm;
}

void Computor::__showReducedForm(const std::map<double, double> &vars)
{
	std::cout << "Reduced form: ";
	for (std::map<double, double>::const_iterator v = vars.begin(); v != vars.end(); v++)
	{
		if (v == vars.begin())
		{
			std::cout << v->second << " * X^" << v->first;
			continue;
		}
		std::cout << (v->second >= 0 ? " + " : " - ");
		std::cout << (v->second >= 0 ? v->second : -v->second);
		std::cout << " * X^" << v->first;
	}
	std::cout << " = 0" << std::endl;
}

void Computor::check(const std::string &expr)
{
	if (expr.empty() != false)
		throw std::invalid_argument("empty expression");
	for (std::string::const_iterator c = expr.begin(); c != expr.end(); c++)
		if (std::strchr("X0123456789+-*^=.", *c) == NULL && std::isspace(*c) == false)
			throw std::invalid_argument("expression has invalid characters");
}

void Computor::solve(const std::string &expr)
{
	try
	{
		Computor::check(expr);
	}
	catch (const std::exception &e)
	{
		throw;
	}

	std::vector<Token> tokens = Computor::__parse(expr);
	if (tokens.size() < 1)
		throw std::invalid_argument("empty expression");

	std::map<double, double> vars = Computor::__reduce(tokens);

	Computor::__showReducedForm(vars);

	std::pair<double, double> highestDegreeTerm = Computor::__getHighestDegreeTerm(vars);
	if (highestDegreeTerm.first == 0)
	{
		std::cout << (highestDegreeTerm.second == 0 ? "Any real number is a solution." : "No solution.") << std::endl;
		return;
	}
	std::cout << "Polynomial degree: " << highestDegreeTerm.first << std::endl;
	if (highestDegreeTerm.first > 2)
	{
		std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
		return;
	}
	if (highestDegreeTerm.first == 1)
	{
		double solution = -vars[0] / vars[1];
		std::cout << "The solution is:" << std::endl;
		std::cout << solution << std::endl;
	}
	else if (highestDegreeTerm.first == 2)
	{
		double a = vars[2], b = vars[1], c = vars[0];
		double discriminant = b * b - 4 * a * c;
		if (discriminant > 0)
		{
			double solution1 = (-b + ft_sqrt(discriminant)) / (2 * a);
			double solution2 = (-b - ft_sqrt(discriminant)) / (2 * a);
			std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
			std::cout << std::max(solution1, solution2) << std::endl;
			std::cout << std::min(solution1, solution2) << std::endl;
		}
		else if (discriminant == 0) // 2 * X^2 + 4 * X^1 + 2 * X^0 = 0
		{
			std::cout << "The solution is:" << std::endl;
			std::cout << -b / (2 * a) << std::endl;
		}
		else if (discriminant < 0)
		{
			std::cout << "Complex numbers 💀" << std::endl;
		}
	}
}
