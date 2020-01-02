/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRState.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:09:41 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/02 01:28:01 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRSTATE_HPP
# define LRSTATE_HPP

# include <iostream>
# include "LRTransition.hpp"
# include "LRItem.hpp"

template<typename T, typename C>
class LRState
{
	public:
		LRState(void)
		{
			
		}

		LRState(AbstractGrammar<T, C> &cfg)
		{
			LRItem<T, C> *firstItem;
		
			firstItem = new LRItem<T, C>(*(*cfg.getStartingSymbol()->getProductions().begin()), *cfg.getEndOfInput());
			_items.push_back(firstItem);
		}

		LRState(LRState const &instance)
		{
			*this = instance;
		}

		
		LRState<T, C> &operator=(LRState<T, C> const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}

		std::vector<LRItem<T, C> *> & getItems()
		{
			return _items;
		}

		virtual ~LRState(void)
		{
			
		}

		void addItem(Production<T,C> &production, AbstractToken<T, C> &lookahead)
		{
			LRItem <T, C> *item;
		
			item = new LRItem<T, C> (production, lookahead);
			_items.push_back(item);
		}

		bool hasItem(Production<T,C> &production, AbstractToken<T, C> &lookahead)
		{
			LRItem<T, C> *item;
			typename std::vector<LRItem<T, C> *>::iterator it = _items.begin();
		
			while (it != _items.end())
			{
				item = *it;

				if (&item->getProduction() == &production
					&& &item->getLookahead() == &lookahead
					&& item->getProgress() == item->getProduction().getSymbols().begin())
				{
					return true;
				}
				it++;
			}
			return false;
		}

	private:
		std::vector<LRItem<T, C> *> _items;
		std::vector<LRTransition<T, C> *> _transitions;

};
template<typename T, typename C>
std::ostream &operator<<(std::ostream &o, LRState<T, C> &instance)
{
	typename std::vector<LRItem<T, C> *>::iterator it = instance.getItems().begin();
	while (it != instance.getItems().end())
	{
		o << *(*it) << std::endl;	
		it++;
	}
	return o;
}
#endif