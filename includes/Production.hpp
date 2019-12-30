/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Production.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:10:12 by ldedier           #+#    #+#             */
/*   Updated: 2019/12/29 19:54:59 by ldedier          ###   ########.fr       */
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
class Production
{
	public:

		Production(AbstractSymbol<T, C> & from, AbstractGrammar<T, C> &cfg, int nbSymbols, std::string *tbl) : _from(&from), _symbols()
		{
			int i;

			i = 0;
			while (i < nbSymbols)
			{
				_symbols.push_back(cfg.getSymbol(tbl[i]));
				i++;
			}
		}

		Production(AbstractSymbol<T, C> & from, AbstractGrammar<T, C> &cfg) : _from(&from), _symbols()
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

		AbstractSymbol<T, C> *getFrom(void) const
		{
			return _from;
		}
		
		const std::vector<AbstractSymbol<T, C> *> & getSymbols(void) const
		{
			return _symbols;
		}
		
	private:
		AbstractSymbol<T, C> * _from;
		std::vector<AbstractSymbol<T, C> *> _symbols;
};

template<typename T, typename C>
std::ostream &operator<<(std::ostream &o, Production<T, C> const &instance)
{
	o << *(instance.getFrom()) << " => ";
	typename std::vector<AbstractSymbol<T, C> * >::const_iterator it = instance.getSymbols().begin();
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