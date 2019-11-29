/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractNonTerminal.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:15:12 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 09:47:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTNONTERMINAL_HPP
# define ABSTRACTNONTERMINAL_HPP

# include <iostream>
# include <map>
# include "AbstractSymbol.hpp"
# include "AbstractToken.hpp"


template<typename T, typename C>
class AbstractGrammar;

template<typename T, typename C>
class AbstractNonTerminal : public AbstractSymbol<T, C>
{
	public:
		AbstractNonTerminal(void)
		{
			
		}

		AbstractNonTerminal(std::string identifier) : AbstractSymbol<T, C>(identifier)
		{
			
		}

		AbstractNonTerminal(AbstractNonTerminal const &instance)
		{
			*this = instance;
		}

		AbstractNonTerminal &operator=(AbstractNonTerminal const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}
		
		virtual ~AbstractNonTerminal(void)
		{
			
		}

		void addProduction(AbstractGrammar<T, C> &cfg, int nbSymbols, std::string  *tbl)
		{
			Production<T, C> prod(*this, cfg, nbSymbols, tbl);
			_productions.push_back(prod);
		}

		virtual void computeProductions(AbstractGrammar<T, C> &cfg) = 0;

	private:
		std::vector<Production<T, C> > _productions;
		std::map<AbstractToken<T, C> &, AbstractToken<T, C> &> _first_set;
};

// std::ostream &operator<<(std::ostream &o, AbstractNonTerminal const &instance);
#endif