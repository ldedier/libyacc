/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Integer.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 04:44:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 09:07:10 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Integer.hpp"

Integer::Integer(void): AbstractToken("integer"), _value(0)
{
}


Integer::Integer(int value): AbstractToken("integer"),  _value(value)
{

}

Integer::~Integer(void)
{
	
}

std::string	Integer::repr(void) const
{
	return "integer";
}

int	Integer::traverse(ASTNode<int, int> & node, int dummy) const
{
	(void)node;
	(void)dummy;
	return _value;
}