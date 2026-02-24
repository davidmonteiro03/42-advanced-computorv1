/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:35:27 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/24 10:48:20 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

Term::Term(void) : __value(),
				   __degree() {}

Term::Term(const Real &value,
		   const Integer &degree) : __value(value),
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

const Real &Term::getValue(void) const { return this->__value; }

const Integer &Term::getDegree(void) const { return this->__degree; }
