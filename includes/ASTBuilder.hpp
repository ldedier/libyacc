/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASTBuilder.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 08:48:51 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 07:12:06 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTBUILDER_HPP
# define ASTBUILDER_HPP

# include <iostream>
# include "ASTNode.hpp"

template<typename T, typename C>
class ASTBuilder
{
	public:
		ASTBuilder(void)
		{
			
		}

		ASTBuilder(ASTBuilder const &instance)
		{
			*this = instance;
		}
		
		ASTBuilder &operator=(ASTBuilder const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}
		
		virtual ~ASTBuilder(void)
		{
			
		}

	private:
		ASTNode<T, C> * _astRoot;
		ASTNode<T, C> * _cstRoot;
};

// std::ostream &operator<<(std::ostream &o, ASTBuilder const &instance);
#endif