/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:08:14 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 23:05:03 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ArithmeticGrammar.hpp"
#include "LRParser.hpp"
#include "ASTBuilder.hpp"
#include "Token.hpp"
#include <fstream>


int main(void)
{
	ArithmeticGrammar ag;
	LRParser<int, int> parser(ag);
	std::deque<Token<int, int> *> tokens;

	tokens = ag.lex(std::cin);
	try {
		ASTBuilder<int, int> *b = parser.parse(tokens);
		std::cout << *b << std::endl;
		delete b;
		b = parser.parse(tokens);
		std::cout << *b << std::endl;
		delete b;
		deleteTokens(tokens);
	}
	catch (std::exception e)
	{
		deleteTokens(tokens);
		std::cerr << e.what() << std::endl;
	}
	return (0);
}