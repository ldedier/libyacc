/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRActionAccept.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:29:58 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 07:31:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRACTIONACCEPT_HPP
# define LRACTIONACCEPT_HPP

# include <iostream>
# include "AbstractLRAction.hpp"

class LRActionAccept : public AbstractLRAction
{
	public:
		LRActionAccept(void);
		LRActionAccept(LRActionAccept const &instance);
		LRActionAccept &operator=(LRActionAccept const &rhs);
		~LRActionAccept(void);

	private:

};

std::ostream &operator<<(std::ostream &o, LRActionAccept const &instance);
#endif