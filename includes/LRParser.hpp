/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRParser.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:19:48 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/02 02:14:32 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRPARSER_HPP
# define LRPARSER_HPP

# include <iostream>
# include <map>
# include "AbstractLRAction.hpp"
# include "LRState.hpp"
# include "ASTBuilder.hpp"

template<typename T, typename C>
class LRParser
{
	public:
		LRParser(void)
		{

		}

		LRParser(AbstractGrammar<T, C> & cfg) : _cfg(&cfg)
		{
			LRState<T, C> *firstState;
		
			firstState = new LRState<T, C>(cfg);
			_states.push_back(firstState);
			while (computeAllStates())
			{
			}
			this->debug();
		}

		LRParser(LRParser const &instance)
		{
			*this = instance;
		}

		LRParser &operator=(LRParser const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}

		ASTBuilder<T, C> parse(void)
		{
			ASTBuilder<T, C> res;
			return res;
		}

		~LRParser(void)
		{

		}

		void debug()
		{
			std::cout << "States:" << std::endl << std::endl;
			int i;
		
			typename std::list <LRState<T, C> *>::iterator it = _states.begin();
			i = 0;
			while (it != _states.end())
			{
				std::cout << "state #" << i++ << std::endl << std::endl;
				std::cout << *(*it);
				it++;
			}
		}

		bool computeTransitions(LRState<T, C> &state)
		{
			bool changes = false;
			(void)state;
			return (changes);
		}

		bool computeClosureFromLookahead(LRState<T, C> &state, AbstractNonTerminal<T, C> & nonTerminal, AbstractToken<T, C> &lookahead)
		{
			int changes = false;
		
			typename std::vector<Production<T, C> *>::iterator it = nonTerminal.getProductions().begin();
			while (it != nonTerminal.getProductions().end())
			{
				if (!state.hasItem(*(*it), lookahead))
				{
					// std::cout << *(*it) << std::endl;
					// std::cout << lookahead << std::endl;
					state.addItem(*(*it), lookahead);
					changes = true;
				}
				it++;
			}
			return changes;
		}

		bool computeClosureFromNonTerminal(LRState<T, C> &state, AbstractNonTerminal<T, C> & nonTerminal, Set<T, C> &set)
		{
			bool changes = false;
			typename std::map<std::string, AbstractToken<T, C> * >::iterator it = set.getTokensMap().begin();

			while (it != set.getTokensMap().end())
			{
				changes |= computeClosureFromLookahead(state, nonTerminal, *(it->second));
				it++;
			}
			if (set.hasEpsilon())
				changes |= computeClosureFromLookahead(state, nonTerminal, *_cfg->getEndOfInput());
			return changes;
		}

		bool computeClosureFromItem(LRState<T, C> &state, LRItem<T, C> &item)
		{
			bool changes = false;
			typename std::vector<AbstractSymbol<T, C> *>::const_iterator it;
			AbstractSymbol<T, C> *symbol;
			AbstractNonTerminal<T, C> *nonTerminal;
	
			it = item.getProgress();
			if (it != item.getProduction().getSymbols().end())
			{
				symbol = *it;
				if ((nonTerminal = dynamic_cast<AbstractNonTerminal<T, C> * >(symbol)))
				{
					Set<T, C> set = Set<T, C>(*_cfg, ++it, item.getProduction().getSymbols(), item.getLookahead());
					// std::cout << "set: \n";
					// std::cout << set;
					changes |= computeClosureFromNonTerminal(state, *nonTerminal, set);
				}
				it++;
			}
			item.setParsed(!changes);
			return changes;
		}

		bool computeClosure(LRState<T, C> &state)
		{
			bool changes = false;
			typename std::vector<LRItem<T, C> *>::iterator it;
			LRItem<T, C>* currentItem;
			size_t i = 0;
			while (i < state.getItems().size())
			{
				currentItem = state.getItems()[i];
				if (!currentItem->isParsed())
					changes |= computeClosureFromItem(state, *currentItem);
				i++;
			}
			return (changes);
		}

		bool computeState(LRState <T, C> & state)
		{
			bool changes = false;
		
			changes |= computeClosure(state);
			changes |= computeTransitions(state);
			return changes;
		}

		bool computeAllStates()
		{
			bool changes = false;

			typename std::list <LRState<T, C> * >::iterator it = _states.begin();
		
			while (it != _states.end())
			{
				changes |= computeState(*(*it));
				it++;
			}
			return changes;
		}

	private:
		std::vector < std::vector <AbstractLRAction<T, C> > > _tables;
		std::list <LRState<T, C> * > _states;
		AbstractGrammar<T, C> *_cfg;

};
#endif