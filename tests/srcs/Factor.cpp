/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factor.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 05:52:53 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 23:52:38 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factor.hpp"

Factor::Factor(void) : AbstractNonTerminal("factor")
{
	
}

Factor::~Factor(void)
{
	
}

int	Factor::traverse(ASTNode<int, int> & node, int dummy) const
{
	if (node.getChildren().size() == 2)
	{
		if (node.getChildIdentifier(0) == "-")
			return - node.getChild(1)->getTraversed(dummy);
		else //(node.getChildIdentifier(1) == "-")
			return node.getChild(1)->getTraversed(dummy);
	}
	else
		return node.getChild(0)->getTraversed(dummy);
}

void	Factor::computeProductions(AbstractGrammar<int, int> &cfg)
{
	addProduction(cfg, {"integer"});
	addProduction(cfg, {"-", "factor"});
	addProduction(cfg, {"+", "factor"});
}
