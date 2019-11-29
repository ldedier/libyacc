/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArithmeticGrammar.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 09:57:18 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 05:29:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ArithmeticGrammar.hpp"
#include "Integer.hpp"
#include "Arithmetic.hpp"
#include "Term.hpp"
#include "Factor.hpp"
#include "Expr.hpp"

ArithmeticGrammar::ArithmeticGrammar(void)
{
	_startSymbol = new Arithmetic();

	addNonTerminal(_startSymbol);
	addNonTerminal(new Expr());
	addNonTerminal(new Term());
	addNonTerminal(new Factor());

	addToken(new Integer());

	computeProductions();
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