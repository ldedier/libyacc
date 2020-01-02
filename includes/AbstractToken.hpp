/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractToken.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:14:12 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/01 17:56:43 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTTOKEN_HPP
# define ABSTRACTTOKEN_HPP

# include <iostream>
# include "AbstractSymbol.hpp"
# include "Production.hpp"

template<typename T, typename C>
class AbstractToken : public AbstractSymbol<T, C>
{
	public:
		AbstractToken(void)
		{
			
		}

		AbstractToken(std::string identifier) : AbstractSymbol<T, C>(identifier)
		{
			
		}

		AbstractToken(AbstractToken<T, C> const &instance)
		{
			*this = instance;
		}

		AbstractToken &operator=(AbstractToken<T, C> const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}
		
		virtual ~AbstractToken(void)
		{
			
		}

		virtual void initFirstSet()
		{
			this->_firstSet.addToken(this);
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

// std::ostream &operator<<(std::ostream &o, AbstractToken const &instance);
#endif