/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Divide.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 07:53:32 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 08:54:31 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIVIDE_HPP
# define DIVIDE_HPP

# include <iostream>
# include "AbstractToken.hpp"

class Divide : public AbstractToken<int, int>
{
	public:
		Divide(void);
		~Divide(void);
		virtual int traverse(ASTNode<int, int> & ast, int dummy) const;
	
	private:

};

#endif