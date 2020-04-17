# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 23:08:04 by ldedier           #+#    #+#              #
#    Updated: 2019/11/29 08:01:01 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= arithmetic

CC		= g++ -std=c++11

ECHO = echo
MKDIR = mkdir
RM = rm

DEBUG ?= 0

SRCDIR			=	srcs/
OBJ_DIR			=	objs/
BINDIR			=	./
INCLUDESDIR		=	includes/

INCLUDES		=	ArithmeticGrammar.hpp \
					Arithmetic.hpp \
					Expr.hpp \
					Factor.hpp \
					Integer.hpp \
					Term.hpp \
					Multiply.hpp \
					Plus.hpp \
					Minus.hpp \
					Divide.hpp 

SRCS			=	ArithmeticGrammar.cpp \
					Arithmetic.cpp \
					Expr.cpp \
					Factor.cpp \
					Integer.cpp \
					Term.cpp \
					Multiply.cpp \
					Plus.cpp \
					Minus.cpp \
					Divide.cpp \
					main.cpp

VPATH			=	$(INCLUDESDIR) \
					$(SRCDIR)

OBJECTS			=	$(addprefix $(OBJ_DIR), $(SRCS:.cpp=.o))

CFLAGS			= -I $(INCLUDESDIR) -Wall -Wextra -Werror -I ../includes

OK_COLOR	=	\x1b[32;01m
EOC			=	\033[0m

ifeq ($(DEBUG), 1)
	CFLAGS += -fsanitize=address
	CC += -g3
endif

all: $(NAME)

debug:
	@$(MAKE) all DEBUG=1

$(BINDIR)$(NAME): $(OBJ_DIR) $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)
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
