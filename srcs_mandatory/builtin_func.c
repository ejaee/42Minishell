/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:26:27 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/03 19:22:36 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_code;

void	set_fail_exit_code(char *buf, int output_flag)
{
	if (output_flag)
		ft_fprintf(STDERR_FILENO, RED"%s: export: `%s': %s\n"RESET, \
		PROMPT_NAME, buf, ERR_EXPORT);
	g_exit_code = 1;
}

void	builtin_export(char *buf, t_config *config, int output_flag)
{
	t_list *list;
	char **splited_env_by_pipe;
	char **splited_env_by_space;
	char **splited_env;

	list = config->head;
	splited_env_by_pipe = ft_split(buf, '|');
	splited_env_by_space = ft_split(splited_env_by_pipe[0], ' ');
	splited_env = ft_split_one_cstm(splited_env_by_space[0], '=');
	if (splited_env == NULL)
		panic("Fail: splited_env");
	g_exit_code = 0;
	if (!ft_isalpha(splited_env_by_pipe[0][0]))
	{
		set_fail_exit_code(splited_env_by_space[0], output_flag);
	}
	else if (set_env_list(list, splited_env[0], splited_env[1]))
	{
		ft_d_lstadd_back(&list, ft_lstnew(new_env(splited_env_by_space[0])));
	}
	free_split(splited_env_by_pipe);
	free_split(splited_env_by_space);
	free_split(splited_env);
}

void	builtin_unset(char *buf, t_config *config, int output_flag)
{
	t_list	*cur;
	char	**splited_env;

	cur = config->head;
	splited_env = ft_split_one_cstm(buf, '=');
	if (splited_env == NULL)
		panic("Fail: splited_env");
	g_exit_code = 0;
	if (!ft_isalpha(*buf))
	{
		set_fail_exit_code(buf, output_flag);
	}
	else
	{
		cur = get_env_list(cur, splited_env[0]);
		if (splited_env[1] == NULL && cur)
		{
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			ft_lstdelone(cur, ft_del);
		}
	}
	free_split(splited_env);
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