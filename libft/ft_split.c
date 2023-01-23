/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 09:02:17 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/21 09:36:55 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_arrlen(char const *s, char c);
static size_t	add_wd(char const *s, char c, char **outarr, size_t arridx);
static size_t	get_wdcnt(char const **sp, const char c);

char	**ft_split(char const *s, char c)
{
	size_t	arrlen;
	char	**outarr;

	arrlen = get_arrlen(s, c);
	outarr = (char **)malloc(sizeof(char *) * (arrlen + 1));
	if (outarr == (void *)0)
		return ((void *)0);
	if (arrlen && add_wd(s, c, outarr, 0) == 0)
		return ((void *)0);
	outarr[arrlen] = (void *)0;
	return (outarr);
}

static size_t	get_arrlen(char const *s, char c)
{
	size_t	arrlen;

	arrlen = 0;
	while (*s)
	{
		if (get_wdcnt(&s, c) > 0)
			arrlen++;
	}
	return (arrlen);
}

static size_t	add_wd(char const *s, char c, char **outarr, size_t arridx)
{
	size_t	wdcnt;

	while (*s)
	{
		wdcnt = get_wdcnt(&s, c);
		if (wdcnt > 0)
		{
			outarr[arridx] = (char *)malloc(wdcnt + 1);
			if (outarr[arridx] == (void *)0)
			{
				while (arridx == 0 || arridx - 1 >= 0)
				{
					free(outarr[arridx - 1]);
					outarr[arridx - 1] = (void *)0;
					arridx--;
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

static size_t	get_wdcnt(char const **sp, const char c)
{
	size_t	wdcnt;

	wdcnt = 0;
	while (**sp && **sp == c)
		(*sp)++;
	while (**sp && **sp != c)
	{
		wdcnt++;
		(*sp)++;
	}
	return (wdcnt);
}
