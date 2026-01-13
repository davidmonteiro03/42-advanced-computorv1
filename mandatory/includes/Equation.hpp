/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Equation.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:32:30 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/13 10:45:24 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_computor.hpp"

class Equation
{
private:
	terms_t __leftSide, __rightSide;

public:
	Equation(void);
	Equation(const args_t &);
	Equation(const Equation &);
	Equation &operator=(const Equation &);
	~Equation();

	reduced_t reduce(void) const;
};
