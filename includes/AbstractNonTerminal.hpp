/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractNonTerminal.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:15:12 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 14:51:29 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTNONTERMINAL_HPP
# define ABSTRACTNONTERMINAL_HPP

# include <iostream>
# include <map>
# include "AbstractSymbol.hpp"
# include "AbstractToken.hpp"

template<typename T, typename C>
class AbstractNonTerminal : public AbstractSymbol<T, C>
{
	public:
		AbstractNonTerminal(void)
		{
			
		}
		AbstractNonTerminal(AbstractNonTerminal const &instance)
		{
			*this = instance;
		}
		AbstractNonTerminal &operator=(AbstractNonTerminal const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}
		
		virtual ~AbstractNonTerminal(void)
		{
			
		}

	private:
		std::map<AbstractToken<T, C> &, AbstractToken<T, C> &> _first_set;
};

// std::ostream &operator<<(std::ostream &o, AbstractNonTerminal const &instance);
#endif