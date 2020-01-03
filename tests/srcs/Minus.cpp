/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minus.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 07:59:12 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/03 00:46:07 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minus.hpp"

Minus::Minus(void) : AbstractTerminal("-")
{
	
}

Minus::~Minus(void)
{
	
}

int	Minus::traverse(ASTNode<int, int> & ast, int dummy) const
{
	(void)ast;
	(void)dummy;
	return 0;
}