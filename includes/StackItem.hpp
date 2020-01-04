/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StackItem.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:33:34 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 03:04:04 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACKITEM_HPP
# define STACKITEM_HPP

# include <iostream>

typedef enum	e_stackItemType
{
	E_STACK_ITEM_STATE,
	E_STACK_ITEM_AST_BUILDER,
}				t_stackItemType;

template <typename T, typename C>
union	u_stackItemUnion
{
	LRState<T, C> *state;
	ASTBuilder<T, C> *builder;
};

template<typename T, typename C>
class StackItem
{
	public:
		StackItem(void)
		{

		}

		StackItem(LRState<T, C> &state) : _type(E_STACK_ITEM_STATE)
		{
			_itemUnion.state = &state;
		}

		StackItem(ASTBuilder<T, C> &astBuilder) : _type(E_STACK_ITEM_AST_BUILDER)
		{
			_itemUnion.builder = &astBuilder;
		}

		StackItem(Token<T, C> *token) : _type(E_STACK_ITEM_AST_BUILDER)
		{
			_itemUnion.builder = new ASTBuilder<T, C>(token);
		}

		StackItem(AbstractNonTerminal<T, C> *nonTerminal) : _type(E_STACK_ITEM_AST_BUILDER)
		{
			_itemUnion.builder = new ASTBuilder<T, C>(nonTerminal);
		}

		StackItem(StackItem const &instance)
		{
			*this = instance;
		}

		StackItem &operator=(StackItem const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}

		virtual ~StackItem(void)
		{

		}

		LRState<T, C> * getState()
		{
			return _itemUnion.state;
		}

		ASTBuilder<T, C> * getASTBuilder()
		{
			return _itemUnion.builder;
		}

		t_stackItemType getType()
		{
			return _type;
		}

	private:
		u_stackItemUnion<T, C>	_itemUnion;
		t_stackItemType			_type;
};

template<typename T, typename C>
std::ostream &operator<<(std::ostream &o, StackItem<T, C>  &instance)
{
	static_cast<void>(instance);
	if (instance.getType() == E_STACK_ITEM_AST_BUILDER)
	{
		o << *instance.getASTBuilder();
	}
	else
	{
		o << *instance.getState();
	}	
	return o;
}
#endif