/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRActionError.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:29:09 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 14:53:53 by ldedier          ###   ########.fr       */
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

	private:

};

// std::ostream &operator<<(std::ostream &o, LRActionError const &instance);
#endif