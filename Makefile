# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 23:08:04 by ldedier           #+#    #+#              #
#    Updated: 2019/12/29 18:34:44 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libyacc

CC		= g++
AR		= ar rc

ECHO = echo
MKDIR = mkdir
RM = rm

DEBUG ?= 0

SRCDIR			=	srcs/
OBJ_DIR			=	objs/
BINDIR			=	./
INCLUDESDIR		=	includes/

INCLUDES		=	AbstractSymbol.hpp \
					ASTNode.hpp \
					ASTBuilder.hpp \
					AbstractGrammar.hpp \
					AbstractLRAction.hpp \
					AbstractNonTerminal.hpp \
					AbstractSymbol.hpp \
					AbstractToken.hpp \
					LRActionAccept.hpp \
					LRActionError.hpp \
					LRActionReduce.hpp \
					EndOfInput.hpp \
					Start.hpp \
					LRActionReduce.hpp \
					LRActionShift.hpp \
					LRItem.hpp \
					LRParser.hpp \
					LRState.hpp \
					LRTransition.hpp \
					Set.hpp \

					Production.hpp

SRCS			=	


VPATH			=	$(INCLUDESDIR) \
					$(SRCDIR)

OBJECTS			=	$(addprefix $(OBJ_DIR), $(SRCS:.cpp=.o))

CFLAGS			= -I $(INCLUDESDIR) -Wall -Wextra -Werror

OK_COLOR	=	\x1b[32;01m
EOC			=	\033[0m

ifeq ($(DEBUG), 1)
	CFLAGS += -fsanitize=address
	CC += -g3
endif
	
SPEED = -j8

all: $(NAME)

debug:
	@$(MAKE) all DEBUG=1

$(BINDIR)$(NAME): $(OBJ_DIR) $(OBJECTS)
	$(AR) $@ $(OBJECTS)
	@$(ECHO) "$(OK_COLOR)$(NAME) linked with success !$(EOC)"

$(OBJ_DIR):
	@$(MKDIR) $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(INCLUDES)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@$(RM) -rf $(OBJ_DIR)

fclean: clean
	@$(RM) -f $(BINDIR)$(NAME)

re: fclean all

.PHONY: all clean fclean re debug
