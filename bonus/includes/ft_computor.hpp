/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_computor.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:54:50 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/12 17:48:28 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <map>
#include <list>
#include <limits>

using tokens_t = std::list<std::string>;
using term_t = std::pair<long long int, double>;
using terms_t = std::vector<term_t>;
using equation_t = std::pair<terms_t, terms_t>;
using reduced_t = std::map<long long int, double>;

#include "Computor.hpp"
