/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:01:58 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/25 17:40:46 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_computor.hpp"

class Term
{
public:
	Term(void);
	Term(const long double &,
		 const unsigned long long int &);
	Term(const Term &);
	Term &operator=(const Term &);
	~Term();

	const long double &getValue(void) const;
	const unsigned long long int &getDegree(void) const;

private:
	long double __value;
	unsigned long long int __degree;
};
