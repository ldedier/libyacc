/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArithmeticGrammar.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 09:46:25 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/10 00:37:15 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARITHMETICGRAMMAR_HPP
# define ARITHMETICGRAMMAR_HPP

# include <iostream>

# include "../../includes/AbstractGrammar.hpp"

# include "Integer.hpp"
# include "Arithmetic.hpp"
# include "Term.hpp"
# include "Factor.hpp"
# include "Expr.hpp"

# include "Plus.hpp"
# include "Minus.hpp"
# include "Multiply.hpp"
# include "Divide.hpp"

class ArithmeticGrammar: public AbstractGrammar<int, int>
{
	public:
		ArithmeticGrammar(void);
		ArithmeticGrammar(ArithmeticGrammar const &instance);
		ArithmeticGrammar &operator=(ArithmeticGrammar const &rhs);
		virtual ~ArithmeticGrammar(void);
		// virtual std::deque<Token<int, int> *> innerLex(std::istream & istream);

	private:

};

// std::ostream &operator<<(std::ostream &o, ArithmeticGrammar const &instance);
#endif