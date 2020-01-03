/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASTBuilder.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 08:48:51 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/03 17:35:20 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTBUILDER_HPP
# define ASTBUILDER_HPP

# include <iostream>
# include "ASTNode.hpp"

template<typename T, typename C>
class Token;

template<typename T, typename C>
class ASTBuilder
{
	public:
		ASTBuilder(void)
		{
			
		}

		ASTBuilder(Token<T, C> *token) : _astRoot(new ASTNode<T, C>(token)), _cstRoot(new ASTNode<T, C>(token))
		{

		}

		ASTBuilder(ASTBuilder const &instance)
		{
			*this = instance;
		}
		
		ASTBuilder &operator=(ASTBuilder const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}
		
		virtual ~ASTBuilder(void)
		{
			
		}

	private:
		ASTNode<T, C> * _astRoot;
		ASTNode<T, C> * _cstRoot;
};

// std::ostream &operator<<(std::ostream &o, ASTBuilder const &instance);
#endif