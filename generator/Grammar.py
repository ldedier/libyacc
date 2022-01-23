# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Grammar.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/05 21:38:46 by ldedier           #+#    #+#              #
#    Updated: 2022/01/23 04:52:37 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from Symbol import Symbol

terminalSubclasses = {
	"int": "AbstractIntegerTerminal",
	"unsigned_int": "AbstractUnsignedIntegerTerminal",
	"separator": "AbstractSeparatorTerminal",
	"string": "AbstractStringTerminal",
	"float": "AbstractFloatTerminal",
}

class Grammar:

	@staticmethod
	def smartSplit(line):
		if (line.lstrip().startswith('#')): return []
		return line.split()

	def __repr__(self):
		res = ""
		for string in self.symbols:
			res += self.symbols[string].__repr__() + "\n"
		res += "starting symbol: " + self.startSymbol.identifier + "\n"
		return res

	def __init__(self):
		self.nonTerminals = {}
		self.symbols = {}
		self.terminals = {}
		self.startSymbol = None
		self.blankAsDelimiter = True
		self.markStartOfComment = None
		self.markEndOfComment = None

	def parseTokens(self, line):
		split = Grammar.smartSplit(line)
		if (len(split) >= 2):
			symbol = Symbol(split[0], split[1])
			if (len(split) == 3):
				if (not split[2] in list(terminalSubclasses.keys())):
					raise Exception(split[2] + " : not a valid role")
				symbol.subClass = terminalSubclasses[split[2]]
			self.terminals[symbol.identifier] = symbol
			self.symbols[symbol.identifier] = symbol

	def getNonTerminal(self, identifier):
		if (identifier in self.nonTerminals):
			symbol = self.nonTerminals[identifier]
		else:
			symbol = Symbol(identifier, identifier)
			self.nonTerminals[identifier] = symbol
			self.symbols[identifier] = symbol
		return symbol

	def parseNonTerminals(self, fd):
		split = Grammar.smartSplit(line)
		if len(split) >= 2 and split[1] == ':':
			symbol = self.getNonTerminal(split[0])
			symbol.addProduction(split[2:], self)
			for line in fd:
				split = Grammar.smartSplit(line)
				if len(split) >= 1:
					if split[0] == ';':
						break
					elif (split[0] != '|'):
						raise Exception("line \"" + line + "\" not well formated")
					else:
						symbol.addProduction(split[1:], self)
		elif len(split) == 2 and split[0] == "%start":
			self.startSymbol = self.getNonTerminal(split[1])

	def fillGrammar(self, fd):
		for line in fd:
			if line == "%nonterminals\n":
				break
			else:
				self.parseTokens(line)
		for line in fd:
			self.parseNonTerminals(line, fd)

	def parseTokensFromFd(self, fd):
		for line in fd:
			if line.startswith("%%"):
				break
			else:
				self.parseTokens(line)

	def parseNonTerminalsFromFd(self, fd):
		for line in fd:
			split = Grammar.smartSplit(line)
			if len(split) >= 1 and split[0] == "%%":
				if self.startSymbol == None:
					raise Exception("You shall add the starting symbol of your grammar\n"\
					"with: %start id in the %%nonterminals section")
				break
			else:
				if len(split) >= 2 and split[1] == ':':
					symbol = self.getNonTerminal(split[0])
					symbol.addProduction(split[2:], self)
					for line in fd:
						split = Grammar.smartSplit(line)
						if len(split) >= 1:
							if split[0] == ';':
								break
							elif (split[0] != '|'):
								raise Exception("line \"" + line + "\" not well formated")
							else:
								symbol.addProduction(split[1:], self)
				elif len(split) == 2 and split[0] == "%start":
					self.startSymbol = self.getNonTerminal(split[1])

	def parseMarkStartOfCommentFromFd(self, fd):
		self.markStartOfComment = ''
		for line in fd:
			if line.startswith("%%"):
				break
			else:
				self.markStartOfComment += line

	def parseMarkEndOfCommentFromFd(self, fd):
		self.markEndOfComment = ''
		for line in fd:
			if line.startswith("%%"):
				break
			else:
				self.markEndOfComment += line
