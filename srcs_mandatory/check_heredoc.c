/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:55:48 by ilhna             #+#    #+#             */
/*   Updated: 2023/02/10 17:25:51 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include "ft_printf.h"
#include "libft.h"
#include "minishell.h"

static int	get_new_buf_len(const char *buf, t_list *hd_head)
{
	int	new_buf_len;
	int	buf_len;
	int	file_len;
	int	raw_lim_len;

	raw_lim_len = 0;
	file_len = 0;
	buf_len = ft_strlen(buf);
	while (hd_head)
	{
		file_len += ft_strlen(((t_hd_info *)hd_head->content)->file);
		raw_lim_len += ((t_hd_info *)hd_head->content)->idxs.end - \
						((t_hd_info *)hd_head->content)->idxs.begin + 1;
		hd_head = hd_head->next;
	}
	new_buf_len = buf_len - raw_lim_len + file_len;
	return (new_buf_len);
}

static void	setup_get_new_buf(char *buf, char **new_buf, int *new_buf_len, \
								t_list *hd_head)
{
	*new_buf_len = get_new_buf_len(buf, hd_head);
	*new_buf = (char *)malloc(*new_buf_len + 1);
	if (*new_buf == NULL)
		panic(ERR_MALLOC);
	ft_bzero(*new_buf, *new_buf_len + 1);
}

static char	*get_new_buf_free(char *buf, t_list *hd_head, int b_idx, int nb_idx)
{
	char		*new_buf;
	t_hd_info	*hd_i;
	int			buf_len;
	int			new_buf_len;

	setup_get_new_buf(buf, &new_buf, &new_buf_len, hd_head);
	buf_len = ft_strlen(buf);
	while (hd_head)
	{
		hd_i = hd_head->content;
		ft_memcpy(new_buf + nb_idx, buf + b_idx, hd_i->idxs.begin - b_idx);
		nb_idx += hd_i->idxs.begin - b_idx;
		b_idx += hd_i->idxs.begin - b_idx;
		ft_memcpy(new_buf + nb_idx, hd_i->file, ft_strlen(hd_i->file));
		b_idx += hd_i->idxs.end - hd_i->idxs.begin + 1;
		nb_idx += ft_strlen(hd_i->file);
		hd_head = hd_head->next;
	}
	if (nb_idx < new_buf_len)
		ft_memcpy(new_buf + nb_idx, buf + b_idx, buf_len - b_idx);
	free(buf);
	return (new_buf);
}

char	*check_heredoc(char *buf, t_list **hd_head)
{
	size_t	hdoc_error;

	*hd_head = NULL;
	if (buf == NULL)
		return (NULL);
	hdoc_error = add_all_hdoc_node(buf, hd_head);
	make_hdoc_file(*hd_head);
	if (hdoc_error == true)
	{
		ft_fprintf(STDERR_FILENO, RED"Syntax error\n"RESET);
		free(buf);
		buf = (char *)malloc(sizeof(char) * 2);
		ft_bzero(buf, 2);
	}
	else if (*buf != '\0')
		buf = get_new_buf_free(buf, *hd_head, 0, 0);
	return (buf);
}
