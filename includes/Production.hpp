/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Production.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:10:12 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 04:30:57 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRODUCTION_HPP
# define PRODUCTION_HPP

# include <iostream>
# include "AbstractSymbol.hpp"
# include <vector>

template<typename T, typename C>
class AbstractGrammar;

template<typename T, typename C>
class AbstractNonTerminal;

template<typename T, typename C>
class Production
{
	public:

		Production(AbstractNonTerminal<T, C> & from, AbstractGrammar<T, C> &cfg, int nbSymbols, std::string *tbl) : _from(&from), _symbols(), _replacing(false)
		{
			int i;

			i = 0;
			while (i < nbSymbols)
			{
				_symbols.push_back(cfg.getSymbol(tbl[i]));
				i++;
			}
		}

		Production(AbstractNonTerminal<T, C> & from, AbstractGrammar<T, C> &cfg, int nbSymbols, std::string *tbl, bool replacing) : _from(&from), _symbols(), _replacing(replacing)
		{
			int i;

			i = 0;
			while (i < nbSymbols)
			{
				_symbols.push_back(cfg.getSymbol(tbl[i]));
				i++;
			}
		}

		Production(AbstractNonTerminal<T, C> & from, AbstractGrammar<T, C> &cfg) : _from(&from), _symbols()
		{
			_symbols.push_back(cfg.getGrammarStartingSymbol());
		}

		Production(void)
		{
			
		}

		Production(Production const &instance)
		{
			*this = instance;
		}

		Production<T, C> &operator=(Production<T, C> const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}

		virtual ~Production(void)
		{
			
		}

		AbstractNonTerminal<T, C> *getFrom(void)
		{
			return _from;
		}
		
		std::vector<AbstractSymbol<T, C> *> & getSymbols(void) 
		{
			return _symbols;
		}
		
		bool isReplacing()
		{
			return _replacing;
		}

	private:
		AbstractNonTerminal<T, C> * _from;
		std::vector<AbstractSymbol<T, C> *> _symbols;
		bool _replacing;
};

template<typename T, typename C>
std::ostream &operator<<(std::ostream &o, Production<T, C>  &instance)
{
	o << *(instance.getFrom()) << " => ";
	typename std::vector<AbstractSymbol<T, C> * >::iterator it = instance.getSymbols().begin();
	if (!instance.getSymbols().size())
		o << "ε";
	else
	{
		while (it != instance.getSymbols().end())
		{
			o << *(*it) << " ";
			it++;
		}
	}
	o << std::endl;
	return o;
}
#endif