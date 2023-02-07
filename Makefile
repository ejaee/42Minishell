# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: choiejae <choiejae@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 23:39:37 by ilhna             #+#    #+#              #
#    Updated: 2023/02/07 16:11:10 by choiejae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

INCLUDES_DIR = ./includes
MANDATORY_DIR = ./srcs_mandatory

MANDATORY_SRCS = \
load_config.c \
main.c \
new_env.c \
builtin_func.c \
builtin_env_set.c \
builtin_echo.c \
builtin_cd.c \
builtin_exit.c \
signal.c \
utils.c \
parse_quote.c\

OBJS_DIR = ./objs

OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

LIB_FT_DIR = ./libft
LIB_FT = ft

LIB_FT_PRINTF_DIR = ./libftprintf
LIB_FT_PRINTF = ftprintf

LIB_READLINE_DIR = ./readline
LIB_READLINE = libreadline.a
LIB_READLINE_VER = readline-8.2
LIB_READLINE_VER_TAR = $(LIB_READLINE_VER).tar.gz

LIBS =	-L$(LIB_FT_DIR) -l$(LIB_FT) \
		-L$(LIB_FT_PRINTF_DIR) -l$(LIB_FT_PRINTF) \
		$(LDFLAGS) -lreadline -lhistory

UNAME_N = $(shell uname -n)
ifneq ($(filter %42seoul.kr,$(UNAME_N)),)
	LDFLAGS="-L$(HOME)/goinfre/brew/opt/readline/lib"
	CPPFLAGS="-I$(HOME)/goinfre/brew/opt/readline/include"
else
	LDFLAGS="-L/opt/homebrew/opt/readline/lib"
	CPPFLAGS="-I/opt/homebrew/opt/readline/include"
endif

ifeq "$(findstring debug, $(MAKECMDGOALS))" "debug"
	DFLAGS = -g3 -fsanitize=address
else
	ARG.DEBUG = 0
	DFLAGS =
endif

ifeq "$(findstring bonus, $(MAKECMDGOALS))" "bonus"
	ARG.BONUS = 1
	SRCS_DIR = $(BONUS_DIR)
	SRCS = $(BONUS_SRCS)
else
	ARG.BONUS = 0
	SRCS_DIR = $(MANDATORY_DIR)
	SRCS = $(MANDATORY_SRCS)
endif

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIB_FT_DIR)
	make -C $(LIB_FT_PRINTF_DIR)
	$(CC) $(CFLAGS) $(DFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@ -I$(INCLUDES_DIR) \
	-I$(LIB_FT_DIR) \
	-I$(LIB_FT_PRINTF_DIR) \
	$(CPPFLAGS) \
	-MJ $@.part.json

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

readline:
	cd $(HOME)/goinfre; git clone https://github.com/Homebrew/brew.git
	$(HOME)/goinfre/brew/bin/brew install readline;
	$(HOME)/goinfre/brew/bin/brew info readline;

.PHONY: clean
clean:
	make clean -C $(LIB_FT_DIR)
	make clean -C $(LIB_FT_PRINTF_DIR)
	rm -f $(OBJS)

.PHONY: fclean
fclean:
	make fclean -C $(LIB_FT_DIR)
	make fclean -C $(LIB_FT_PRINTF_DIR)
	make clean
	rm -rf $(OBJS_DIR)
	rm -f $(NAME)
	rm -f compile_commands.json

.PHONY: re
re:
	make fclean
	make all
	
.PHONY: debug
debug: $(NAME)

run:
	make
	./minishell

.PHONY: ccm
ccm:
	make
	(echo '[' && cat ./$(OBJS_DIR)/*.part.json && echo ']') > compile_commands.json
