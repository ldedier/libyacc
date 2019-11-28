/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractGrammar.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:09:59 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 07:36:08 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTGRAMMAR_HPP
# define ABSTRACTGRAMMAR_HPP

# include <iostream>
# include "AbstractSymbol.hpp"
# include "AbstractToken.hpp"
# include "AbstractNonTerminal.hpp"

class AbstractGrammar
{
	public:
		AbstractGrammar(void);
		AbstractGrammar(AbstractGrammar const &instance);
		AbstractGrammar &operator=(AbstractGrammar const &rhs);
		~AbstractGrammar(void);

	private:
		std::vector<AbstractSymbol &> _symbols;
		std::vector<AbstractNonTerminal &> _nonTerminals;
		std::vector<AbstractToken &> _tokens;
};

std::ostream &operator<<(std::ostream &o, AbstractGrammar const &instance);
#endif