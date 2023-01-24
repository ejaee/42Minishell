/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:47:41 by ilhna             #+#    #+#             */
/*   Updated: 2023/01/24 12:56:11 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	load_config(t_config *config, char **envp)
{
	int		env_idx;
	t_list	*cur;

	env_idx = 0;
	config->env_list = ft_lstnew(new_env(envp[env_idx]));
	if (config->env_list == NULL)
		panic("Fail: ft_lstnew()");
	cur = config->env_list;
	while (envp[++env_idx])
	{
		cur->next = ft_lstnew((void *)new_env(envp[env_idx]));
		if (cur->next == NULL)
			panic("Fail: ft_lstnew()");
		cur = cur->next;
	}
}
