/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractSymbol.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 06:48:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 14:51:33 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTSYMBOL_HPP
# define ABSTRACTSYMBOL_HPP

# include <iostream>
# include "ASTNode.hpp"

template<typename T, typename C>
class AbstractSymbol
{
	public:
		AbstractSymbol<T, C>(void)
		{
			
		}
		
		AbstractSymbol<T, C>(AbstractSymbol const &instance)
		{
			*this = instance;
		}
		
		AbstractSymbol<T, C> &operator=(AbstractSymbol const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}

		virtual ~AbstractSymbol(void)
		{
			
		}

		virtual std::string repr(void) const = 0;
		virtual T traverse(ASTNode<T, C>) const = 0;

	private:
};

// std::ostream &operator<<(std::ostream &o, AbstractSymbol<T, C> const &instance);
#endif