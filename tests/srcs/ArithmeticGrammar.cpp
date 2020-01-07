/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArithmeticGrammar.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 09:57:18 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 23:57:42 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ArithmeticGrammar.hpp"

ArithmeticGrammar::ArithmeticGrammar(void) : AbstractGrammar(new Arithmetic())
{
	addNonTerminal(new Expr());
	addNonTerminal(new Term());
	addNonTerminal(new Factor());

	addToken(new Integer());
	addToken(new Plus());
	addToken(new Minus());
	addToken(new Multiply());
	addToken(new Divide());

	computeGrammar();
}

std::deque<Token<int, int> *> ArithmeticGrammar::innerLex(std::istream & istream)
{
	char c;

	std::deque<Token<int, int> *> res;
	while (istream.get(c))
	{
		if (c == '\n')
			return res;
		if (c == '+')
			res.push_back(new Token<int, int>(*(getTerminal("+"))));
		else if (c == '*')
			res.push_back(new Token<int, int>(*(getTerminal("*"))));
		else if (c == '/')
			res.push_back(new Token<int, int>(*(getTerminal("/"))));
		else if (c == '-')
			res.push_back(new Token<int, int>(*(getTerminal("-"))));
		else if (isdigit(c))
			res.push_back(new Token<int, int>(*(getTerminal("integer")), (int)(c - '0')));
		else if (!isspace(c))
			throw std::exception();
	}
	return (res);
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
