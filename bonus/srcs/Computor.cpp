/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:54:03 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/12 17:54:58 by dcaetano         ###   ########.fr       */
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

bool Computor::__isOperator(const std::string &s)
{
	if (s.empty() != false)
		return false;
	if (s.size() != 1)
		return false;
	return std::strchr("+-*=^X", s[0]) != NULL;
}

void Computor::__checkSyntaxNumbers(const tokens_t::const_iterator &curr,
									const tokens_t::const_iterator &end)
{
	tokens_t::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (prev != end && (*prev == "*" || *prev == "X"))
		throw std::invalid_argument("numbers can't contain '" + *prev + "' before it");
	if (prev != end && Computor::__isOperator(*prev) == false)
		throw std::invalid_argument("numbers can't contain other numbers before it");
	if (next != end && *next == "^")
		throw std::invalid_argument("numbers can't contain '" + *next + "' after it");
	if (next != end && Computor::__isOperator(*next) == false)
		throw std::invalid_argument("numbers can't contain other numbers after it");
}

void Computor::__checkSyntaxPlusMinus(const tokens_t::const_iterator &curr,
									  const tokens_t::const_iterator &end)
{
	tokens_t::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (next == end)
		throw std::invalid_argument("'" + *curr + "' sign must contain something after it");
	if (prev != end && (*prev == "*" || *prev == "^"))
		throw std::invalid_argument("'" + *curr + "' sign can't contain '" + *prev + "' before it");
	if (next != end && (*next == "*" || *next == "=" || *next == "^"))
		throw std::invalid_argument("'" + *curr + "' sign can't contain '" + *next + "' after it");
	if (prev != end && next != end && ((*prev == "+" || *prev == "-") && (*next == "+" || *next == "-")))
		throw std::invalid_argument("expression can't have three '+'/'-' consecutive signs");
}

void Computor::__checkSyntaxEquals(const tokens_t::const_iterator &curr,
								   const tokens_t::const_iterator &end)
{
	tokens_t::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (prev == end)
		throw std::invalid_argument("'" + *curr + "' sign must contain something before it");
	if (next == end)
		throw std::invalid_argument("'" + *curr + "' sign must contain something after it");
	if (prev != end && Computor::__isOperator(*prev) != false && *prev != "X")
		throw std::invalid_argument("'" + *curr + "' sign can't contain '" + *prev + "' before it");
	if (next != end && (*next == "*" || *next == "=" || *next == "^"))
		throw std::invalid_argument("'" + *curr + "' sign can't contain '" + *next + "' after it");
}

void Computor::__checkSyntaxAsterik(const tokens_t::const_iterator &curr,
									const tokens_t::const_iterator &end)
{
	tokens_t::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (prev == end)
		throw std::invalid_argument("'" + *curr + "' sign must contain something before it");
	if (next == end)
		throw std::invalid_argument("'" + *curr + "' sign must contain something after it");
	if (prev != end && Computor::__isOperator(*prev) != false)
		throw std::invalid_argument("'" + *curr + "' sign must contain numbers before it");
	if (next != end && *next != "X")
		throw std::invalid_argument("'" + *curr + "' sign must contain an 'X' after it");
}

void Computor::__checkSyntaxCaret(const tokens_t::const_iterator &curr,
								  const tokens_t::const_iterator &end)
{
	tokens_t::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (prev == end)
		throw std::invalid_argument("'" + *curr + "' sign must contain something before it");
	if (next == end)
		throw std::invalid_argument("'" + *curr + "' sign must contain something after it");
	if (prev != end && *prev != "X")
		throw std::invalid_argument("'" + *curr + "' sign must contain an 'X' before it");
	if (next != end && Computor::__isOperator(*next) != false)
		throw std::invalid_argument("'" + *curr + "' sign must contain numbers after it");
}

void Computor::__checkSyntaxVariableX(const tokens_t::const_iterator &curr,
									  const tokens_t::const_iterator &end)
{
	tokens_t::const_iterator prev = std::prev(curr), next = std::next(curr);
	if (prev != end && (*prev == "^" || *prev == "X"))
		throw std::invalid_argument("'" + *curr + "' sign must contain an '" + *prev + "' before it");
	if (next != end && (*next == "*" || *next == "X"))
		throw std::invalid_argument("'" + *curr + "' sign must contain an '" + *next + "' after it");
}

void Computor::__checkSyntax(const tokens_t &tokens)
{
	if (tokens.empty() != false)
		return;
	for (tokens_t::const_iterator t = tokens.begin(); t != tokens.end(); t++)
	{
		if (Computor::__isOperator(*t) == false)
		{
			Computor::__checkSyntaxNumbers(t, tokens.end());
			continue;
		}
		if (*t == "+" || *t == "-")
		{
			Computor::__checkSyntaxPlusMinus(t, tokens.end());
			continue;
		}
		if (*t == "=")
		{
			Computor::__checkSyntaxEquals(t, tokens.end());
			continue;
		}
		if (*t == "*")
		{
			Computor::__checkSyntaxAsterik(t, tokens.end());
			continue;
		}
		if (*t == "^")
		{
			Computor::__checkSyntaxCaret(t, tokens.end());
			continue;
		}
		if (*t == "X")
		{
			Computor::__checkSyntaxVariableX(t, tokens.end());
			continue;
		}
	}
}

