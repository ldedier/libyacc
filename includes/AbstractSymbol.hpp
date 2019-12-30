/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractSymbol.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 06:48:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/12/30 01:21:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTSYMBOL_HPP
# define ABSTRACTSYMBOL_HPP

# include <iostream>
# include "ASTNode.hpp"
# include "Set.hpp"

# define YACC_EOC	"\033[0m"                                                   
# define YACC_BLUE	"\x1B[34m"
# define YACC_RED	"\x1B[31m"

template<typename T, typename C>
class AbstractGrammar;


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

		const std::string getIdentifier(void) const
		{
			return _identifier;
		}

		Set <T, C> &getFirstSet (void)
		{
			return _firstSet;
		}

		void printFirstSet()
		{
			std::cout << *this << ":" << std::endl;
			std::cout << this->_firstSet;
			std::cout << std::endl;
		}
		
		virtual void initFirstSet() = 0;
		virtual T traverse(ASTNode<T, C> & ast, C) const = 0;
		virtual std::string color(void) const = 0;

	private:
		std::string _identifier;
	
	protected:
		Set<T, C> _firstSet;
};

template<typename T, typename C>
std::ostream &operator<<(std::ostream &o, AbstractSymbol<T, C> const &instance)
{
	(void)o;
	(void)instance;
	o << instance.color() << instance.repr() << YACC_EOC;
	// o << YACC_RED << YACC_EOC;
	// o << "salut";
	return o;
}
#endif