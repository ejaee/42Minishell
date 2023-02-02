/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:38:52 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/01 18:41:52 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_son_signal()
{
	signal(SIGQUIT, SIG_DFL);
}

void	sig_ctrl_c(int signal)
{
	int	pid;

	pid = waitpid(-1, NULL, WNOHANG);
	g_exit_code = 1;

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
		else
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
	}
}

void	set_signal()
{
	signal(SIGINT, sig_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}