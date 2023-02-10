/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choiejae <choiejae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:38:52 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/10 15:47:14 by choiejae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "ft_printf.h"
#include "minishell.h"

static void	sig_ctrl_c(int signal)
{
	int	pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (signal == SIGINT)
	{
		if (pid == -1)
		{
			if (rl_on_new_line() == -1)
				exit(1);
			rl_replace_line("", 1);
			ft_putstr_fd("\n", STDOUT_FILENO);
			rl_redisplay();
		}
	}
}

void	set_son_signal(void)
{
	signal(SIGQUIT, SIG_DFL);
}

void	set_signal(void)
{
	signal(SIGINT, sig_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
