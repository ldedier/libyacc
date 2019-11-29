/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Integer.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:18:44 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 08:54:26 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTEGER_HPP
# define INTEGER_HPP

# include <iostream>
# include "AbstractToken.hpp"

class Integer : public AbstractToken<int, int>
{
	public:
		Integer(void);
		Integer(int value);
		virtual ~Integer(void);
		virtual std::string	repr(void) const;
		virtual int traverse(ASTNode<int, int> & node, int dummy) const;

	private:
		int _value;
};
#endif