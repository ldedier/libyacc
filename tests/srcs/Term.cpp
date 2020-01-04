/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 04:46:08 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 04:42:59 by ldedier          ###   ########.fr       */
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
	(void)node;
	(void)dummy;
	return 0;
}

void	Term::computeProductions(AbstractGrammar<int, int> &cfg)
{
	addProduction(cfg, 1, (std::string []){"factor"});
	addProduction(cfg, 3, (std::string []){"term", "*", "factor"});
	addProduction(cfg, 3, (std::string []){"term", "/", "factor"});
}