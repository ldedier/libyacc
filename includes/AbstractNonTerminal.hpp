/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractNonTerminal.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:15:12 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 07:34:53 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTNONTERMINAL_HPP
# define ABSTRACTNONTERMINAL_HPP

# include <iostream>
# include <map>
# include "AbstractSymbol.hpp"
# include "AbstractToken.hpp"

class AbstractNonTerminal : public AbstractSymbol
{
	public:
		AbstractNonTerminal(void);
		AbstractNonTerminal(AbstractNonTerminal const &instance);
		AbstractNonTerminal &operator=(AbstractNonTerminal const &rhs);
		~AbstractNonTerminal(void);

	private:
		std::map<AbstractToken &> _first_set;
};

std::ostream &operator<<(std::ostream &o, AbstractNonTerminal const &instance);
#endif