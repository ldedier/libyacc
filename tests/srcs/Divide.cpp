/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Divide.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 07:58:44 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 23:31:26 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Divide.hpp"

Divide::Divide(void) : AbstractTerminal("/")
{
	
}

Divide::~Divide(void)
{
	
}

int	Divide::traverse(ASTNode<int, int> & ast, int dummy) const
{
	(void)ast;
	(void)dummy;
	return 0;
}