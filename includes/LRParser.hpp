/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRParser.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:19:48 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/29 07:11:28 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRPARSER_HPP
# define LRPARSER_HPP

# include <iostream>
# include <map>
# include "AbstractLRAction.hpp"
# include "LRState.hpp"
# include "ASTBuilder.hpp"

template<typename T, typename C>
class LRParser
{
	public:
		LRParser(void)
		{

		}

		LRParser(AbstractGrammar<T, C> & cfg)
		{
			(void)cfg;
		}

		LRParser(LRParser const &instance)
		{
			*this = instance;
		}

		LRParser &operator=(LRParser const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}

		ASTBuilder<T, C> parse(void)
		{
			ASTBuilder<T, C> res;
			return res;
		}

		~LRParser(void)
		{

		}

	private:
		std::vector < std::vector <AbstractLRAction<T, C> > > _tables;
		std::list <LRState<T, C> > _states;

};
#endif