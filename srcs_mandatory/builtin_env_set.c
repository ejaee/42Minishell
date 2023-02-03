/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:26:27 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/03 21:58:10 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_code;

t_list	*get_env_list(t_list *env_list, char *env_key)
{
	t_env *cur_env;
	
	while (env_list)
	{
		cur_env = (t_env *)env_list->content;
		if (!ft_strncmp(cur_env->key, env_key, ft_strlen(env_key) + 1))
			return (env_list);
		env_list = env_list->next;
	}
	return NULL;
}

int	set_env_list(t_list *env_list, char *env_key, char *new_value)
{
	t_env *cur_env;
	
	while (env_list)
	{
		cur_env = (t_env *)env_list->content;
		if (!ft_strncmp(cur_env->key, env_key, ft_strlen(env_key) + 1))
		{
			if (cur_env->value != NULL)
				free(cur_env->value);
			if (new_value == NULL)
				cur_env->value = NULL;	
			else
				cur_env->value = ft_strdup(new_value);
			cur_env = NULL;
			return (0);
		}
		env_list = env_list->next;
	}
	cur_env = NULL;
	return (1);
}

void	set_fail_exit_code(char *buf, int output_flag)
{
	if (output_flag)
		ft_fprintf(STDERR_FILENO, RED"%s: export: `%s': %s\n"RESET, \
		PROMPT_NAME, buf, ERR_EXPORT);
	g_exit_code = 1;
	exit(1);
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
