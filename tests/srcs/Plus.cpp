/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plus.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 08:01:14 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 09:06:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Plus.hpp"

Plus::Plus(void) : AbstractToken("+")
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