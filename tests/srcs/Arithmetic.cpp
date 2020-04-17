/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Arithmetic.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:49:02 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 23:59:45 by ldedier          ###   ########.fr       */
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
	if (node.getChildren().size() == 0)
		return 0;
	else
		return node.getChild(0)->getTraversed(dummy);
}

void	Arithmetic::computeProductions(AbstractGrammar<int, int> &cfg)
{
	addProduction(cfg, {"expr"});
	addProduction(cfg, {});
}
