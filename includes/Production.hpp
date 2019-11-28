/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Production.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:10:12 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 14:57:43 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRODUCTION_HPP
# define PRODUCTION_HPP

# include <iostream>
# include "AbstractSymbol.hpp"
# include <vector>

template<typename T, typename C>
class Production
{
	public:
		Production(void)
		{
			
		}

		Production(Production const &instance)
		{
			*this = instance;
		}

		Production<T, C> &operator=(Production<T, C> const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}

		virtual ~Production(void)
		{
			
		}

	private:
		AbstractSymbol<T, C> & _from;
		std::vector<AbstractSymbol<T, C> &> _symbols;
};

// std::ostream &operator<<(std::ostream &o, Production const &instance);
#endif