/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:02:39 by ilhna             #+#    #+#             */
/*   Updated: 2023/01/30 14:00:03 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static int		do_print(char *str, va_list *ap, int type_flag, int fd);
static ssize_t	chk_percent_out_len_out_flag(char c, \
int *type_flag, t_vars *vars, int fd);
static int		chk_type(char *args, va_list *ap, int fd);

int	ft_printf(const char *args, ...)
{
	int		res_cnt;
	char	*args_cp;
	va_list	ap;
	int	fd;

	fd = STDOUT_FILENO;
	args_cp = (char *)args;
	va_start(ap, args);
	res_cnt = do_print(args_cp, &ap, 0, fd);
	va_end(ap);
	return (res_cnt);
}

static int	do_print(char *str, va_list *ap, int type_flag, int fd)
{
	t_vars	vars;
	int	rtn_len;

	vars.len = 0;
	vars.idx = 0;
	while (str[vars.idx])
	{
		if (type_flag == 0)
			chk_percent_out_len_out_flag(str[vars.idx], &type_flag, &vars, fd);
		else if (type_flag == 1)
		{
			type_flag = 0;
			rtn_len = chk_type(str + vars.idx, ap, fd);
			if (rtn_len == PF_ERROR)
				return (PF_ERROR);
			vars.idx++;
			if (rtn_len == NULL_STR)
				vars.len += 6;
			else
				vars.len += rtn_len;
		}
	}
	return (vars.len);
}

static ssize_t	chk_percent_out_len_out_flag(char c, \
int *type_flag, t_vars *vars, int fd)
{
	if (c != '%')
	{
		if (ft_putchar_fd_cstm(c, fd) == PF_ERROR)
			return (PF_ERROR);
		vars->len += 1;
	}
	else
		*type_flag += 1;
	vars->idx += 1;
	return (0);
}

static int	chk_type(char *args, va_list *ap, int fd)
{
	int		len;

	len = 0;
	if (*args == 'c')
		len = print_c(ap, fd);
	else if (*args == 's')
		len = print_s(ap, fd);
	else if (*args == 'p')
		len = print_p(ap, fd);
	else if (*args == 'd' || *args == 'i')
		len = print_di(ap, fd);
	else if (*args == 'u')
		len = print_u(ap, fd);
	else if (*args == 'x')
		len = print_lowx(ap, fd);
	else if (*args == 'X')
		len = print_uppx(ap, fd);
	else if (*args == '%')
		len = ft_putchar_fd_cstm(*args, fd);
	if (len == PF_ERROR)
		return (PF_ERROR);
	return (len);
}