void Computor::__checkVocabularyEquals(const tokens_t &tokens)
{
	bool hasEquals = false;
	for (tokens_t::const_iterator t = tokens.begin(); t != tokens.end(); t++)
	{
		if (*t == "=")
		{
			if (hasEquals == true)
				throw std::invalid_argument("expression must have only one '=' sign");
			hasEquals = true;
		}
	}
	if (hasEquals == false)
		throw std::invalid_argument("expression must have a '=' sign");
}

void Computor::__checkVocabularyNumbers(const tokens_t &tokens)
{
	for (tokens_t::const_iterator t = tokens.begin(); t != tokens.end(); t++)
	{
		if (Computor::__isOperator(*t) == false)
		{
			tokens_t::const_iterator prev = std::prev(t);
			if (prev != tokens.end() && *prev == "^")
			{
				double dDouble = 0;
				long long int dInt = 0;
				std::stringstream ssDouble(*t), ssInt(*t);
				ssDouble >> dDouble;
				ssInt >> dInt;
				double check = static_cast<double>(dInt);
				if (dDouble != check)
					throw std::invalid_argument("'X' exponents must be integer");
			}
		}
	}
}

void Computor::__checkVocabulary(const tokens_t &tokens)
{
	if (tokens.empty() != false)
		throw std::invalid_argument("expression must not be empty");
	Computor::__checkVocabularyNumbers(tokens);
	Computor::__checkVocabularyEquals(tokens);
}

tokens_t Computor::__tokenization(const std::string &expr)
{
	for (std::string::const_iterator c = expr.begin(); c != expr.end(); c++)
		if (std::strchr("0123456789+-*=.X^", *c) == NULL && std::isspace(*c) == false)
			throw std::invalid_argument("expression contains invalid characters");
	tokens_t tokens;
	for (std::string::const_iterator c = expr.begin(); c != expr.end();)
	{
		if (std::isspace(*c) != false)
		{
			c++;
			continue;
		}
		if (std::strchr("+-*=^X", *c) != NULL)
		{
			tokens.push_back(expr.substr(std::distance(expr.begin(), c++), 1));
			continue;
		}
		std::string::const_iterator start = c;
		for (; c != expr.end() && std::isspace(*c) == false && std::strchr("+-*=^X", *c) == NULL; c++)
			;
		std::string::const_iterator end = c;
		tokens.push_back(expr.substr(std::distance(expr.begin(), start), std::distance(start, end)));
	}
	return tokens;
}

equation_t Computor::__parse(const tokens_t &tokens)
{
	equation_t equation;
	double sign = 1;
	bool switchSide = false;
	for (tokens_t::const_iterator t = tokens.begin(); t != tokens.end(); t++)
	{
		terms_t &side = (switchSide == false ? equation.first : equation.second);
		if (Computor::__isOperator(*t) == false)
		{
			tokens_t::const_iterator v = t, next = std::next(t);
			double value = 0;
			std::stringstream vSs(*v);
			vSs >> value;
			if (next == tokens.end())
			{
				if (value != 0)
					side.push_back(std::make_pair(0, value * sign));
				sign = 1;
				break;
			}
			if (*next != "*" && *next != "X")
			{
				if (value != 0)
					side.push_back(std::make_pair(0, value * sign));
				sign = 1;
				continue;
			}
			if (*next == "*")
				next = std::next(++t);
			next = std::next(++t);
			if (next == tokens.end())
			{
				if (value != 0)
					side.push_back(std::make_pair(1, value * sign));
				sign = 1;
				break;
			}
			if (*next != "^")
			{
				if (value != 0)
					side.push_back(std::make_pair(1, value * sign));
				sign = 1;
				continue;
			}
			next = std::next(++t);
			long long int degree = 0;
			std::stringstream dSs(*next);
			dSs >> degree;
			if (value != 0)
				side.push_back(std::make_pair(degree, value * sign));
			sign = 1;
			++t;
		}
		else if (*t == "X")
		{
			tokens_t::const_iterator next = std::next(t);
			if (next == tokens.end())
			{
				side.push_back(std::make_pair(1, sign));
				sign = 1;
				break;
			}
			if (*next != "^")
			{
				side.push_back(std::make_pair(1, sign));
				sign = 1;
				continue;
			}
			next = std::next(++t);
			long long int degree = 0;
			std::stringstream dSs(*next);
			dSs >> degree;
			side.push_back(std::make_pair(degree, sign));
			sign = 1;
			++t;
		}
		else if (*t == "-")
			sign = -sign;
		else if (*t == "=")
			switchSide = !switchSide;
	}
	return equation;
}

