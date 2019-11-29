/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractSymbol.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 06:48:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 15:50:32 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTSYMBOL_HPP
# define ABSTRACTSYMBOL_HPP

# include <iostream>
# include "ASTNode.hpp"

# define YACC_EOC	"\033[0m"                                                   
# define YACC_BLUE	"\x1B[34m"
# define YACC_RED	"\x1B[31m"

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

		std::string getIdentifier(void)
		{
			return _identifier;
		}
		
		virtual T traverse(ASTNode<T, C> & ast, C) const = 0;
		virtual std::string color(void) const = 0;

	private:
		std::string _identifier;
};


template<typename T, typename C>
std::ostream &operator<<(std::ostream &o, AbstractSymbol<T, C> const &instance)
{
	o << instance.color() << instance.repr() << YACC_EOC;
	return o;
}
#endif