/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractLRAction.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:28:41 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 07:28:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTLRACTION_HPP
# define ABSTRACTLRACTION_HPP

# include <iostream>

class AbstractLRAction
{
	public:
		AbstractLRAction(void);
		AbstractLRAction(AbstractLRAction const &instance);
		AbstractLRAction &operator=(AbstractLRAction const &rhs);
		~AbstractLRAction(void);

	private:

};

std::ostream &operator<<(std::ostream &o, AbstractLRAction const &instance);
#endif