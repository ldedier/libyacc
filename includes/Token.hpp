/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 00:47:40 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/03 17:38:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
# define TOKEN_HPP

# include "AbstractTerminal.hpp"
# include <iostream>

template<typename T, typename C>
class Token
{
	public:
		Token(void)
		{

		}

		Token(AbstractTerminal<T, C> &terminal): _terminal(&terminal)
		{

		}

		Token(AbstractTerminal<T, C> &terminal, int value): _terminal(&terminal), _ivalue(value)
		{

		}

		Token(Token const &instance)
		{
			*this = instance;
		}

		Token &operator=(Token const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}
		
		AbstractTerminal<T, C> *getTerminal()
		{
			return _terminal;
		}

		int getIValue(void)
		{
			return _ivalue;
		}

		virtual ~Token(void)
		{

		}

	private:
		AbstractTerminal<T, C>		*_terminal;
		int							_ivalue;
};

template<typename T, typename C>
std::ostream &operator<<(std::ostream &o, Token<T, C>  &instance)
{
	o << *(instance.getTerminal());
	return o;
}
#endif