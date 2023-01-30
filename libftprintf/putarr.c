/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putarr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:15:17 by ilhna             #+#    #+#             */
/*   Updated: 2023/01/30 14:04:04 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putarr(char *arr, int len, int fd)
{
	int	tmp;

	tmp = -1;
	while (++tmp < len)
	{
		if (arr[tmp] == 'g')
			continue ;
		if (ft_putchar_fd_cstm(arr[tmp], fd) == PF_ERROR)
			return (PF_ERROR);
	}
	return (0);
}
