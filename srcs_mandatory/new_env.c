/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:49:55 by ilhna             #+#    #+#             */
/*   Updated: 2023/02/03 22:01:51 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(const char	*env)
{
	t_env	*new_env;
	char	**splited_env;

	new_env = ft_calloc(1, sizeof(t_env));
	splited_env = ft_split_one_cstm(env, '=');
	if (new_env == NULL || splited_env == NULL)
		panic("Fail: new_env()");
	new_env->key = splited_env[0];
	new_env->value = splited_env[1];
	free(splited_env);
	return (new_env);
}