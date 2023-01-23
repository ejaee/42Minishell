/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 10:45:02 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/20 15:59:40 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;
	size_t	hidx;

	if (*needle == '\0')
		return ((char *)haystack);
	nlen = ft_strlen(needle);
	hidx = 0;
	while (*(haystack + hidx) && hidx + nlen - 1 < len)
	{
		if (ft_strncmp(haystack + hidx, needle, nlen) == 0)
			return ((char *)(haystack + hidx));
		hidx++;
	}
	return ((void *)0);
}
