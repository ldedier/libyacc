/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiply.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 07:52:40 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/03 00:46:07 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTIPLY_HPP
# define MULTIPLY_HPP

# include <iostream>
# include "AbstractTerminal.hpp"

class Multiply : public AbstractTerminal<int, int>
{
	public:
		Multiply(void);
		~Multiply(void);
		virtual int traverse(ASTNode<int, int> & ast, int dummy) const;

	private:

};
#endif