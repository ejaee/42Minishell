/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:11:07 by ilhna             #+#    #+#             */
/*   Updated: 2023/01/30 14:11:34 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_u(va_list *ap, int fd)
{
	int				len;
	unsigned int	num;
	char			str[10];

	num = va_arg(*ap, unsigned int);
	if (num == 0)
	{
		if (ft_putchar_fd_cstm('0', fd) == PF_ERROR)
			return (PF_ERROR);
		return (1);
	}
	ft_memset(str, 'g', 10);
	len = 0;
	while (num > 0)
	{
		str[10 - len - 1] = num % 10 + '0';
		num /= 10;
		len++;
	}
	if (putarr(str, 10, fd) == PF_ERROR)
		return (PF_ERROR);
	return (len);
}
