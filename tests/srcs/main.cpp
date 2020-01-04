/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:08:14 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 03:13:42 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ArithmeticGrammar.hpp"
#include "LRParser.hpp"
#include "ASTBuilder.hpp"
#include "Token.hpp"
#include <fstream>

std::deque<Token<int, int> *> lex(std::istream &stream, ArithmeticGrammar &cfg)
{
	char c;

	std::deque<Token<int, int> *> res;
	while (stream.get(c))
	{
		if (c == '\n')
			return res;
		if (c == '+')
			res.push_back(new Token<int, int>(*(cfg.getTerminal("+"))));
		else if (c == '*')
			res.push_back(new Token<int, int>(*(cfg.getTerminal("*"))));
		else if (c == '/')
			res.push_back(new Token<int, int>(*(cfg.getTerminal("/"))));
		else if (c == '-')
			res.push_back(new Token<int, int>(*(cfg.getTerminal("-"))));
		else if (isdigit(c))
			res.push_back(new Token<int, int>(*(cfg.getTerminal("integer")), c - '0'));
		else if (!isspace(c))
			throw std::exception();
	}
	return (res);
}

int main(void)
{
	ArithmeticGrammar ag;

	LRParser<int, int> parser(ag);
	std::deque<Token<int, int> *> tokens;

	tokens = lex(std::cin, ag);
	tokens.push_back(new Token<int, int>(*(ag.getTerminal("_EOI_"))));
	try {
		ASTBuilder<int, int> *b = parser.parse(tokens);
		std::cout << *b << std::endl;
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}