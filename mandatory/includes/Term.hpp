/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:01:58 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/23 09:30:52 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_computor.hpp"

class Term
{
public:
	Term(void);
	Term(const double &,
		 const long long int &);
	Term(const Term &);
	Term &operator=(const Term &);
	~Term();

	const double &getValue(void) const;
	const long long int &getDegree(void) const;

private:
	double __value;
	long long int __degree;
};
