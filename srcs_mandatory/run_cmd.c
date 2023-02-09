/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:19:41 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/09 17:22:06 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	runcmd_exec(struct execcmd *ecmd, t_config *config, int *status)
{
	int	result;

	result = -1;
	if (ecmd->argv[0] == 0)
		exit(1);
	result = builtin_func(ecmd->argv[0], ecmd->argv, config);
	if (result)
		execv(ecmd->argv[0], ecmd->argv);
	if (result)
	{
		ft_fprintf(STDERR_FILENO, RED"%s: %s: %s\n"RESET, \
	PROMPT_NAME, ecmd->argv[0], ERR_CMD);
		*status = 127 * 256;
	}
	return (result);
}

void	runcmd_redir(struct redircmd *rcmd, t_config *config)
{
	rcmd = (struct redircmd *)rcmd;
	close(rcmd->fd);
	if (open(rcmd->file, rcmd->mode) < 0)
	{
		ft_printf("open %s failed\n", rcmd->file);
		exit(1);
	}
	runcmd(rcmd->cmd, *config);
}

void	runcmd_pipe(struct pipecmd *pcmd, t_config *config, int *status)
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

void	runcmd(struct cmd *cmd, t_config config)
{
	int	status;
	int	result;

	status = 0;
	set_son_signal();
	if (cmd == 0)
		exit(0);
	result = -1;
	if (cmd->type == EXEC)
		result = runcmd_exec((struct execcmd *)cmd, &config, &status);
	else if (cmd->type == REDIR)
		runcmd_redir((struct redircmd *)cmd, &config);
	else if (cmd->type == PIPE)
		runcmd_pipe((struct pipecmd *)cmd, &config, &status);
	else
		panic("runcmd");
	exit(status / 256);
}