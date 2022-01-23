/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractGrammar.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:09:59 by ldedier           #+#    #+#             */
/*   Updated: 2022/01/23 09:17:59 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTGRAMMAR_HPP
# define ABSTRACTGRAMMAR_HPP

# include <iostream>
# include <deque>
# include "AbstractSymbol.hpp"
# include "AbstractTerminal.hpp"
# include "AbstractNonTerminal.hpp"
# include "Start.hpp"
# include "EndOfInput.hpp"
# include "Token.hpp"

template<typename T, typename C>
class AbstractGrammar
{
	public:

		AbstractGrammar(void) {}

		AbstractGrammar(AbstractNonTerminal <T, C> *startGrammarSymbol) : _startGrammarSymbol(startGrammarSymbol), _index(0),
			_blankAsDelimiters(true)
		{
			addNonTerminal(_startGrammarSymbol);
			_startSymbol = new Start<T, C>();
			_endOfInput = new EndOfInput<T, C>();
			addTerminal(_endOfInput);
		}

		AbstractGrammar(AbstractNonTerminal <T, C> *startGrammarSymbol, bool blankAsDelimiter) : _startGrammarSymbol(startGrammarSymbol), _index(0),
			_blankAsDelimiters(blankAsDelimiter)
		{
			addNonTerminal(_startGrammarSymbol);
			_startSymbol = new Start<T, C>();
			_endOfInput = new EndOfInput<T, C>();
			addTerminal(_endOfInput);
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
			typename std::map<std::string, AbstractSymbol<T, C> *>::iterator it = _symbolsMap.begin();

			while (it != _symbolsMap.end())
			{
				delete it->second;
				it++;
			}
			delete _startSymbol;
		}

		void debug(bool printFirstSets)
		{
			typename std::vector<AbstractNonTerminal<T, C> * >::iterator it = _nonTerminals.begin();

			std::cout << "Productions: " << std::endl << std::endl;
			_startSymbol->printProductions();
			while (it != _nonTerminals.end())
			{
				(*it)->printProductions();
				it++;
			}
			if (printFirstSets)
			{

				std::cout << "First Sets: " << std::endl << std::endl;
				it = _nonTerminals.begin();
				while (it != _nonTerminals.end())
				{
					(*it)->printFirstSet();
					it++;
				}
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

		std::map<std::string, AbstractSymbol<T, C> *> &getSymbolsMap()
		{
			return _symbolsMap;
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

		AbstractTerminal<T, C> *getTerminal(std::string identifier)
		{
			AbstractTerminal<T, C> *res;
			typename std::map<std::string, AbstractSymbol<T, C> *>::iterator it = _symbolsMap.find(identifier);

			if (it != _symbolsMap.end())
			{
				if (!(res = dynamic_cast<AbstractTerminal<T,C> *>(it->second)))
				{
					std::cout << "not found token: " << identifier << std::endl;
					throw std::exception();
				}
				return res;
			}
			else
			{
				std::cout << "not found: " << identifier << std::endl;
				throw std::exception();
			}
		}

		std::deque<Token<T, C> *> lex(bool stopAtNewline, std::istream & istream)
		{
			std::deque<Token<T, C> *> res;

			res = innerLex(stopAtNewline, istream);
			res.push_back(new Token<T, C>(*(getTerminal("_EOI_"))));
			return res;
		}

		class LexicalErrorException : public std::exception
		{
			public:

				LexicalErrorException(void): _reason("lexical error")
				{

				}

				LexicalErrorException(const std::string current) : _reason("lexical error: \"" + current + "\" can't refer to a token belonging to this grammar")
				{

				}

				LexicalErrorException(LexicalErrorException const &instance)
				{
					*this = instance;
				}

				LexicalErrorException &operator=(LexicalErrorException const &rhs)
				{
					static_cast<void>(rhs);
					return *this;
				}

				virtual ~LexicalErrorException(void) throw()
				{

				}

				virtual const char *what() const throw()
				{
					return (this->_reason.c_str());
				}

			private:
				const std::string _reason;
		};

	protected:

		void addNonTerminal(AbstractNonTerminal<T, C> * nonTerminal)
		{
			_nonTerminals.push_back(nonTerminal);
			addSymbol(nonTerminal);
		}

		void addTerminal(AbstractTerminal<T, C> *terminal)
		{
			_tokens.push_back(terminal);
			addSymbol(terminal);
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
			typename std::map<std::string, AbstractTerminal<T, C> * >::iterator it = symbol->getFirstSet().getTokensMap().begin();

			while (it != symbol->getFirstSet().getTokensMap().end()) //iterate through first sets of symbol
			{
				if (nonTerminal.getFirstSet().getTokensMap().find(it->first) == nonTerminal.getFirstSet().getTokensMap().end()) // check if is not in nonterminal
				{
					nonTerminal.getFirstSet().getTokensMap().insert(std::pair <std::string, AbstractTerminal<T, C> *>(it->first, it->second));
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
				it++;
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
			symbol->setIndex(_index++);
			_symbolsMap.insert(std::pair <std::string, AbstractSymbol<T, C> *>(symbol->getIdentifier(), symbol));
		}

		void computeGrammar(void)
		{
			computeProductions();
			computeFirstSets();
		}

		virtual bool markStartOfComment(std::string currentLex) {
			static_cast<void>(currentLex);
			return false;
		}

		virtual bool markEndOfComment(std::string currentLex) {
			static_cast<void>(currentLex);
			return false;
		}

		virtual std::deque<Token<T, C> *> innerLex(bool stopAtNewline, std::istream & istream)
		{
			std::deque<Token<T, C> *>	res;
			int							pos;
			int							endPos;
			std::string					current;
			AbstractTerminal<T, C>		*terminal;
			Token <T, C>				*token;
			char						c;
			bool						isToDiscard;

			isToDiscard = false;
			while (!istream.eof()) //loop on all tokens created
			{
				current.clear();
				terminal = nullptr;
				pos = 0;
				endPos = 0;

				while (!istream.eof()) //loop on all characters of current token
				{
					if ((c = istream.peek()) != EOF && (c != '\n' || !stopAtNewline)) //check if not end of parsing
					{
						current += c;
						if (markStartOfComment(current))
							isToDiscard = true;
						else if (isToDiscard && markEndOfComment(current))
						{
							isToDiscard = false;
							break;
						}
						if (!isToDiscard && !treatTerminalEligibility(current, &terminal, res)) // we have no eligible for current
						{
							if (terminal)
							{
								token = terminal->createToken(current.substr(0, endPos - pos));
								res.push_back(token);
								break;
							}
							else if (isblank(c) && _blankAsDelimiters && current.size() == 1)
							{
								istream.get();
								break;
							}
							else
							{
								deleteTokens(res);
								throw AbstractGrammar<T, C>::LexicalErrorException(current);
							}
						}
						else
						{
							endPos++;
							istream.get();
						}
					}
					else //end of parsing
					{
						if (terminal)
						{
							token = terminal->createToken(current.substr(0, endPos - pos));
							res.push_back(token);
						}
						else if (current != "")
						{
							deleteTokens(res);
							throw AbstractGrammar<T, C>::LexicalErrorException(current);
						}
						return res;
					}
				}
			}
        	return (res);
		}

	protected:

		Start<T, C>										* _startSymbol;
		AbstractNonTerminal<T, C>						* _startGrammarSymbol;
		EndOfInput<T, C>								* _endOfInput;

		int												_index;
		std::vector<AbstractNonTerminal<T, C> *>		_nonTerminals;
		std::vector<AbstractTerminal<T, C> *>			_tokens;
		std::map<std::string, AbstractSymbol<T, C> *>	_symbolsMap;

		bool											_blankAsDelimiters;

		private:

		bool treatTerminalEligibility(std::string current, AbstractTerminal<T, C> **terminal, std::deque<Token<T, C> *>	&tokens)
		{
			typename std::vector<AbstractTerminal<T, C> *>::iterator it = _tokens.begin();
			bool res = false;

			while (it != _tokens.end())
			{
				if ((*it)->canBeAdded(tokens))
				{
					if ((*it)->staysEligibleForCurrent(current))
						res = true;
					if ((*it)->isEligibleForCurrent(current))
						*terminal = *it;
				}
				it++;
			}
			return res;
		}
};

template<typename T, typename C>
void deleteTokens(std::deque<Token<T, C> *> &tokens)
{
	typename std::deque<Token<T, C> *>::iterator it = tokens.begin();
	while (it != tokens.end())
	{
		delete *it;
		it++;
	}
}

template<typename T, typename C>
void printTokenQueue(std::deque<Token<T, C> *> &tokens)
{
	size_t i = 0;
	typename std::deque<Token<T, C> *>::iterator it = tokens.begin();
	std::cout << std::endl << "tokens:" << std::endl;
	while (it != tokens.end())
	{
		std::cout << "Token #" << i << ": " << *(*it) << std::endl;
		i++;
		it++;
	}
}

#endif
