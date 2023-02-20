/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:19:41 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/20 16:12:23 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_printf.h"
#include "minishell.h"

extern int	g_exit_code;

static void	runcmd_exec(t_execcmd *ecmd, t_config *config, int *status)
{
	int	result;

	result = -1;
	if (ecmd->argv[0] == 0)
		exit(1);
	result = builtin_func(ecmd->argv[0], ecmd->argv, config);
	if (result)
	{
		if (ft_strnstr("/bin/expr", ecmd->argv[0], 10))
		{
			ecmd->argv[1] = ft_itoa(g_exit_code);
			ecmd->argv[3] = ft_itoa(g_exit_code);
		}
		execve(ecmd->argv[0], ecmd->argv, get_envp(config->head));
		free(ecmd->argv[1]);
		free(ecmd->argv[3]);
	}
	if (result)
	{
		ft_fprintf(STDERR_FILENO, RED"%s: %s: %s\n"RESET, \
	PROMPT_NAME, ecmd->argv[0], ERR_CMD);
		*status = 127 * 256;
	}
}

static void	runcmd_redir(t_redircmd *rcmd, t_config *config)
{
	rcmd = (t_redircmd *)rcmd;
	close(rcmd->fd);
	if (open(rcmd->file, rcmd->mode, 0755) < 0)
	{
		ft_fprintf(2, "open %s failed\n", rcmd->file);
		exit(1);
	}
	runcmd(rcmd->cmd, *config);
}

static void	runcmd_pipe(t_pipecmd *pcmd, t_config *config, int *status)
{
	int	p[2];

	if (pipe(p) < 0)
		panic("pipe");
	if (fork() == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->left, *config);
	}
	if (fork() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->right, *config);
	}
	close(p[0]);
	close(p[1]);
	wait(status);
	wait(status);
}

void	runcmd(t_cmd *cmd, t_config config)
{
	int	status;

	status = 0;
	set_son_signal();
	if (cmd == 0)
		exit(0);
	if (cmd->type == EXEC)
		runcmd_exec((t_execcmd *)cmd, &config, &status);
	else if (cmd->type == REDIR)
		runcmd_redir((t_redircmd *)cmd, &config);
	else if (cmd->type == PIPE)
		runcmd_pipe((t_pipecmd *)cmd, &config, &status);
	else
		panic("runcmd");
	exit(status / 256);
}
