/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:26:27 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/01 19:36:30 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(char *buf, t_config *config, int flag)
{
	char	*pwd_buf;

	pwd_buf = ft_calloc(1, MAXPATHLEN);
	if (getcwd(pwd_buf, MAXPATHLEN) == NULL)
		ft_printf("fail: getcwd()\n");
	if (flag)
		buf += 3;
	if (chdir(buf))
	{
		if (!flag)
			ft_fprintf(STDERR_FILENO, "%s: cd: %s: %s\n", \
			PROMPT_NAME, buf, ERR_CD);
		return ;
	}
	if (flag)
	{
		char key[MAXPATHLEN] = {"OLDPWD="};
		builtin_export(ft_strcat(key, pwd_buf), config, 0);
	}
	if (getcwd(pwd_buf, MAXPATHLEN) == NULL)
		ft_printf("fail: getcwd()\n");
	if (flag)
		set_env_list(config->head, "PWD", pwd_buf);
	free(pwd_buf);
}

int builtin_export(char *buf, t_config *config, int flag)
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
		if (flag)
			ft_fprintf(STDERR_FILENO, "%s: export: '%s': %s\n", \
			PROMPT_NAME, splited_env_by_space[0], ERR_EXPORT);
	}
	if (splited_env[1] != NULL && set_env_list(list, splited_env[0], splited_env[1]))
	{
		ft_d_lstadd_back(&list, ft_lstnew(new_env(splited_env_by_space[0])));
	}
	free_split(splited_env_by_pipe);
	free_split(splited_env_by_space);
	free_split(splited_env);
	return (0);
}

int builtin_unset(char *const buf, t_config *config)
{
	t_list	*cur;
	char **splited_env;

	cur = config->head;
	splited_env = ft_split_one_cstm(buf, '=');
	if (splited_env == NULL)
		panic("Fail: ft_split_one_cstm()");
	cur = get_env_list(cur, splited_env[0]);
	if (splited_env[1] == NULL && cur)
	{
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		ft_lstdelone(cur, ft_del);
	}
	free_split(splited_env);
	return (0);
}

void	builtin_func(char *buf, t_config *config)
{
	char **splited_cmd;
	
	splited_cmd = ft_split(buf, ' ');
	if (ft_strnstr(splited_cmd[0], "cd", 2))
		{
			builtin_cd(buf, config, 1);
		}
		if (ft_strnstr(splited_cmd[0], "export", 6))
		{
			// if (splited_cmd[2] == NULL && builtin_export(splited_cmd[1], config, 1))
			// 	ft_printf("cannot export %s\n", splited_cmd[1]);
			if (splited_cmd[2] == NULL)
				builtin_export(buf, config, 0);
		}
		if (ft_strnstr(buf, "unset", 5))
		{
			if (splited_cmd[2] == NULL && builtin_unset(splited_cmd[1], config))
				ft_printf("cannot unset %s\n", splited_cmd[1]);
		}
		if (ft_strnstr(buf, "exit", 5))
		{
			builtin_exit(splited_cmd, 0);
		}
		free_split(splited_cmd);
}