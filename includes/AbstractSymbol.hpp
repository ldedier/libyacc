/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractSymbol.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 06:48:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 09:09:53 by ldedier          ###   ########.fr       */
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
		AbstractSymbol(void)
		{
			
		}

		AbstractSymbol(std::string identifier): _identifier(identifier)
		{
			
		}
		
		AbstractSymbol(AbstractSymbol const &instance)
		{
			*this = instance;
		}
		
		AbstractSymbol &operator=(AbstractSymbol const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}

		virtual ~AbstractSymbol(void)
		{
			
		}

		virtual std::string repr(void) const
		{
			return _identifier;
		}

		virtual T traverse(ASTNode<T, C> & ast, C) const = 0;

	private:
		std::string _identifier;
};

// std::ostream &operator<<(std::ostream &o, AbstractSymbol<T, C> const &instance);
#endif