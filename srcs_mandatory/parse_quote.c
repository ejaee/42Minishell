/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choiejae <choiejae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:09:16 by choiejae          #+#    #+#             */
/*   Updated: 2023/02/08 09:16:15 by choiejae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	find_beginning_quote(char *buf)
{
	char	*single_quote;
	char	*double_quote;

	single_quote = ft_strchr(buf, '\'');
	double_quote = ft_strchr(buf, '"');
	if (single_quote < double_quote)
	{
		if (single_quote)
			return (*single_quote);
		else
			return (*double_quote);
	}
	else if (single_quote > double_quote)
	{
		if (double_quote)
			return (*double_quote);
		else
			return (*single_quote);
	}
	return (0);
}

char	find_end_quote(char *buf)
{
	char	*r_single_quote;
	char	*r_double_quote;

	r_single_quote = ft_strrchr(buf, '\'');
	r_double_quote = ft_strrchr(buf, '"');
	if (r_single_quote > r_double_quote)
	{
		if (r_single_quote)
			return (*r_single_quote);
		else
			return (*r_double_quote);
	}
	else if (r_single_quote < r_double_quote)
	{
		if (r_double_quote)
			return (*r_double_quote);
		else
			return (*r_single_quote);
	}
	return (0);
}

// buf에서 quote가 있으면 해당 함수 호출
// buf에서 quote 앞뒤를 확인
// 맞으면 1 틀리면 0을 반환
int	parse_quote(char *buf)
{
	char	beginning_quote;
	char	end_quote;

	beginning_quote = find_beginning_quote(buf);
	end_quote = find_end_quote(buf);
	return (beginning_quote == end_quote);
}
