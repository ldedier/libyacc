/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractUnsignedIntegerTerminal.hpp                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 04:46:15 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/10 05:02:29 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTUNSIGNEDINTEGERTERMINAL_HPP
# define ABSTRACTUNSIGNEDINTEGERTERMINAL_HPP

# include <iostream>
# include "AbstractTerminal.hpp"

template<typename T, typename C>
class AbstractUnsignedIntegerTerminal : public AbstractTerminal<T, C>
{
	public:
		AbstractUnsignedIntegerTerminal(void)
		{

		}

		AbstractUnsignedIntegerTerminal(std::string identifier) : AbstractTerminal<T, C>(identifier)
		{

		}

		virtual bool staysEligibleForCurrent(std::string & current)
		{
			size_t i;

			i = 0;
			while (i < current.length())
			{
				if (!isdigit(current[i]))
					return false;
				i++;
			}
			return true;
		}

		virtual bool isEligibleForCurrent(std::string & current)
		{
			size_t i;

			i = 0;
			while (i < current.length())
			{
				if (!isdigit(current[i]))
					return false;
				i++;
			}
			return true;
		}

		virtual Token<T, C> *createToken(std::string tokenContent)
		{
			return new Token<T, C>(*this, stoi(tokenContent));
		}

};

#endif