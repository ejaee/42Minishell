/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:37:07 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/02 14:00:07 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char *const argv[])
{
	int	idx;

	idx = 0;
	while (argv[++idx])
	{
		if (idx > 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(argv[idx], STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int	builtin_pwd(void)
{
	char	*buf;

	buf = ft_calloc(1, MAXPATHLEN);
	if (getcwd(buf, MAXPATHLEN) == NULL)
	{
		ft_printf("check error\n");
		return (1);
	}
	ft_putstr_fd(buf, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(buf);
	return (0);
}

int builtin_env(t_config config)
{
	t_list *list;
	t_env *env;

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
	return (0);
}
