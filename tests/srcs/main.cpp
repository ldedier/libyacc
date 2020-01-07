/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:08:14 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/07 14:44:13 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ArithmeticGrammar.hpp"
#include "LRParser.hpp"

int main(void)
{
	ArithmeticGrammar ag;
	LRParser<int, int> parser(ag);
	std::deque<Token<int, int> *> tokens;

	tokens = ag.lex(std::cin);
	try
	{
		ASTBuilder<int, int> *b = parser.parse(tokens);
		int res = b->getCSTRoot()->getTraversed(0);
		std::cout << *b << std::endl;
		std::cout << "result : " << res << std::endl;
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
