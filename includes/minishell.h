/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:53:34 by ilhna             #+#    #+#             */
/*   Updated: 2023/02/01 15:12:42 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED	"\x1b[31m"
# define GREEN	"\x1b[32m"
# define YELLOW	"\x1b[33m"
# define BLUE	"\x1b[34m"
# define WHITE	"\x1b[0m"
# define BROWN	"\e[38;5;137m"
# define RESET	"\x1b[0m"

# define PROMPT BROWN"M O N G S H E L L$ "RESET
# define PROMPT_NAME "M O N G S H E L L"

# define ERR_EXIT_MANY_ARGS "exit: too many arguments"
# define ERR_EXIT_NUMERIC "numeric argument required"
# define ERR_CD "No such file or directory"
# define ERR_EXPORT "not a valid identifier"

# include "libft.h"

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

int	g_exit_code;

void	load_config(t_config *config, char **envp);
t_env	*new_env(const char	*env);

void	panic(char *s);

#endif
