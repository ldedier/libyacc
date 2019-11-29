/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiply.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 07:52:40 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 08:54:22 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTIPLY_HPP
# define MULTIPLY_HPP

# include <iostream>
# include "AbstractToken.hpp"

class Multiply : public AbstractToken<int, int>
{
	public:
		Multiply(void);
		~Multiply(void);
		virtual int traverse(ASTNode<int, int> & ast, int dummy) const;

	private:

};
#endif