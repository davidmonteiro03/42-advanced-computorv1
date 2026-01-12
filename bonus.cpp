/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:30:31 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/12 07:38:48 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/includes/ft_computor.hpp"

int main(int argc, char **argv)
{
	if (argc > 2)
		return 0;
	std::string expr = "";
	if (argc == 1)
		std::getline(std::cin, expr);
	else
		expr = argv[1];
	try
	{
		Computor::solve(expr);
	}
	catch (const std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
