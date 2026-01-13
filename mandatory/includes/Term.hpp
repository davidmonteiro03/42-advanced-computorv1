/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:16:25 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/13 10:19:46 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_computor.hpp"

class Term
{
private:
	long long int __degree;
	double __value;

public:
	Term(void);
	Term(const long long int &,
		 const double &);
	Term(const Term &);
	Term &operator=(const Term &);
	~Term();

	const long long int &getDegree(void) const;
	const double &getValue(void) const;

	void setDegree(const long long int &);
	void setValue(const double &);
};
