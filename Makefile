# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 23:39:37 by ilhna             #+#    #+#              #
#    Updated: 2023/01/30 14:26:08 by ilhna            ###   ########.fr        #
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
		-lreadline

ifeq "$(findstring debug, $(MAKECMDGOALS))" "debug"
	DFLAGS = -g -fsanitize=address
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
	-MJ $@.part.json 

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(LIB_READLINE_DIR):
	@echo "\033[33m-----Download $(LIB_READLINE_VER)-----"
	curl ftp://ftp.cwru.edu/pub/bash/$(LIB_READLINE_VER_TAR) > \
	$(LIB_READLINE_VER_TAR)
	tar -zxf $(LIB_READLINE_VER_TAR)
	rm -f $(LIB_READLINE_VER_TAR)
	mv $(LIB_READLINE_VER) $@
	cd ./$@; ./configure
	@echo "--Finish download readline lib--"
	@echo "\033[0m"

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
