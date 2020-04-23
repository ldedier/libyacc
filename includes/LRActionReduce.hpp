/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRActionReduce.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:30:29 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/25 14:02:30 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRACTIONREDUCE_HPP
# define LRACTIONREDUCE_HPP

# include <iostream>
# include "AbstractLRAction.hpp"
# include "LRActionShift.hpp"


template<typename T, typename C>
class ASTBuilder;

template<typename T, typename C>
class LRActionReduce : public AbstractLRAction<T, C>
{
	public:
		LRActionReduce(void)
		{
			
		}

		LRActionReduce(Production<T, C> &prod) : _production(&prod)
		{
			
		}

		LRActionReduce(LRActionReduce const &instance)
		{
			*this = instance;
		}
		LRActionReduce &operator=(LRActionReduce const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}

		Production<T, C> *getProduction()
		{
			return _production;
		}

		virtual ~LRActionReduce(void)
		{
			
		}

		virtual std::string repr(void) const
		{
			return "REDUCE";
		}
		
		virtual std::string color(void) const
		{
			return YACC_YELLOW;
		}

		virtual bool execute(LRParser<T, C> &parser, typename std::deque<Token<T, C> *>::iterator &tokens_it,
			std::deque<StackItem<T, C> *> & stack, StackItem<T, C> **rootItem) const
		{
			size_t			size;
			size_t			i;
			StackItem<T, C> *parentASTBuilderItem;
			StackItem<T, C> *stateItem;
			StackItem<T, C> *goalStateItem;
			ASTNode<T, C> *replacingASTNode;
			std::list<ASTNode<T, C>* > childs; 
			typename std::list<ASTNode<T, C > * >::iterator it;

			(void)tokens_it;
			parentASTBuilderItem = new StackItem<T, C>(_production->getFrom());
			size = _production->getSymbols().size();
			i = 0;
			while (i < size)
			{
				popReduce(parentASTBuilderItem, stack, childs);
				i++;
			}			
			if (_production->isReplacing())
			{
				replacingASTNode = childs.front();
				childs.pop_front();
				delete parentASTBuilderItem->getASTBuilder()->getASTRoot();
				parentASTBuilderItem->getASTBuilder()->setASTRoot((replacingASTNode));
			
			}
			it = childs.begin();
			while (it != childs.end())
			{
				parentASTBuilderItem->getASTBuilder()->getASTRoot()->addChildBack(*it);
				it++;
			}
			stateItem = stack.front();
			LRActionShift<T, C> *shiftAction = dynamic_cast<LRActionShift<T, C> *>(parser.getTables()[stateItem->getState()->getIndex()][_production->getFrom()->getIndex()]);
			goalStateItem = new StackItem<T, C>(shiftAction->getState());
			
			*rootItem = parentASTBuilderItem;
			stack.push_front(parentASTBuilderItem);
			stack.push_front(goalStateItem);
			return (1);
		}

	private:

		void popReduce(StackItem<T, C> *parentItem, std::deque<StackItem<T, C> *> & stack, std::list<ASTNode<T, C>* > &childs) const
		{
			StackItem<T, C> *stateItem;
			StackItem<T, C> *childBuilderItem;
		
			stateItem = stack.front();
			delete (stateItem);
			stack.pop_front();
			childBuilderItem = stack.front();
			stack.pop_front();
			
			parentItem->getASTBuilder()->getCSTRoot()->addChildFront(childBuilderItem->getASTBuilder()->getCSTRoot());

			if (childBuilderItem->getASTBuilder()->getASTRoot()->getSymbol().isRelevant())
				childs.push_front(childBuilderItem->getASTBuilder()->getASTRoot());
			else
			{
				delete childBuilderItem->getASTBuilder()->getASTRoot();
				childBuilderItem->getASTBuilder()->setASTRoot(nullptr);
			}
			delete childBuilderItem;
		}

		Production<T, C> *_production;
};
#endif
