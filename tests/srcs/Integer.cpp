/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Integer.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 04:44:30 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 23:56:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Integer.hpp"
#include "Token.hpp"

Integer::Integer(void): AbstractTerminal("integer")
{

}

Integer::~Integer(void)
{
	
}

int	Integer::traverse(ASTNode<int, int> & node, int dummy) const
{
	(void)dummy;
	return node.getToken()->getIntValue();
}
