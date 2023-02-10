/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 19:00:20 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/10 15:12:44 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/param.h>
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"

extern int	g_exit_code;

static char	*set_buf(char *buf, t_config *config, int *env_flag)
{
	t_list	*cur;
	t_env	*env;
	char	*res;

	res = buf;
	if (!res)
		res = ".";
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

static void	set_fail_cd(char *buf, int env_flag, int output_flag)
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
	char	key[MAXPATHLEN];
	int		env_flag;

	pwd_buf = ft_calloc(1, MAXPATHLEN);
	if (getcwd(pwd_buf, MAXPATHLEN) == NULL)
		ft_fprintf(2, "fail: getcwd()\n");
	env_flag = 0;
	buf = set_buf(buf, config, &env_flag);
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
