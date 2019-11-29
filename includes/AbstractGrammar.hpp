/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractGrammar.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:09:59 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 07:14:37 by ldedier          ###   ########.fr       */
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

	protected:
		AbstractNonTerminal<T, C> * _startSymbol;
		std::vector<AbstractSymbol<T, C> *> _symbols;
		std::vector<AbstractNonTerminal<T, C> *> _nonTerminals;
		std::vector<AbstractToken<T, C> *> _tokens;
		
		void addNonTerminal(AbstractNonTerminal<T, C> * nonTerminal)
		{
			_nonTerminals.push_back(nonTerminal);
			_symbols.push_back(nonTerminal);
		}
		
		void addToken(AbstractToken<T, C> *token)
		{
			_tokens.push_back(token);
			_symbols.push_back(token);
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

	private:
		
};

// std::ostream &operator<<(std::ostream &o, AbstractGrammar const &instance);
#endif