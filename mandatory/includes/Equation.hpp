/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Equation.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:08:29 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/25 17:41:07 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_computor.hpp"

class Equation
{
public:
	Equation(void);
	Equation(const std::string &);
	Equation(const Equation &);
	Equation &operator=(const Equation &);
	~Equation();

private:
	std::vector<Term> __leftSide;
	std::vector<Term> __rightSide;

	friend class Solver;
};
