/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractStringTerminal.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier </var/mail/ldedier>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 12:30:51 by ldedier           #+#    #+#             */
/*   Updated: 2020/04/17 12:30:51 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTSTRINGTERMINAL_HPP
# define ABSTRACTSTRINGTERMINAL_HPP

# include <iostream>
# include "AbstractTerminal.hpp"

template<typename T, typename C>
class AbstractStringTerminal : public AbstractTerminal<T, C>
{
	public:
		AbstractStringTerminal(void)
		{

		}

		AbstractStringTerminal(std::string identifier) : AbstractTerminal<T, C>(identifier)
		{

		}

		virtual bool staysEligibleForCurrent(std::string & current)
		{
			size_t i;

			i = 0;
			while (i < current.length())
			{
				if (isblank(current[i]))
					return false;
				i++;
			}
			return true;
		}

		virtual bool isEligibleForCurrent(std::string & current)
		{
			return AbstractStringTerminal::staysEligibleForCurrent(current);
		}

		virtual Token<T, C> *createToken(std::string tokenContent)
		{
			return new Token<T, C>(*this, tokenContent);
		}
};

#endif
