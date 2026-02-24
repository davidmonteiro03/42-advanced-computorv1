/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:33:46 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/24 10:44:57 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_computor.hpp"

class Term
{
public:
	Term(void);
	Term(const Real &,
		 const Integer &);
	Term(const Term &);
	Term &operator=(const Term &);
	~Term();

	const Real &getValue(void) const;
	const Integer &getDegree(void) const;

private:
	Real __value;
	Integer __degree;
};
