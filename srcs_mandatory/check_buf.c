/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:01:43 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/10 17:00:29 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"
#include "minishell.h"

extern int	g_exit_code;

static int	check_quote(char **buf)
{
	char	**splited_buf_by_space;
	int		idx;

	splited_buf_by_space = ft_split(*buf, ' ');
	idx = -1;
	while (splited_buf_by_space[++idx])
	{
		if (ft_strchr(splited_buf_by_space[idx], '\'') || \
			ft_strchr(splited_buf_by_space[idx], '"'))
		{
			if (!parse_quote(splited_buf_by_space[idx]))
			{
				ft_fprintf(2, RED"fail: Wrong input(quote)\n"RESET);
				free_split(splited_buf_by_space);
				g_exit_code = 1;
				return (1);
			}
		}
	}
	free_split(splited_buf_by_space);
	return (0);
}

static void	remove_symbol(char **buf, int *idx, char symbol)
{
	int		jdx;

	if ((*buf)[*idx] == symbol)
	{
		jdx = (*idx) - 1;
		while ((*buf)[++jdx])
			(*buf)[jdx] = (*buf)[jdx + 1];
	}
	else
		(*idx)++;
}

static void	set_quote(char **buf, t_config *config, int idx, int env_idx)
{
	char	symbol;

	while ((*buf)[idx])
	{
		while ((*buf)[idx] && ft_strchr(WHITE_SPACE, (*buf)[idx]))
			idx++;
		while ((*buf)[idx] && !ft_strchr(WHITE_SPACE, (*buf)[idx]))
		{
			symbol = '\0';
			if ((*buf)[idx] == '\'' || (*buf)[idx] == '"')
			{
				symbol = (*buf)[idx];
				break ;
			}
			idx++;
		}
		config->quote_list[++env_idx] = symbol;
		while ((*buf)[idx] && !ft_strchr(WHITE_SPACE, (*buf)[idx]))
			remove_symbol(buf, &idx, symbol);
	}
	while (config->quote_list[++env_idx])
		config->quote_list[env_idx] = '\0';
}

static int	check_quote_and_set(char **buf, t_config *config)
{
	if (check_quote(buf))
		return (1);
	set_quote(buf, config, 0, -1);
	return (0);
}

int	check_buf(char **buf, t_config *config)
{
	if (*buf == NULL)
	{
		ft_putstr_fd(RED"exit\n"RESET, 1);
		exit(0);
	}
	if (ft_strchr(*buf, '\'') || ft_strchr(*buf, '"'))
		if (check_quote_and_set(buf, config))
			return (0);
	if (**buf == '\0')
		**buf = '\n';
	return (1);
}
