/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRState.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:09:41 by ldedier           #+#    #+#             */
/*   Updated: 2019/12/30 13:04:25 by ldedier          ###   ########.fr       */
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

		virtual ~LRState(void)
		{
			
		}

	private:
		std::vector<LRItem<T, C> *> _items;
		std::vector<LRTransition<T, C> *> _transitions;

};

// std::ostream &operator<<(std::ostream &o, LRState const &instance);
#endif