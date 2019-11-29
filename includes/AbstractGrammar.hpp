/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractGrammar.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:09:59 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 17:34:57 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTGRAMMAR_HPP
# define ABSTRACTGRAMMAR_HPP

# include <iostream>
# include "AbstractSymbol.hpp"
# include "AbstractToken.hpp"
# include "AbstractNonTerminal.hpp"

template<typename T, typename C>
class AbstractGrammar
{
	public:
		AbstractGrammar(void)
		{
			// _symbols = std::vector<AbstractSymbol<T, C> >();
			// _nonTerminals = std::vector<AbstractNonTerminal<T, C> *>();
			// _tokens = std::vector<AbstractToken<T, C> *>();
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
			
			while (it != _nonTerminals.end())
			{
				(*it)->printProductions();
				it++;
			}
		}

	protected:
		AbstractNonTerminal<T, C> * _startSymbol;
		std::vector<AbstractNonTerminal<T, C> *> _nonTerminals;
		std::vector<AbstractToken<T, C> *> _tokens;
		// std::vector<AbstractSymbol<T, C> *> _symbols;
		std::map<std::string, AbstractSymbol<T, C> *> _symbolsMap;

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
		}

		void computeFirstSets(void)
		{
			unsigned long i;

			i = 0;
			while (i < this->_nonTerminals.size())
			{
				this->_nonTerminals[i]->computeProductions(*this);
				i++;
			}
		}

	private:
	
		void addSymbol(AbstractSymbol <T, C> *symbol)
		{
			_symbolsMap.insert(std::pair <std::string, AbstractSymbol<T, C> *>(symbol->getIdentifier(), symbol));
		}

};

// std::ostream &operator<<(std::ostream &o, AbstractGrammar const &instance);
#endif