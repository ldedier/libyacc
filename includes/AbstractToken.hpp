/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractToken.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:14:12 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 07:16:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTTOKEN_HPP
# define ABSTRACTTOKEN_HPP

# include <iostream>
# include "AbstractSymbol.hpp"
# include "Production.hpp"

class AbstractToken : public AbstractSymbol
{
	public:
		AbstractToken(void);
		AbstractToken(AbstractToken const &instance);
		AbstractToken &operator=(AbstractToken const &rhs);
		~AbstractToken(void);

	private:
		std::vector<Production> _productions; 

};

std::ostream &operator<<(std::ostream &o, AbstractToken const &instance);
#endif