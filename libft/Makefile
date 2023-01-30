# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: choiejae <choiejae@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/08 21:24:48 by ilhna             #+#    #+#              #
#    Updated: 2023/01/30 21:37:42 by ilhna            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

SOURCES_MANDATORY = \
			ft_atoi.c        ft_memmove.c        ft_strlcpy.c \
			ft_bzero.c       ft_memset.c         ft_strlen.c  \
			ft_calloc.c      ft_putchar_fd.c     ft_strmapi.c \
			ft_isalnum.c     ft_putendl_fd.c     ft_strncmp.c \
			ft_isalpha.c     ft_putnbr_fd.c      ft_strnstr.c \
			ft_isascii.c     ft_putstr_fd.c      ft_strrchr.c \
			ft_isdigit.c     ft_split.c          ft_strtrim.c \
			ft_isprint.c     ft_strchr.c         ft_substr.c  \
			ft_itoa.c        ft_strdup.c         ft_tolower.c \
			ft_memchr.c      ft_striteri.c       ft_toupper.c \
			ft_memcmp.c      ft_strjoin.c \
			ft_memcpy.c      ft_strlcat.c \
			ft_free_split.c \
			\
			ft_split_one_cstm.c \
			ft_atolld.c \
			ft_strnumlen.c \
			ft_d_lstadd_back.c \

SOURCES_BONUS = \
			ft_d_lstadd_back.c  \
			ft_lstadd_back.c  \
			ft_lstadd_front.c \
			ft_lstclear.c     \
			ft_lstdelone.c    \
			ft_lstiter.c      \
			ft_lstlast.c      \
			ft_lstmap.c       \
			ft_lstnew.c       \
			ft_lstsize.c      \

OBJECTS_MANDATORY = $(SOURCES_MANDATORY:.c=.o)
OBJECTS_BONUS = $(SOURCES_BONUS:.c=.o)

ifdef WITH_BONUS
	OBJ_FILES = $(OBJECTS_MANDATORY) $(OBJECTS_BONUS)
else
	OBJ_FILES = $(OBJECTS_MANDATORY) $(OBJECTS_BONUS)
endif

.PHONY : all bonus clean fclean re

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I.

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rc $(NAME) $(OBJ_FILES)
	ranlib $(NAME)

bonus:
	make WITH_BONUS=1 all
	
clean:
	rm -f $(OBJECTS_MANDATORY) $(OBJECTS_BONUS)

fclean: clean
	rm -f $(NAME)

re:
	make fclean
	make all
