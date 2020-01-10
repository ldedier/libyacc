/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractIntegerTerminal.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 02:13:01 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/10 05:03:23 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTINTEGERTERMINAL_HPP
# define ABSTRACTINTEGERTERMINAL_HPP

# include <iostream>
# include "AbstractTerminal.hpp"

template<typename T, typename C>
class AbstractIntegerTerminal : public AbstractTerminal<T, C>
{
	public:
		AbstractIntegerTerminal(void)
		{

		}

		AbstractIntegerTerminal(std::string identifier) : AbstractTerminal<T, C>(identifier)
		{

		}

		virtual bool staysEligibleForCurrent(std::string & current)
		{
			size_t i;

			i = 0;
			while (i < current.length())
			{
				if (!isdigit(current[i]) && (i != 0 || current[i] != '-' ))
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
				if (!isdigit(current[i]) && (i != 0 || current[i] != '-' ))
					return false;
				i++;
			}
			return current.compare("-");
		}

		virtual Token<T, C> *createToken(std::string tokenContent)
		{
			return new Token<T, C>(*this, stoi(tokenContent));
		}
};

#endif