/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choiejae <choiejae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:16:54 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/08 08:13:12 by choiejae         ###   ########.fr       */
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
