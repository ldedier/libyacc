/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRState.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:09:41 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/03 16:24:29 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRSTATE_HPP
# define LRSTATE_HPP

# include <iostream>
# include "LRItem.hpp"

template<typename T, typename C>
class LRState
{
	public:
		LRState(void)
		{
			
		}

		LRState(AbstractGrammar<T, C> &cfg): _index(0)
		{
			LRItem<T, C> *firstItem;
		
			firstItem = new LRItem<T, C>(*(*cfg.getStartingSymbol()->getProductions().begin()), *cfg.getEndOfInput());
			_items.push_back(firstItem);
		}

		LRState(LRItem<T, C> &item, int index): _index(index)
		{
			_items.push_back(&item);
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

		void addNewItem(Production<T,C> &production, AbstractTerminal<T, C> &lookahead)
		{
			LRItem <T, C> *item;
		
			item = new LRItem<T, C> (production, lookahead);
			_items.push_back(item);
		}
		
		void addItem(LRItem<T, C> *item)
		{
			_items.push_back(item);
		}

		bool hasItem(Production<T,C> &production, AbstractTerminal<T, C> &lookahead)
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

		bool hasNextItem(LRItem<T, C> &item)
		{
			typename std::vector<LRItem<T, C> *>::iterator it = _items.begin();
			LRItem<T, C>* currentItem;
			typename std::vector<AbstractSymbol<T, C> *>::const_iterator itemProgressSave = item.getProgress();
			itemProgressSave++;
	
			while (it != _items.end())
			{
				currentItem = *it;
				if (&item.getLookahead() == &currentItem->getLookahead()
					&& &item.getProduction() == &currentItem->getProduction()
					&& itemProgressSave == currentItem->getProgress())
						return true;
				it++;
			}
			// std::cout << "didn't found " << *item.advance() << " in \n" << *this;
			return false;
		}

		LRState<T, C> *getStateByTransition(AbstractSymbol<T, C> &symbol)
		{
			typename std::map<AbstractSymbol<T, C> *, LRState<T, C> * >::iterator it = _transitions.find(&symbol);

			if (it != _transitions.end()) {
				return (it->second);
			}
			else {
				return nullptr;
			}
		}

		std::map<AbstractSymbol<T, C> *, LRState<T, C> *> & getTransitions()
		{
			return _transitions;
		}

		void link(AbstractSymbol<T, C> &symbol, LRState<T, C> &state)
		{
			_transitions.insert(std::pair <AbstractSymbol<T, C> *, LRState<T, C> *>(&symbol, &state));
		}

		int getIndex()
		{
			return _index;
		}

	private:
		int							_index;
		std::vector<LRItem<T, C> *> _items;
		std::map<AbstractSymbol<T, C> *, LRState<T, C> *> _transitions;
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