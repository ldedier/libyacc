/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractTerminal.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:14:12 by ldedier           #+#    #+#             */
/*   Updated: 2020/05/03 20:35:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTTERMINAL_HPP
# define ABSTRACTTERMINAL_HPP

# include <iostream>
# include "AbstractSymbol.hpp"
# include "Production.hpp"
# include "Token.hpp"

template<typename T, typename C>
class AbstractTerminal : public AbstractSymbol<T, C>
{
	public:
	
		typedef enum		e_priority	
		{
			E_PRIORITY_INF,
			E_PRIORITY_STANDARD,
			E_PRIORITY_SUP
		}					t_priority;

		typedef enum		e_adjacent	
		{
			E_ADJACENT_DETACHED = 1,
			E_ADJACENT_ADJACENT = 2,
			E_ADJACENT_BOTH = 3
		}					t_adjacent;


		AbstractTerminal(void) : _priority(E_PRIORITY_STANDARD)
		{
			
		}

		AbstractTerminal(std::string identifier) : AbstractSymbol<T, C>(identifier),
			_priority(E_PRIORITY_STANDARD), _adjacent(E_ADJACENT_BOTH)
		{
			
		}

		AbstractTerminal(std::string identifier, t_priority priority) : AbstractSymbol<T, C>(identifier),
			_priority(priority), _adjacent(E_ADJACENT_BOTH)
		{
			
		}

		AbstractTerminal(std::string identifier, t_priority priority, t_adjacent adjacent) : AbstractSymbol<T, C>(identifier)
			, _priority(priority), _adjacent(adjacent)
		{
			
		}

		AbstractTerminal(AbstractTerminal<T, C> const &instance)
		{
			*this = instance;
		}

		AbstractTerminal &operator=(AbstractTerminal<T, C> const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}

		virtual ~AbstractTerminal(void)
		{
			
		}

		virtual void initFirstSet()
		{
			this->_firstSet.addTerminal(this);
		}

		virtual std::string color(void) const
		{
			return YACC_BLUE;
		}

		virtual bool isTerminal()
		{
			return true;
		}

		virtual std::string getLexerString()
		{
			return this->_identifier;
		}

		virtual t_adjacent getAdjacent()
		{
			return this->_adjacent;
		}

		virtual bool canBeAdded(std::deque<Token<T, C> *> &tokens)
		{
			static_cast<void>(tokens);
			return true;
		}

		virtual bool staysEligibleForCurrent(std::string & current)
		{
			return getLexerString().compare(0, current.size(), current) == 0;
		}

		virtual bool isEligibleForCurrent(std::string & current)
		{
			return getLexerString().compare(current) == 0;
		}

		virtual bool shouldCreateToken(std::string tokenContent,
			char delimiter, std::deque<Token<T, C> *> &tokens)
		{
			static_cast<void>(tokenContent);
			static_cast<void>(tokens);

			
			if (isblank(delimiter) && (E_ADJACENT_DETACHED & _adjacent))
				return true;
			else if (!isblank(delimiter) && (E_ADJACENT_ADJACENT & _adjacent))
				return true;
			return false;
		}

		virtual Token<T, C> *createToken(std::string tokenContent)
		{
			static_cast<void>(tokenContent);
			return new Token<T, C>(*this);
		}

		t_priority getPriority(void)
		{
			return _priority;
		}

	private:
		std::vector<Production<T, C> >	_productions;
		t_priority						_priority;
		t_adjacent						_adjacent;
		

};

// std::ostream &operator<<(std::ostream &o, AbstractTerminal const &instance);
#endif