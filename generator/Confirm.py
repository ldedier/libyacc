# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Confirm.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/27 05:40:28 by ldedier           #+#    #+#              #
#    Updated: 2022/02/02 07:57:14 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

def confirm(warning):
	while True:
		res = input(f'{warning} (y or n)\n')
		if len(res) == 0 or not (c := res[0].lower()) in {'y', 'n'}:
			print("please answer with y or n")
			continue
		else:
			return c == 'y'