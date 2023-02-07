/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choiejae <choiejae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 19:00:20 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/07 23:16:16 by choiejae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_code;

char	*set_by_process(char *buf, int output_flag)
{
	char	*res;

	res = buf;
	if (!output_flag)
	{
		res += 3;
		while (res && ft_strchr(WHITE_SPACE, *res))
			res++;
	}
	return (res);
}

char	*set_quote(char *buf, int output_flag)
{
	char	*res;
	char	*tmp;

	res = set_by_process(buf, output_flag);
	if (ft_strchr(res, '\'') || ft_strchr(res, '"'))
	{
		if (!parse_quote(res))
		{
			if (!output_flag)
				ft_printf(RED"fail: Wrong input(quote)\n"RESET);
			res = ".";
		}
		else
		{
			res += 1;
			tmp = ft_strchr(res, '"');
			*tmp = '\0';
		}
	}
	return (res);
}

char	*set_buf(char *buf, int output_flag, t_config *config, int *env_flag)
{
	t_list	*cur;
	t_env	*env;
	char	*res;

	res = set_quote(buf, output_flag);
	if (*res == '$')
	{
		cur = get_env_list(config->head, res + 1);
		if (cur)
		{
			env = (t_env *)cur->content;
			return (env->value);
		}
		else
			*env_flag = 1;
	}
	return (res);
}

void	set_fail_cd(char *buf, int env_flag, int output_flag)
{
	if (!env_flag)
		{
			if (output_flag)
			{
				ft_fprintf(STDERR_FILENO, RED"%s: cd: %s: %s\n"RESET, \
			PROMPT_NAME, buf, ERR_CD);
				exit (1);
				g_exit_code = 1;
			}
			g_exit_code = 1;
		}
	else
		g_exit_code = 0;
}

int	builtin_cd(char *buf, t_config *config, int output_flag)
{
	char	*pwd_buf;
	char 	key[MAXPATHLEN];
	int		env_flag;

	pwd_buf = ft_calloc(1, MAXPATHLEN);
	if (getcwd(pwd_buf, MAXPATHLEN) == NULL)
		ft_fprintf(2, "fail: getcwd()\n");
	env_flag = 0;
	buf = set_buf(buf, output_flag, config, &env_flag);
	if (chdir(buf))
	{
		set_fail_cd(buf, env_flag, output_flag);
		return (0);
	}
	g_exit_code = 0;
	key[0] = '\0';
	ft_strcat(key, "OLDPWD=");
	builtin_export(ft_strcat(key, pwd_buf), config, 0);
	if (getcwd(pwd_buf, MAXPATHLEN) == NULL)
		ft_fprintf(2, "fail: getcwd()\n");
	set_env_list(config->head, "PWD", pwd_buf);
	free(pwd_buf);
	return (0);
}
