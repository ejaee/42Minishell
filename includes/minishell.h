/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choiejae <choiejae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:53:34 by ilhna             #+#    #+#             */
/*   Updated: 2023/01/27 17:29:29 by choiejae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT BLUE"M O N G S H E L L$ "RESET

# include "libft.h"

// color.h
# define RED	"\x1b[31m"
# define GREEN	"\x1b[32m"
# define YELLOW	"\x1b[33m"
# define BLUE	"\x1b[34m"
# define RESET	"\x1b[0m"

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_config
{
	t_list	*head;
	t_list	*tail;
}	t_config;

int	g_is_sig_interupt;
void	load_config(t_config *config, char **envp);
t_env	*new_env(const char	*env);



void	panic(char *s);


#endif
