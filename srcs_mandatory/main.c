/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 08:42:51 by choiejae          #+#    #+#             */
/*   Updated: 2023/02/10 13:53:25 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

int	g_exit_code = 0;

static void	set_redir(char **str, int *ret)
{
	if (**str == '>')
	{
		(*str)++;
		if (**str == '>')
		{
			(*str)++;
			*ret = '+';
		}
	}
	else if (**str == '<')
	{
		(*str)++;
		if (**str == '<')
		{
			(*str)++;
			*ret = 'h';
		}
	}
}

static int	set_token(char **str, char *str_end)
{
	int	ret;

	ret = **str;
	if (**str == '|' || **str == '(' || **str == ')' || \
		**str == '&')
		(*str)++;
	else if (**str == '>' || **str == '<')
		set_redir(str, &ret);
	else if (**str != 0)
	{
		ret = 'a';
		while ((*str) < str_end && !ft_strchr(WHITE_SPACE, **str) && \
			!ft_strchr(SYMBOLS, **str))
			(*str)++;
	}
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	char		*buf;
	int			status;
	t_config	config;

	(void)argc;
	(void)argv;
	show_shell_logo();
	load_config(&config, envp);
	while (1)
	{
		set_signal();
		buf = readline(PROMPT);
		add_history(buf);
		if (check_buf(&buf, &config))
		{
			if (!ft_strchr(buf, '|'))
				builtin_func(buf, NULL, &config);
			if (fork() == 0)
				runcmd(parse_cmd(buf), config);
			wait(&status);
			g_exit_code = status / 256;
		}
		free(buf);
	}
	exit(0);
}
