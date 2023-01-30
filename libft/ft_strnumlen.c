/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnumlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:14:18 by ilhna             #+#    #+#             */
/*   Updated: 2023/01/30 15:52:16 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

size_t	ft_strnumlen(const char *s)
{
	size_t	len;

	if (*s == '\0')
		return (0);
	len = 0;
	if (*s == '-')
		len++;
	while (*(s + len) == '0')
		s++;
	while (ft_isdigit(*(s + len)) == true)
		len++;
	if (*(s + len) != '\0')
		return (0);
	if (len == 0)
		return (1);
	return (len);
}
