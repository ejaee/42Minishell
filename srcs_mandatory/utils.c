/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:16:54 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/09 15:57:17 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **str)
{
	int	idx;

	idx = -1;
	while (str[++idx])
		free(str[idx]);
	free(str);
}

void	ft_del(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	free(env->key);
	free(env->value);
	free(content);
}

void	panic(char *s)
{
	ft_fprintf(2, "fail: %s\n", s);
	exit(1);
}

/**
 * 공백을 넘긴다
 * 현재 가리키는 문자부터 끝까지 toks 이 있는지 확인한다
 * 있으면 1 없으면 0을 리턴한다
 */
int	skip_space_check_toks(char **out_ps, char *str_end, char *toks)
{
	char	*str;

	str = *out_ps;
	while (str < str_end && strchr(WHITE_SPACE, *str))
		str++;
	*out_ps = str;
	return (*str && strchr(toks, *str));
}
