/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASTNode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:23:18 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 07:23:35 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTNODE_HPP
# define ASTNODE_HPP

# include <iostream>

class ASTNode
{
	public:
		ASTNode(void);
		ASTNode(ASTNode const &instance);
		ASTNode &operator=(ASTNode const &rhs);
		~ASTNode(void);

	private:

};

std::ostream &operator<<(std::ostream &o, ASTNode const &instance);
#endif