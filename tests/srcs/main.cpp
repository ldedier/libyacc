/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:08:14 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 08:06:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ArithmeticGrammar.hpp"
#include "LRParser.hpp"
#include "ASTBuilder.hpp"
#include <fstream>

std::list<AbstractToken<int, int> *> lex(std::istream &stream)
{
	char c;

	std::list<AbstractToken<int, int> *> res;
	while (stream.get(c))
	{
		if (c == '\n')
			return res;
		if (c == '+')
			res.push_back(new Plus());
		else if (c == '*')
			res.push_back(new Multiply());
		else if (c == '/')
			res.push_back(new Divide());
		else if (c == '-')
			res.push_back(new Minus());
		else if (isdigit(c))
			res.push_back(new Integer(c - '0'));
		else if (!isspace(c))
			throw std::exception();
	}
	return (res);
}

int main(void)
{
	ArithmeticGrammar ag;
	LRParser<int, int> parser(ag);
	std::list<AbstractToken<int, int> *> tokens;

	tokens = lex(std::cin);
	try {
		ASTBuilder<int, int> b = parser.parse();
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}