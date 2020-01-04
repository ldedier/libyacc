/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRActionReduce.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:30:29 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 05:47:44 by ldedier          ###   ########.fr       */
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

		virtual bool execute(LRParser<T, C> &parser, std::deque<Token<T, C> *> &tokens, std::deque<StackItem<T, C> *> & stack) const
		{
			size_t size;
			size_t i;
			StackItem<T, C> *astBuilderItem;
			StackItem<T, C> *stateItem;
			StackItem<T, C> *goalStateItem;
			ASTNode<T, C> *replacingASTNode;
			std::list<ASTNode<T, C>* > childs; 

			typename std::list<ASTNode<T, C > * >::iterator it;

			(void)tokens;
			astBuilderItem = new StackItem<T, C>(_production->getFrom());
			size = _production->getSymbols().size();
			i = 0;
			while (i < size)
			{
				popReduce(astBuilderItem, stack, childs);
				i++;
			}			
			if (_production->isReplacing())
			{
				replacingASTNode = childs.front();
				childs.pop_front();
				delete astBuilderItem->getASTBuilder()->getASTRoot();
				// std::cout << "ref became: " << *(childBuilderItem->getASTBuilder()->getASTRoot());
				astBuilderItem->getASTBuilder()->setASTRoot((replacingASTNode));
			}
			it = childs.begin();
			while (it != childs.end())
			{
				astBuilderItem->getASTBuilder()->getASTRoot()->addChildFront(*it);
				it++;
			}
			stateItem = stack.front();
			LRActionShift<T, C> *shiftAction = dynamic_cast<LRActionShift<T, C> *>(parser.getTables()[stateItem->getState()->getIndex()][_production->getFrom()->getIndex()]);
			goalStateItem = new StackItem<T, C>(shiftAction->getState());
			stack.push_front(astBuilderItem);
			stack.push_front(goalStateItem);
			return (1);
		}

	private:

		void popReduce(StackItem<T, C> *parentItem, std::deque<StackItem<T, C> *> & stack, std::list<ASTNode<T, C>* > &childs) const
		{
			StackItem<T, C> *stateItem;
			StackItem<T, C> *childBuilderItem;
		
			stateItem = stack.front();
			delete stateItem;
			stack.pop_front();
			childBuilderItem = stack.front();
			stack.pop_front();
			
			parentItem->getASTBuilder()->getCSTRoot()->addChildFront(childBuilderItem->getASTBuilder()->getCSTRoot());

			(void)index;
			if (childBuilderItem->getASTBuilder()->getASTRoot()->getSymbol().isRelevant())
			{
				// if (_production->isReplacing())
				// {
				// 	std::cout << *_production << std::endl;
				// 	// std::cout << parentItem->getASTBuilder()->getASTRoot()->getSymbol() << std::endl;
				// 	delete parentItem->getASTBuilder()->getASTRoot();
				// 	std::cout << "ref became: " << *(childBuilderItem->getASTBuilder()->getASTRoot());
				// 	parentItem->getASTBuilder()->setASTRoot((childBuilderItem->getASTBuilder()->getASTRoot()));
				// }
				// else
				// 	parentItem->getASTBuilder()->getASTRoot()->addChildFront(childBuilderItem->getASTBuilder()->getASTRoot());
				childs.push_front(childBuilderItem->getASTBuilder()->getASTRoot());
			}
			else
				delete childBuilderItem->getASTBuilder()->getASTRoot();
		}

		Production<T, C> *_production;
};

// std::ostream &operator<<(std::ostream &o, LRActionReduce const &instance);
#endif