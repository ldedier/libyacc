/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractLRAction.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:28:41 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 14:53:58 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTLRACTION_HPP
# define ABSTRACTLRACTION_HPP

# include <iostream>

template<typename T, typename C>
class AbstractLRAction
{
	public:
		AbstractLRAction(void)
		{
			
		}
		
		AbstractLRAction(AbstractLRAction<T, C> const &instance)
		{
			*this = instance;
		}

		AbstractLRAction<T, C> &operator=(AbstractLRAction<T, C> const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}
		virtual ~AbstractLRAction(void)
		{
			
		}

	private:

};

// std::ostream &operator<<(std::ostream &o, AbstractLRAction const &instance);
#endif