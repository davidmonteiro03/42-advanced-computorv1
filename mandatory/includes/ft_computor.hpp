/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_computor.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:54:50 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/09 17:51:06 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <map>
#include <limits>

typedef enum e_token_type
{
	PLUS,
	MINUS,
	EQUAL,
	TERM,
	NONE
} t_token_type;

#include "Computor.hpp"
#include "Token.hpp"
