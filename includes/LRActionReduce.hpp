/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRActionReduce.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:30:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 14:54:37 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRACTIONREDUCE_HPP
# define LRACTIONREDUCE_HPP

# include <iostream>
# include "AbstractLRAction.hpp"

template<typename T, typename C>
class LRActionReduce : public AbstractLRAction<T, C>
{
	public:
		LRActionReduce(void)
		{
			
		}
		LRActionReduce(LRActionReduce const &instance)
		{
			*this = instance;
		}
		LRActionReduce &operator=(LRActionReduce const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}
		virtual ~LRActionReduce(void)
		{
			
		}

	private:

};

// std::ostream &operator<<(std::ostream &o, LRActionReduce const &instance);
#endif