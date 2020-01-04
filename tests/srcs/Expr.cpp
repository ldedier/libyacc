/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Expr.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 04:42:37 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 04:49:15 by ldedier          ###   ########.fr       */
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
	(void)node;
	(void)dummy;
	return 0;
}

void	Expr::computeProductions(AbstractGrammar<int, int> &cfg)
{
	addProduction(cfg, 1, (std::string []){"term"});
	addProduction(cfg, 3, (std::string []){"expr", "+", "term"}, true);
	addProduction(cfg, 3, (std::string []){"expr", "-", "term"}, true);
}