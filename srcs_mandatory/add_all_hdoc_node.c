/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_all_hdoc_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:49:07 by ilhna             #+#    #+#             */
/*   Updated: 2023/02/09 20: by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static t_hd_info	*new_hdoc_info(const char *limiter, int lim_len, \
									int file_num, int file_w_space)
{
	char		*tmp_file;
	t_hd_info	*new_hd_info;

	new_hd_info = (t_hd_info *)malloc(sizeof(t_hd_info));
	if (new_hd_info == NULL)
		return (NULL);
	new_hd_info->limiter = (char *)malloc(lim_len + 1);
	if (new_hd_info->limiter == NULL)
		return (NULL);
	ft_strlcpy(new_hd_info->limiter, limiter, lim_len + 1);
	tmp_file = ft_strjoin(".", ft_itoa(file_num));
	new_hd_info->file = ft_strjoin(tmp_file, ".heredoc");
	free(tmp_file);
	tmp_file = NULL;
	new_hd_info->file_w_space = file_w_space;
	return (new_hd_info);
}

static const char	*chk_hd_mv_buf(const char *buf, t_list **out_hd_head, \
								int *hd_flag, int *file_num)
{
	int			lim_len;
	t_list		*tmp_hd_list;
	const char	*buf_begin;

	*hd_flag += 1;
	lim_len = 0;
	buf_begin = buf;
	while (*buf == ' ')
		buf++;
	while (buf[lim_len] && (ft_isalnum(buf[lim_len]) == true || \
					ft_strchr("~!@$%^*-_=+", buf[lim_len]) != NULL))
		lim_len++;
	if (buf[lim_len] != '\0' && \
		(lim_len == 0 || ft_strchr("#<>|&", buf[lim_len]) != NULL))
		return (buf);
	*hd_flag -= 1;
	tmp_hd_list = ft_lstnew(new_hdoc_info(buf, lim_len, *file_num, \
											buf - buf_begin));
	if (tmp_hd_list == NULL)
		panic(ERR_MALLOC);
	*file_num += 1;
	ft_lstadd_back(out_hd_head, tmp_hd_list);
	buf += lim_len;
	return (buf);
}

static void	setup_vars(t_add_node_vars *vs, const char *buf)
{
	vs->hd_flag = 0;
	vs->file_num = 0;
	vs->buf_begin = buf;
	vs->idxs.begin = -1;
	vs->idxs.end = -1;
}

static void	update_last_node_idxs(t_list **out_hd_head, const t_idxs *idxs)
{
	t_list		*lstcp;
	t_hd_info	*info;

	lstcp = *out_hd_head;
	if (lstcp == NULL)
		return ;
	lstcp = ft_lstlast(lstcp);
	info = lstcp->content;
	info->idxs.begin = idxs->begin;
	info->idxs.end = idxs->end;
}

int	add_all_hdoc_node(const char *buf, t_list **o_hd_head)
{
	t_add_node_vars	v;

	setup_vars(&v, buf);
	while (*buf)
	{
		while (*buf == ' ')
			buf++;
		if (*buf && *buf == '<')
		{
			buf++;
			if (*buf && *buf == '<')
			{
				v.idxs.begin = buf - v.buf_begin;
				buf = chk_hd_mv_buf(++buf, o_hd_head, &v.hd_flag, &v.file_num);
				v.idxs.end = buf - v.buf_begin - 1;
				if (v.hd_flag == 1)
					break ;
				update_last_node_idxs(o_hd_head, &v.idxs);
			}
		}
		if (*buf == '\0')
			break ;
		buf++;
	}
	return (v.hd_flag);
}
