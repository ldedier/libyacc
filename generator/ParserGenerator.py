#!/usr/local/bin/python3
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ParserGenerator.py                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/05 18:48:35 by ldedier           #+#    #+#              #
#    Updated: 2020/01/05 18:48:35 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys
from HeaderWriter import HeaderWriter as hw
from Grammar  import Grammar

class ParserGenerator:
	
	def __init__(self, path):
		self.path = path;
		self.grammar_fd = open(path, "r");
		self.grammar = Grammar(self.grammar_fd);

	def generateHeaders(self):
		print("generated Headers !");

    def generateSources(self):
    	print("generated sources !");

	def generateMakefile(self):
		print("generated Makefile !");
	
	def generateCode(self):
		print(self.grammar);
		self.generateHeaders();
		self.generateSources();
		self.generateMakefile();


if len(sys.argv) >= 2:
	path = sys.argv[1]
else:
	sys.exit("you shall add the path of your grammar")
try:
	gen = ParserGenerator(path);
	gen.generateCode();
except Exception as e:
	print(e);
	exit(1);
