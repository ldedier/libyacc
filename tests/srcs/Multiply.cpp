/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiply.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 07:57:32 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 08:57:05 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Multiply.hpp"

Multiply::Multiply(void) : AbstractToken("*")
{
	
}

Multiply::~Multiply(void)
{
	
}

int	Multiply::traverse(ASTNode<int, int> & ast, int dummy) const
{
	(void)ast;
	(void)dummy;
	return 0;
}