/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:08:14 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 17:20:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ArithmeticGrammar.hpp"
#include "LRParser.hpp"

int main(void)
{
	ArithmeticGrammar ag;

	LRParser<int, int> parser(ag);
	
	try {
		ASTBuilder<int, int> b = parser.parse();
	}
	catch(std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}