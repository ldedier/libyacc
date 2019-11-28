/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LRParser.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:19:48 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 07:34:45 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LRPARSER_HPP
# define LRPARSER_HPP

# include <iostream>
# include <map>
# include "AbstractLRAction.hpp"
# include "LRState.hpp"

class LRParser
{
	public:
		LRParser(void);
		LRParser(LRParser const &instance);
		LRParser &operator=(LRParser const &rhs);
		~LRParser(void);

	private:
		std::vector < std::vector <AbstractLRAction> > _tables;
		std::map<LRState> _states;

};

std::ostream &operator<<(std::ostream &o, LRParser const &instance);
#endif