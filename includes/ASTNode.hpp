/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASTNode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:23:18 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 23:54:16 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTNODE_HPP
# define ASTNODE_HPP

# include <iostream>
# include <deque>
# include <list>
// # include "AbstractSymbol.hpp"

template<typename T, typename C>
class AbstractSymbol;

// template<typename T, typename C>
// class AbstractTerminal;

template<typename T, typename C>
class AbstractNonTerminal;

template<typename T, typename C>
class Token;

template<typename T, typename C>
class ASTNode
{
	public:
		ASTNode(void): _parent(nullptr)
		{
			
		}

		ASTNode(Token<T, C> *token): _symbol(*token->getTerminal()), _token(token), _parent(nullptr)
		{

		}

		ASTNode(AbstractNonTerminal<T, C> *nonTerminal): _symbol(*nonTerminal), _token(nullptr), _parent(nullptr)
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
			typename std::deque<ASTNode<T, C> *>::iterator it = _children.begin();
		
			while (it != _children.end())
			{
				delete *it;
				it++;
			}
		}

		void addChildFront(ASTNode<T, C> *node)
		{
			node->_parent = this;
			_children.push_front(node);
		}

		void addChildBack(ASTNode<T, C> *node)
		{
			node->_parent = this;
			_children.push_back(node);
		}

		void debug(std::ostream &o, size_t depth)
		{
			typename std::deque<ASTNode<T, C> *>::iterator it = _children.begin();

			int i = 0;
			int j = 0;
			if (_token)
				o << *_token << std::endl;
			else
				o << _symbol << std::endl;
			i = 1;
			while (it != _children.end())
			{
				j = 0;
				while (j < (int)depth)
				{
					o << "| ";
					j++;
				}
				o << "o child #" << i++  << " : ";
				(*it)->debug(o, depth + 1);
				it++;
			} 
		}

		AbstractSymbol<T, C> & getSymbol()
		{
			return _symbol;
		}

		ASTNode<T, C> *getParent()
		{
			return _parent;
		}

		std::deque<ASTNode<T, C> *> &getChildren(void)
		{
			return _children;
		}

		ASTNode<T, C> * getChild(int index)
		{
			return _children[index];
		}

		std::string getChildIdentifier(int index)
		{
			return _children[index]->getSymbol().getIdentifier();
		}

		T getTraversed(C context)
		{
			return _symbol.traverse(*this, context);
		}

		Token<T, C> *getToken()
		{
			return _token;
		}

	private:
		AbstractSymbol<T, C> & _symbol;
		Token<T, C> * _token;
		std::deque<ASTNode<T, C> *> _children;
		ASTNode<T, C> *_parent;
};


template<typename T, typename C>
std::ostream &operator<<(std::ostream &o, ASTNode<T, C>  &instance)
{
	instance.debug(o, 0);
	return o;
}
#endif