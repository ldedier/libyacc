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
import os
from HeaderWriter import HeaderWriter as hw
from Grammar import Grammar

class ParserGenerator:
	
	def __init__(self, path):
		fd = open(path, "r");
		self.prefix = "";
		self.nonTerminalPrefix = "";
		self.terminalPrefix = "";
		self.grammarName = "MyConcreteGrammar";
		self.folder = "./libyacc";
		self.returnType = "int";
		self.context = None;
		self.contextInstance = None;
		self.generateMain = False;
		self.parse(fd);
		self.grammar = Grammar(fd);
		print(self);

	def parse(self, fd):
		for line in fd:
			split = Grammar.smartSplit(line);
			if (len(split) == 2):
				if split[0] == "%prefix":
					self.prefix = split[1];
				if split[0] == "%terminalPrefix":
					self.terminalPrefix = split[1];
				if split[0] == "%nonTerminalPrefix":
					self.nonTerminalPrefix = split[1];
				elif split[0] == "%grammarName":
					self.grammarName = split[1];
				elif split[0] == "%folder":
					self.folder = split[1];
				elif split[0] == "%returnType":
					self.returnType = split[1];
				elif split[0] == "%context":
					self.context = split[1];
				elif split[0] == "%contextInstance":
					self.contextInstance = split[1];
				elif split[0] == "%generateMain":
					print(split[1]);
					if (split[1].lower() == "true"):
						self.generateMain = True;
					elif (split[1].lower() == "false"):
						self.generateMain = False;
					else:
						raise Exception(split[1] + ": not a valid boolean");
			elif len(split) == 1:
				if split[0] == "%tokens":
					break ;

	def openFile(self, folder, prefix, symbol, extension):
		fd = hw.openFile(sys.path[0] + "/../../" + folder + "/" + prefix + symbol.fileBaseName + extension);
		fd.write("\n");
		define = (prefix + symbol.fileBaseName).upper() + "_HPP";
		fd.write("#ifndef " + define + "\n");
		fd.write("# define " + define + "\n");
		return fd;

	def openFileString(self, folder, string, extension):
		fd = hw.openFile(sys.path[0] + "/../../" + folder + "/" + string + extension);
		return fd;

	@staticmethod
	def mkdir(path):
		if not os.path.exists(path):
			os.mkdir(path);

	def getContext(self):
		if (self.context == None):
			return "int"
		else:
			return self.context;

	def getContextInstance(self):
		if (self.context == None):
			return "dummy"
		elif (self.contextInstance == None):
			return "context"
		else:
			return self.contextInstance;

	def getDefaultReturnValue(self):
		if (self.returnType == "int"):
			return "0";
		else:
			return (self.returnType + "()");
	
	def getTypes(self):
		return "<" + self.returnType + ", " + self.getContext() + ">";

	def generateTerminalInclude(self, terminal):
		fd = self.openFile("includes", self.terminalPrefix + self.prefix, terminal, ".hpp");
	
		className = self.terminalPrefix + self.prefix + terminal.fileBaseName;
		fd.write("\n");
	#	fd.write("# include <iostream>\n");
		fd.write("# include \"AbstractTerminal.hpp\"\n");
		fd.write("\n");
		fd.write("class " + className + " : public AbstractTerminal<" + self.returnType + ", " + self.getContext() + ">\n");
		fd.write("{\n");
		fd.write("\tpublic:\n");
		fd.write("\t\t" + className + "(void);\n");
		fd.write("\t\t~" + className + "(void);\n");
		fd.write("\t\tvirtual " + self.returnType + " traverse(ASTNode" + self.getTypes() + " & ast, " + self.getContext() + " " + self.getContextInstance() + ") const;\n");
		fd.write("\n");
		fd.write("\tprivate:\n");
		fd.write("\n");
		fd.write("};\n");
		fd.write("\n");
		fd.write("#endif\n");

	def generateNonTerminalInclude(self, nonTerminal):
		fd = self.openFile("includes", self.nonTerminalPrefix + self.prefix, nonTerminal, ".hpp");
		className = self.nonTerminalPrefix + self.prefix + nonTerminal.fileBaseName;
		fd.write("\n");
	#	fd.write("# include <iostream>\n");
		fd.write("# include \""+ self.grammarName + ".hpp" + "\"\n");
		fd.write("\n");
		fd.write("class " + className + " : public AbstractNonTerminal"+  self.getTypes() + "\n");
		fd.write("{\n");
		fd.write("\tpublic:\n");
		fd.write("\t\t" + className + "(void);\n");
		fd.write("\t\t~" + className + "(void);\n");
		fd.write("\t\tvirtual " + self.returnType + " traverse(ASTNode" + self.getTypes() +" & ast, " + self.getContext() + " " + self.getContextInstance() + ") const;\n");
		fd.write("\t\tvirtual void computeProductions(AbstractGrammar" + self.getTypes() + " & cfg);\n");
		fd.write("\n");
		fd.write("\tprivate:\n");
		fd.write("\n");
		fd.write("};\n");
		fd.write("\n");
		fd.write("#endif\n");

	def generateGrammarInclude(self):
		fd = self.openFileString("includes", self.grammarName, ".hpp");
		fd.write("\n");
		define = self.grammarName.upper() + "_HPP";
		fd.write("#ifndef " + define + "\n");
		fd.write("# define " + define + "\n");
		fd.write("\n");
		fd.write("#include \"libyacc/includes/AbstractGrammar.hpp\"\n");
		fd.write("\n");
		for oldIdentifier in self.grammar.nonTerminals:
			fd.write("#include \"" + self.grammar.nonTerminals[oldIdentifier].fileBaseName + ".hpp\"\n");
		fd.write("\n");
		for oldIdentifier in self.grammar.terminals:
			fd.write("#include \"" + self.grammar.terminals[oldIdentifier].fileBaseName + ".hpp\"\n");
		fd.write("\n");
		fd.write("class " + self.grammarName + " : public AbstractGrammar" + self.getTypes() + "\n");
		fd.write("{\n");
		fd.write("\tpublic:\n");
		fd.write("\t\t" + self.grammarName + "(void);\n");
		fd.write("\t\t" + self.grammarName + "(" + self.grammarName + " const &instance);\n");
		fd.write("\t\t" + self.grammarName + " &operator=(" + self.grammarName + " const &rhs);\n");
		fd.write("\t\tvirtual ~" + self.grammarName + "(void);\n");
		fd.write("\t\tvirtual std::deque<Token" + self.getTypes() + " *> innerLex(std::istream &istream);\n")
		fd.write("\n");
		fd.write("\tprivate:");
		fd.write("\n");
		fd.write("\n};");
		fd.write("\n");
		fd.write("\n");
		fd.write("#endif\n");

	def generateIncludes(self):
		self.mkdir(sys.path[0] + "/../../" + "includes");
		for oldIdentifier in self.grammar.terminals:
			self.generateTerminalInclude(self.grammar.terminals[oldIdentifier]);
		for oldIdentifier in self.grammar.nonTerminals:
			self.generateNonTerminalInclude(self.grammar.nonTerminals[oldIdentifier]);
		self.generateGrammarInclude();
		print("generated Headers !");
	
	def generateTerminalSource(self, terminal):
		fd = self.openFile("srcs", self.terminalPrefix + self.prefix, terminal, ".cpp");
		className = self.terminalPrefix + self.prefix + terminal.fileBaseName;
		fd.write("\n");
		fd.write("# include \""+ className + ".hpp" + "\"\n");
		fd.write("\n");
		fd.write(className + "::" + className + "(void) : AbstractTerminal(\""+ terminal.identifier + "\")\n");
		fd.write("{\n\t\n}\n\n");
		fd.write(className + "::~" + className + "(void)\n");
		fd.write("{\n\t\n}\n\n");
		fd.write(self.returnType + "\t" + className + "::" + "traverse(ASTNode" + self.getTypes() + " & ast, " + self.getContext() + " " + self.getContextInstance() + ") const\n");
		fd.write("{\n");
		fd.write("\tstatic_cast<void>(ast);\n");
		fd.write("\tstatic_cast<void>(" + self.getContextInstance() + ");\n");
		fd.write("\treturn (" + self.getDefaultReturnValue() + ");\n")
		
		fd.write("}\n");
		fd.write("\n");


	def generateNonTerminalSource(self, nonTerminal):
		fd = self.openFile("srcs", self.nonTerminalPrefix + self.prefix, nonTerminal, ".cpp");
		className = self.nonTerminalPrefix + self.prefix + nonTerminal.fileBaseName;
		fd.write("\n");
		fd.write("# include \""+ className + ".hpp" + "\"\n");
		fd.write("\n");
		fd.write(className + "::" + className + "(void) : AbstractNonTerminal(\""+ nonTerminal.identifier + "\")\n");
		fd.write("{\n\t\n}\n\n");
		fd.write(className + "::~" + className + "(void)\n");
		fd.write("{\n\t\n}\n\n");
		fd.write(self.returnType + "\t" + className + "::" + "traverse(ASTNode<" + self.returnType + ", " + self.getContext() + "> & ast, " + self.getContext() + " " + self.getContextInstance() + ") const\n");
		fd.write("{\n");
		fd.write("\tstatic_cast<void>(ast);\n");
		fd.write("\tstatic_cast<void>(" + self.getContextInstance() + ");\n");
		fd.write("\treturn (" + self.getDefaultReturnValue() + ");\n")
		fd.write("}\n");
		fd.write("\n");
		fd.write("void\t" + className + "::" + "computeProductions(AbstractGrammar<" + self.returnType + ", " + self.getContext() + "> & cfg)\n");
		fd.write("{\n");
		for prod in nonTerminal.productions:
			fd.write("\taddProduction(cfg, " + str(len(prod)) + ", ");
			if (len(prod) == 0):
				fd.write("nullptr);\n");
			else:
				fd.write("(std::string[]){");
				for i, symbol in enumerate(prod):
					fd.write("\"" + symbol.identifier + "\"");
					if len(prod) - 1 != i:
						fd.write(", ");
				fd.write("});\n");
		fd.write("}\n");

	def generateGrammarSource(self):
		fd = self.openFileString("srcs", self.grammarName, ".cpp");

		fd.write("\n");
		fd.write(self.grammarName + "::" + self.grammarName + "(void) : AbstractGrammar(new " + \
			self.grammar.startSymbol.fileBaseName + "())\n");
		fd.write("{\n");
		for oldIdentifier in self.grammar.nonTerminals:
			fd.write("\taddNonTerminal(new " + self.grammar.nonTerminals[oldIdentifier].fileBaseName + "());\n");
		fd.write("\n");
		for oldIdentifier in self.grammar.terminals:
			fd.write("\taddTerminal(new " + self.grammar.terminals[oldIdentifier].fileBaseName + "());\n");
		fd.write("\n");
		fd.write("\tcomputeGrammar();\n");
		fd.write("}\n\n")
		fd.write("std::deque<Token" + self.getTypes() + " *>" + self.grammarName + "::innerLex(std::istream &istream)\n");
		fd.write("{\n")
		fd.write("\tstd::deque>Token" + self.getTypes() + " *>res;\n");
		fd.write("\treturn (res);\n");
		fd.write("}\n")
		fd.write(self.grammarName + "::" + self.grammarName + "(" + self.grammarName + " const &instance)\n");
		fd.write("{\n")
		fd.write("\t*this = instance;\n")
		fd.write("}\n\n")
		fd.write(self.grammarName + "::~" + self.grammarName + "(void)\n");
		fd.write("{\n\t\n}\n\n")
		fd.write(self.grammarName + " & " + self.grammarName + "::operator=(" + self.grammarName + " const &rhs)\n")
		fd.write("{\n");
		fd.write("\tstatic_cast<void>(rhs);\n");
		fd.write("\treturn *this;\n");
		fd.write("}\n");
	
	def generateSources(self):
		self.mkdir(sys.path[0] + "/../../" + "srcs");
		for oldIdentifier in self.grammar.terminals:
			self.generateTerminalSource(self.grammar.terminals[oldIdentifier]);
		for oldIdentifier in self.grammar.nonTerminals:
			self.generateNonTerminalSource(self.grammar.nonTerminals[oldIdentifier]);
		self.generateGrammarSource();
		print("generated sources !");

	def generateMakefile(self):
		print("generated Makefile !");
	
	def generateCode(self):
		self.generateIncludes();
		self.generateSources();
		self.generateMakefile();
	
	def __repr__(self):
		res = "";
		res += self.grammar.__repr__() + "\n";
		res += "prefix: " + self.prefix + "\n";
		res += "NonTerminalPrefix: \"" + self.nonTerminalPrefix + "\"\n";
		res += "terminalPrefix: \"" + self.terminalPrefix + "\"\n";
		res += "grammarName: \"" + self.grammarName + "\"\n";
		res += "folder: \"" + self.folder + "\"\n";
		res += "generateMain: " + str(self.generateMain) + "\n";
		return res;

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
