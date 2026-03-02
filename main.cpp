/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 15:21:21 by dcaetano          #+#    #+#             */
/*   Updated: 2026/03/02 09:02:24 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory/includes/ft_computor.hpp"

int main(int argc, char **argv)
{
	std::cout.precision(std::numeric_limits<long double>::digits10);
	std::string expr = "";
	if (argc < 2)
		std::getline(std::cin, expr);
	else
		expr = static_cast<std::string>(argv[1]);
	Equation equation(expr);
	Solver::solve(equation);
	return 0;
}
