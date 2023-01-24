/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_one_cstm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 09:02:17 by ilhna             #+#    #+#             */
/*   Updated: 2023/01/24 01:35:37 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

static size_t	get_limit_one_cstm(char const *s, char c);
static size_t	add_wd(char const *s, char c, char **outarr, size_t arridx);
static size_t	get_wdcnt_one_cstm(char const **sp, const char c, size_t flag);

char	**ft_split_one_cstm(char const *s, char c)
{
	size_t	arrlen;
	char	**outarr;

	arrlen = get_limit_one_cstm(s, c);
	outarr = (char **)malloc(sizeof(char *) * (arrlen + 1));
	if (outarr == (void *)0)
		return ((void *)0);
	if (arrlen && add_wd(s, c, outarr, 0) == 0)
		return ((void *)0);
	outarr[arrlen] = (void *)0;
	return (outarr);
}

static size_t	get_limit_one_cstm(char const *s, char c)
{
	size_t	arrlen;
	size_t	limit_len;
	size_t	flag;

	arrlen = 0;
	limit_len = 2;
	flag = 0;
	while (get_wdcnt_one_cstm(&s, c, flag) > 0)
	{
		if (arrlen == limit_len)
			break ;
		arrlen++;
		flag++;
	}
	return (arrlen);
}

static size_t	add_wd(char const *s, char c, char **outarr, size_t arridx)
{
	size_t	wdcnt;
	size_t	flag;

	flag = -1;
	while (*s)
	{
		wdcnt = get_wdcnt_one_cstm(&s, c, ++flag);
		if (wdcnt > 0)
		{
			outarr[arridx] = (char *)malloc(wdcnt + 1);
			if (outarr[arridx] == (void *)0)
			{
				while (arridx == 0 || arridx - 1 >= 0)
				{
					free(outarr[arridx - 1]);
					outarr[arridx-- - 1] = (void *)0;
				}
				return (0);
			}
			outarr[arridx] = ft_memcpy(outarr[arridx], s - wdcnt, wdcnt);
			outarr[arridx][wdcnt] = 0;
			arridx++;
		}
	}
	return (1);
}

static size_t	get_wdcnt_one_cstm(char const **sp, const char c, size_t flag)
{
	size_t	wdcnt;

	wdcnt = 0;
	if (**sp && **sp == c)
		(*sp)++;
	while (**sp)
	{
		if (flag == 0 && **sp == c)
			break ;
		wdcnt++;
		(*sp)++;
	}
	return (wdcnt);
}
