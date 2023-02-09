/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choiejae <choiejae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 08:42:51 by choiejae          #+#    #+#             */
/*   Updated: 2023/02/09 23:17:54 by choiejae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

int	main(int argc, char **argv, char **envp)
{
	char		*buf;
	int			status;
	t_config	config;

	(void)argc;
	(void)argv;
	show_shell_logo();
	load_config(&config, envp);
	while (1)
	{
		set_signal();
		buf = readline(PROMPT);
		add_history(buf);
		if (check_buf(&buf, &config))
		{
			if (!ft_strchr(buf, '|'))
				builtin_func(buf, NULL, &config);
			if (fork() == 0)
				runcmd(parse_cmd(buf), config);
			wait(&status);
			g_exit_code = status / 256;
		}
		free(buf);
	}
	exit(0);
}

/**
 * 공백을 지나가고
 * | & 의 경우 한칸 넘기고
 * > 인 경우 넘기고
 * >> 인 경우 ret = '+' 주고 넘기고
 * < 인 경우 ret = 'h' 주고 넘기고
 * 나머지는 ret = 'a' 주고 공백 쭉 민다
 * 매개변수 1 는 다음 토큰 대상을 가리키고(공백을 지났음)
 * 3, 4 는 토큰의 처음과 끝을 가리킨다
 * 3. **out_q : 값을 가져오고 싶을 때 0이 아닌 값을 준다
 */
void	set_redir(char **str, int *ret)
{
	if (**str == '>')
	{
		(*str)++;
		if (**str == '>')
		{
			(*str)++;
			*ret = '+';
		}
	}
	else if (**str == '<')
	{
		(*str)++;
		if (**str == '<')
		{
			(*str)++;
			*ret = 'h';
		}
	}
}

int	set_token(char **str, char *str_end)
{
	int	ret;

	ret = **str;
	if (**str == '|' || **str == '(' || **str == ')' || \
		**str == '&')
		(*str)++;
	else if (**str == '>' || **str == '<')
		set_redir(str, &ret);
	else if (**str != 0)
	{
		ret = 'a';
		while ((*str) < str_end && !strchr(WHITE_SPACE, **str) && \
			!strchr(SYMBOLS, **str))
			(*str)++;
	}
	return (ret);
}

int	get_token(char **out_str_ptr, char *str_end, char **out_q, char **out_eq)
{
	char	*str;
	int		ret;

	str = *out_str_ptr;
	while (str < str_end && strchr(WHITE_SPACE, *str))
		str++;
	if (out_q)
		*out_q = str;
	ret = set_token(&str, str_end);
	if (out_eq)
		*out_eq = str;
	while (str < str_end && strchr(WHITE_SPACE, *str))
		str++;
	*out_str_ptr = str;
	return (ret);
}

t_cmd	*nulterminate(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;
	int			i;

	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		i = -1;
		while (ecmd->argv[++i])
			*ecmd->eargv[i] = 0;
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		nulterminate(rcmd->cmd);
		*rcmd->efile = 0;
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		nulterminate(pcmd->left);
		nulterminate(pcmd->right);
	}
	return (cmd);
}
