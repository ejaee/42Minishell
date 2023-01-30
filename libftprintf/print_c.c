/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:44:32 by ilhna             #+#    #+#             */
/*   Updated: 2023/01/30 13:00:30 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(va_list *ap, int fd)
{
	char	c;

	c = va_arg(*ap, int);
	if (ft_putchar_fd_cstm(c, fd) == PF_ERROR)
		return (PF_ERROR);
	return (1);
}
