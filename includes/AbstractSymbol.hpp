/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractSymbol.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 06:48:30 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 20:35:43 by ldedier          ###   ########.fr       */
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
# define YACC_GREEN	"\x1B[32m"
# define YACC_YELLOW	"\x1B[33m"
# define YACC_ACCEPT	"\x1B[35m"

template<typename T, typename C>
class AbstractGrammar;

template<typename T, typename C>
class AbstractSymbol
{
	public:
		AbstractSymbol(void)
		{
			
		}

		AbstractSymbol(std::string identifier): _identifier(identifier), _relevant(true)
		{
			
		}

		AbstractSymbol(std::string identifier, bool relevant): _identifier(identifier), _relevant(relevant)
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

		int getIndex()
		{
			return _index;
		}

		void setIndex(int index)
		{
			_index = index;
		}

		bool isRelevant()
		{
			return _relevant;
		}

		void printFirstSet()
		{
			std::cout << *this << ":" << std::endl;
			std::cout << this->_firstSet;
			std::cout << std::endl;
		}

		virtual bool isTerminal() = 0;
		virtual void initFirstSet() = 0;
		virtual T traverse(ASTNode<T, C> & ast, C) const = 0;
		virtual std::string color(void) const = 0;

	private:
		std::string _identifier;
		int			_index;
		bool		_relevant;
	protected:
		Set<T, C> _firstSet;
};

template<typename T, typename C>
std::ostream &operator<<(std::ostream &o, AbstractSymbol<T, C> const &instance)
{
	o << instance.color() << instance.repr() << YACC_EOC;
	return o;
}
#endif