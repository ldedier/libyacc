/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASTNode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:23:18 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 14:54:10 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTNODE_HPP
# define ASTNODE_HPP

# include <iostream>
# include <list>
// # include "AbstractSymbol.hpp"

template<typename T, typename C>
class AbstractSymbol;

template<typename T, typename C>
class ASTNode
{
	public:
		ASTNode(void)
		{
			
		}

		ASTNode(ASTNode<T, C> const &instance)
		{
			*this = instance;
		}

		ASTNode<T, C> &operator=(ASTNode<T, C> const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}

		virtual ~ASTNode(void)
		{
			
		}

	private:
		AbstractSymbol<T, C> & _symbol;
		std::list<ASTNode<T, C> &> _children;
		ASTNode<T, C> *_parent;
};
// std::ostream &operator<<(std::ostream &o, ASTNode const &instance);
#endif