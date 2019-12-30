/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Term.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:20:08 by ldedier           #+#    #+#             */
/*   Updated: 2019/12/30 01:19:05 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_HPP
# define TERM_HPP

# include <iostream>
// # include "AbstractNonTerminal.hpp"
# include "ArithmeticGrammar.hpp"

class Term : public AbstractNonTerminal<int, int>
{
	public:
		Term(void);
		~Term(void);
		virtual int traverse(ASTNode<int, int> & node, int dummy) const;
		virtual void computeProductions(AbstractGrammar<int, int> &cfg);

	private:

};
#endif