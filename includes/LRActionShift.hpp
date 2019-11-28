/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRActionShift.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:31:04 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 07:31:44 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRACTIONSHIFT_HPP
# define LRACTIONSHIFT_HPP

# include <iostream>
# include "AbstractLRAction.hpp"

class LRActionShift : public AbstractLRAction
{
	public:
		LRActionShift(void);
		LRActionShift(LRActionShift const &instance);
		LRActionShift &operator=(LRActionShift const &rhs);
		~LRActionShift(void);

	private:

};

std::ostream &operator<<(std::ostream &o, LRActionShift const &instance);
#endif