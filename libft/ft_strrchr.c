/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 09:40:38 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/20 18:00:03 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*scp;
	char	*c_addr;

	scp = (char *)s;
	c_addr = (void *)0;
	while (*scp)
	{
		if ((unsigned char)c == *(unsigned char *)scp)
			c_addr = scp;
		scp++;
	}
	if (c == '\0')
		return (scp);
	else if (c_addr != (void *)0)
		return (c_addr);
	return ((void *)0);
}
