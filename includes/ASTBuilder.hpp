/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASTBuilder.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 08:48:51 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 21:47:10 by ldedier          ###   ########.fr       */
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

		ASTBuilder(AbstractNonTerminal<T, C> *nonTerminal) : _astRoot(new ASTNode<T, C>(nonTerminal)), _cstRoot(new ASTNode<T, C>(nonTerminal))
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
			delete _astRoot;
			delete _cstRoot;
		}

		ASTNode<T, C> *getASTRoot()
		{
			return _astRoot;
		}

		ASTNode<T, C> *getCSTRoot()
		{
			return _cstRoot;
		}

		void setASTRoot(ASTNode<T, C> *astRoot)
		{
			_astRoot = astRoot;
		}

	private:
		ASTNode<T, C> * _astRoot;
		ASTNode<T, C> * _cstRoot;
};

template<typename T, typename C>
std::ostream &operator<<(std::ostream &o, ASTBuilder<T, C>  &instance)
{
	o << "AST:" << std::endl;
	o << *(instance.getASTRoot()) << std::endl;

	o << "CST:" << std::endl;
	o << *(instance.getCSTRoot())<< std::endl;
	return o;
}
#endif