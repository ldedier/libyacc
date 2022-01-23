# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    HeaderWriter.py                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/05 19:12:07 by ldedier           #+#    #+#              #
#    Updated: 2022/01/21 08:09:15 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from datetime import datetime
import sys

class HeaderWriter:

	login = "ldedier"
	email = "ldedier@student.42.fr"

	@classmethod
	def writeHeaderStrings(HeaderWriter, fd, name, start, end):
		split = name.split("/")
		name = split[len(split) - 1]
		name = name[:40]
		time = datetime.today().strftime('%Y/%m/%d %H:%M:%S') + " by " + HeaderWriter.login
		by = HeaderWriter.login + " <" + HeaderWriter.email + ">"

		fd.write(start + " " + ("*" * (2 - len(start))) + "**************************************************************************"+ ("*" *  (2 - len(end)))+ " "  + end + "\n")
		fd.write(start + " " + (" " * (2 - len(start))) + "                                                                          " + (" " * (2 - len(end)))+ " " + end + "\n")
		fd.write(start + " " + (" " * (2 - len(start))) + "                                                       :::      ::::::::  " + (" " * (2 - len(end)))+ " " + end + "\n")
		fd.write(start + " " + (" " * (2 - len(start))) + "  " + name + (" " * (51 - len(name)))         +     ":+:      :+:    :+:  " + (" " * (2 - len(end)))+ " " + end + "\n")
		fd.write(start + " " + (" " * (2 - len(start))) + "                                                   +:+ +:+         +:+    " + (" " * (2 - len(end)))+ " " + end + "\n")
		fd.write(start + " " + (" " * (2 - len(start))) + "  By: " + by + (" " * (43 - len(by)))   +       "+#+  +:+       +#+       " + (" " * (2 - len(end)))+ " " + end + "\n")
		fd.write(start + " " + (" " * (2 - len(start))) + "                                               +#+#+#+#+#+   +#+          " + (" " * (2 - len(end)))+ " " + end + "\n")
		fd.write(start + " " + (" " * (2 - len(start))) + "  Created: " + time + (" " * (42 - len(time))) +    "#+#    #+#           " + (" " * (2 - len(end)))+ " " + end + "\n")
		fd.write(start + " " + (" " * (2 - len(start))) + "  Updated: " + time + (" " * (41 - len(time))) +   "###   ########.fr     " + (" " * (2 - len(end)))+ " " + end + "\n")
		fd.write(start + " " + (" " * (2 - len(start))) + "                                                                          " + (" " * (2 - len(end)))+ " " + end + "\n")
		fd.write(start + " " + ("*" * (2 - len(start))) + "**************************************************************************" + ("*" * (2 - len(end)))+ " " + end + "\n")

	@classmethod
	def writeHeader(HeaderWriter, fd, name):
		HeaderWriter.writeHeaderStrings(fd, name, "/*", "*/")

	@classmethod
	def writeHeaderString(HeaderWriter, fd, name, string):
		HeaderWriter.writeHeaderStrings(fd, name, string, string)

	@classmethod
	def openFile(HeaderWriter, name, openComment="/*", closeComment='*/'):
		fd = open(name, "w")
		HeaderWriter.writeHeaderStrings(fd, name, openComment, closeComment)
		return fd
