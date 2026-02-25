/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 07:15:40 by dcaetano          #+#    #+#             */
/*   Updated: 2026/02/25 17:41:13 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_computor.hpp"

class Parser
{
public:
	static std::vector<std::string> split(const std::string &);

	static bool checkAsterisk(const std::string &);
	static bool checkVariableX(const std::string &);
	static bool checkOperator(const std::string &);

	static long double getValue(const std::string &);
	static unsigned long long int getDegree(const std::string &);

private:
	Parser(void);
	Parser(const Parser &);
	Parser &operator=(const Parser &);
	~Parser();
};
