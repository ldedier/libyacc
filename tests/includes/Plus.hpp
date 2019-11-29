/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plus.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 07:41:38 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 09:05:35 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLUS_HPP
# define PLUS_HPP

# include <iostream>
# include "AbstractToken.hpp"

class Plus : public AbstractToken<int, int>
{
	public:
		Plus(void);
		~Plus(void);
		virtual int traverse(ASTNode<int, int> & ast, int dummy) const;

	private:

};
#endif