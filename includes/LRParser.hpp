/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRParser.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:19:48 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/03 01:32:46 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRPARSER_HPP
# define LRPARSER_HPP

# include <iostream>
# include <map>
# include "AbstractLRAction.hpp"
# include "LRState.hpp"
# include "LRActionError.hpp"
# include "LRActionReduce.hpp"
# include "LRActionShift.hpp"
# include "LRActionAccept.hpp"
# include "ASTBuilder.hpp"
# include "Token.hpp"

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
				;
			computeTables();
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

		ASTBuilder<T, C> parse(std::list<Token<T, C> *> &tokens)
		{
			ASTBuilder<T, C> res;
			(void)tokens;
			return res;
		}

		~LRParser(void)
		{

		}

		void debug()
		{
			std::cout << "States:" << std::endl << std::endl;
			int i;
		
			typename std::vector<LRState<T, C> *>::iterator it = _states.begin();
			i = 0;
			while (it != _states.end())
			{
				std::cout << "state #" << i++ << std::endl << std::endl;
				std::cout << *(*it);
				it++;
			}
			printTable();
		}

		void printTable()
		{
			typename std::map<std::string, AbstractSymbol<T, C> *>::iterator it = _cfg->getSymbolsMap().begin();
			std::cout << "\t";
			size_t i = 0;
			while (it != _cfg->getSymbolsMap().end())
			{
				std::cout << *(it->second) << '\t';
				it++;
			}
			std::cout << std::endl;
			while (i < _states.size())
			{
				it = _cfg->getSymbolsMap().begin();
				std::cout << i << "\t";
				while (it != _cfg->getSymbolsMap().end())
				{
					std::cout << *(_tables[i][(it->second)->getIndex()]) << '\t';
					it++;
				}
				std::cout << std::endl;
				i++;
			}
			std::cout << std::endl;
		}

		bool addToStateCheck(LRState<T, C> &destinationState, LRItem<T, C> &item)
		{
			LRItem<T, C> *newItem;
			if (destinationState.hasNextItem(item))
				return false;
			else
			{
				newItem = item.advance();
				destinationState.addItem(newItem);
				return true;
			}
		}

		/*
		** returns the state that contains the appropriate item so that it should be linked by a transition from 'item'
		*/
		LRState<T, C> *getStateFromItem(LRItem<T, C> &item)
		{
			size_t i = 0;

			while (i < _states.size())
			{
				if (_states[i]->hasNextItem(item))
					return _states[i];
				i++;
			}
			return nullptr;
		}

		LRState<T, C > *newStateFromItem(LRItem<T, C> &item)
		{
			LRState<T, C> *newState;
		
			newState = new LRState<T, C>(*item.advance());
			// std::cout << "on add" << *newState << "from" << item ;
			_states.push_back(newState);
			return newState;
		}

		bool computeTransitionsFromItem(LRState<T, C> &state, LRItem<T, C> &item)
		{
			LRState<T, C> *destinationState;

			if ((destinationState = state.getStateByTransition(*(*(item.getProgress())))))
				return addToStateCheck(*destinationState, item);
			else
			{
				if (!(destinationState = getStateFromItem(item)))
					destinationState = newStateFromItem(item);
				state.link(*(*(item.getProgress())), *destinationState);
				return true;
			}
		}

		bool computeTransitions(LRState<T, C> &state)
		{
			bool changes = false;
			typename std::vector<LRItem<T, C> *>::iterator it;
			LRItem<T, C>* currentItem;

			size_t i = 0;
			while (i < state.getItems().size())
			{
				currentItem = state.getItems()[i];
				if (currentItem->getProgress() != currentItem->getProduction().getSymbols().end())
					changes |= computeTransitionsFromItem(state, *currentItem);
				i++;
			}
			return (changes);
		}

		bool computeClosureFromLookahead(LRState<T, C> &state, AbstractNonTerminal<T, C> & nonTerminal, AbstractTerminal<T, C> &lookahead)
		{
			int changes = false;
		
			typename std::vector<Production<T, C> *>::iterator it = nonTerminal.getProductions().begin();
			while (it != nonTerminal.getProductions().end())
			{
				if (!state.hasItem(*(*it), lookahead))
				{
					// std::cout << *(*it) << std::endl;
					// std::cout << lookahead << std::endl;
					state.addNewItem(*(*it), lookahead);
					changes = true;
				}
				it++;
			}
			return changes;
		}

		bool computeClosureFromNonTerminal(LRState<T, C> &state, AbstractNonTerminal<T, C> & nonTerminal, Set<T, C> &set)
		{
			bool changes = false;
			typename std::map<std::string, AbstractTerminal<T, C> * >::iterator it = set.getTokensMap().begin();

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
			size_t i = 0;
			while (i < _states.size())
			{
				changes |= computeState(*(_states[i]));
				i++;
			}
			return changes;
		}

		void initTables()
		{
			size_t i = 0;

			_tables = new AbstractLRAction<T, C> **[_states.size()];
			while (i <_states.size())
			{
				_tables[i] = new AbstractLRAction<T, C> *[_cfg->getSymbolsMap().size()];
				size_t j = 0;
				while (j < _cfg->getSymbolsMap().size())
				{
					_tables[i][j] = new LRActionError<T, C>();
					j++;
				}
				i++;
			}
		}

		void computeReduce(LRState<T, C> &currentState, int stateIndex)
		{
			size_t					j;
			LRItem<T, C>			*currentItem;
			LRActionShift<T, C>		*testShift;
			LRActionReduce<T, C>	*testReduce;

			j = 0;
			while (j < currentState.getItems().size())
			{
				currentItem = currentState.getItems()[j];
				if (currentItem->getProgress() == currentItem->getProduction().getSymbols().end())
				{
					if ((testReduce = dynamic_cast<LRActionReduce<T, C> *>(_tables[stateIndex][currentItem->getLookahead().getIndex()])))
					{
						std::cerr << "Reduce Reduce conflict" << std::endl;
					}
					if ((testShift = dynamic_cast<LRActionShift<T, C> *>(_tables[stateIndex][currentItem->getLookahead().getIndex()])))
					{
						std::cerr << "Shift Reduce conflict" << std::endl;
					}
					if (currentItem->getProduction().getFrom() == _cfg->getStartingSymbol())
					{
						delete _tables[stateIndex][currentItem->getLookahead().getIndex()];
						_tables[stateIndex][currentItem->getLookahead().getIndex()] = new LRActionAccept<T, C>();
					}
					else
					{
						delete _tables[stateIndex][currentItem->getLookahead().getIndex()];
						_tables[stateIndex][currentItem->getLookahead().getIndex()] = new LRActionReduce<T, C>(currentItem->getProduction());
					}
				}
				j++;
			}
		}

		void computeShift(LRState<T, C> &state, int stateIndex)
		{
			LRActionShift<T, C>		*testShift;
			LRActionReduce<T, C>	*testReduce;
			typename std::map<AbstractSymbol<T, C> *, LRState<T, C> *>::iterator it = state.getTransitions().begin();
			
			while (it != state.getTransitions().end())
			{
				if ((testReduce = dynamic_cast<LRActionReduce<T, C> *>(_tables[stateIndex][(it->first)->getIndex()])))
				{
					std::cerr << "Shift Reduce conflict" << std::endl;
				}
				if ((testShift = dynamic_cast<LRActionShift<T, C> *>(_tables[stateIndex][(it->first)->getIndex()])))
				{
					std::cerr << "Shift Shift conflict" << std::endl;
				}
				delete _tables[stateIndex][(it->first)->getIndex()];
				_tables[stateIndex][(it->first)->getIndex()] = new LRActionShift<T, C>(*(it->second));
				it++;
			}
		}

		void computeTables()
		{
			size_t i = 0;
			LRState<T, C> *currentState;
			
			initTables();
			while (i < _states.size())
			{
				currentState = _states[i];
				computeReduce(*currentState, i);
				computeShift(*currentState, i);
				i++;
			}
		}

	private:
		AbstractLRAction<T, C> ***_tables;
		std::vector <LRState<T, C> * > _states;
		AbstractGrammar<T, C> *_cfg;
};
#endif