#!/usr/local/bin/python3
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Grammar.py                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/05 21:38:46 by ldedier           #+#    #+#              #
#    Updated: 2020/01/05 21:38:46 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from Symbol import Symbol

terminalRoles = {
	"int",
	"double",
	"string",
}

class Grammar:

	@staticmethod
	def smartSplit(line):
		split = line.rstrip().split(" ");
		split = list(filter(None, split));
		return split;

	def __repr__(self):
		res = "";
		for string in self.symbols:
			res += self.symbols[string].__repr__() + "\n";
		res += "starting symbol: " + self.startSymbol.identifier + "\n";
		return res;
	
	def __init__(self, fd):
		self.nonTerminals = {};
		self.symbols = {};
		self.terminals = {};
		self.terminalRoles = {};
		self.startSymbol = None;
		self.fillGrammar(fd);

	def parseTokens(self, line):
		split = Grammar.smartSplit(line);
		if (len(split) >= 2):
			symbol = Symbol(split[0], split[1]);
			if (len(split) == 3):
				if (not split[2] in terminalRoles):
					raise Exception(split[2] + " : not a valid role");
				self.terminalRoles[split[2]] = symbol;
				symbol.role = split[2];
			self.terminals[symbol.oldIdentifier] = symbol;
			self.symbols[symbol.oldIdentifier] = symbol;

	def getNonTerminal(self, identifier):
		if (identifier in self.nonTerminals):
			symbol = self.nonTerminals[identifier];
		else:
			symbol = Symbol(identifier, identifier);
			self.nonTerminals[identifier] = symbol;
			self.symbols[identifier] = symbol;
		return symbol

	def parseNonTerminals(self, line, fd):
		split = Grammar.smartSplit(line);
		if len(split) >= 2 and split[1] == ':':
			symbol = self.getNonTerminal(split[0]);
			symbol.addProduction(split[2:], self);
			for line in fd:
				split = Grammar.smartSplit(line);
				if len(split) >= 1:
					if split[0] == ';':
						break ;
					elif (split[0] != '|'):
						raise Exception("line \"" + line + "\" not well formated");
					else:
						symbol.addProduction(split[1:], self);
		elif len(split) == 2 and split[0] == "%start":
			self.startSymbol = self.getNonTerminal(split[1]);

	def fillGrammar(self, fd):
		for line in fd:
			if line == "%nonterminals\n":
				break ;
			else:
				self.parseTokens(line);
		for line in fd:
			self.parseNonTerminals(line, fd);
		if self.startSymbol == None:
			raise Exception("You shall add the starting symbol of your grammar\n"\
				"with: %start id in the %NONTERMINALS section");