equation_t Computor::__moveAllToOneSide(const equation_t &equation)
{
	equation_t allInOneSide(equation);
	while (allInOneSide.second.empty() == false)
	{
		term_t elementToMove = allInOneSide.second.front();
		allInOneSide.first.push_back(std::make_pair(elementToMove.first, -elementToMove.second));
		allInOneSide.second.erase(allInOneSide.second.begin());
	}
	return allInOneSide;
}

reduced_t Computor::__reduce(const equation_t &allInOneSide)
{
	reduced_t reducedForm;
	for (terms_t::const_iterator t = allInOneSide.first.begin(); t != allInOneSide.first.end(); t++)
		reducedForm[t->first] += t->second;
	for (reduced_t::iterator t = reducedForm.begin(); t != reducedForm.end();)
	{
		if (t->second == 0)
			t = reducedForm.erase(t);
		else
			++t;
	}
	return reducedForm;
}

term_t Computor::__getHighestDegreeTerm(const reduced_t &p)
{
	term_t highestDegreeTerm;
	if (p.size() < 1)
		return highestDegreeTerm;
	highestDegreeTerm = *p.begin();
	for (reduced_t::const_iterator t = p.begin(); t != p.end(); t++)
		if (t->first > highestDegreeTerm.first)
			highestDegreeTerm = *t;
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
			Computor::__displayTerm(t->first, t->second, true);
		else
			Computor::__displayTerm(t->first, t->second, false);
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

equation_t Computor::__solveStep1(const tokens_t &tokens)
{
	equation_t understandable = Computor::__parse(tokens);
	std::cout << "STEP 1" << std::endl;
	std::cout << "Understandable form: ";
	__displayTerms(understandable.first);
	std::cout << " = ";
	__displayTerms(understandable.second);
	std::cout << std::endl
			  << std::endl;
	return understandable;
}

equation_t Computor::__solveStep2(const equation_t &understandable)
{
	equation_t allInOneSide = Computor::__moveAllToOneSide(understandable);
	std::cout << "STEP 2" << std::endl;
	std::cout << "One-side polynomial equation: ";
	__displayTerms(allInOneSide.first);
	std::cout << " = ";
	__displayTerms(allInOneSide.second);
	std::cout << std::endl
			  << std::endl;
	return allInOneSide;
}

reduced_t Computor::__solveStep3(const equation_t &allInOneSide)
{
	reduced_t reducedForm = Computor::__reduce(allInOneSide);
	std::cout << "STEP 3" << std::endl;
	std::cout << "Reduced form: ";
	Computor::__displayReducedForm(reducedForm);
	std::cout << " = 0" << std::endl
			  << std::endl;
	return reducedForm;
}

void Computor::__solveStep4(const reduced_t &reducedForm)
{
	std::cout << "STEP 4" << std::endl;
	if (reducedForm.empty())
	{
		std::cout << "Any real number is a solution." << std::endl;
		return;
	}
	term_t highestDegreeTerm = Computor::__getHighestDegreeTerm(reducedForm);
	if (highestDegreeTerm.first == 0)
	{
		std::cout << (highestDegreeTerm.second == 0 ? "Any real number is a solution." : "No solution.") << std::endl;
		return;
	}
	std::cout << "Polynomial degree: " << highestDegreeTerm.first << std::endl;
	if (highestDegreeTerm.first == 1)
	{
		Computor::__solveFirstDegreeEquation(reducedForm);
		return;
	}
	if (highestDegreeTerm.first == 2)
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
	double x = -b / a;
	std::cout << "The solution is:" << std::endl;
	std::cout << x << std::endl;
}

void Computor::__solveSecondDegreeEquation(const reduced_t &eq)
{
	reduced_t tmp(eq);
	double a = tmp[2], b = tmp[1], c = tmp[0];
	double disc = b * b - 4 * a * c;
	if (disc > 0)
		return Computor::__solveSecondDegreeEquationPositiveDiscriminant(a, b, disc);
}

void Computor::__solveSecondDegreeEquationPositiveDiscriminant(const double &,
															   const double &,
															   const double &)
{
}

void Computor::solve(const std::string &expr)
{
	try
	{
		tokens_t tokens = Computor::__tokenization(expr);
		Computor::__checkSyntax(tokens);
		Computor::__checkVocabulary(tokens);
		equation_t understandable = Computor::__solveStep1(tokens);
		equation_t allInOneSide = Computor::__solveStep2(understandable);
		reduced_t reducedForm = Computor::__solveStep3(allInOneSide);
		Computor::__solveStep4(reducedForm);
	}
	catch (const std::exception &e)
	{
		throw;
	}
}
