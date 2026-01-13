/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Equation.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:32:30 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/13 11:26:02 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_computor.hpp"

class Equation
{
private:
	terms_t __leftSide, __rightSide;

	static bool __isOperator(const std::string &);

public:
	Equation(void);
	Equation(const tokens_t &);
	Equation(const Equation &);
	Equation &operator=(const Equation &);
	~Equation();

	const terms_t &getLeftSide(void) const;
	const terms_t &getRightSide(void) const;

	Equation moveAllToOneSide(void) const;
	reduced_t reduce(void) const;
};
