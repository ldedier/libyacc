/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minus.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 07:54:12 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/03 00:46:07 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINUS_HPP
# define MINUS_HPP

# include <iostream>
# include "AbstractTerminal.hpp"

class Minus : public AbstractTerminal<int, int>
{
	public:
		Minus(void);
		~Minus(void);
		virtual int traverse(ASTNode<int, int> & ast, int dummy) const;

	private:

};

#endif