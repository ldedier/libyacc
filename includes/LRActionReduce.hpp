/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRActionReduce.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:30:29 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 07:31:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRACTIONREDUCE_HPP
# define LRACTIONREDUCE_HPP

# include <iostream>
# include "AbstractLRAction.hpp"

class LRActionReduce : public AbstractLRAction
{
	public:
		LRActionReduce(void);
		LRActionReduce(LRActionReduce const &instance);
		LRActionReduce &operator=(LRActionReduce const &rhs);
		~LRActionReduce(void);

	private:

};

std::ostream &operator<<(std::ostream &o, LRActionReduce const &instance);
#endif