# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/23 13:16:49 by ilhna             #+#    #+#              #
#    Updated: 2023/01/30 14:09:44 by ilhna            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a

SRCS = 	ft_printf.c 	\
		ft_fprintf.c 	\
						\
		ft_putchar_fd_cstm.c \
		ft_itoa.c 		\
		ft_strlen.c 	\
		ft_putstr_fd.c 	\
		ft_memset.c 	\
						\
		print_c.c 		\
		print_s.c 		\
		print_di.c 		\
		print_p.c 		\
		print_u.c 		\
		print_lowx.c 	\
		print_uppx.c 	\
		putarr.c		\


OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I.

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -f $(OBJS)

fclean:
	make clean
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re