/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRItem.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:08:59 by ldedier           #+#    #+#             */
/*   Updated: 2019/12/30 13:05:15 by ldedier          ###   ########.fr       */
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
		LRItem(void)
		{

		}

		LRItem(Production<T, C> &production, AbstractToken<T, C> &lookahead): _production(production),
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

	private:
		Production<T, C> & _production;
		AbstractToken<T, C> & _lookahead;
		typename std::vector<AbstractSymbol<T, C> *>::const_iterator _progress;
};

// std::ostream &operator<<(std::ostream &o, LRItem<T, C> const &instance);
#endif