/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 09:40:42 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/20 17:59:57 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*scp;

	scp = (char *)s;
	while (*scp)
	{
		if ((unsigned char)c == *(unsigned char *)scp)
			return (scp);
		scp++;
	}
	if (c == '\0')
		return (scp);
	return (0);
}
