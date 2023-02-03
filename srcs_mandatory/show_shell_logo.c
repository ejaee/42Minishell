/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_logo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:05:09 by ejachoi           #+#    #+#             */
/*   Updated: 2023/02/03 21:05:26 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_logo_1(void)
{
	ft_printf("%s╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗%s\n", BROWN, WHITE);
	ft_printf("%s║                                                                                                      ║%s\n", BROWN, WHITE);
	ft_printf("%s║   Welcome to 42 minishell project. %sLEE %s& %sGUN                                                         %s║%s\n", BROWN, RED, BROWN, YELLOW, BROWN, WHITE);
	ft_printf("%s║                                                                                                      ║%s\n", BROWN, WHITE);
	ft_printf("%s║                                                                                                      ║%s\n", BROWN, WHITE);
	ft_printf("%s║          ██╗   ██╗████████╗██╗   ██╗████████╗  ████████╗██╗   ██╗████████╗██╗      ██╗               ║%s\n", BROWN, WHITE);
	ft_printf("%s║          %s███╗ ███║██╔═══██║███╗  ██║██╔═════╝  ██╔═════╝██║   ██║██╔═════╝██║      ██║               %s║%s\n", BROWN, WHITE, BROWN, WHITE);
	ft_printf("%s║          ██╔██╗██║██║   ██║██╔██╗██║██║ ████╗  ████████╗████████║██████╗  ██║      ██║               ║%s\n", BROWN, WHITE);
	ft_printf("%s║          %s██║╚═╝██║██║   ██║██║╚═███║██║ ╚═██║  ╚═════██║██╔═══██║██╔═══╝  ██║      ██║               %s║%s\n", BROWN, WHITE, BROWN, WHITE);
	ft_printf("%s║          ██║   ██║████████║██║  ╚██║████████║  ████████║██║   ██║████████╗████████╗████████╗         ║%s\n", BROWN, WHITE);
	ft_printf("%s║          ╚═╝   ╚═╝╚═══════╝╚═╝   ╚═╝╚═══════╝  ╚═══════╝╚═╝   ╚═╝╚═══════╝╚═══════╝╚═══════╝         ║%s\n", BROWN, WHITE);
	ft_printf("%s║                                                                                                      ║%s\n", BROWN, WHITE);
	ft_printf("%s║                                                                         %s.created by ejachoi & ilhna  %s║%s\n", BROWN, WHITE, BROWN, WHITE);
	ft_printf("%s║                                                                                                      ║%s\n", BROWN, WHITE);
	ft_printf("%s╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝%s\n", BROWN, WHITE);
	ft_printf("\n");
}

void	show_shell_logo(void)
{
	show_logo_1();
	// show_logo_2();
}