/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choiejae <choiejae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:37:10 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/09 23:08:57 by choiejae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_parse_info(char **out_str_ptr, char *str_end, \
	t_execcmd **cmd, int *argc)
{
	int		tok;
	char	*q;
	char	*eq;

	tok = get_token(out_str_ptr, str_end, &q, &eq);
	if (tok == 0)
		return (1);
	if (tok != 'a')
		panic("syntax");
	(*cmd)->argv[*argc] = q;
	(*cmd)->eargv[*argc] = eq;
	(*argc)++;
	if (*argc >= MAXARGS)
		panic(RED"too many args"RESET);
	return (0);
}

t_cmd	*parse_exec(char **out_str_ptr, char *str_end)
{
	int			argc;
	t_cmd		*ret;
	t_execcmd	*cmd;

	ret = init_execcmd();
	cmd = (t_execcmd *)ret;
	argc = 0;
	ret = parse_redirs(ret, out_str_ptr, str_end);
	while (!skip_space_check_toks(out_str_ptr, str_end, "|&"))
	{
		if (save_parse_info(out_str_ptr, str_end, &cmd, &argc))
			break ;
		ret = parse_redirs(ret, out_str_ptr, str_end);
	}
	cmd->argv[argc] = 0;
	cmd->eargv[argc] = 0;
	return (ret);
}

t_cmd	*parse_redirs(t_cmd *cmd, char **str_ptr, char *str_end)
{
	int		tok;
	char	*q;
	char	*eq;

	while (skip_space_check_toks(str_ptr, str_end, "<>"))
	{
		tok = get_token(str_ptr, str_end, 0, 0);
		if (get_token(str_ptr, str_end, &q, &eq) != 'a')
			panic("missing file for redirection");
		if (tok == '<')
			cmd = redircmd(cmd, q, eq, O_RDONLY);
		else if (tok == '>')
			cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREAT);
		else if (tok == '+')
			cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREAT);
		else if (tok == 'h')
			cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREAT);
	}
	return (cmd);
}

t_cmd	*parse_pipe(char **out_str_ptr, char *str_end)
{
	t_cmd	*cmd;

	cmd = parse_exec(out_str_ptr, str_end);
	if (skip_space_check_toks(out_str_ptr, str_end, "|"))
	{
		get_token(out_str_ptr, str_end, 0, 0);
		cmd = pipecmd(cmd, parse_pipe(out_str_ptr, str_end));
	}
	return (cmd);
}

t_cmd	*parse_cmd(char *str)
{
	char	*str_end;
	t_cmd	*cmd;

	str_end = str + ft_strlen(str);
	cmd = parse_pipe(&str, str_end);
	skip_space_check_toks(&str, str_end, "");
	if (str != str_end)
	{
		ft_printf("leftovers: %s\n", str);
		panic("syntax");
	}
	nulterminate(cmd);
	return (cmd);
}
