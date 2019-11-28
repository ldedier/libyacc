/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractSymbol.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 06:50:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 06:53:25 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractSymbol.hpp"

AbstractSymbol::AbstractSymbol(void)
{
	
}

AbstractSymbol::AbstractSymbol(AbstractSymbol const &instance)
{
	*this = instance;	
}

AbstractSymbol::~AbstractSymbol(void)
{
	
}

AbstractSymbol &	AbstractSymbol::operator=(AbstractSymbol const &rhs)
{
	static_cast<void>(rhs);
	return *this;
}

std::ostream &	operator<<(std::ostream &o, AbstractSymbol const &instance)
{
	o << instance.repr();
	return o;
}