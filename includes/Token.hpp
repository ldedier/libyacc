/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 00:47:40 by ldedier           #+#    #+#             */
/*   Updated: 2020/05/03 21:28:22 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
# define TOKEN_HPP

# include "AbstractTerminal.hpp"
# include <iostream>

typedef enum	e_tokenType
{
	E_TOKEN_TYPE_NONE,
	E_TOKEN_TYPE_STRING,
	E_TOKEN_TYPE_CHAR,
	E_TOKEN_TYPE_INT,
	E_TOKEN_TYPE_FLOAT,
	E_TOKEN_TYPE_DOUBLE,
	E_TOKEN_TYPE_LONG
}				t_tokenType;



union	u_tokenUnion
{
	char		c;
	int			ival;
	float		fval;
	double		dval;
	long		lval;

};

template<typename T, typename C>
class Token
{
	
	public:

		Token(void)
		{

		}

		Token(AbstractTerminal<T, C> &terminal): _terminal(&terminal), _type(E_TOKEN_TYPE_NONE)
		{

		}

		Token(AbstractTerminal<T, C> &terminal, int value): _terminal(&terminal), _type(E_TOKEN_TYPE_INT)
		{
			_tokenUnion.ival = value;
		}

		Token(AbstractTerminal<T, C> &terminal, double value): _terminal(&terminal), _type(E_TOKEN_TYPE_DOUBLE)
		{
			_tokenUnion.dval = value;
		}

		Token(AbstractTerminal<T, C> &terminal, float value): _terminal(&terminal), _type(E_TOKEN_TYPE_FLOAT)
		{
			_tokenUnion.fval = value;
		}

		Token(AbstractTerminal<T, C> &terminal, long value): _terminal(&terminal), _type(E_TOKEN_TYPE_LONG)
		{
			_tokenUnion.lval = value;
		}

		Token(AbstractTerminal<T, C> &terminal, std::string value): _terminal(&terminal), _type(E_TOKEN_TYPE_STRING)
		{
			_str = value;
		}

		Token(AbstractTerminal<T, C> &terminal, char c): _terminal(&terminal), _type(E_TOKEN_TYPE_CHAR)
		{
			_tokenUnion.c = c;
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

		int getIntValue(void)
		{
			return _tokenUnion.ival;
		}

		float getFloatValue(void)
		{
			return _tokenUnion.fval;
		}

		double getDoubleValue(void)
		{
			return _tokenUnion.dval;
		}

		std::string getStringValue(void)
		{
			return _str;
		}

		long getLongValue(void)
		{
			return _tokenUnion.lval;
		}

		char getCharValue(void)
		{
			return _tokenUnion.c;
		}

		t_tokenType getType()
		{
			return _type;
		}

		virtual ~Token(void)
		{

		}

		virtual std::ostream &repr(std::ostream &o) 
		{
			
			if (getType() == E_TOKEN_TYPE_NONE)
				return o;
			o << YACC_YELLOW << " (";
			if (getType() == E_TOKEN_TYPE_CHAR)
			{
				o << getCharValue();
			}
			else if (getType() == E_TOKEN_TYPE_DOUBLE)
			{
				o << getDoubleValue();
			}
			else if (getType() == E_TOKEN_TYPE_FLOAT)
			{
				o << getFloatValue();
			}
			else if (getType() == E_TOKEN_TYPE_INT)
			{
				o << getIntValue();
			}
			else if (getType() == E_TOKEN_TYPE_LONG)
			{
				o << getLongValue();
			}
			else if (getType() == E_TOKEN_TYPE_STRING)
			{
				o << getStringValue();
			}
			o << ")" << YACC_EOC;
			return o;
		}

	private:
		AbstractTerminal<T, C>		*_terminal;
		u_tokenUnion				_tokenUnion;
		t_tokenType					_type;
		std::string					_str;
};

template<typename T, typename C>
std::ostream &operator<<(std::ostream &o, Token<T, C>  &instance)
{
	o << *(instance.getTerminal());
	instance.repr(o);
	return o;
}
#endif
