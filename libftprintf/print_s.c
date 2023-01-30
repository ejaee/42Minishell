/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:45:24 by ilhna             #+#    #+#             */
/*   Updated: 2023/01/30 14:02:01 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_s(va_list *ap, int fd)
{
	int		len;
	char	*str;

	str = va_arg(*ap, char *);
	if (str == NULL)
	{
		write(fd, "(null)", 6);
		return (NULL_STR);
	}
	len = 0;
	while (*(str + len))
	{
		if (ft_putchar_fd_cstm(*(str + len), fd) == PF_ERROR)
			return (PF_ERROR);
		len++;
	}
	return (len);
}
