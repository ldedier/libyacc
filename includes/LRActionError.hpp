/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRActionError.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:29:09 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/03 17:57:09 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRACTIONERROR_HPP
# define LRACTIONERROR_HPP

# include <iostream>
# include "AbstractLRAction.hpp"

template<typename T, typename C>
class LRActionError : public AbstractLRAction<T, C>
{
	public:
		LRActionError(void)
		{
			
		}

		LRActionError(LRActionError const &instance)
		{
			*this = instance;
		}

		LRActionError &operator=(LRActionError const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}
		
		virtual ~LRActionError(void)
		{
			
		}

		virtual std::string repr(void) const
		{
			return "ERROR";
		}

		virtual std::string color(void) const
		{
			return YACC_RED;
		}

		virtual bool execute(std::deque<Token<T, C> *> &tokens, std::deque<StackItem<T, C> *> & stack) const
		{
			(void)tokens;
			(void)stack;
			return 1;
		}

	private:

};

// std::ostream &operator<<(std::ostream &o, LRActionError const &instance);
#endif