/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Equation.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:49:23 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/24 11:20:53 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_computor.hpp"

class Equation
{
public:
	Equation(void);
	Equation(const std::list<std::string> &);
	Equation(const Equation &);
	Equation &operator=(const Equation &);
	~Equation();

	friend std::ostream &operator<<(std::ostream &,
									const std::vector<Term> &);

	friend std::ostream &operator<<(std::ostream &,
									const Equation &);

private:
	std::vector<Term> __leftSide;
	std::vector<Term> __rightSide;

	static bool __isOperator(const std::string &);

	static void __displayTerm(std::ostream &,
							  const Term &,
							  const bool &);

	friend class Solver;
};
