/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:15:35 by dcaetano          #+#    #+#             */
/*   Updated: 2026/01/09 14:18:49 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_computor.hpp"

Token::Token(void) : __token(""),
					 __type(NONE) {}

Token::Token(const std::string &token,
			 const t_token_type &type) : __token(token),
										 __type(type) {}

Token::Token(const Token &copy) : __token(copy.__token),
								  __type(copy.__type) {}

Token &Token::operator=(const Token &other)
{
	if (this != &other)
		;
	return *this;
}

Token::~Token() {}

const std::string &Token::getToken(void) const { return this->__token; }

const t_token_type &Token::getType(void) const { return this->__type; }
