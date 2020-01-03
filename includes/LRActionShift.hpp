/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRActionShift.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:31:04 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/03 00:01:33 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRACTIONSHIFT_HPP
# define LRACTIONSHIFT_HPP

# include <iostream>
# include "AbstractLRAction.hpp"

template<typename T, typename C>
class LRActionShift : public AbstractLRAction<T, C>
{
	public:
		LRActionShift(void)
		{
			
		}

		LRActionShift(LRState<T, C> &state) : _state(&state)
		{

		}

		LRActionShift(LRActionShift const &instance)
		{
			*this = instance;
		}
		LRActionShift<T, C> &operator=(LRActionShift<T, C> const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}
		virtual ~LRActionShift(void)
		{
			
		}

		virtual std::string repr(void) const
		{
			return "SHIFT";
		}

		virtual std::string color(void) const
		{
			return YACC_GREEN;
		}

	private:
		LRState<T, C> *_state;
};

// std::ostream &operator<<(std::ostream &o, LRActionShift const &instance);
#endif