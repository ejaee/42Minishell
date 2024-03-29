/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 08:42:51 by choiejae          #+#    #+#             */
/*   Updated: 2023/02/20 17:57:02 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "minishell.h"

int	g_exit_code = 0;

static void	check_add_history(char *buf)
{
	if (*buf != '\0')
		add_history(buf);
}

static void	init_setup(int argc, char **argv, t_list **hd_head)
{
	(void)argc;
	(void)argv;
	*hd_head = NULL;
	show_shell_logo();
}

int	main(int argc, char **argv, char **envp)
{
	char		*buf;
	int			status;
	t_config	config;
	t_list		*hd_head;

	init_setup(argc, argv, &hd_head);
	load_config(&config, envp);
	while (1)
	{
		set_signal();
		buf = readline(PROMPT);
		check_add_history(buf);
		buf = check_heredoc(buf, &hd_head);
		if (check_buf(&buf, &config) && *buf != '\n')
		{
			if (!ft_strchr(buf, '|'))
				builtin_func(buf, NULL, &config);
			if (fork() == 0)
				runcmd(parse_cmd(buf), config);
			wait(&status);
			g_exit_code = status / 256;
		}
		remove_heredoc_free_buf(hd_head, buf);
	}
	exit(0);
}
