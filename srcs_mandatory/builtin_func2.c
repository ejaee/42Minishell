/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:37:07 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/02 16:24:27 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(char *const argv[])
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
}

void	builtin_pwd(void)
{
	char	*buf;

	buf = ft_calloc(1, MAXPATHLEN);
	if (getcwd(buf, MAXPATHLEN) == NULL)
		ft_printf("fail: getcwd()\n");
	ft_putstr_fd(buf, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(buf);
}

void	builtin_env(char *buf, t_config config)
{
	t_list *list;
	t_env *env;
	
	if (buf)
		ft_fprintf(STDERR_FILENO, RED"env: %s: %s\n"RESET, \
			buf, ERR_CD);
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
}
