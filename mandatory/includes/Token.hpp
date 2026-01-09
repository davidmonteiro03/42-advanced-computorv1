/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:11:38 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/09 14:17:54 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../includes/ft_computor.hpp"

class Token
{
private:
	const std::string __token;
	const t_token_type __type;

public:
	Token(void);
	Token(const std::string &,
		  const t_token_type &);
	Token(const Token &);
	Token &operator=(const Token &);
	~Token();

	const std::string &getToken(void) const;
	const t_token_type &getType(void) const;
};
