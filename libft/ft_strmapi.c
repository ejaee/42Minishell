/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:37:16 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/21 09:33:53 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dst;
	size_t	idx;

	dst = (char *)malloc(ft_strlen(s) + 1);
	if (dst == (void *)0)
		return ((void *)0);
	idx = 0;
	while (s[idx] != '\0')
	{
		dst[idx] = f(idx, s[idx]);
		idx++;
	}
	dst[idx] = '\0';
	return (dst);
}
