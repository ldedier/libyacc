/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractTerminal.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:14:12 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/07 13:03:40 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTTERMINAL_HPP
# define ABSTRACTTERMINAL_HPP

# include <iostream>
# include "AbstractSymbol.hpp"
# include "Production.hpp"

template<typename T, typename C>
class AbstractTerminal : public AbstractSymbol<T, C>
{
	public:
		AbstractTerminal(void)
		{
			
		}

		AbstractTerminal(std::string identifier) : AbstractSymbol<T, C>(identifier)
		{
			
		}

		AbstractTerminal(AbstractTerminal<T, C> const &instance)
		{
			*this = instance;
		}

		AbstractTerminal &operator=(AbstractTerminal<T, C> const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}
		
		virtual ~AbstractTerminal(void)
		{
			
		}

		virtual void initFirstSet()
		{
			this->_firstSet.addTerminal(this);
		}

		virtual std::string color(void) const
		{
			return YACC_BLUE;
		}

		virtual bool isTerminal()
		{
			return true;
		}

	private:
		std::vector<Production<T, C> > _productions; 

};

// std::ostream &operator<<(std::ostream &o, AbstractTerminal const &instance);
#endif