/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Divide.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 07:53:32 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/03 00:46:07 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIVIDE_HPP
# define DIVIDE_HPP

# include <iostream>
# include "AbstractTerminal.hpp"

class Divide : public AbstractTerminal<int, int>
{
	public:
		Divide(void);
		~Divide(void);
		virtual int traverse(ASTNode<int, int> & ast, int dummy) const;
	
	private:

};

#endif