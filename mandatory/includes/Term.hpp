/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:53:45 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/09 15:04:06 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Term
{
private:
	double __value;
	double __degree;

public:
	Term(void);
	Term(const double &,
		 const double &);
	Term(const Term &);
	Term &operator=(const Term &);
	~Term();

	const double &getValue(void) const;
	const double &getDegree(void) const;

	void setValue(const double &);
	void setDegree(const double &);
};
