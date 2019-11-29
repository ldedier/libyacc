/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractToken.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:14:12 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 09:16:22 by ldedier          ###   ########.fr       */
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

	private:
		std::vector<Production<T, C> > _productions; 

};

// std::ostream &operator<<(std::ostream &o, AbstractToken const &instance);
#endif