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

from ast import arg
import sys
import os
import argparse
from os import path as osp
from HeaderWriter import HeaderWriter as hw
from Grammar import Grammar
from Confirm import confirm

class ParserGenerator:

	def __init__(self, configPath, override, files):
		self.prefix = ""
		self.nonTerminalPrefix = ""
		self.terminalPrefix = ""
		self.grammarName = "MyConcreteGrammar"
		self.makefileFolder = "../../"
		self.libyaccFolder = "."
		self.generatedIncludesFolder = "../../includes/parser/"
		self.generatedSourcesFolder = "../../srcs/parser/"

		self.makefileRefSourcesFolder = "srcs/parser/"
		self.makefileRefIncludesFolder = "includes/parser/"

		self.returnType = "int"
		self.contextType = None
		self.contextInstance = None
		self.contextFileBaseName = None
		self.passContextBy = "reference"
		self.generateMain = False
		self.programName = "a.out"
		self.blankAsDelimiter = True
		self.stopAtNewLine = False
		self.grammar = Grammar()
		self.grammar.blankAsDelimiter = self.blankAsDelimiter
		self.parse(open(configPath, "r"))
		if self.passContextBy == "reference":
			self.contextSuffix = " &"
		elif (self.passContextBy == "pointer"):
			self.contextSuffix = " *"
		else:
			self.contextSuffix = ""
		self.override = override
		self.files = files
		print(self)

	def parse(self, fd):
		for line in fd:
			split = Grammar.smartSplit(line)
			if len(split) == 2:
				if split[0] == "%prefix":
					self.prefix = split[1]
				elif split[0] == "%terminalPrefix":
					self.terminalPrefix = split[1]
				elif split[0] == "%nonTerminalPrefix":
					self.nonTerminalPrefix = split[1]
				elif split[0] == "%grammarName":
					self.grammarName = split[1]
				elif split[0] == "%returnType":
					self.returnType = split[1]
				elif split[0] == "%contextType":
					self.contextType = split[1]
				elif split[0] == "%generatedIncludesFolder":
					self.generatedIncludesFolder = split[1]
				elif split[0] == "%generatedSourcesFolder":
					self.generatedSourcesFolder = split[1]
				elif split[0] == "%makefileFolder":
					self.makefileFolder = split[1]
				elif split[0] == "%libyaccFolder":
					self.libyaccFolder = split[1]
				elif split[0] == "%programName":
					self.programName = split[1]
				elif split[0] == "%contextInstance":
					self.contextInstance = split[1]
				elif split[0] == "%contextFileBaseName":
					self.contextFileBaseName = split[1]
				elif split[0] == "%passContextBy":
					if (split[1].lower() == "copy" or split[1].lower() == "reference" or split[1].lower() == "pointer"):
						self.passContextBy = split[1].lower()
					else:
						raise Exception(split[1] + ": not a valid argument (copy/reference/pointer)")
				elif split[0] == "%generateMain":
					if (split[1].lower() == "true"):
						self.generateMain = True
					elif (split[1].lower() == "false"):
						self.generateMain = False
					else:
						raise Exception(split[1] + ": not a valid boolean")
				elif split[0] == "%blankAsDelimiter":
					if (split[1].lower() == "true"):
						self.blankAsDelimiter = True
					elif (split[1].lower() == "false"):
						self.blankAsDelimiter = False
					else:
						raise Exception(split[1] + ": not a valid boolean")
				elif split[0] == "%stopAtNewLine":
					if (split[1].lower() == "true"):
						self.stopAtNewLine = True
					elif (split[1].lower() == "false"):
						self.stopAtNewLine = False
					else:
						raise Exception(split[1] + ": not a valid boolean")
				elif (len(split[0]) and split[0][0] != '#'):
					raise Exception(split[0] + ": invalid option")
			elif len(split) == 1:
				if split[0] == "%%tokens":
					self.grammar.parseTokensFromFd(fd)
				elif split[0] == "%%nonterminals":
					self.grammar.parseNonTerminalsFromFd(fd)
				elif split[0] == "%%markStartOfComment":
					self.grammar.parseMarkStartOfCommentFromFd(fd)
				elif split[0] == "%%markEndOfComment":
					self.grammar.parseMarkEndOfCommentFromFd(fd)

	def checkFileCreation(self, folder, name, extension=''):
		## override
		# confirm: replace if confirmation
		# noconfirm: replace without having to confirm
		# no-override: do not replace ever
		## files
		# if empty: all files

		basename = name + extension
		filename = osp.join(folder, name) + extension

		if self.files and basename not in self.files:
			return False
		existFilename = osp.exists(filename)
		if self.override == 'confirm' and existFilename and not confirm(f'override {filename} ?'):
			return False
		elif self.override == 'noOverride' and existFilename:
			if self.files and basename in self.files:
				print(f'did not generate {filename} because it already exist (use -f option to force overriding files)')
			return False
		return True

	def openFile(self, folder, name, extension=''):
		fd = hw.openFile(osp.join(folder, name + extension))
		return fd

	def openFileHeader(self, folder, name, extension):
		fd = self.openFile(folder, name, extension)
		fd.write("\n")
		define = name.upper() + "_HPP"
		fd.write("#ifndef " + define + "\n")
		fd.write("# define " + define + "\n")
		return fd

	@staticmethod
	def mkdir(path):
		os.makedirs(path, exist_ok=True)

	def getContextType(self):
		if (self.contextType == None):
			return "int"
		else:
			return self.contextType

	def getContextTypeWithSuffix(self):
		return self.getContextType() + self.contextSuffix

	def getContextInstance(self):
		if (self.contextType == None):
			return "dummy"
		elif (self.contextInstance == None):
			return "context"
		else:
			return self.contextInstance

	def getDefaultReturnValue(self):
		if (self.returnType == "int"):
			return "0"
		else:
			return (self.returnType + "()")

	def getTypes(self):
		return "<" + self.returnType + ", " + self.getContextTypeWithSuffix() + ">"

	def getFullBaseName(self, symbol):
		if len(symbol.productions) == 0:
			pref = self.terminalPrefix
		else:
			pref = self.nonTerminalPrefix
		return self.prefix + pref + symbol.fileBaseName

	def generateTerminalInclude(self, terminal):
		openFileHeaderArgs=(self.generatedIncludesFolder, self.getFullBaseName(terminal), ".hpp")
		if not self.checkFileCreation(*openFileHeaderArgs): return
		fd = self.openFileHeader(*openFileHeaderArgs)
		className = self.getFullBaseName(terminal)
		fd.write("\n")
		fd.write("# include "+"\"" + terminal.subClass + ".hpp\"\n")
		if (self.contextFileBaseName != None):
			fd.write("# include \"" + self.contextFileBaseName + ".hpp\"\n")
		fd.write("\n")
		fd.write("class " + className + " : public "+ terminal.subClass + "<" + self.returnType + ", " + self.getContextTypeWithSuffix() + ">\n")
		fd.write("{\n")
		fd.write("\tpublic:\n")
		fd.write("\t\t" + className + "(void);\n")
		fd.write("\t\t~" + className + "(void);\n")
		fd.write("\t\tvirtual " + self.returnType + " traverse(ASTNode" + self.getTypes() + " & ast, " + self.getContextTypeWithSuffix() + " " + self.getContextInstance() + ") const;\n")
		fd.write("\n")
		fd.write("\tprivate:\n")
		fd.write("\n")
		fd.write("};\n")
		fd.write("\n")
		fd.write("#endif\n")

	def generateNonTerminalInclude(self, nonTerminal):
		openFileHeaderArgs=(self.generatedIncludesFolder, self.getFullBaseName(nonTerminal), ".hpp")
		if not self.checkFileCreation(*openFileHeaderArgs): return
		fd = self.openFileHeader(*openFileHeaderArgs)
		className = self.getFullBaseName(nonTerminal)
		fd.write("\n")
		fd.write("# include \""+ self.grammarName + ".hpp" + "\"\n")
		fd.write("\n")
		fd.write("class " + className + " : public AbstractNonTerminal"+  self.getTypes() + "\n")
		fd.write("{\n")
		fd.write("\tpublic:\n")
		fd.write("\t\t" + className + "(void);\n")
		fd.write("\t\t~" + className + "(void);\n")
		fd.write("\t\tvirtual " + self.returnType + " traverse(ASTNode" + self.getTypes() +" & ast, " + self.getContextTypeWithSuffix() + " " + self.getContextInstance() + ") const;\n")
		fd.write("\t\tvirtual void computeProductions(AbstractGrammar" + self.getTypes() + " & cfg);\n")
		fd.write("\n")
		fd.write("\tprivate:\n")
		fd.write("\n")
		fd.write("};\n")
		fd.write("\n")
		fd.write("#endif\n")

	def generateGrammarInclude(self):
		openFileHeaderArgs=(self.generatedIncludesFolder, self.grammarName, ".hpp")
		if not self.checkFileCreation(*openFileHeaderArgs): return
		fd = self.openFileHeader(*openFileHeaderArgs)
		fd.write("#include \"AbstractGrammar.hpp\"\n")
		fd.write("\n")
		if (self.contextFileBaseName != None):
			fd.write("#include \"" + self.contextFileBaseName + ".hpp\"\n")
		for identifier in self.grammar.nonTerminals:
			fd.write("#include \"" + self.getFullBaseName(self.grammar.nonTerminals[identifier]) + ".hpp\"\n")
		fd.write("\n")
		for identifier in self.grammar.terminals:
			fd.write("#include \"" + self.getFullBaseName(self.grammar.terminals[identifier]) + ".hpp\"\n")
		fd.write("\n")
		fd.write("class " + self.grammarName + " : public AbstractGrammar" + self.getTypes() + "\n")
		fd.write("{\n")
		fd.write("\tpublic:\n")
		fd.write("\t\t" + self.grammarName + "(void);\n")
		fd.write("\t\t" + self.grammarName + "(" + self.grammarName + " const &instance);\n")
		fd.write("\t\t" + self.grammarName + " &operator=(" + self.grammarName + " const &rhs);\n")
		fd.write("\t\tvirtual ~" + self.grammarName + "(void);\n")
		if self.grammar.markStartOfComment != None:
			fd.write("\t\tvirtual bool markStartOfComment(std::string currentLex);\n")
		if self.grammar.markEndOfComment != None:
			fd.write("\t\tvirtual bool markEndOfComment(std::string currentLex);\n")
		fd.write("\n")
		fd.write("\tprivate:")
		fd.write("\n")
		fd.write("\n};")
		fd.write("\n")
		fd.write("\n")
		fd.write("#endif\n")

	def generateBasicInclude(self, path, baseClassName):
		openFileHeaderArgs=(path, baseClassName, ".hpp")
		if not self.checkFileCreation(*openFileHeaderArgs): return
		fd = self.openFileHeader(*openFileHeaderArgs)
		fd.write("\n")
		fd.write("class " + baseClassName + "\n")
		fd.write("{\n")
		fd.write("\n")
		fd.write("\tpublic:\n\n")
		fd.write("\t\t" + baseClassName + "(void);\n")
		fd.write("\t\t" + baseClassName + "(" + baseClassName + " const &instance);\n")
		fd.write("\t\t" + baseClassName + " & " + "operator=(" + baseClassName + " const &rhs);\n")
		fd.write("\t\t" + "~" + baseClassName + "(void);\n")
		fd.write("\n")
		fd.write("};\n")
		fd.write("#endif\n")

	def generateIncludes(self):
		self.mkdir(sys.path[0] + "/" + self.generatedIncludesFolder)
		for identifier in self.grammar.terminals:
			self.generateTerminalInclude(self.grammar.terminals[identifier])
		for identifier in self.grammar.nonTerminals:
			self.generateNonTerminalInclude(self.grammar.nonTerminals[identifier])
		self.generateGrammarInclude()
		if self.contextFileBaseName != None:
			self.generateBasicInclude(self.generatedIncludesFolder, self.contextFileBaseName)

	def generateTerminalSource(self, terminal):
		openFileArgs=(self.generatedSourcesFolder, self.getFullBaseName(terminal), ".cpp")
		if not self.checkFileCreation(*openFileArgs): return
		fd = self.openFile(*openFileArgs)
		className = self.getFullBaseName(terminal)
		fd.write("\n")
		fd.write("# include \"" + className + ".hpp" + "\"\n")
		fd.write("\n")
		fd.write(className + "::" + className + "(void) : " + terminal.subClass +"(\""+ terminal.identifier + "\")\n")
		fd.write("{\n\t\n}\n\n")
		fd.write(className + "::~" + className + "(void)\n")
		fd.write("{\n\t\n}\n\n")
		fd.write(self.returnType + "\t" + className + "::" + "traverse(ASTNode" + self.getTypes() + " & ast, " + self.getContextTypeWithSuffix() + " " + self.getContextInstance() + ") const\n")
		fd.write("{\n")
		fd.write("\tstatic_cast<void>(ast);\n")
		fd.write("\tstatic_cast<void>(" + self.getContextInstance() + ");\n")
		fd.write("\treturn (" + self.getDefaultReturnValue() + ");\n")
		fd.write("}\n")
		fd.write("\n")

	def generateNonTerminalSource(self, nonTerminal):
		openFileArgs=(self.generatedSourcesFolder, self.getFullBaseName(nonTerminal), ".cpp")
		if not self.checkFileCreation(*openFileArgs): return
		fd = self.openFile(*openFileArgs)
		className = self.getFullBaseName(nonTerminal)
		fd.write("\n")
		fd.write("# include \""+ className + ".hpp" + "\"\n")
		fd.write("\n")
		fd.write(className + "::" + className + "(void) : AbstractNonTerminal(\""+ nonTerminal.identifier + "\")\n")
		fd.write("{\n\t\n}\n\n")
		fd.write(className + "::~" + className + "(void)\n")
		fd.write("{\n\t\n}\n\n")
		fd.write(self.returnType + "\t" + className + "::" + "traverse(ASTNode<" + self.returnType + ", " + self.getContextTypeWithSuffix() + "> & ast, " + self.getContextTypeWithSuffix() + " " + self.getContextInstance() + ") const\n")
		fd.write("{\n")
		fd.write("\tstatic_cast<void>(ast);\n")
		fd.write("\tstatic_cast<void>(" + self.getContextInstance() + ");\n")
		fd.write("\treturn (" + self.getDefaultReturnValue() + ");\n")
		fd.write("}\n")
		fd.write("\n")
		fd.write("void\t" + className + "::" + "computeProductions(AbstractGrammar<" + self.returnType + ", " + self.getContextTypeWithSuffix() + "> & cfg)\n")
		fd.write("{\n")
		for prod in nonTerminal.productions:
			fd.write("\taddProduction(cfg, {")
			for i, symbol in enumerate(prod):
				fd.write("\"" + symbol.identifier + "\"")
				if len(prod) - 1 != i:
					fd.write(", ")
			if len(prod) > 0 and prod[0].identifier == nonTerminal.identifier:
				fd.write("}, true);\n") # automatize AST node replacing process on recursive productions
			else:
				fd.write("});\n")
		fd.write("}\n")

	def generateGrammarSource(self):
		openFileArgs=(self.generatedSourcesFolder, self.grammarName, ".cpp")
		if not self.checkFileCreation(*openFileArgs): return
		fd = self.openFile(*openFileArgs)
		fd.write("\n")
		fd.write("#include \"" + self.grammarName + ".hpp\"\n")
		if (self.contextFileBaseName != None):
			fd.write("#include \"" + self.contextFileBaseName + ".hpp\"\n")
		fd.write("\n")
		fd.write(self.grammarName + "::" + self.grammarName + "(void) : AbstractGrammar(new " + \
		self.getFullBaseName(self.grammar.startSymbol) + "(), " + ("true" if self.grammar.blankAsDelimiter else "false")+ ")\n")
		fd.write("{\n")
		for identifier in self.grammar.nonTerminals:
			if (identifier != self.grammar.startSymbol.identifier):
				fd.write("\taddNonTerminal(new " + self.getFullBaseName(self.grammar.nonTerminals[identifier]) + "());\n")
		fd.write("\n")
		for identifier in self.grammar.terminals:
			fd.write("\taddTerminal(new " + self.getFullBaseName(self.grammar.terminals[identifier]) + "());\n")
		fd.write("\n")
		fd.write("\tcomputeGrammar();\n")
		fd.write("}\n\n")
		fd.write(self.grammarName + "::" + self.grammarName + "(" + self.grammarName + " const &instance) : AbstractGrammar" + self.getTypes() + "(instance)\n")
		fd.write("{\n")
		fd.write("\t*this = instance;\n")
		fd.write("}\n\n")
		fd.write(self.grammarName + "::~" + self.grammarName + "(void)\n")
		fd.write("{\n\t\n}\n\n")
		fd.write(self.grammarName + " & " + self.grammarName + "::operator=(" + self.grammarName + " const &rhs)\n")
		fd.write("{\n")
		fd.write("\tstatic_cast<void>(rhs);\n")
		fd.write("\treturn *this;\n")
		fd.write("}\n")
		if self.grammar.markStartOfComment != None:
			fd.write("\n")
			fd.write("bool " + self.grammarName + "::markStartOfComment(std::string currentLex)\n")
			fd.write("{\n")
			fd.write(self.grammar.markStartOfComment)
			fd.write("}\n")
		if self.grammar.markEndOfComment != None:
			fd.write("\n")
			fd.write("bool " + self.grammarName + "::markEndOfComment(std::string currentLex)\n")
			fd.write("{\n")
			fd.write(self.grammar.markEndOfComment)
			fd.write("}\n")

	def generateMainSource(self):
		openFileArgs=(self.generatedSourcesFolder, "main", ".cpp")
		if not self.checkFileCreation(*openFileArgs): return
		fd = self.openFile(*openFileArgs)
		fd.write("\n")
		fd.write("#include \"" + self.grammarName + ".hpp\"\n")
		fd.write("#include \"LRParser.hpp\"\n")
		fd.write("\n")
		fd.write("int main(void)\n")
		fd.write("{\n")
		fd.write("\t" + self.grammarName + " grammar;\n")
		fd.write("\tLRParser" + self.getTypes() + " parser(grammar);\n")
		fd.write("\tstd::deque<Token" + self.getTypes() + " *> tokens;\n")
		if (self.passContextBy != "copy"):
			fd.write("\t" + self.getContextType() + " " + self.getContextInstance() + ";\n")
		fd.write("\n")
		fd.write("\tgrammar.debug(false);\n")
		fd.write("\ttry\n")
		fd.write("\t{\n")
		fd.write("\t\ttokens = grammar.lex(" + ("true" if self.stopAtNewLine else "false") +", std::cin);\n")
		fd.write("\t\tprintTokenQueue(tokens);\n")
		fd.write("\t\tASTBuilder" + self.getTypes() + "*b = parser.parse(tokens);\n")
		if (self.passContextBy == "copy"):
			fd.write("\t\t" + self.returnType + " res = b->getASTRoot()->getTraversed(" + self.getContextType() + "()" + ");\n")
		elif (self.passContextBy == "reference"):
			fd.write("\t\t" + self.returnType + " res = b->getASTRoot()->getTraversed(" + self.getContextInstance() + ");\n")
		elif (self.passContextBy == "pointer"):
			fd.write("\t\t" + self.returnType + " res = b->getASTRoot()->getTraversed(" + "&" + self.getContextInstance() + ");\n")
		fd.write("\t\tstd::cout << *b << std::endl;\n")
		fd.write("\t\tstd::cout << \"result: \" << res << std::endl;\n")
		fd.write("\t\tdelete b;\n")
		fd.write("\t\tdeleteTokens(tokens);\n")
		fd.write("\t}\n")
		fd.write("\tcatch (const LRActionError" + self.getTypes() + "::SyntaxErrorException &e)\n")
		fd.write("\t{\n")
		fd.write("\t\tdeleteTokens(tokens);\n")
		fd.write("\t\tstd::cerr << std::endl << e.what() << std::endl;\n")
		fd.write("\t}\n")
		fd.write("\tcatch (const AbstractGrammar" + self.getTypes() + "::LexicalErrorException &e)\n")
		fd.write("\t{\n")
		fd.write("\t\tdeleteTokens(tokens);\n")
		fd.write("\t\tstd::cerr << e.what() << std::endl;\n")
		fd.write("\t}\n")
		fd.write("\treturn (0);\n")
		fd.write("}\n")

	def generateBasicSource(self, path, baseClassName):
		openFileArgs=(path, baseClassName, ".cpp")
		if not self.checkFileCreation(*openFileArgs): return
		fd = self.openFile(*openFileArgs)
		fd.write("\n")
		fd.write("#include \"" + baseClassName + ".hpp\"\n")
		fd.write("\n")
		fd.write(baseClassName + "::" + baseClassName + "(void) \n")
		fd.write("{\n\t\n}\n\n")
		fd.write(baseClassName + "::" + baseClassName + "(" + baseClassName + " const &instance)\n")
		fd.write("{\n")
		fd.write("\t*this = instance;\n")
		fd.write("}\n\n")
		fd.write(baseClassName + "::~" + baseClassName + "(void)\n")
		fd.write("{\n\t\n}\n\n")
		fd.write(baseClassName + " & " + baseClassName + "::operator=(" + baseClassName + " const &rhs)\n")
		fd.write("{\n")
		fd.write("\tstatic_cast<void>(rhs);\n")
		fd.write("\treturn *this;\n")
		fd.write("}\n")

	def generateSources(self):
		self.mkdir(sys.path[0] + "/" + self.generatedSourcesFolder)
		for identifier in self.grammar.terminals:
			self.generateTerminalSource(self.grammar.terminals[identifier])
		for identifier in self.grammar.nonTerminals:
			self.generateNonTerminalSource(self.grammar.nonTerminals[identifier])
		self.generateGrammarSource()
		if (self.generateMain):
			self.generateMainSource()
		if self.contextFileBaseName != None:
			self.generateBasicSource(self.generatedSourcesFolder, self.contextFileBaseName)

	def generateMakefile(self):
		if not self.checkFileCreation(self.makefileFolder, "Makefile"): return
		fd = hw.openFile(osp.join(self.makefileFolder, "Makefile"), "#", "#")
		fd.write("\n")
		fd.write("NAME\t\t\t=\t" + self.programName + "\n")
		fd.write("\n")
		fd.write("CC\t\t\t\t=\tg++ -std=c++11 -O3\n")
		fd.write("\n")
		fd.write("ECHO\t\t\t=\techo\n")
		fd.write("MKDIR\t\t\t=\tmkdir\n")
		fd.write("\n")
		fd.write("DEBUG ?= 0\n")
		fd.write("\n")
		fd.write("SRCDIR\t\t\t=\t" + self.makefileRefSourcesFolder + "\n")
		fd.write("OBJDIR\t\t\t=\tobjs/\n")
		fd.write("BINDIR\t\t\t=\t./\n")
		fd.write("INCLUDESDIR\t\t=\t" + self.makefileRefIncludesFolder + "\n")
		fd.write("\n")
		fd.write("INCLUDES\t\t=\t" + self.grammarName + ".hpp \\\n")

		for identifier in self.grammar.terminals:
			fd.write("\t\t\t\t\t" + self.getFullBaseName(self.grammar.terminals[identifier]) + ".hpp \\\n")
		for identifier in self.grammar.nonTerminals:
			fd.write("\t\t\t\t\t" + self.getFullBaseName(self.grammar.nonTerminals[identifier]) + ".hpp \\\n")
		if (self.contextFileBaseName != None):
			fd.write("\t\t\t\t\t" + self.contextFileBaseName + ".hpp \\\n")


		fd.write("\n")
		fd.write("SRCS\t\t\t=\t" + self.grammarName + ".cpp \\\n")

		for identifier in self.grammar.terminals:
			fd.write("\t\t\t\t\t" + self.getFullBaseName(self.grammar.terminals[identifier]) + ".cpp \\\n")
		for identifier in self.grammar.nonTerminals:
			fd.write("\t\t\t\t\t" + self.getFullBaseName(self.grammar.nonTerminals[identifier]) + ".cpp \\\n")
		if self.generateMain:
			fd.write("\t\t\t\t\t" + "main.cpp \\\n")
		if (self.contextFileBaseName != None):
			fd.write("\t\t\t\t\t" + self.contextFileBaseName + ".cpp \\\n")
		fd.write("\n")
		fd.write("VPATH\t\t\t\t=\t$(INCLUDESDIR) \\\n")
		fd.write("\t\t\t\t\t=\t$(SRCDIR)\n")
		fd.write("\n")
		fd.write("OBJECTS\t\t\t=\t$(addprefix $(OBJDIR), $(SRCS:.cpp=.o))")
		fd.write("\n")
		fd.write("CFLAGS\t\t\t=\t-I $(INCLUDESDIR) -Wall -Wextra -Werror -I " + osp.join(self.libyaccFolder, "libyacc", "includes") + "\n")
		fd.write("LFLAGS\t\t\t=\t")
		fd.write("\n")
		fd.write("OK_COLOR\t\t\t=\t\\033[92m\n")
		fd.write("EOC\t\t\t\t\t=\t\\033[0m\n")
		fd.write("\n")
		fd.write("ifeq ($(DEBUG), 1)\n")
		fd.write("\tCFLAGS += -fsanitize=address\n")
		fd.write("\tLFLAGS += -fsanitize=address\n")
		fd.write("\tCC += -g3\n")
		fd.write("endif\n")
		fd.write("\n")
		fd.write("all: $(NAME)\n")
		fd.write("\n")
		fd.write("debug:\n")
		fd.write("\t@$(MAKE) all DEBUG=1\n")
		fd.write("\n")
		fd.write("$(BINDIR)$(NAME): $(OBJDIR) $(OBJECTS)\n")
		fd.write("\t$(CC) -o $@ $(OBJECTS) $(LFLAGS)\n")
		fd.write("\t@$(ECHgO) \"$(OK_COLOR)$(NAME) linked with success ! $(EOC)\"\n")
		fd.write("\n")
		fd.write("$(OBJDIR):\n")
		fd.write("\t@$(MKDIR) $@\n")
		fd.write("\n")
		fd.write("$(OBJDIR)%.o: $(SRCDIR)%.cpp $(INCLUDES)\n")
		fd.write("\t$(CC) -c $< -o $@ $(CFLAGS)\n")
		fd.write("\n")
		fd.write("clean:\n")
		fd.write("\t@$(RM) -rf $(OBJDIR)")
		fd.write("\n")
		fd.write("fclean: clean\n")
		fd.write("\t@$(RM) -f $(BINDIR)$(NAME)\n")
		fd.write("\n")
		fd.write("re: fclean all\n")
		fd.write("\n")
		fd.write(".PHONY: all clean fclean re debug\n")
		print("generated Makefile !")

	def generateCode(self):
		self.generateIncludes()
		self.generateSources()
		self.generateMakefile()

	def __repr__(self):
		res = ""
		res += self.grammar.__repr__() + "\n"
		res += "prefix: \"" + self.prefix + "\"\n"
		res += "NonTerminalPrefix: \"" + self.nonTerminalPrefix + "\"\n"
		res += "terminalPrefix: \"" + self.terminalPrefix + "\"\n"
		res += "grammarName: \"" + self.grammarName + "\"\n"
		res += "generateMain: " + str(self.generateMain) + "\n"
		res += "returnType: \"" + self.returnType + "\"\n"
		res += "contextType: \"" + self.getContextType() + "\"\n"
		res += "contextInstance: \"" + self.getContextInstance() + "\"\n"
		if (self.contextFileBaseName != None):
			res += "contextFileBaseName: \"" + self.contextFileBaseName + "\"\n"
		else:
			res += "contextFileBaseName: None\n"
		return res

class NamebaseAction(argparse.Action):
	def __init__(self, option_strings, dest, **kwargs):
		super().__init__(option_strings, dest, '+', **kwargs)
	def __call__(self, parser, namespace, values, option_string=None):
		setattr(namespace, self.dest, [osp.basename(val) for val in values])

if __name__ == '__main__':
	argParser = argparse.ArgumentParser('generate a c++ parser skeleton from a config file')
	argParser.add_argument('confPath', help="path of the config file", type=str)
	argParser.add_argument('-f'                , dest='override', action='store_const', help="override without confirmation"   , const='noConfirm', default='noOverride')
	argParser.add_argument('--override-confirm', dest='override', action='store_const', help="override files with confirmation", const='confirm'  , default='noOverride')
	argParser.add_argument('--files', metavar='file', action=NamebaseAction, help="files to generate")

	args = argParser.parse_args()
	if not args.files and args.override == 'noConfirm' and not confirm("You are about to override all of the files already generated, continue ?"):
		exit(0)
	gen = ParserGenerator(args.confPath, args.override, args.files)
	gen.generateCode()
	exit(0)