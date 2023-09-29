/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:37:07 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/20 17:49:38 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>
#include "libft.h"
#include "ft_printf.h"
#include "minishell.h"

extern int	g_exit_code;

static int	builtin_pwd(void)
{
	char	*buf;

	buf = ft_calloc(1, MAXPATHLEN);
	if (getcwd(buf, MAXPATHLEN) == NULL)
		ft_fprintf(2, "fail: getcwd()\n");
	ft_putstr_fd(buf, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(buf);
	g_exit_code = 0;
	return (0);
}

static char	**set_buf_by_process(char **buf, char **argv, int *output_flag)
{
	if (argv)
	{
		*output_flag = PERMISSION;
		*buf = argv[1];
		return (argv);
	}
	else
	{
		*output_flag = PERMISSION_DENIED;
		return (ft_split(*buf, ' '));
	}
}

void	print_env(t_list *list, int export_flag)
{
	t_env	*env;

	while (list->next)
	{
		if (export_flag)
			ft_putstr_fd(RED"declare"RESET" -x ", STDOUT_FILENO);
		env = list->content;
		ft_putstr_fd(env->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		if (env->value != NULL)
		{
			ft_putstr_fd(CYAN, STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
			ft_putstr_fd(RESET, STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		list = list->next;
	}
}

int	builtin_env(char *buf, t_config config, int export_flag)
{
	if (buf)
	{
		ft_fprintf(STDERR_FILENO, RED"env: %s: %s\n"RESET, \
			buf, ERR_CD);
		exit(127);
	}
	else
	{
		print_env(config.head->next, export_flag);
		g_exit_code = 0;
	}
	return (0);
}

int	builtin_func(char *buf, char **argv, t_config *config)
{
	char	**splited_cmd;
	int		output_flag;
	int		result;

	result = -1;
	splited_cmd = set_buf_by_process(&buf, argv, &output_flag);
	if (ft_strncmp("cd", splited_cmd[0], 3) == 0)
		result = builtin_cd(splited_cmd[1], config, output_flag);
	if (ft_strncmp("export", splited_cmd[0], 7) == 0)
		if (splited_cmd[2] == NULL)
			result = builtin_export(splited_cmd[1], config, output_flag);
	if (ft_strncmp("unset", splited_cmd[0], 6) == 0)
		if (splited_cmd[2] == NULL)
			result = builtin_unset(splited_cmd[1], config, output_flag);
	if (ft_strncmp("exit", splited_cmd[0], 5) == 0)
		result = builtin_exit(splited_cmd, output_flag);
	if (argv && ft_strncmp("echo", splited_cmd[0], 5) == 0)
		result = builtin_echo(splited_cmd, config);
	if (argv && ft_strncmp("env", splited_cmd[0], 4) == 0)
		result = builtin_env(splited_cmd[1], *config, 0);
	if (argv && ft_strncmp("pwd", splited_cmd[0], 4) == 0)
		result = builtin_pwd();
	if (!argv)
		free_split(splited_cmd);
	return (result);
}
