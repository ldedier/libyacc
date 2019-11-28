/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRParser.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:19:48 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 15:15:26 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRPARSER_HPP
# define LRPARSER_HPP

# include <iostream>
# include <map>
# include "AbstractLRAction.hpp"
# include "LRState.hpp"
# include "LRItem.hpp"
# include "ASTBuilder.hpp"
# include "AbstractGrammar.hpp"

template<typename T, typename C>
class LRParser
{
	public:
		LRParser(void)
		{
			
		}
	
		LRParser(AbstractGrammar<T, C> &cfg)
		{
			(void)cfg;
		}

		LRParser(LRParser<T, C> const &instance)
		{
			*this = instance;
		}

		LRParser<T, C> &operator=(LRParser<T, C> const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}
		
		virtual ~LRParser(void)
		{
			
		}
		
		ASTBuilder<T, C> &parse();

	private:
		std::vector < std::vector <AbstractLRAction<T, C> > > _tables;
		std::map<LRState<T, C>, LRItem<T, C> > _states;
};

// std::ostream &operator<<(std::ostream &o, LRParser const &instance);
#endif