/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plus.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 07:41:38 by ldedier           #+#    #+#             */
/*   Updated: 2020/01/03 00:46:07 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLUS_HPP
# define PLUS_HPP

# include <iostream>
# include "AbstractTerminal.hpp"

class Plus : public AbstractTerminal<int, int>
{
	public:
		Plus(void);
		~Plus(void);
		virtual int traverse(ASTNode<int, int> & ast, int dummy) const;

	private:

};
#endif