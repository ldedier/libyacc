/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRActionError.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:29:09 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 07:29:49 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRACTIONERROR_HPP
# define LRACTIONERROR_HPP

# include <iostream>
# include "AbstractLRAction.hpp"

class LRActionError : public AbstractLRAction
{
	public:
		LRActionError(void);
		LRActionError(LRActionError const &instance);
		LRActionError &operator=(LRActionError const &rhs);
		~LRActionError(void);

	private:

};

std::ostream &operator<<(std::ostream &o, LRActionError const &instance);
#endif