/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 04:46:08 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 23:51:10 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Term.hpp"

Term::Term(void) : AbstractNonTerminal("term")
{
	
}

Term::~Term(void)
{
	
}

int	Term::traverse(ASTNode<int, int> & node, int dummy) const
{
	int tmp;

	if (node.getChildren().size() == 3)
	{
		if (node.getChildIdentifier(1) == "*")
			return node.getChild(0)->getTraversed(dummy) * node.getChild(2)->getTraversed(dummy);
		else //(node.getChildIdentifier(1) == "-")
		{
			tmp = node.getChild(2)->getTraversed(dummy);
			if (tmp == 0)
				throw new std::exception;
			else
				return node.getChild(0)->getTraversed(dummy) / tmp;
		}
	}
	else
		return node.getChild(0)->getTraversed(dummy);
	return 0;
}

void	Term::computeProductions(AbstractGrammar<int, int> &cfg)
{
	addProduction(cfg, {"factor"});
	addProduction(cfg, {"term", "*", "factor"});
	addProduction(cfg, {"term", "/", "factor"});
}
