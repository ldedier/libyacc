/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Start.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 17:49:27 by ldedier           #+#    #+#             */
/*   Updated: 2019/12/30 12:48:14 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef START_HPP
# define START_HPP

# include <iostream>
# include "Production.hpp"
# include "AbstractNonTerminal.hpp"

template<typename T, typename C>
class Start : public AbstractNonTerminal<T, C>
{
	public:

		Start(void) : AbstractNonTerminal<T, C>("START")
		{

		}

		Start(Start const &instance)
		{
			static_cast<void>(instance);
		}

		Start &operator=(Start const &rhs)
		{
			*this = rhs;
			return *this;
		}

		~Start(void)
		{

		}

		T traverse(ASTNode<T, C> & node, C dummy) const
		{
			static_cast<void>(node);
			static_cast<void>(dummy);
			throw std::exception();
		}

		void computeProductions(AbstractGrammar<T, C> & cfg)
		{
			Production<T, C> *prod = new Production<T, C>(*this, cfg);
			this->getProductions().push_back(prod);
		}

	private:

};

// std::ostream &operator<<(std::ostream &o, Start<T, C> const &instance);
#endif