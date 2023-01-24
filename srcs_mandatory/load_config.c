/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:47:41 by ilhna             #+#    #+#             */
/*   Updated: 2023/01/24 01:50:26 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	load_config(t_config *config, char **envp)
{
	int		env_idx;
	t_list	*node;

	env_idx = 0;
	node = ft_lstnew(new_env(envp[env_idx]));
	if (node == NULL)
		panic("Fail: ft_lstnew()");
	config->env_node = node;
	while (envp[++env_idx])
	{
		node->next = ft_lstnew((void *)new_env(envp[env_idx]));
		if (node->next == NULL)
			panic("Fail: ft_lstnew()");
		node = node->next;
	}
}
