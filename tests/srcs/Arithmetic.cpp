/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Arithmetic.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:49:02 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 10:03:53 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Arithmetic.hpp"

Arithmetic::Arithmetic(void) : AbstractNonTerminal("arithmetic")
{
	
}

Arithmetic::~Arithmetic(void)
{
	
}

int	Arithmetic::traverse(ASTNode<int, int> & node, int dummy) const
{
	(void)node;
	(void)dummy;
	return 0;
}

void	Arithmetic::computeProductions(AbstractGrammar<int, int> &cfg)
{
	addProduction(cfg, 1, (std::string []){"expr"});
	addProduction(cfg, 0, nullptr);
}