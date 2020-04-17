/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractSeparatorTerminal.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 02:09:09 by ldedier           #+#    #+#             */
/*   Updated: 2020/04/17 03:09:12 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTSEPARATORTERMINAL_HPP
# define ABSTRACTSEPARATORTERMINAL_HPP

# include <iostream>
# include "AbstractTerminal.hpp"

template<typename T, typename C>
class AbstractSeparatorTerminal : public AbstractTerminal<T, C>
{
	public:
		AbstractSeparatorTerminal(void)
		{

		}

		AbstractSeparatorTerminal(std::string identifier) : AbstractTerminal<T, C>(identifier)
		{

		}

		virtual bool staysEligibleForCurrent(std::string & current)
		{
			size_t i;

			i = 0;
			while (i < current.length())
			{
				if (!isblank(current[i]))
					return false;
				i++;
			}
			return true;
		}

		virtual bool isEligibleForCurrent(std::string & current)
		{
			return AbstractSeparatorTerminal::staysEligibleForCurrent(current);
		}

		virtual Token<T, C> *createToken(std::string tokenContent)
		{
			return new Token<T, C>(*this, stoi(tokenContent));
		}

};

#endif