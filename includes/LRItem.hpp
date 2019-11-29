/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRItem.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:08:59 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 04:41:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRITEM_HPP
# define LRITEM_HPP

# include <iostream>
# include "Production.hpp"
# include "Production.hpp"

class LRItem
{
	public:
		LRItem(void);
		LRItem(LRItem const &instance);
		LRItem &operator=(LRItem const &rhs);
		~LRItem(void);

	private:
		Production &production;
		AbstractToken &Lookahead;
		//progress


};

std::ostream &operator<<(std::ostream &o, LRItem const &instance);
#endif