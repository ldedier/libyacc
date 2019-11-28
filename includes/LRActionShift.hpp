/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRActionShift.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:31:04 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 14:54:41 by ldedier          ###   ########.fr       */
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

	private:

};

// std::ostream &operator<<(std::ostream &o, LRActionShift const &instance);
#endif