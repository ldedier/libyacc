/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Production.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:10:12 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 07:12:19 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRODUCTION_HPP
# define PRODUCTION_HPP

# include <iostream>
# include "AbstractSymbol.hpp"
# include <vector>

class Production
{
	public:
		Production(void);
		Production(Production const &instance);
		Production &operator=(Production const &rhs);
		~Production(void);

	private:
		AbstractSymbol &_from;
		std::vector<AbstractSymbol &> _symbols;

};

std::ostream &operator<<(std::ostream &o, Production const &instance);
#endif