/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:47:41 by ilhna             #+#    #+#             */
/*   Updated: 2023/01/30 21:27:29 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	load_config(t_config *config, char **envp)
{
	int		env_idx;
	t_list	*cur;

	env_idx = -1;
	config->head = ft_lstnew(new_env("dummy node=(null)"));
	if (config->head == NULL)
		panic("Fail: make head node");
	config->tail = ft_lstnew(new_env("dummy node=(null)"));
	if (config->tail == NULL)
		panic("Fail: make tail node");
	config->head->next = config->tail;
	config->tail->prev = config->head;
	cur = config->head;
	while (envp[++env_idx])
	{
		cur->next = ft_lstnew((void *)new_env(envp[env_idx]));
		cur->next->prev = cur;
		config->tail->prev = cur->next;
		cur->next->next = config->tail;
		if (cur->next == NULL)
			panic("Fail: make next node");
		cur = cur->next;
	}
	cur = config->head;
}
