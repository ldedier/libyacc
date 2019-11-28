/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArithmeticGrammar.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 09:57:18 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 17:28:44 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ArithmeticGrammar.hpp"

static AbstractNonTerminal _nonTerminals[AR_NB_NON_TERMINALS] = {
	Arithmetic(),
	Arithmetic(),
	Arithmetic(),
	Arithmetic(),
	Arithmetic(),
};
static AbstractToken _tokens[AR_NB_TOKENS] = {
	Integer();
};


ArithmeticGrammar::ArithmeticGrammar(_nonTerminals, sizeof(_nonTerminals) / sizeof(_nonTerminals[0]),
	 _tokens, sizeof(_tokens) / sizeof(_tokens[0]))
{
	// _startSymbol = Arithmetic();
	// addNonTerminal(_startSymbol);
	// addNonTerminal(Expr());
	// addNonTerminal(Term());
	// addNonTerminal(Factor());
	// addNonTerminal(Arithmetic());
	// addToken(Integer());
}

ArithmeticGrammar::ArithmeticGrammar(ArithmeticGrammar const &instance)
{
	*this = instance;
}

ArithmeticGrammar::~ArithmeticGrammar(void)
{
	
}

ArithmeticGrammar &	ArithmeticGrammar::operator=(ArithmeticGrammar const &rhs)
{
	static_cast<void>(rhs);
	return *this;
}