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
		self.returnType = "int";
		self.context = None;
		self.contextInstance = None;
		self.contextFileBaseName = None;
		self.generateMain = False;
		self.programName = "a.out";
		self.blankAsDelimiter = True;
		self.parse(fd);
		self.grammar = Grammar(fd);
		self.grammar.blankAsDelimiter = self.blankAsDelimiter;
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
				elif split[0] == "%returnType":
					self.returnType = split[1];
				elif split[0] == "%contextType":
					self.context = split[1];
				elif split[0] == "%programName":
					self.programName = split[1];
				elif split[0] == "%contextInstance":
					self.contextInstance = split[1];
				elif split[0] == "%contextFileBaseName":
					self.contextFileBaseName = split[1];
				elif split[0] == "%generateMain":
					if (split[1].lower() == "true"):
						self.generateMain = True;
					elif (split[1].lower() == "false"):
						self.generateMain = False;
					else:
						raise Exception(split[1] + ": not a valid boolean");
				elif split[0] == "%blankAsDelimiter":
					if (split[1].lower() == "true"):
						self.blankAsDelimiter = True;
					elif (split[1].lower() == "false"):
						self.blankAsDelimiter = False;
					else:
						raise Exception(split[1] + ": not a valid boolean");
			elif len(split) == 1:
				if split[0] == "%tokens":
					break ;

	def openFile(self, folder, name, extension):
		fd = hw.openFile(sys.path[0] + "/../../" + folder + "/" + name + extension);
		return fd;
	
	def openFileHeader(self, folder, name, extension):
		fd = hw.openFile(sys.path[0] + "/../../" + folder + "/" + name + extension);
		fd.write("\n");
		define = name.upper() + "_HPP";
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

	def getFullBaseName(self, symbol):
		
		if len(symbol.productions) == 0:
			pref = self.terminalPrefix;
		else:
			pref = self.nonTerminalPrefix;
		return self.prefix + pref + symbol.fileBaseName;


	def generateTerminalInclude(self, terminal):
		fd = self.openFileHeader("includes", self.getFullBaseName(terminal), ".hpp");
	
		className = self.getFullBaseName(terminal);
		fd.write("\n");
	#	fd.write("# include <iostream>\n");
		fd.write("# include "+"\"" + terminal.subClass + ".hpp\"\n");
		fd.write("\n");
		fd.write("class " + className + " : public "+ terminal.subClass + "<" + self.returnType + ", " + self.getContext() + ">\n");	
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
		fd = self.openFileHeader("includes", self.getFullBaseName(nonTerminal), ".hpp");
		className = self.getFullBaseName(nonTerminal);
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
		fd.write("#include \"../libyacc/includes/AbstractGrammar.hpp\"\n");
		fd.write("\n");
		if (self.contextFileBaseName != None):
			fd.write("#include \"" + self.contextFileBaseName + ".hpp\"\n");
		for oldIdentifier in self.grammar.nonTerminals:
			fd.write("#include \"" + self.getFullBaseName(self.grammar.nonTerminals[oldIdentifier]) + ".hpp\"\n");
		fd.write("\n");
		for oldIdentifier in self.grammar.terminals:
			fd.write("#include \"" + self.getFullBaseName(self.grammar.terminals[oldIdentifier]) + ".hpp\"\n");
		fd.write("\n");
		fd.write("class " + self.grammarName + " : public AbstractGrammar" + self.getTypes() + "\n");
		fd.write("{\n");
		fd.write("\tpublic:\n");
		fd.write("\t\t" + self.grammarName + "(void);\n");
		fd.write("\t\t" + self.grammarName + "(" + self.grammarName + " const &instance);\n");
		fd.write("\t\t" + self.grammarName + " &operator=(" + self.grammarName + " const &rhs);\n");
		fd.write("\t\tvirtual ~" + self.grammarName + "(void);\n");
		#fd.write("\t\tvirtual std::deque<Token" + self.getTypes() + " *> innerLex(std::istream &istream);\n")
		fd.write("\n");
		fd.write("\tprivate:");
		fd.write("\n");
		fd.write("\n};");
		fd.write("\n");
		fd.write("\n");
		fd.write("#endif\n");

	def generateBasicInclude(self, path, baseClassName, override):
		fileFullPath = path + "/" + baseClassName + ".hpp";
		if not os.path.exists(fileFullPath) and not override:
			return;
		fd = open(fileFullPath, "w");
		hw.writeHeader(fd, fileFullPath);
		fd.write("\n");
		define = baseClassName.upper() + "_HPP";
		fd.write("#ifndef " + define + "\n");
		fd.write("# define " + define + "\n");
		fd.write("\n");
		fd.write("class " + baseClassName + "\n");
		fd.write("{\n");
		fd.write("\n");
		fd.write("\tpublic:\n\n");
		fd.write("\t\t" + baseClassName + "(void);\n");
		fd.write("\t\t" + baseClassName + "(" + baseClassName + " const &instance);\n");
		fd.write("\t\t" + baseClassName + " & " + "operator=(" + baseClassName + " const &rhs);\n");
		fd.write("\t\t" + "~" + baseClassName + "(void);\n");
		fd.write("\n");
		fd.write("};\n");
		fd.write("#endif\n");

	def generateIncludes(self):
		self.mkdir(sys.path[0] + "/../../" + "includes");
		for oldIdentifier in self.grammar.terminals:
			self.generateTerminalInclude(self.grammar.terminals[oldIdentifier]);
		for oldIdentifier in self.grammar.nonTerminals:
			self.generateNonTerminalInclude(self.grammar.nonTerminals[oldIdentifier]);
		self.generateGrammarInclude();
		if self.contextFileBaseName != None:
			self.generateBasicInclude(sys.path[0] + "/../../includes/", self.contextFileBaseName, True);
	
	def generateTerminalSource(self, terminal):
		fd = self.openFile("srcs", self.getFullBaseName(terminal), ".cpp");

		className = self.getFullBaseName(terminal);
		fd.write("\n");
		fd.write("# include \"" + className + ".hpp" + "\"\n");
		if (self.contextFileBaseName != None):
			fd.write("# include \"" + self.contextFileBaseName + ".hpp" + "\"\n");
		fd.write("\n");
		fd.write(className + "::" + className + "(void) : " + terminal.subClass +"(\""+ terminal.identifier + "\")\n");
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
		fd = self.openFile("srcs", self.getFullBaseName(nonTerminal), ".cpp");
		className = self.getFullBaseName(nonTerminal);
		fd.write("\n");
		fd.write("# include \""+ className + ".hpp" + "\"\n");
		if (self.contextFileBaseName != None):
			fd.write("# include \"" + self.contextFileBaseName + ".hpp" + "\"\n");
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
		fd.write("#include \"../includes/" + self.grammarName + ".hpp\"\n");
		if (self.contextFileBaseName != None):
			fd.write("#include \"../includes/" + self.contextFileBaseName + ".hpp\"\n");
		fd.write("\n");
		fd.write(self.grammarName + "::" + self.grammarName + "(void) : AbstractGrammar(new " + \
		self.getFullBaseName(self.grammar.startSymbol) + "(), " + ("true" if self.grammar.blankAsDelimiter else "false")+ ")\n");
		fd.write("{\n");
		for oldIdentifier in self.grammar.nonTerminals:
			if (oldIdentifier != self.grammar.startSymbol.oldIdentifier):
				fd.write("\taddNonTerminal(new " + self.getFullBaseName(self.grammar.nonTerminals[oldIdentifier]) + "());\n");
		fd.write("\n");
		for oldIdentifier in self.grammar.terminals:
			fd.write("\taddTerminal(new " + self.getFullBaseName(self.grammar.terminals[oldIdentifier]) + "());\n");
		fd.write("\n");
		fd.write("\tcomputeGrammar();\n");
		fd.write("}\n\n")
	#	fd.write("std::deque<Token" + self.getTypes() + " *>" + self.grammarName + "::innerLex(std::istream &istream)\n");
	#	fd.write("{\n");
	#	fd.write("\tstd::deque<Token" + self.getTypes() + " *> res;\n");

	#	fd.write("\tstatic_cast<void>(istream);\n\n");
	#	fd.write("\treturn (res);\n");
	#	fd.write("}\n\n");
		fd.write(self.grammarName + "::" + self.grammarName + "(" + self.grammarName + " const &instance)\n");
		fd.write("{\n");
		fd.write("\t*this = instance;\n");
		fd.write("}\n\n");
		fd.write(self.grammarName + "::~" + self.grammarName + "(void)\n");
		fd.write("{\n\t\n}\n\n");
		fd.write(self.grammarName + " & " + self.grammarName + "::operator=(" + self.grammarName + " const &rhs)\n")
		fd.write("{\n");
		fd.write("\tstatic_cast<void>(rhs);\n");
		fd.write("\treturn *this;\n");
		fd.write("}\n");
	
	def generateMainSource(self):
		fd = self.openFileString("srcs", "main", ".cpp");
		fd.write("\n");
		fd.write("#include \"" + self.grammarName + ".hpp\"\n");
		fd.write("#include \"LRParser.hpp\"\n");
		fd.write("\n");
		fd.write("int main(void)\n");
		fd.write("{\n");
		fd.write("\t" + self.grammarName + " grammar;\n");
		fd.write("\tLRParser" + self.getTypes() + " parser(grammar);\n");
		fd.write("\tstd::deque<Token" + self.getTypes() + " *> tokens;\n");
		fd.write("\n");
		fd.write("\tgrammar.debug();\n");
		fd.write("\ttokens = grammar.lex(true, std::cin);\n");
		fd.write("\n");
		fd.write("\ttry\n");
		fd.write("\t{\n");
		fd.write("\t\tASTBuilder" + self.getTypes() + "*b = parser.parse(tokens);\n");
		fd.write("\t\t" + self.returnType + " res = b->getASTRoot()->getTraversed(0);\n");
		fd.write("\t\tstd::cout << *b << std::endl;\n");
		fd.write("\t\tstd::cout << \"result: \" << res << std::endl;\n");
		fd.write("\t\tdelete b;\n");
		fd.write("\t\tdeleteTokens(tokens);\n");
		fd.write("\t}\n");
		fd.write("\tcatch (std::exception e)\n");
		fd.write("\t{\n");
		fd.write("\t\tdeleteTokens(tokens);\n");
		fd.write("\t\tstd::cerr << e.what() << std::endl;\n");
		fd.write("\t}\n");
		fd.write("\treturn (0);\n");
		fd.write("}\n");

	def generateBasicSource(self, path, baseClassName, override):
		fileFullPath = path + "/" + baseClassName + ".cpp";
		if not os.path.exists(fileFullPath) and not override:
			return;
		fd = open(fileFullPath, "w");
		hw.writeHeader(fd, fileFullPath);
		fd.write("\n");
		fd.write("#include \"" + baseClassName + ".hpp\"\n");
		fd.write("\n");
		fd.write(baseClassName + "::" + baseClassName + "(void) \n");
		fd.write("{\n\t\n}\n\n");
		fd.write(baseClassName + "::" + baseClassName + "(" + baseClassName + " const &instance)\n");
		fd.write("{\n");
		fd.write("\t*this = instance;\n");
		fd.write("}\n\n");
		fd.write(baseClassName + "::~" + baseClassName + "(void)\n");
		fd.write("{\n\t\n}\n\n");
		fd.write(baseClassName + " & " + baseClassName + "::operator=(" + baseClassName + " const &rhs)\n")
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
		if (self.generateMain):
			self.generateMainSource();
		if self.contextFileBaseName != None:
			self.generateBasicSource(sys.path[0] + "/../../srcs/", self.contextFileBaseName, True);

	def generateMakefile(self):
		fd = open(sys.path[0] + "/../../Makefile", "w");
		hw.writeHeaderStrings(fd, "Makefile", "#", "#");
		fd.write("\n");
		fd.write("NAME\t\t\t=\t" + self.programName + "\n");
		fd.write("\n");
		fd.write("CC\t\t\t\t=\tg++\n");
		fd.write("\n");
		fd.write("ECHO\t\t\t=\techo\n");
		fd.write("MKDIR\t\t\t=\tmkdir\n");
		fd.write("\n");
		fd.write("DEBUG ?= 0\n");
		fd.write("\n");
		fd.write("SRCDIR\t\t\t=\tsrcs/\n");
		fd.write("OBJDIR\t\t\t=\tobjs/\n");
		fd.write("BINDIR\t\t\t=\t./\n");
		fd.write("INCLUDESDIR\t\t=\tincludes/\n");
		fd.write("\n");
		fd.write("INCLUDES\t\t=\t" + self.grammarName + ".hpp \\\n");

		for oldIdentifier in self.grammar.terminals:
			fd.write("\t\t\t\t\t" + self.getFullBaseName(self.grammar.terminals[oldIdentifier]) + ".hpp \\\n")
			self.generateTerminalSource(self.grammar.terminals[oldIdentifier]);
		for oldIdentifier in self.grammar.nonTerminals:
			fd.write("\t\t\t\t\t" + self.getFullBaseName(self.grammar.nonTerminals[oldIdentifier]) + ".hpp \\\n")


		fd.write("\n");
		fd.write("SRCS\t\t\t=\t" + self.grammarName + ".cpp \\\n");

		for oldIdentifier in self.grammar.terminals:
			fd.write("\t\t\t\t\t" + self.getFullBaseName(self.grammar.terminals[oldIdentifier]) + ".cpp \\\n")
			self.generateTerminalSource(self.grammar.terminals[oldIdentifier]);
		for oldIdentifier in self.grammar.nonTerminals:
			fd.write("\t\t\t\t\t" + self.getFullBaseName(self.grammar.nonTerminals[oldIdentifier]) + ".cpp \\\n")
		if self.generateMain:
			fd.write("\t\t\t\t\t" + "main.cpp \\\n")
		if (self.contextFileBaseName != None):
			fd.write("\t\t\t\t\t" + self.contextFileBaseName + ".cpp \\\n");
		fd.write("\n");
		fd.write("VPATH\t\t\t\t=\t$(INCLUDESDIR) \\\n");
		fd.write("\t\t\t\t\t=\t$(SRCDIR)\n");
		fd.write("\n");
		fd.write("OBJECTS\t\t\t=\t$(addprefix $(OBJDIR), $(SRCS:.cpp=.o))");
		fd.write("\n");
		fd.write("CFLAGS\t\t\t=\t-I $(INCLUDESDIR) -Wall -Wextra -Werror -I ../includes -I libyacc/includes\n");
		fd.write("\n");
		fd.write("OK_COLOR\t\t\t=\t\\x1b[32;01m\n");
		fd.write("EOC\t\t\t\t\t=\t\\033[0m\n");
		fd.write("\n");
		fd.write("ifeq ($(DEBUG), 1)\n");
		fd.write("\tCFLAGS += -fsanitize=address\n");
		fd.write("\t\CC += -g3\n");
		fd.write("endif\n");
		fd.write("\n");
		fd.write("all: $(NAME)\n");
		fd.write("\n");
		fd.write("debug:\n");
		fd.write("\t@$(MAKE) all DEBUG=1\n");
		fd.write("\n");
		fd.write("$(BINDIR)$(NAME): $(OBJDIR) $(OBJECTS)\n");
		fd.write("\t$(CC) -o $@ $(OBJECTS)\n");
		fd.write("\t@$(ECHO) \"$(OK_COLOR)$(NAME) linked with success ! $(EOC)\"\n");
		fd.write("\n");
		fd.write("$(OBJDIR):\n");
		fd.write("\t@$(MKDIR) $@\n");
		fd.write("\n");
		fd.write("$(OBJDIR)%.o: $(SRC_DIR)%.cpp $(INCLUDES)\n");
		fd.write("\t$(CC) -c $< -o $@ $(CFLAGS)\n");
		fd.write("\n");
		fd.write("clean:\n");
		fd.write("\t@$(RM) -rf $(OBJDIR)");
		fd.write("\n");
		fd.write("fclean: clean\n");
		fd.write("\t@$(RM) -f $(BINDIR)$(NAME)\n");
		fd.write("\n");
		fd.write("re: fclean all\n");
		fd.write("\n");
		fd.write(".PHONY: all clean fclean re debug\n");
		print("generated Makefile !");

	
	def generateCode(self):
		self.generateIncludes();
		self.generateSources();
		self.generateMakefile();
	
	def __repr__(self):
		res = "";
		res += self.grammar.__repr__() + "\n";
		res += "prefix: \"" + self.prefix + "\"\n";
		res += "NonTerminalPrefix: \"" + self.nonTerminalPrefix + "\"\n";
		res += "terminalPrefix: \"" + self.terminalPrefix + "\"\n";
		res += "grammarName: \"" + self.grammarName + "\"\n";
		res += "generateMain: " + str(self.generateMain) + "\n";
		res += "returnType: \"" + self.returnType + "\"\n";
		res += "context: \"" + self.getContext() + "\"\n";
		res += "contextInstance: \"" + self.getContextInstance() + "\"\n";
		if (self.contextFileBaseName != None):
			res += "contextFileBaseName: \"" + self.contextFileBaseName + "\"\n";
		else:
			res += "contextFileBaseName: None\n";
		return res;

if len(sys.argv) >= 2:
	path = sys.argv[1]
else:
	sys.exit("you shall add the path of your grammar")
# try:
gen = ParserGenerator(path);
gen.generateCode();
# except Exception as e:
# print(e);
exit(1);
