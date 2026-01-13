/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_computor.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:54:50 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/13 10:42:52 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <limits>

#include "Term.hpp"

using terms_t = std::vector<Term>;
using args_t = std::vector<std::string>;
using reduced_t = std::map<long long int, double>;

#include "Equation.hpp"
#include "Computor.hpp"
