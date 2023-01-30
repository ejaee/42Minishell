/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:10:26 by ilhna             #+#    #+#             */
/*   Updated: 2023/01/30 14:08:34 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>	

# define PF_ERROR -1
# define NULL_STR -6
# define ADDR_LEN 17

typedef struct	vars
{
	int	len;
	int	idx;
}				t_vars;

int		ft_printf(const char *args, ...);
int		ft_fprintf(int fd, const char *args, ...);

ssize_t	ft_putchar_fd_cstm(char c, int fd);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	*ft_memset(void *b, int c, size_t len);

int		print_c(va_list *ap, int fd);
int		print_s(va_list *ap, int fd);
int		print_di(va_list *ap, int fd);
int		print_p(va_list *ap, int fd);
int		print_u(va_list *ap, int fd);
int		print_lowx(va_list *ap, int fd);
int		print_uppx(va_list *ap, int fd);
int		putarr(char *arr, int len, int fd);

#endif
