/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRActionShift.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:31:04 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 22:54:06 by ldedier          ###   ########.fr       */
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

		virtual bool execute(LRParser<T, C> &parser, typename std::deque<Token<T, C> *>::iterator &it,
			std::deque<StackItem<T, C> *> & stack, StackItem<T, C> **rootItem) const
		{
			Token<T, C> *token;
			StackItem <T, C> *astBuilderItem;
			StackItem <T, C> *stateItem;

			(void)parser;
			(void)rootItem;
			token = *it;
			it++;
			astBuilderItem = new StackItem<T, C>(token);
			stateItem = new StackItem<T, C>(*_state);
			stack.push_front(astBuilderItem);
			stack.push_front(stateItem);
			return (1);
		}

		LRState<T, C> &getState(void)
		{
			return *_state;
		}

	private:
		LRState<T, C> *_state;
};
#endif