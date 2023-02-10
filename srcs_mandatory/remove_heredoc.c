/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:05:49 by ilhna             #+#    #+#             */
/*   Updated: 2023/02/09 18:42:57 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

static void	del_hdoc_info(void *content)
{
	t_hd_info	*hd_info;

	hd_info = (t_hd_info *)content;
	free(hd_info->limiter);
	hd_info->limiter = NULL;
	free(hd_info->file);
	hd_info->file = NULL;
	free(content);
	content = NULL;
}

static void	remove_hdoc_list(t_list *hd_head)
{
	t_list	*hd_del;

	while (hd_head)
	{
		hd_del = hd_head;
		hd_head = hd_head->next;
		ft_lstdelone(hd_del, del_hdoc_info);
	}
}

static void	remove_hdoc_files(t_list *hd_head)
{
	t_hd_info	*hd_info;
	char		pwd[MAXPATHLEN];
	char		*pwd_slash;
	char		*path;

	while (hd_head)
	{
		hd_info = (t_hd_info *)hd_head->content;
		ft_bzero(pwd, MAXPATHLEN);
		getcwd(pwd, MAXPATHLEN);
		pwd_slash = ft_strjoin(pwd, "/");
		path = ft_strjoin(pwd_slash, hd_info->file);
		unlink(path);
		free(pwd_slash);
		free(path);
		hd_head = hd_head->next;
	}
	pwd_slash = NULL;
	path = NULL;
}

void	remove_heredoc(t_list *hd_head)
{
	remove_hdoc_files(hd_head);
	remove_hdoc_list(hd_head);
}
