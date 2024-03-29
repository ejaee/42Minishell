/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:06:07 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/10 14:00:47 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"

extern int	g_exit_code;

static size_t	get_argv_count(char *const argv[])
{
	size_t	len;

	len = 0;
	while (argv[len])
		len++;
	return (len);
}

static int	check_lld_range(char *arg, size_t lld_max_len, \
							const char *lld_minmax_str[])
{
	const char	*lld_str;

	if (lld_max_len > ft_strlen(arg))
		return (true);
	if (arg[0] == '-')
		lld_str = lld_minmax_str[0];
	else
		lld_str = lld_minmax_str[1];
	if (ft_strncmp(lld_str, arg, lld_max_len) < 0)
		return (false);
	return (true);
}

static int	check_exit_param(char *arg, int *out_exit_code)
{
	const char	*lld_minmax_str[2];
	long long	lld_arg;
	size_t		lld_max_len;
	size_t		arg_len;

	lld_minmax_str[0] = "-9223372036854775808";
	lld_minmax_str[1] = "9223372036854775807";
	arg_len = ft_strnumlen(arg);
	lld_max_len = ft_strlen(lld_minmax_str[0]);
	if (arg_len == 0 || arg_len > lld_max_len)
		return (false);
	if (arg[0] != '-')
		lld_max_len--;
	if (check_lld_range(arg, lld_max_len, lld_minmax_str) == false)
		return (false);
	lld_arg = ft_atolld(arg);
	*out_exit_code = lld_arg % 256;
	return (true);
}

static void	argc_one_or_two(size_t argc, int output_flag)
{
	if (argc == 1)
	{
		if (!output_flag)
			ft_fprintf(STDOUT_FILENO, "exit\n");
		exit (0);
	}
	else if (argc == 2)
	{
		if (!output_flag)
			ft_fprintf(STDOUT_FILENO, "exit\n");
		exit (g_exit_code);
	}
}

int	builtin_exit(char *const argv[], int output_flag)
{
	size_t	argc;

	argc = get_argv_count(argv);
	if (argc >= 2 && check_exit_param(argv[1], &g_exit_code) == false)
	{
		if (!output_flag)
			ft_fprintf(STDOUT_FILENO, "exit\n");
		ft_fprintf(STDERR_FILENO, RED"%s: exit: %s: %s\n"RESET, \
			PROMPT_NAME, argv[1], ERR_EXIT_NUMERIC);
		exit (255);
	}
	if (argc == 1 || argc == 2)
		argc_one_or_two(argc, output_flag);
	else if (argc > 2)
	{
		if (output_flag)
		{
			ft_fprintf(STDERR_FILENO, RED"%s: %s\n"RESET, \
			PROMPT_NAME, ERR_EXIT_MANY_ARGS);
			exit(1);
		}
		g_exit_code = 1;
	}
	return (0);
}
