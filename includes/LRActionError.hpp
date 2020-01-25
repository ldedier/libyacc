/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRActionError.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:29:09 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/24 21:39:33 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRACTIONERROR_HPP
# define LRACTIONERROR_HPP

# include <iostream>
# include "AbstractLRAction.hpp"

template<typename T, typename C>
class LRActionError : public AbstractLRAction<T, C>
{
	public:
		LRActionError(void)
		{
			
		}

		LRActionError(LRActionError const &instance)
		{
			*this = instance;
		}

		LRActionError &operator=(LRActionError const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}
		
		virtual ~LRActionError(void)
		{
			
		}

		virtual std::string repr(void) const
		{
			return "ERROR";
		}

		virtual std::string color(void) const
		{
			return YACC_RED;
		}

		virtual bool execute(LRParser<T, C> &parser, typename std::deque<Token<T, C> *>::iterator &it,
			std::deque<StackItem<T, C> *> & stack, StackItem<T, C> **rootItem) const
		{
			(void)it;
			(void)parser;
			(void)stack;
			(void)rootItem;
			throw LRActionError::SyntaxErrorException();
		}

		class SyntaxErrorException : public std::exception
		{
			public:
				SyntaxErrorException(void) {}
				
				SyntaxErrorException(SyntaxErrorException const &instance)
				{
					*this = instance;
				}

				SyntaxErrorException &operator=(SyntaxErrorException const &rhs)
				{
					static_cast<void>(rhs);
					return *this;
				}

				virtual ~SyntaxErrorException(void) throw()
				{

				}

				virtual const char *what() const throw()
				{
					return "Syntax error";
				}

			private:
		};

	private:

};
#endif