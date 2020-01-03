/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRActionError.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:29:09 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/02 23:01:45 by ldedier          ###   ########.fr       */
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

	private:

};

// std::ostream &operator<<(std::ostream &o, LRActionError const &instance);
#endif