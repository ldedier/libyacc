/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EndOfInput.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 08:40:39 by ldedier           #+#    #+#             */
/*   Updated: 2019/11/28 15:02:54 by ldedier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENDOFINPUT_HPP
# define ENDOFINPUT_HPP

# include <iostream>
# include "AbstractToken.hpp"

template<typename T, typename C>
class EndOfInput : public AbstractToken<T, C>
{
	public:
		EndOfInput(void)
		{
			
		}
		
		EndOfInput(EndOfInput const &instance)
		{
			*this = instance;
		}
		EndOfInput &operator=(EndOfInput const &rhs)
		{
			static_cast<void>(rhs);
			return *this;
		}

		virtual T traverse(ASTNode<T, C>)
		{
			T t;
			return t;		
		}

		virtual ~EndOfInput(void)
		{
			
		}

	private:

};

// std::ostream &operator<<(std::ostream &o, EndOfInput const &instance);
#endif