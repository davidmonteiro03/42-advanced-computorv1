/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:04:15 by dcaetano          #+#    #+#             */
/*   Updated: 2026/03/02 07:33:30 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

Term::Term(void) : __value(0.0L),
				   __degree(0.0L) {}

Term::Term(const long double &value,
		   const unsigned long long int &degree) : __value(value),
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

const long double &Term::getValue(void) const { return this->__value; }

const unsigned long long int &Term::getDegree(void) const { return this->__degree; }
