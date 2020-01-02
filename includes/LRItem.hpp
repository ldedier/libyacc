/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRItem.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:08:59 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/02 01:28:36 by ldedier          ###   ########.fr       */
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

		LRItem(Production<T, C> &production, AbstractToken<T, C> &lookahead): _isParsed(false), _production(production),
			_lookahead(lookahead), _progress(production.getSymbols().begin())
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
		
		AbstractToken<T, C> & getLookahead(void)
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

	private:

		bool					_isParsed;
		Production<T, C> &		_production;
		AbstractToken<T, C> &	_lookahead;
		typename std::vector<AbstractSymbol<T, C> *>::const_iterator _progress;
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
	std::cout << "·";
	while (it != instance.getProduction().getSymbols().end())
	{
		o << *(*it);
		it++;
	}
	o << " (for lookahead: [" << instance.getLookahead() << "])";
	return o;
}

#endif