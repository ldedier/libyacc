/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractGrammar.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:09:59 by ldedier           #+#    #+#             */
/*   Updated: 2019/12/30 12:58:20 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTGRAMMAR_HPP
# define ABSTRACTGRAMMAR_HPP

# include <iostream>
# include "AbstractSymbol.hpp"
# include "AbstractToken.hpp"
# include "AbstractNonTerminal.hpp"
# include "Start.hpp"
# include "EndOfInput.hpp"

template<typename T, typename C>
class AbstractGrammar
{
	public:
		
		AbstractGrammar(void) {}

		AbstractGrammar(AbstractNonTerminal <T, C> *startGrammarSymbol) : _startGrammarSymbol(startGrammarSymbol)
		{
			addNonTerminal(_startGrammarSymbol);
			_startSymbol = new Start<T, C>();
			_endOfInput = new EndOfInput<T, C>();
		}

		AbstractGrammar(AbstractGrammar<T, C> const &instance)
		{
			*this = instance;
		}
	
		AbstractGrammar<T, C> &operator=(AbstractGrammar<T, C> const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}

		virtual ~AbstractGrammar(void)
		{
			
		}

		AbstractSymbol<T, C> *getSymbol(std::string identifier)
		{
			typename std::map<std::string, AbstractSymbol<T, C> *>::iterator it = _symbolsMap.find(identifier);
			
			if (it != _symbolsMap.end()) {
				return it->second;
			}
			else {
				std::cout << "not found: " << identifier << std::endl;
				throw std::exception();
			}
		}

		void debugGrammar()
		{
			typename std::vector<AbstractNonTerminal<T, C> * >::iterator it = _nonTerminals.begin();

		
			std::cout << "Productions: " << std::endl << std::endl;

			_startSymbol->printProductions();
			
			while (it != _nonTerminals.end())
			{
				(*it)->printProductions();
				it++;
			}

			std::cout << "First Sets: " << std::endl << std::endl;
			it = _nonTerminals.begin();
			while (it != _nonTerminals.end())
			{
				(*it)->printFirstSet();
				it++;
			}
		}

	public:

		AbstractNonTerminal<T, C> * getGrammarStartingSymbol()
		{
			return _startGrammarSymbol;
		}

		EndOfInput<T, C> * getEndOfInput()
		{
			return _endOfInput;
		}

		Start<T, C> * getStartingSymbol()
		{
			return _startSymbol;
		}

	protected:

		void addNonTerminal(AbstractNonTerminal<T, C> * nonTerminal)
		{
			_nonTerminals.push_back(nonTerminal);
			addSymbol(nonTerminal);
		}
		
		void addToken(AbstractToken<T, C> *token)
		{
			_tokens.push_back(token);
			addSymbol(token);
		}

		void computeProductions()
		{
			unsigned long i;

			i = 0;
			while (i < this->_nonTerminals.size())
			{
				this->_nonTerminals[i]->computeProductions(*this);
				i++;
			}
			_startSymbol->computeProductions(*this);
		}

		int addToFirstSetByProductionFromSymbol(AbstractNonTerminal<T, C> &nonTerminal, AbstractSymbol<T, C>* symbol)
		{
			int changes = 0;
			typename std::map<std::string, AbstractToken<T, C> * >::iterator it = symbol->getFirstSet().getTokensMap().begin();

			while (it != symbol->getFirstSet().getTokensMap().end()) //iterate through first sets of symbol
			{
				if (nonTerminal.getFirstSet().getTokensMap().find(it->first) == nonTerminal.getFirstSet().getTokensMap().end()) // check if is not in nonterminal
				{
					nonTerminal.getFirstSet().getTokensMap().insert(std::pair <std::string, AbstractToken<T, C> *>(it->first, it->second));
					changes |= 1;
				}
				it++;
			}
			return changes;
		}

		int addToFirstSetByProduction(Production<T, C> *production, AbstractNonTerminal<T, C> &nonTerminal)
		{
			int changes = 0;
			typename std::vector<AbstractSymbol<T, C> *>::const_iterator it = production->getSymbols().begin();
			
			while (it != production->getSymbols().end())
			{
				changes |= addToFirstSetByProductionFromSymbol(nonTerminal, *it);
				if (!(*it)->getFirstSet().hasEpsilon())
					return (changes);
			}
			if (!nonTerminal.getFirstSet().hasEpsilon())
			{
				nonTerminal.getFirstSet().setEpsilon();
				return (1);
			}
			return (changes);
		}

		int addFirstSetIteration(AbstractNonTerminal<T, C> & nonTerminal)
		{
			int changes = 0;
			typename std::vector<Production<T, C> * >::const_iterator it = nonTerminal.getProductions().begin();
			while (it != nonTerminal.getProductions().end())
			{
				changes |= addToFirstSetByProduction(*it, nonTerminal);
				it++;
			}
			return changes;
		}

		int computeFirstSetsIteration()
		{
			int changes = 0;
			typename std::vector<AbstractNonTerminal<T, C> * >::iterator it = _nonTerminals.begin();
		
			while (it != _nonTerminals.end())
			{
				changes |= addFirstSetIteration(*(*it));
				it++;
			}
			return changes;
		}

		void computeFirstSets(void)
		{
			typename std::map<std::string, AbstractSymbol<T, C> *>::iterator it = _symbolsMap.begin();
			
			while (it != _symbolsMap.end()) {
				(it->second)->initFirstSet();
				it++;
			}
			while (computeFirstSetsIteration())
				;
		}

		void addSymbol(AbstractSymbol <T, C> *symbol)
		{
			_symbolsMap.insert(std::pair <std::string, AbstractSymbol<T, C> *>(symbol->getIdentifier(), symbol));
		}



		virtual void fillGrammar() = 0;

		Start<T, C> * _startSymbol;
		AbstractNonTerminal<T, C> * _startGrammarSymbol;
		EndOfInput<T, C> * _endOfInput;

		std::vector<AbstractNonTerminal<T, C> *> _nonTerminals;
		std::vector<AbstractToken<T, C> *> _tokens;
		
		std::map<std::string, AbstractSymbol<T, C> *> _symbolsMap;

};

// std::ostream &operator<<(std::ostream &o, AbstractGrammar const &instance);
#endif