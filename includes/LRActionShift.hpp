/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRActionShift.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:31:04 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 04:48:02 by ldedier          ###   ########.fr       */
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

		virtual bool execute(LRParser<T, C> &parser, std::deque<Token<T, C> *> &tokens, std::deque<StackItem<T, C> *> & stack) const
		{
			Token<T, C> *token;
			StackItem <T, C> *astBuilderItem;
			StackItem <T, C> *stateItem;

			(void)parser;
			token = tokens.front();
			tokens.pop_front();
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

// std::ostream &operator<<(std::ostream &o, LRActionShift const &instance);
#endif