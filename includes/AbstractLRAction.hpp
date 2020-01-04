/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractLRAction.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:28:41 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 22:06:00 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTLRACTION_HPP
# define ABSTRACTLRACTION_HPP

# include <iostream>
// # include "Token.hpp"
// # include "StackItem.hpp"

template<typename T, typename C>
class Token;

template<typename T, typename C>
class StackItem;

template<typename T, typename C>
class LRState;

template<typename T, typename C>
class StackItem;

template<typename T, typename C>
class LRParser;

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
		virtual bool execute(LRParser<T, C> &parser, typename std::deque<Token<T, C> *>::iterator &it,
			std::deque<StackItem<T, C> *> &stack, StackItem<T, C> **rootItem) const = 0;

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