/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:19:19 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/13 10:24:18 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

Term::Term(void) : __degree(0), __value(0) {}

Term::Term(const long long int &degree,
		   const double &value) : __degree(degree),
								  __value(value) {}

Term::Term(const Term &copy) : __degree(copy.__degree),
							   __value(copy.__value) {}

Term &Term::operator=(const Term &other)
{
	if (this != &other)
	{
		this->__degree = other.__degree;
		this->__value = other.__value;
	}
	return *this;
}

Term::~Term() {}

const long long int &Term::getDegree(void) const { return this->__degree; }

const double &Term::getValue(void) const { return this->__value; }

void Term::setDegree(const long long int &degree) { this->__degree = degree; }

void Term::setValue(const double &value) { this->__value = value; }
