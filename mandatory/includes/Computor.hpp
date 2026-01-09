/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:53:01 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/09 16:31:21 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../includes/ft_computor.hpp"
#include "Token.hpp"
#include "Term.hpp"

class Computor
{
private:
	Computor(void);
	Computor(const Computor &);
	Computor &operator=(const Computor &);
	~Computor();

	static Term __strtoterm(const std::string &);

	static std::vector<Token> __parse(const std::string &);
	static std::map<double, double> __reduce(const std::vector<Token> &);

	static void __showReducedForm(const std::map<double, double> &);

public:
	static void check(const std::string &);
	static void solve(const std::string &);
};
