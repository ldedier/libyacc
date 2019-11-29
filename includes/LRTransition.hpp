/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRTransition.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 08:34:45 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 07:15:50 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRTRANSITION_HPP
# define LRTRANSITION_HPP

# include <iostream>
# include "AbstractSymbol.hpp"
# include "LRState.hpp"


template<typename T, typename C>
class LRState;

template<typename T, typename C>
class LRTransition
{
	public:
		LRTransition(void)
		{
			
		}

		LRTransition(LRTransition<T, C> const &instance)
		{
			*this = instance;
		}
		
		LRTransition<T, C> &operator=(LRTransition<T, C> const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}
		
		virtual ~LRTransition(void)
		{
			
		}

	private:
		AbstractSymbol<T, C>	* _symbol;
		LRState<T, C>			* state;

};

// std::ostream &operator<<(std::ostream &o, LRTransition const &instance);
#endif