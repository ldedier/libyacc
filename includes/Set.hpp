/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 19:03:16 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/02 01:57:12 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include <iostream>
# include <map>
// # include "AbstractGrammar.hpp"

template<typename T, typename C>
class AbstractToken;

template<typename T, typename C>
class AbstractGrammar;

template<typename T, typename C>
class Set
{
	public:
		Set(void): _hasEpsilon(false)
		{

		}

		Set(Set const &instance)
		{
			*this = instance;
		}

		void addTransitive(AbstractSymbol<T, C> &symbol)
		{
			typename std::map<std::string, AbstractToken<T, C> * >::iterator it = symbol.getFirstSet().getTokensMap().begin();

			while (it != symbol.getFirstSet().getTokensMap().end())
			{
				if (_tokensMap.find(it->first) == _tokensMap.end()) 
				{
					_tokensMap.insert(std::pair <std::string, AbstractToken<T, C> *>(it->first, it->second));
				}
				it++;
			}
		}

		Set(AbstractGrammar<T, C> &grammar,
			typename std::vector<AbstractSymbol<T, C> *>::const_iterator &it,
				const std::vector<AbstractSymbol<T, C> *> & symbols,
					AbstractToken<T, C> &lookahead)
		{
			AbstractSymbol<T, C> *symbol;
			(void)grammar;
			while (it != symbols.end())
			{
				symbol = *it;
				addTransitive(*symbol);
				if (!symbol->getFirstSet().hasEpsilon())
					return ;
				it++;
			}
			addTransitive(lookahead);
		}

		Set &operator=(Set const &rhs)
		{
			this->_hasEpsilon = rhs._hasEpsilon;
			return *this;
		}

		~Set(void)
		{

		}

		void setEpsilon()
		{
			_hasEpsilon = true;
		}

		bool hasEpsilon() const
		{
			return _hasEpsilon;
		}

		void addToken(AbstractToken<T,C> *token)
		{
			_tokensMap.insert(std::pair <std::string, AbstractToken<T, C> *>(token->getIdentifier(), token));
		}

		std::map<std::string, AbstractToken<T, C> *> & getTokensMap()
		{
			return _tokensMap;
		}

	private:
		bool _hasEpsilon;
		std::map<std::string, AbstractToken<T, C> *> _tokensMap;

};

template<typename T, typename C>
std::ostream &operator<<(std::ostream &o, Set<T, C>  &instance)
{
	(void)instance;
	typename std::map<std::string, AbstractToken<T, C> * >::iterator it = instance.getTokensMap().begin();
	while (it != instance.getTokensMap().end())
	{
		std::cout << *(it->second);
		std::cout << " ; ";
		it++;
	}
	if (instance.hasEpsilon())
		std::cout << "ε";
	return o;
}

#endif