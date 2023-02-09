/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:09:16 by choiejae          #+#    #+#             */
/*   Updated: 2023/02/09 15:57:45 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_beginning_quote(char *buf)
{
	char	*single_quote;
	char	*double_quote;

	single_quote = ft_strchr(buf, '\'');
	double_quote = ft_strchr(buf, '"');
	if (single_quote < double_quote)
	{
		if (single_quote)
			return (single_quote);
		else
			return (double_quote);
	}
	else if (single_quote > double_quote)
	{
		if (double_quote)
			return (double_quote);
		else
			return (single_quote);
	}
	return (0);
}

char	*find_end_quote(char *buf)
{
	char	*r_single_quote;
	char	*r_double_quote;

	r_single_quote = ft_strrchr(buf, '\'');
	r_double_quote = ft_strrchr(buf, '"');
	if (r_single_quote > r_double_quote)
	{
		if (r_single_quote)
			return (r_single_quote);
		else
			return (r_double_quote);
	}
	else if (r_single_quote < r_double_quote)
	{
		if (r_double_quote)
			return (r_double_quote);
		else
			return (r_single_quote);
	}
	return (0);
}

int	parse_count_quote(char *buf)
{
	int	single_count;
	int	double_count;
	int	idx;

	single_count = 0;
	double_count = 0;
	idx = -1;
	while (buf[++idx])
	{
		if (buf[idx] == '\'')
			single_count++;
		else if (buf[idx] == '"')
			double_count++;
	}
	if (single_count && single_count % 2 != 0)
		return (-1);
	else if (double_count && double_count % 2 != 0)
		return (-1);
	return (0);
}

/**
 * buf에서 quote가 있으면 해당 함수 호출
 * buf에서 quote 앞뒤를 확인
 * 맞으면 1 틀리면 0을 반환
 */
int	parse_quote(char *buf)
{
	char	*beginning_quote;
	char	*end_quote;
	int		count_parse_result;

	beginning_quote = find_beginning_quote(buf);
	end_quote = find_end_quote(buf);
	count_parse_result = parse_count_quote(buf);
	if (count_parse_result)
		return (0);
	return ((beginning_quote != end_quote) & \
	(*beginning_quote == *end_quote));
}
