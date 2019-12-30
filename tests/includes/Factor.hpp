/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factor.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:21:18 by ldedier           #+#    #+#             */
/*   Updated: 2019/12/30 01:19:17 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTOR_HPP
# define FACTOR_HPP

# include <iostream>

#include "AbstractNonTerminal.hpp"
# include "ArithmeticGrammar.hpp"

class Factor : public AbstractNonTerminal<int, int>
{
	public:
		Factor(void);
		virtual ~Factor(void);
		virtual int traverse(ASTNode<int, int> & node, int dummy) const;
		virtual void computeProductions(AbstractGrammar<int, int> &cfg);

	private:

};
#endif