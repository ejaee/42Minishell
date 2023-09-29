/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:50:03 by ilhna             #+#    #+#             */
/*   Updated: 2023/02/20 15:27:08 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	set_redir(char **str, int *ret)
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
		(*str)++;
}

static int	set_token(char **str, char *str_end)
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
		while ((*str) < str_end && !ft_strchr(WHITE_SPACE, **str) && \
			!ft_strchr(SYMBOLS, **str))
			(*str)++;
	}
	return (ret);
}

int	get_token(char **out_str_ptr, char *str_end, char **out_q, char **out_eq)
{
	char	*str;
	int		ret;

	str = *out_str_ptr;
	while (str < str_end && ft_strchr(WHITE_SPACE, *str))
		str++;
	if (out_q)
		*out_q = str;
	ret = set_token(&str, str_end);
	if (out_eq)
		*out_eq = str;
	while (str < str_end && ft_strchr(WHITE_SPACE, *str))
		str++;
	*out_str_ptr = str;
	return (ret);
}
