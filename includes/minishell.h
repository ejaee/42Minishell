/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:53:34 by ilhna             #+#    #+#             */
/*   Updated: 2023/02/03 19:04:36 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* color */

# define RED	"\x1b[31m"
# define GREEN	"\x1b[32m"
# define YELLOW	"\x1b[33m"
# define BLUE	"\x1b[34m"
# define WHITE	"\x1b[0m"
# define BROWN	"\e[38;5;137m"
# define RESET	"\x1b[0m"

/* string */

# define PROMPT BROWN"M O N G S H E L L$ "RESET
# define PROMPT_NAME "M O N G S H E L L"

# define ERR_EXIT_MANY_ARGS "exit: too many arguments"
# define ERR_EXIT_NUMERIC "numeric argument required"
# define ERR_CD "No such file or directory"
# define ERR_EXPORT "not a valid identifier"

/* flag */

# define PERMISSION 1
# define PERMISSION_DENIED 0

#include <fcntl.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_pid_t.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/param.h>
#include "libft.h"
#include "ft_printf.h"

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

/* builtin_cd.c */
void	builtin_cd(char *buf, t_config *config, int output_flag);


/* builtin_echo.c */
int		count_env_key_length(char *str);
int		check_env_echo(char *str, t_config *config);
int		check_opt_flag(char *str, int *idx);
void	print_env_echo(char *str, int *jdx, t_config *config);
void	builtin_echo(char *const argv[], t_config *config);


/* builtin_exit.c */
size_t	get_argv_count(char *const argv[]);
int		check_lld_range(char *arg, size_t lld_max_len, const char *lld_minmax_str[]);
int		check_exit_param(char *arg, int *out_exit_code);
void	builtin_exit(char *const argv[], int flag);


/* builtin_func.c */
void	builtin_cd(char *buf, t_config *config, int flag);
void	builtin_export(char *buf, t_config *config, int flag);
void	builtin_unset(char *const buf, t_config *config, int flag);
void	builtin_func(char *buf, t_config *config);


/* builtin_func.c */
void	builtin_pwd(void);
void	builtin_env(char *buf, t_config config);


/* load_config.c */
void	load_config(t_config *config, char **envp);


/* main.c */
t_list	*get_env_list(t_list *env_list, char *env_key);
int		set_env_list(t_list *env_list, char *env_key, char *new_value);


/* new_env */
t_env	*new_env(const char	*env);


/* signals.c */
void	set_son_signal();
void	sig_ctrl_c(int signal);
void	set_signal();


/* utils.c */
void	free_split(char **str);
void	ft_del(void *content);
void	panic(char *s);





#endif
