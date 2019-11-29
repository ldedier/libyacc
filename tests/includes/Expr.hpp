/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Expr.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:34:41 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 09:05:48 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPR_HPP
# define EXPR_HPP

# include <iostream>
# include "AbstractNonTerminal.hpp"
# include "ArithmeticGrammar.hpp"

class Expr : public AbstractNonTerminal<int, int>
{
	public:
		Expr(void);
		virtual ~Expr(void);
		virtual int traverse(ASTNode<int, int> & node, int dummy) const;
		virtual void computeProductions(AbstractGrammar<int, int> &cfg);

};
#endif