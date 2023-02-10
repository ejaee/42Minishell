/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:28:11 by ilhna             #+#    #+#             */
/*   Updated: 2023/02/10 16:01:12 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static int	get_envp_count(t_list *config_head)
{
	int	count;

	count = -2;
	while (config_head)
	{
		count++;
		config_head = config_head->next;
	}
	return (count);
}

static char	*get_env_str(t_env *env_content)
{
	char	*env;
	int		key_len;
	int		val_len;
	int		equal_null_char;

	key_len = ft_strlen(env_content->key);
	val_len = ft_strlen(env_content->value);
	equal_null_char = 2;
	env = (char *)malloc(key_len + val_len + equal_null_char);
	if (env == NULL)
		panic(ERR_MALLOC);
	env = ft_strcat(env, env_content->key);
	env = ft_strcat(env, "=");
	env = ft_strcat(env, env_content->value);
	return (env);
}

char	**get_envp(t_list *config_head)
{
	char		**envp;
	int			envp_count;
	int			e_idx;

	envp_count = get_envp_count(config_head);
	envp = ft_calloc(sizeof(char *), envp_count);
	if (envp == NULL)
		panic(ERR_MALLOC);
			e_idx = 0;
	while (config_head)
	{
		if (e_idx == 0 || e_idx == envp_count + 1)
		{
			config_head = config_head->next;
			continue ;
		}
		envp[e_idx] = get_env_str(config_head->content);
		e_idx++;
		config_head = config_head->next;
	}	
	return (envp);
}
