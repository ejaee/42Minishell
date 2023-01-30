/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd_cstm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:53:36 by ilhna             #+#    #+#             */
/*   Updated: 2022/11/10 20:53:44 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_putchar_fd_cstm(char c, int fd)
{
	ssize_t	write_val;

	write_val = write(fd, &c, 1);
	return (write_val);
}
