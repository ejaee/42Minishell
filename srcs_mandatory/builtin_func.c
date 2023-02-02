/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:26:27 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/02 15:49:29 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(char *buf, t_config *config, int output_flag)
{
	char	*pwd_buf;
	char 	key[MAXPATHLEN];

	pwd_buf = ft_calloc(1, MAXPATHLEN);
	if (getcwd(pwd_buf, MAXPATHLEN) == NULL)
		ft_printf("fail: getcwd()\n");
	if (!output_flag)
		buf += 3;
	if (chdir(buf))
	{
		if (output_flag)
			ft_fprintf(STDERR_FILENO, RED"%s: cd: %s: %s\n"RESET, \
			PROMPT_NAME, buf, ERR_CD);
		return ;
	}
	key[0] = '\0';
	ft_strcat(key, "OLDPWD=");
	builtin_export(ft_strcat(key, pwd_buf), config, 0);
	if (getcwd(pwd_buf, MAXPATHLEN) == NULL)
		ft_printf("fail: getcwd()\n");
	set_env_list(config->head, "PWD", pwd_buf);
	free(pwd_buf);
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
	if (!ft_isalpha(splited_env_by_pipe[0][0]))
	{
		if (output_flag)
			ft_fprintf(STDERR_FILENO, RED"%s: export: `%s': %s\n"RESET, \
			PROMPT_NAME, splited_env_by_space[0], ERR_EXPORT);
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
	char **splited_env;

	cur = config->head;
	splited_env = ft_split_one_cstm(buf, '=');
	if (splited_env == NULL)
		panic("Fail: splited_env");
	if (!ft_isalpha(*buf))
	{
		if (output_flag)
			ft_fprintf(STDERR_FILENO, RED"%s: unset: `%s': %s\n"RESET, \
			PROMPT_NAME, buf, ERR_EXPORT);
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