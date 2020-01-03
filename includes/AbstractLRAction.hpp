/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractLRAction.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:28:41 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/02 23:01:08 by ldedier          ###   ########.fr       */
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

		virtual std::string repr(void) const = 0;
		virtual std::string color(void) const = 0;

	private:

};

template<typename T, typename C>
std::ostream &operator<<(std::ostream &o, AbstractLRAction<T, C> const &instance)
{
	(void)o;
	(void)instance;
	o << instance.color() << instance.repr() << YACC_EOC;
	return o;
}
// std::ostream &operator<<(std::ostream &o, AbstractLRAction const &instance);
#endif