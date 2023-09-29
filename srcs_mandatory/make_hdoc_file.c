/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_hdoc_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:53:03 by ilhna             #+#    #+#             */
/*   Updated: 2023/02/10 18:23:24 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

static char	*size_up_free_ma_out(char **src, size_t *cur_size)
{
	char	*dst;

	*cur_size = *cur_size * 2;
	dst = (char *)ft_calloc(*cur_size, 1);
	if (dst == NULL)
		panic(ERR_MALLOC);
	ft_memcpy(dst, *src, ft_strlen(*src));
	free(*src);
	*src = NULL;
	return (dst);
}

static int	read_line(char **buf)
{
	char	*tmp_buf;
	size_t	m_size;
	char	c;
	int		r_len;
	size_t	idx;

	m_size = 4096;
	tmp_buf = (char *)ft_calloc(m_size, 1);
	if (tmp_buf == NULL)
		panic(ERR_MALLOC);
	ft_putstr_fd("> ", 2);
	r_len = read(0, &c, 1);
	idx = 0;
	while (r_len && c != '\n' && c != '\0')
	{
		if (m_size < idx + 2)
			tmp_buf = size_up_free_ma_out(&tmp_buf, &m_size);
		tmp_buf[idx] = c;
		idx++;
		r_len = read(0, &c, 1);
	}
	tmp_buf[idx] = '\n';
	*buf = tmp_buf;
	return (r_len);
}

static void	here_doc(char *limiter, char *file)
{
	int		fd;
	char	*buf;
	int		limiter_len;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (fd == -1)
		panic(ERR_OPEN);
	limiter_len = ft_strlen(limiter);
	while (read_line(&buf))
	{
		if ((ft_strncmp(buf, limiter, limiter_len) == 0 && \
			buf[limiter_len] == '\n') || *buf == 0)
			break ;
		write(fd, buf, ft_strlen(buf));
		free(buf);
	}
	if (buf != NULL)
		free(buf);
	close(fd);
	exit(EXIT_SUCCESS);
}

void	make_hdoc_file(t_list *hd_head)
{
	t_list		*hd_curr;
	t_hd_info	*hdoc_info;
	pid_t		pid;
	int			status;

	if (hd_head == NULL)
		return ;
	hd_curr = hd_head;
	while (hd_curr)
	{
		hdoc_info = hd_curr->content;
		pid = fork();
		if (pid == -1)
			panic(ERR_FORK);
		if (pid == 0)
		{
			set_son_signal();
			here_doc(hdoc_info->limiter, hdoc_info->file);
		}
		wait(&status);
		hd_curr = hd_curr->next;
	}
}
