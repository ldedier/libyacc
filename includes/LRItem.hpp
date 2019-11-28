/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRItem.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:08:59 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 14:54:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRITEM_HPP
# define LRITEM_HPP

# include <iostream>
# include "Production.hpp"
# include "AbstractToken.hpp"

template<typename T, typename C>
class LRItem
{
	public:
		LRItem(void)
		{
			
		}

		LRItem(LRItem<T, C> const &instance)
		{
			*this = instance;
		}

		LRItem<T, C> &operator=(LRItem<T, C> const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}
		
		virtual ~LRItem(void)
		{
			
		}

	private:
		Production<T, C> &production;
		AbstractToken<T, C> &Lookahead;
		//progress
};

// std::ostream &operator<<(std::ostream &o, LRItem const &instance);
#endif