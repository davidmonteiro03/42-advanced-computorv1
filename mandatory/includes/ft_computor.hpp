/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_computor.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:54:50 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/12 07:37:46 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <limits>

using args_t = std::vector<std::string>;
using term_t = std::pair<double, double>;
using terms_t = std::vector<term_t>;
using reduced_t = std::map<double, double>;
using equation_t = std::pair<terms_t, terms_t>;

#include "Computor.hpp"
