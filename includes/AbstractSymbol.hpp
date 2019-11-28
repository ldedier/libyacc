/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractSymbol.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 06:48:30 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 07:00:35 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTSYMBOL_HPP
# define ABSTRACTSYMBOL_HPP

# include <iostream>

class AbstractSymbol
{
	public:
		AbstractSymbol(void);
		AbstractSymbol(int index);
		AbstractSymbol(AbstractSymbol const &instance);
		AbstractSymbol &operator=(AbstractSymbol const &rhs);
		~AbstractSymbol(void);

		virtual std::string repr(void) const = 0;
		// virtual std::string traverse(void) const = 0;
		// virtual void (void) const = 0;
	private:
};

std::ostream &operator<<(std::ostream &o, AbstractSymbol const &instance);
#endif