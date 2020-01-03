/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Integer.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:18:44 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/03 01:31:34 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTEGER_HPP
# define INTEGER_HPP

# include <iostream>
# include "AbstractTerminal.hpp"

class Integer : public AbstractTerminal<int, int>
{
	public:
		Integer(void);
		Integer(int value);
		virtual ~Integer(void);
		virtual int traverse(ASTNode<int, int> & node, int dummy) const;

	private:
		int _value;
};
#endif