/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:37:07 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/03 15:23:44 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	count_env_key_length(char *str)
{
	int count;

	count = 0;
	while (*str)
	{
		if (ft_isalnum(*str++))
			count++;
	}
	return (count);
}

int	check_env_echo(char *str, t_config *config)
{
	t_list	*cur;
	t_env	*env;
	char	**env_key;
	char	key[128];
	int		idx_count;
	
	env_key = ft_split(str, '$');
	if (env_key[0][0] == '?')
	{
		ft_printf("%d", g_exit_code);
		ft_free_split(&env_key);
		return (1);
	}
	idx_count = count_env_key_length(env_key[0]);
	key[0] = '\0';
	ft_strlcpy(key, env_key[0], idx_count + 1);
	cur = get_env_list(config->head, key);
	if (cur)
	{
		env = (t_env *)cur->content;
		ft_printf("%s%s%s", GREEN, env->value, RESET);
	}
	ft_free_split(&env_key);
	return idx_count;
}

int	check_opt_flag(char *str, int *idx)
{
	if (ft_strnstr(str, "-n", 3))
	{
		++*idx;
		return (1);
	}
	return (0);
}

void	print_env_echo(char *str, int *jdx, t_config *config)
{
	int moving_jdx;

	moving_jdx = 0;
	if (*(str + (*jdx + 1)) && *(str + (*jdx + 1)) != '$')
	{
		moving_jdx = check_env_echo(str + (*jdx + 1), config);
		*jdx += moving_jdx;
	}
	else
		ft_putchar_fd(*(str + *jdx), STDOUT_FILENO);
}

void	builtin_echo(char *const argv[], t_config *config)
{
	int	idx;
	int	jdx;
	int	opt_flag;

	idx = 0;
	opt_flag = check_opt_flag(argv[1], &idx);
	while (argv[++idx])
	{
		jdx = -1;
		if (idx > 1 + opt_flag)
			ft_putchar_fd(' ', STDOUT_FILENO);
		while (argv[idx][++jdx])
		{
			if (argv[idx][jdx] == '$')
				print_env_echo(argv[idx], &jdx, config);
			else
				ft_putchar_fd(argv[idx][jdx], STDOUT_FILENO);
		}
	}
	if (!opt_flag)
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
