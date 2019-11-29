/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factor.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 05:52:53 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 10:07:26 by ldedier          ###   ########.fr       */
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
	(void)node;
	(void)dummy;
	return 0;
}

void	Factor::computeProductions(AbstractGrammar<int, int> &cfg)
{
	addProduction(cfg, 1, (std::string []){"integer"});
	addProduction(cfg, 2, (std::string []){"-", "factor"});
	addProduction(cfg, 2, (std::string []){"+", "factor"});
}