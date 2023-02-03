/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:37:07 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/03 21:57:29 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_code;

void	builtin_pwd(void)
{
	char	*buf;

	buf = ft_calloc(1, MAXPATHLEN);
	if (getcwd(buf, MAXPATHLEN) == NULL)
		ft_printf("fail: getcwd()\n");
	ft_putstr_fd(buf, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(buf);
	g_exit_code = 0;
}

void	builtin_env(char *buf, t_config config)
{
	t_list *list;
	t_env *env;
	
	if (buf)
	{
		ft_fprintf(STDERR_FILENO, RED"env: %s: %s\n"RESET, \
			buf, ERR_CD);
		exit(127);
	}
	else
	{
		list = config.head->next;
		while (list->next)
		{
			env = list->content;
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			if (env->value != NULL)
				ft_putstr_fd(env->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			list = list->next;
		}
		g_exit_code = 0;
	}
}

void	builtin_func(char *buf, t_config *config)
{
	char **splited_cmd;
	
	splited_cmd = ft_split(buf, ' ');
	if (ft_strnstr(splited_cmd[0], "cd", 2))
	{
		builtin_cd(buf, config, PERMISSION_DENIED);
	}
	if (ft_strnstr(splited_cmd[0], "export", 6))
	{
		if (splited_cmd[2] == NULL)
			builtin_export(splited_cmd[1], config, PERMISSION_DENIED);
	}
	if (ft_strnstr(splited_cmd[0], "unset", 5))
	{
		if (splited_cmd[2] == NULL)
			builtin_unset(splited_cmd[1], config, PERMISSION_DENIED);
	}
	if (ft_strnstr(buf, "exit", 5))
	{
		builtin_exit(splited_cmd, PERMISSION_DENIED);
	}
	free_split(splited_cmd);
}