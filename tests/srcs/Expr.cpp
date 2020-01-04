/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Expr.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 04:42:37 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 23:42:26 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Expr.hpp"

Expr::Expr(void) : AbstractNonTerminal("expr")
{
	
}

Expr::~Expr(void)
{
	
}

int	Expr::traverse(ASTNode<int, int> & node, int dummy) const
{
	if (node.getChildren().size() == 3)
	{
		if (node.getChildIdentifier(1) == "+")
			return node.getChild(0)->getTraversed(dummy) + node.getChild(2)->getTraversed(dummy);
		else //(node.getChildIdentifier(1) == "-")
			return node.getChild(0)->getTraversed(dummy) - node.getChild(2)->getTraversed(dummy);
	}
	else
		return node.getChild(0)->getTraversed(dummy);
}

void	Expr::computeProductions(AbstractGrammar<int, int> &cfg)
{
	addProduction(cfg, 1, (std::string []){"term"});
	addProduction(cfg, 3, (std::string []){"expr", "+", "term"}, true);
	addProduction(cfg, 3, (std::string []){"expr", "-", "term"});
}