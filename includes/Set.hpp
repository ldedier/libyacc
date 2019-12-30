/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 19:03:16 by ldedier           #+#    #+#             */
/*   Updated: 2019/12/29 16:18:18 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include <iostream>
# include <map>

template<typename T, typename C>
class AbstractToken;

template<typename T, typename C>
class Set
{
	public:
		Set(void): _hasEpsilon(false)
		{

		}

		Set(Set const &instance)
		{
			*this = instance;
		}

		Set &operator=(Set const &rhs)
		{
			this->_hasEpsilon = rhs._hasEpsilon;
			return *this;
		}

		~Set(void)
		{

		}

		void setEpsilon()
		{
			_hasEpsilon = true;
		}

		bool hasEpsilon() const
		{
			return _hasEpsilon;
		}

		void addToken(AbstractToken<T,C> *token)
		{
			_tokensMap.insert(std::pair <std::string, AbstractToken<T, C> *>(token->getIdentifier(), token));
		}

		std::map<std::string, AbstractToken<T, C> *> & getTokensMap()
		{
			return _tokensMap;
		}

	private:
		bool _hasEpsilon;
		std::map<std::string, AbstractToken<T, C> *> _tokensMap;

};

template<typename T, typename C>
std::ostream &operator<<(std::ostream &o, Set<T, C>  &instance)
{
	(void)instance;
	typename std::map<std::string, AbstractToken<T, C> * >::iterator it = instance.getTokensMap().begin();
	while (it != instance.getTokensMap().end())
	{
		std::cout << *(it->second);
		std::cout << " ; ";
		it++;
	}
	if (instance.hasEpsilon())
		std::cout << "ε";
	return o;
}

#endif