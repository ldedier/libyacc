/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minus.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 07:54:12 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 09:05:39 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINUS_HPP
# define MINUS_HPP

# include <iostream>
# include "AbstractToken.hpp"

class Minus : public AbstractToken<int, int>
{
	public:
		Minus(void);
		~Minus(void);
		virtual int traverse(ASTNode<int, int> & ast, int dummy) const;

	private:

};

#endif