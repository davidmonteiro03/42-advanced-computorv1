/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:21:28 by dcaetano          #+#    #+#             */
/*   Updated: 2026/03/02 07:24:30 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/includes/ft_computor.hpp"

int main(int argc, char **argv)
{
	std::string expr = "";
	if (argc < 2)
		std::getline(std::cin, expr);
	else
		expr = static_cast<std::string>(argv[1]);
	std::list<std::string> tokens = Parser::tokenization(expr);
	try
	{
		Parser::checkSyntax(tokens);
		Parser::checkVocabulary(tokens);
		Equation equation(tokens);
		Solver::solve(equation);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
