/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plus.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 08:01:14 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/03 00:46:07 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Plus.hpp"

Plus::Plus(void) : AbstractTerminal("+")
{
	
}

Plus::~Plus(void)
{
	
}

int	Plus::traverse(ASTNode<int, int> & ast, int dummy) const
{
	(void)ast;
	(void)dummy;
	return (0);
}