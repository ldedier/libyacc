/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRItem.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:08:59 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 17:43:35 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRITEM_HPP
# define LRITEM_HPP

# include <iostream>
# include <vector>
# include "Production.hpp"

template<typename T, typename C>
class LRItem
{
	public:
		LRItem(void) : _isParsed(false)
		{

		}

		LRItem(Production<T, C> &production, AbstractTerminal<T, C> &lookahead): _isParsed(false), _production(production),
			_lookahead(lookahead), _progress(production.getSymbols().begin())
		{
			
		}

		LRItem(Production<T, C> &production, AbstractTerminal<T, C> &lookahead,
			typename std::vector<AbstractSymbol<T, C> *>::const_iterator it): _isParsed(false), _production(production),
				_lookahead(lookahead), _progress(it)
		{
			
		}

		LRItem(LRItem const &instance)
		{
			*this = instance;
		}

		LRItem &operator=(LRItem const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}

		~LRItem(void)
		{

		}

		typename std::vector<AbstractSymbol<T, C> *>::const_iterator & getProgress(void)
		{
			return _progress;
		}
		
		AbstractTerminal<T, C> & getLookahead(void)
		{
			return _lookahead;
		}

		Production<T, C> & getProduction(void)
		{
			return _production;
		}

		bool isParsed()
		{
			return _isParsed;
		}

		void setParsed(bool parsed)
		{
			_isParsed = parsed;
		}

		LRItem<T, C> *advance()
		{
			return new LRItem<T, C>(this->_production, this->_lookahead, this->_progress + 1);
		}

	private:

		bool															_isParsed;
		Production<T, C> &												_production;
		AbstractTerminal<T, C> 											&_lookahead;
		typename std::vector<AbstractSymbol<T, C> *>::const_iterator	_progress;
};

template<typename T, typename C>
std::ostream &operator<<(std::ostream &o, LRItem<T, C> &instance)
{
	typename std::vector<AbstractSymbol<T, C> *>::const_iterator it = instance.getProduction().getSymbols().begin();
	
	o << *(instance.getProduction().getFrom()) << " → ";
	while (it != instance.getProgress())
	{
		o << *(*it);
		it++;
	}
	std::cout << "· ";
	while (it != instance.getProduction().getSymbols().end())
	{
		o << *(*it) << " ";
		it++;
	}
	o << "(for lookahead: [" << instance.getLookahead() << "])";
	return o;
}

#endif