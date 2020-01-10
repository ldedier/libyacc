/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EndOfInput.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 08:40:39 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/10 01:52:49 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENDOFINPUT_HPP
# define ENDOFINPUT_HPP

# include <iostream>
# include "AbstractTerminal.hpp"

template<typename T, typename C>
class EndOfInput : public AbstractTerminal<T, C>
{
	public:
		EndOfInput(void) : AbstractTerminal<T, C>("_EOI_")
		{
			
		}
		
		EndOfInput(EndOfInput const &instance)
		{
			*this = instance;
		}
		EndOfInput &operator=(EndOfInput const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}

		T traverse(ASTNode<T, C> & node, C dummy) const
		{
			static_cast<void>(node);
			static_cast<void>(dummy);
			throw std::exception();
		}

		virtual ~EndOfInput(void)
		{
			
		}

		virtual bool staysEligibleForCurrent(std::string & current)
		{
			static_cast<void>(current);
			return false;
		}

		virtual bool isEligibleForCurrent(std::string & current)
		{
			static_cast<void>(current);
			return false;
		}

	private:

};

// std::ostream &operator<<(std::ostream &o, EndOfInput const &instance);
#endif