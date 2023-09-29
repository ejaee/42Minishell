/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:16:54 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/10 13:46:23 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"
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

int	skip_space_check_toks(char **out_ps, char *str_end, char *toks)
{
	char	*str;

	str = *out_ps;
	while (str < str_end && ft_strchr(WHITE_SPACE, *str))
		str++;
	*out_ps = str;
	return (*str && ft_strchr(toks, *str));
}
