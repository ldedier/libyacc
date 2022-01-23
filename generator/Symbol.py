#!/usr/local/bin/python3
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Symbol.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/06 00:32:56 by ldedier           #+#    #+#              #
#    Updated: 2020/01/06 00:32:56 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from functools import reduce

class Symbol:

	@staticmethod
	def capitalizeCustom(string):
		if (len(string) > 0):
			res = string[0].upper() + string[1:]
		else:
			res = string[:]
		return res

	def __init__(self, identifier, fileBaseName):
		self.productions = []
		self.identifier = identifier
		self.fileBaseName = Symbol.capitalizeCustom(fileBaseName)
		self.subClass = "AbstractTerminal"

	def addProduction(self, identifiers, grammar):
		prod = []
		if (identifiers != ["_EPS_"]):
			for identifier in identifiers:
				if (identifier in grammar.symbols):
					symbol = grammar.symbols[identifier]
				else:
					symbol = Symbol(identifier, identifier)
					grammar.symbols[identifier] = symbol
					grammar.nonTerminals[identifier] = symbol
				prod.append(symbol)
		self.productions.append(prod)

	def __repr__(self):
		res = self.identifier
		res += " ( " + self.fileBaseName + " )\n"
		for production in self.productions:
			res += self.identifier + " => "
			for symbol in production:
				res += symbol.identifier + " "
			res += "\n"
		return res