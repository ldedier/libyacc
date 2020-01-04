/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Arithmetic.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:17:18 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/04 03:15:29 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARITHMETIC_HPP
# define ARITHMETIC_HPP

# include <iostream>

# include "ArithmeticGrammar.hpp"

class Arithmetic : public AbstractNonTerminal<int, int>
{
	public:
		Arithmetic(void);
		virtual ~Arithmetic(void);
		virtual int traverse(ASTNode<int, int> & node, int dummy) const;
		virtual void computeProductions(AbstractGrammar<int, int> &cfg);

};

#endif