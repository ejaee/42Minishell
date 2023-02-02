/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:37:07 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/02 18:51:46 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	check_env_for_echo(char *str, t_config *config)
{
	t_list	*cur;
	t_env	*env;
	char	**env_key;
	char	key[100];
	int		idx_count;
	
	env_key = ft_split(str, '$');
	if (env_key[0][0] == '?')
	{
		ft_printf("%s", g_exit_code);
		ft_free_split(&env_key);
		return (1);
	}
// printf("전체 문자열 ||"GREEN"%s"RESET"||\n", str);
// printf("$ 로 분리된 문자열 ||"GREEN"%s"RESET"||\n", env_key[0]);
	idx_count = count_env_key_length(env_key[0]);
// printf("이동할 갯수 ||"GREEN"%d"RESET"||\n", idx_count);
	// PWD
	key[0] = '\0';
	ft_strlcpy(key, env_key[0], idx_count + 1);
// printf("현재 echo에서 찾고있는 환경변수명 : ||"GREEN"%s"RESET"||\n", key);
	cur = config->head;
	cur = get_env_list(cur, key);
	if (cur)
	{
		env = (t_env *)cur->content;
		ft_putstr_fd(GREEN, STDOUT_FILENO);
		ft_putstr_fd(env->value, STDOUT_FILENO);
		ft_putstr_fd(RESET, STDOUT_FILENO);
	}
	ft_free_split(&env_key);
	return idx_count;
}

void	builtin_echo(char *const argv[], t_config *config)
{
	int	idx;
	int	jdx;
	int	moving_jdx;

	idx = 0;
	while (argv[++idx])
	{
		jdx = -1;

		while (argv[idx][++jdx]) // asdf$$$PWD??asdf$sdf
		{
			if (idx > 1)
				ft_putchar_fd(' ', STDOUT_FILENO);
			if (argv[idx][jdx] == '$')
			{
				moving_jdx = 0;
				if (argv[idx][jdx + 1] && argv[idx][jdx + 1] != '$')
				{
					moving_jdx = check_env_for_echo(argv[idx] + (jdx + 1), config);
					jdx += moving_jdx;
				}
				else
					ft_putchar_fd(argv[idx][jdx], STDOUT_FILENO);
			}
			else
				ft_putchar_fd(argv[idx][jdx], STDOUT_FILENO);
		}
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
