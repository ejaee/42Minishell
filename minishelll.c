/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishelll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choiejae <choiejae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:46:26 by choiejae          #+#    #+#             */
/*   Updated: 2023/01/18 21:41:10 by choiejae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void print_intro() 
{
	int		intro_fd;
	int		read_size;
	char	buffer[1024];

	intro_fd = open("intro.txt", O_RDONLY);
	if (intro_fd < 0)
	{
		printf("fail to open intro.txt");
		return ;
	}
		
	while (1)
	{
		read_size = read(intro_fd, buffer, 1024);
		buffer[read_size] = '\0';
		if (read_size < 1)
		{
			printf("\n");
			break;
		}
		printf("%s", buffer);
	}
	close(intro_fd);
}

int	getcmd(char *buffer)
{
	printf("$ ");
	memset(buffer, 0, sizeof(buffer));
	gets(buffer);
	if (buffer[0] == '\0')
		return -1;
	return 0;
}

int	prompt(char *buffer)
{
	while (getcmd(buffer) >= 0)
	{
		
	}
}

int main(int argc, char **argv, char **env)
{
	t_cmd	*cmd;
	static char *buffer[1024];

	print_intro();
	getcmd(buffer);

	// init();
	// prompt(buffer);
	return 0;
}