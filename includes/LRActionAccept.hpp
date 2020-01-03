/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRActionAccept.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:29:58 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/03 17:57:02 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRACTIONACCEPT_HPP
# define LRACTIONACCEPT_HPP

# include <iostream>
# include "AbstractLRAction.hpp"

template<typename T, typename C>
class LRActionAccept : public AbstractLRAction<T, C>
{
	public:
		LRActionAccept(void)
		{
			
		}
		
		LRActionAccept(LRActionAccept const &instance)
		{
			*this = instance;
		}
		
		LRActionAccept<T, C> &operator=(LRActionAccept<T, C> const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}

		virtual ~LRActionAccept(void)
		{
			
		}

		virtual std::string repr(void) const
		{
			return "ACCEPT";
		}

		virtual std::string color(void) const
		{
			return YACC_ACCEPT;
		}

		virtual bool execute(std::deque<Token<T, C> *> &tokens, std::deque<StackItem<T, C> *> & stack) const
		{
			(void)tokens;
			(void)stack;
			return (0);
		}

	private:

};

// std::ostream &operator<<(std::ostream &o, LRActionAccept const &instance);
#endif