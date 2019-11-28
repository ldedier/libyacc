/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArithmeticGrammar.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 09:46:25 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 15:58:22 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARITHMETICGRAMMAR_HPP
# define ARITHMETICGRAMMAR_HPP

# include <iostream>
# include "../../includes/AbstractGrammar.hpp"

# define AR_NB_NON_TERMINALS 4
# define AR_NB_TOKENS 1

class ArithmeticGrammar: public AbstractGrammar<int, int>
{
	public:
		ArithmeticGrammar(void);
		ArithmeticGrammar(ArithmeticGrammar const &instance);
		ArithmeticGrammar &operator=(ArithmeticGrammar const &rhs);
		virtual ~ArithmeticGrammar(void);

	private:

};

// std::ostream &operator<<(std::ostream &o, ArithmeticGrammar const &instance);
#endif