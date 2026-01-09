/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:01:09 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/09 15:04:07 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Term.hpp"

Term::Term(void) : __value(0),
				   __degree(0) {}

Term::Term(const double &value,
		   const double &degree) : __value(value),
								   __degree(degree) {}

Term::Term(const Term &copy) : __value(copy.__value),
							   __degree(copy.__degree) {}

Term &Term::operator=(const Term &other)
{
	if (this != &other)
	{
		this->__value = other.__value;
		this->__degree = other.__degree;
	}
	return *this;
}

Term::~Term() {}

const double &Term::getValue(void) const { return this->__value; }

const double &Term::getDegree(void) const { return this->__degree; }

void Term::setValue(const double &value) { this->__value = value; }

void Term::setDegree(const double &degree) { this->__degree = degree; }
