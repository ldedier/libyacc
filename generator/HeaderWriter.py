# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    HeaderWriter.py                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/05 19:12:07 by ldedier           #+#    #+#              #
#    Updated: 2020/01/05 19:12:07 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from datetime import datetime
import sys

class HeaderWriter:

	login = "ldedier"
	email = "ldedier@student.42.fr"

	@classmethod
	def writeHeader(HeaderWriter, fd, name):

		name = name[:40];
		time = datetime.today().strftime('%Y/%m/%d %H:%M:%S') + " by " + HeaderWriter.login;
		by = HeaderWriter.login + " " + HeaderWriter.email;

		fd.write("/* ************************************************************************** */\n")
		fd.write("/*                                                                            */\n")
		fd.write("/*                                                        :::      ::::::::   */\n")
		fd.write("/*   " + name + (" " * (51 - len(name)))         +     ":+:      :+:    :+:   */\n")
		fd.write("/*                                                    +:+ +:+         +:+     */\n")
		fd.write("/*   By: " + by + (" " * (len(by) - 15))   +       "+#+  +:+       +#+        */\n")
		fd.write("/*                                                +#+#+#+#+#+   +#+           */\n")
		fd.write("/*   Created:" + time + (" " * (len(time) - 17)) +     "#+#    #+#            */\n")
		fd.write("/*   Updated:" + time + (" " * (len(time) - 18)) +    "###   ########.fr      */\n")
		fd.write("/*                                                                            */\n")
		fd.write("/* ************************************************************************** */\n")

	@classmethod
	def openFile(HeaderWriter, name):
		try:
			fd = open(name, "w")
			HeaderWriter.writeHeader(fd, name);
			return fd
		except Exception as e:
			print (e)
