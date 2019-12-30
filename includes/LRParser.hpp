/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRParser.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:19:48 by ldedier           #+#    #+#             */
/*   Updated: 2019/12/30 16:26:31 by ldedier          ###   ########.fr       */
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
			LRState<T, C> firstState;

			firstState = LRState<T, C>(cfg);
			_states.push_back(firstState);
			while (computeStates())
				;
			this->debug();
			
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

		void debug()
		{
			std::cout << "States:" << std::endl;
		
			typename std::list <LRState<T, C> >::iterator it = _states.begin();
			while (it != _states.end())
			{
				std::cout << *it;
				it++;
			}

		}

		bool computeStates()
		{
			int changes = false;
			return changes;
		}

	private:
		std::vector < std::vector <AbstractLRAction<T, C> > > _tables;
		std::list <LRState<T, C> > _states;

};
#endif