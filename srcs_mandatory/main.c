// Shell.
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
#include "libft.h"
#include "minishell.h"
#include "ft_printf.h"

// Parsed command representation
#define EXEC 1
#define REDIR 2
#define PIPE 3
#define BACK 5

#define MAXARGS 10

struct cmd
{
	int type;
};

struct execcmd
{
	int type;
	char *argv[MAXARGS];
	char *eargv[MAXARGS];
};

struct redircmd
{
	int type;
	struct cmd *cmd;
	char *file;
	char *efile;
	int mode;
	int fd;
};

struct pipecmd
{
	int type;
	struct cmd *left;
	struct cmd *right;
};

struct backcmd
{
	int type;
	struct cmd *cmd;
};

// int fork1(void); // Fork but panics on failure.
void panic(char *);
struct cmd *parsecmd(char *);

char *ft_gets(char *buf, int max)
{
	int i, cc;
	char c;

	for (i = 0; i + 1 < max;)
	{
		cc = read(0, &c, 1);
		if (cc < 1)
			break;
		buf[i++] = c;
		if (c == '\n' || c == '\r')
			break;
	}
	buf[i] = '\0';
	return buf;
}

#include <sys/param.h>

t_list	*get_env_list(t_list *env_list, char *env_key)
{
	t_env *cur_env;
	
	while (env_list)
	{
		cur_env = (t_env *)env_list->content;
		if (!ft_strncmp(cur_env->key, env_key, ft_strlen(env_key) + 1))
			return (env_list);
		env_list = env_list->next;
	}
	return NULL;
}

int	set_env_list(t_list *env_list, char *env_key, char *new_value)
{
	t_env *cur_env;
	
	while (env_list)
	{
		cur_env = (t_env *)env_list->content;
		if (!ft_strncmp(cur_env->key, env_key, ft_strlen(env_key) + 1))
		{
			if (cur_env->value != NULL)
				free(cur_env->value);
			
			cur_env->value = ft_strdup(new_value);
			cur_env = NULL;
			// printf(RED"check result ||%s||\n"RESET, cur_env->value);
			return (0);
		}
		env_list = env_list->next;
	}
	cur_env = NULL;
	return (1);
}

int	builtin_echo(char *const argv[])
{
	int	idx;

	idx = 0;
	while (argv[++idx])
	{
		if (idx > 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(argv[idx], STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int builtin_cd(char *const buf, t_config *config)
{
	char	*pwd_buf;

	pwd_buf = ft_calloc(1, MAXPATHLEN);
	if (getcwd(pwd_buf, MAXPATHLEN) == NULL)
	{
		printf("check error\n");
		return (1);
	}
	
	set_env_list(config->head, "OLDPWD", pwd_buf);
    
	if (chdir(buf+3))
	{
		printf("error check\n");
		return (1);
	}
	
	if (getcwd(pwd_buf, MAXPATHLEN) == NULL)
	{
		printf("check error\n");
		return (1);
	}
	
	set_env_list(config->head, "PWD", pwd_buf);
	free(pwd_buf);
	return (0);
}

void	free_split(char **str)
{
	int idx;

	idx = -1;
	while(str[++idx])
		free(str[idx]);
	free(str);
}

int builtin_export(char *buf, t_config *config)
{
	t_list *list;
	char **splited_env_by_pipe;
	char **splited_env_by_space;
	char **splited_env;

	list = config->head;
	splited_env_by_pipe = ft_split(buf, '|');
	splited_env_by_space = ft_split(splited_env_by_pipe[0], ' ');
	splited_env = ft_split_one_cstm(splited_env_by_space[0], '=');
	if (splited_env == NULL)
		panic("Fail: splited_env");
	if (splited_env[1] != NULL && set_env_list(list, splited_env[0], splited_env[1]))
		ft_d_lstadd_back(&list, ft_lstnew(new_env(splited_env_by_space[0])));
	free_split(splited_env_by_pipe);
	free_split(splited_env_by_space);
	free_split(splited_env);
	return (0);
}

void	ft_del(void *content)
{
	t_env *env;

	env = (t_env *)content;
	free(env->key);
	free(env->value);
	free(content);
}

int builtin_unset(char *const buf, t_config *config)
{
	t_list	*cur;
	char **splited_env;

	cur = config->head;
	splited_env = ft_split_one_cstm(buf, '=');
	if (splited_env == NULL)
		panic("Fail: ft_split_one_cstm()");
	cur = get_env_list(cur, splited_env[0]);
	if (splited_env[1] == NULL && cur)
	{
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		ft_lstdelone(cur, ft_del);
	}
	free_split(splited_env);
	return (0);
}

int	builtin_pwd(void)
{
	char	*buf;

	buf = ft_calloc(1, MAXPATHLEN);
	if (getcwd(buf, MAXPATHLEN) == NULL)
	{
		printf("check error\n");
		return (1);
	}
	ft_putstr_fd(buf, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(buf);
	return (0);
}

int builtin_env(t_config config)
{
	t_list *list;
	t_env *env;

	list = config.head->next;
	while (list->next)
	{
		env = list->content;
		ft_putstr_fd(env->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(env->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		list = list->next;
	}
	return (0);
}

size_t	get_argv_count(char *const argv[])
{
	size_t	len;

	len = 0;
	while (argv[len])
		len++;
	return (len);
}

int	check_lld_range(char *arg, size_t lld_max_len, const char *lld_minmax_str[])
{
	const char	*lld_str;

	if (lld_max_len > ft_strlen(arg))
		return (true);
	if (arg[0] == '-')
		lld_str = lld_minmax_str[0];
	else
		lld_str = lld_minmax_str[1];
	if (ft_strncmp(lld_str, arg, lld_max_len) < 0)
		return (false);
	return (true);
}

int	check_exit_param(char *arg, int *out_exit_code)
{
	const char	*lld_minmax_str[2];
	size_t	lld_max_len;
	long long	lld_arg;
	size_t	arg_len;

	lld_minmax_str[0] = "-9223372036854775808";
	lld_minmax_str[1] = "9223372036854775807";
	arg_len = ft_strnumlen(arg);
	lld_max_len = ft_strlen(lld_minmax_str[0]);
	if (arg_len == 0 || arg_len > lld_max_len)
		return (false);
	if (arg[0] != '-')
		lld_max_len--;
	if (check_lld_range(arg, lld_max_len, lld_minmax_str) == false)
		return (false);
	lld_arg = ft_atolld(arg);
	*out_exit_code = lld_arg % 256;
	return (true);
}

int	builtin_exit(char *const argv[])
{
	size_t			argc;

	argc = get_argv_count(argv);
	if (argc == 1)
	{
		ft_fprintf(STDOUT_FILENO, "exit\n");
		exit (0);
	}
	if (argc > 2 && check_exit_param(argv[1], &g_exit_code) == false)
	{
		ft_fprintf(STDOUT_FILENO, "exit\n");
		ft_fprintf(STDERR_FILENO, "%s: exit: %s: %s\n", \
					PROMPT_NAME, argv[1], ERR_EXIT_NUMERIC);
		g_exit_code = 255;
	}
	else if (argc > 2)
	{
		ft_fprintf(STDERR_FILENO, "%s: %s\n", PROMPT_NAME, ERR_EXIT_MANY_ARGS);
		return (0);
	}
	exit (g_exit_code);
}

void	set_son_signal()
{
	signal(SIGQUIT, SIG_DFL);
}

void runcmd(struct cmd *cmd, t_config config)
{
	int status;
	int	result;
	int p[2];
	struct backcmd *bcmd;
	struct execcmd *ecmd;
	struct pipecmd *pcmd;
	struct redircmd *rcmd;

	set_son_signal();
	if (cmd == 0)
		exit(0);
	result = -1;
	if (cmd->type == EXEC)
	{
		ecmd = (struct execcmd *)cmd;
		if (ecmd->argv[0] == 0)
			exit(1);
		if (ft_strnstr(ecmd->argv[0], "echo", 5))
			result = builtin_echo(ecmd->argv);
		if (ft_strnstr(ecmd->argv[0], "cd", 3))
			result = 0;
		else if (ft_strnstr(ecmd->argv[0], "pwd", 4))
			result = builtin_pwd();
		else if (ft_strnstr(ecmd->argv[0], "export", 7))
			result = 0;
		else if (ft_strnstr(ecmd->argv[0], "unset", 6))
			result = 0;
		else if (ft_strnstr(ecmd->argv[0], "env", 4))
			result = builtin_env(config);
		else if (ft_strnstr(ecmd->argv[0], "exit", 5))
			builtin_exit(ecmd->argv);

		else
			execv(ecmd->argv[0], ecmd->argv);
		if (result)
			printf("exec %s failed\n", ecmd->argv[0]);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (struct redircmd *)cmd;
		close(rcmd->fd);
		if (open(rcmd->file, rcmd->mode) < 0)
		{
			printf("open %s failed\n", rcmd->file);
			exit(1);
		}
		runcmd(rcmd->cmd, config);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (struct pipecmd *)cmd;
		if (pipe(p) < 0)
			panic("pipe");
		if (fork() == 0)
		{
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->left, config);
		}
		if (fork() == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->right, config);
		}
		close(p[0]);
		close(p[1]);
		wait(&status);
		wait(&status);
	}
	else if (cmd->type == BACK)
	{
		bcmd = (struct backcmd *)cmd;
		if (fork() == 0)
			runcmd(bcmd->cmd, config);
	}
	else
		panic("runcmd");
	exit(0);
}

// 2. 히어독 추가
// 3. 시그널 처리 (ctrl-C, ctrl-D, ctrl-\)
// 4. 빌트인 함수 만들기
//		4-7. exit
// 5. exit() 코드($?)
// 6. add_history();
// 7. parsing 에서 argc[] 이해
// 8. $
// 9. quoting " '

size_t	get_envp_count(char **system_envp)
{
	size_t	len;

	len = 0;
	while (system_envp[len])
		len++;
	return (len);
}

extern int	g_exit_code;

void	sig_ctrl_c(int signal)
{
	int	pid;

	pid = waitpid(-1, NULL, WNOHANG);
	g_exit_code = 1;

	if (signal == SIGINT)
	{
		if (pid == -1)
		{
			if (rl_on_new_line() == -1)
				exit(1);
			rl_replace_line("", 1);
			ft_putstr_fd("\n", STDOUT_FILENO);
			rl_redisplay();
		}
		else
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
	}
}

void	set_signal()
{
	signal(SIGINT, sig_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	check_buf(char **buf)
{
	if (*buf == NULL)
	{
		ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
		ft_putstr_fd("\033[19C", STDOUT_FILENO);
		ft_putstr_fd(RED"exit\n"RESET, 1);
		exit(0);
	}
	if (**buf == '\0')
	{
		**buf ='\n';
	}
}
void	show_logo_1(void)
{
	printf("%s╔══════════════════════════════════════════════════════════════════════════════════════════════════════════╗%s\n", BROWN, WHITE);
	printf("%s║                                                                                                          ║%s\n", BROWN, WHITE);
	printf("%s║   Welcome to 42 minishell project. %sLEE %s& %sGUN                                                             %s║%s\n", BROWN, RED, BROWN, YELLOW, BROWN, WHITE);
	printf("%s║                                                                                                          ║%s\n", BROWN, WHITE);
	printf("%s║                                                                                                          ║%s\n", BROWN, WHITE);
	printf("%s║            ██╗   ██╗████████╗██╗   ██╗████████╗  ████████╗██╗   ██╗████████╗██╗      ██╗                 ║%s\n", BROWN, WHITE);
	printf("%s║            %s███╗ ███║██╔═══██║███╗  ██║██╔═════╝  ██╔═════╝██║   ██║██╔═════╝██║      ██║                 %s║%s\n", BROWN, WHITE, BROWN, WHITE);
	printf("%s║            ██╔██╗██║██║   ██║██╔██╗██║██║ ████╗  ████████╗████████║██████╗  ██║      ██║                 ║%s\n", BROWN, WHITE);
	printf("%s║            %s██║╚═╝██║██║   ██║██║╚═███║██║ ╚═██║  ╚═════██║██╔═══██║██╔═══╝  ██║      ██║                 %s║%s\n", BROWN, WHITE, BROWN, WHITE);
	printf("%s║            ██║   ██║████████║██║  ╚██║████████║  ████████║██║   ██║████████╗████████╗████████╗           ║%s\n", BROWN, WHITE);
	printf("%s║            ╚═╝   ╚═╝╚═══════╝╚═╝   ╚═╝╚═══════╝  ╚═══════╝╚═╝   ╚═╝╚═══════╝╚═══════╝╚═══════╝           ║%s\n", BROWN, WHITE);
	printf("%s║                                                                                                          ║%s\n", BROWN, WHITE);
	printf("%s║                                                                             %s.created by ejachoi & ilhna  %s║%s\n", BROWN, WHITE, BROWN, WHITE);
	printf("%s║                                                                                                          ║%s\n", BROWN, WHITE);
	printf("%s╚══════════════════════════════════════════════════════════════════════════════════════════════════════════╝%s\n", BROWN, WHITE);
	printf("\n");
}

void	show_shell_logo(void)
{
	show_logo_1();
	// show_logo_2();
}

void	check_run_exit_parent(struct cmd *cmd)
{
	struct execcmd	*ecmd;

	if (cmd == 0)
		exit(0);

	if (cmd->type == EXEC)
	{
		ecmd = (struct execcmd *)cmd;
		if (ecmd->argv[0] == 0)
			exit(1);
		if (ft_strnstr(ecmd->argv[0], "exit", 5))
			builtin_exit(ecmd->argv);
	}
}

int main(int argc, char **argv, char **envp)
{
	char	*buf;
	int			status;
	t_config	config;
	char **splited_cmd;

	(void)argc;
	(void)argv;
	show_shell_logo();
	load_config(&config, envp);
	while (1)
	{
		set_signal();
		buf = readline(PROMPT);
		check_buf(&buf);
		splited_cmd = ft_split(buf, ' ');
		if (ft_strnstr(splited_cmd[0], "cd", 2))
		{
			if (builtin_cd(buf, &config))
				printf("cannot cd %s\n", buf+3);
		}
		if (ft_strnstr(splited_cmd[0], "export", 6))
		{
			if (splited_cmd[2] == NULL && builtin_export(splited_cmd[1], &config))
				printf("cannot export %s\n", splited_cmd[1]);
		}
		if (ft_strnstr(buf, "unset", 5))
		{
			if (splited_cmd[2] == NULL && builtin_unset(splited_cmd[1], &config))
				printf("cannot unset %s\n", splited_cmd[1]);
		}
		// system("leaks minishell");/////////////////////////////////////////////
		free_split(splited_cmd);
		check_run_exit_parent(parsecmd(buf));

		if (fork() == 0)
			runcmd(parsecmd(buf), config);
		wait(&status);
		free(buf);
	}
	exit(0);
}

void panic(char *s)
{
	printf("%s\n", s);
	exit(1);
}

struct cmd *init_execcmd(void)
{
	struct execcmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return (struct cmd *)cmd;
}

struct cmd *redircmd(struct cmd *subcmd, char *file, char *efile, int mode, int fd)
{
	struct redircmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->efile = efile;
	cmd->mode = mode;
	cmd->fd = fd;
	return (struct cmd *)cmd;
}

struct cmd *pipecmd(struct cmd *left, struct cmd *right)
{
	struct pipecmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return (struct cmd *)cmd;
}

struct cmd *backcmd(struct cmd *subcmd)
{
	struct backcmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = BACK;
	cmd->cmd = subcmd;
	return (struct cmd *)cmd;
}
// PAGEBREAK!
//  Parsing

char whitespace[] = " \t\r\n\v";
char symbols[] = "<|>&()";

int gettoken(char **out_str_ptr, char *str_end, char **out_q, char **out_eq)
{
	char *str;
	int ret;

	str = *out_str_ptr;
	while (str < str_end && strchr(whitespace, *str))
		str++;
	// 포인터가 가리키고 있는 시점에서 가장 가까운 text, sym
	if (out_q)
		*out_q = str;
	ret = *str;
	if (*str == '|' || *str == '(' || *str == ')' || \
		*str == '&')
		str++;
	else if (*str == '>')
	{
		str++;
		if (*str == '>')
		{
			ret = '+';
			str++;
		}
	}
	else if (*str == '<')
	{
		str++;
		if (*str == '<')
		{
			ret = 'h';
			str++;
		}
	}
	else if (*str != 0)
	{
		ret = 'a';
		// text를 공백이나 sym 이 올 때까지 밀어버린다
		while (str < str_end && !strchr(whitespace, *str) && !strchr(symbols, *str))
			str++;
	}
	
	// sym 일 경우에는 sym이 끝난 바로 다음, text 일 경우에는 공백 또는 sym 또는 끝
	if (out_eq)
		*out_eq = str;

	while (str < str_end && strchr(whitespace, *str))
		str++;
	*out_str_ptr = str;
	return ret;
}

// 공백을 넘긴다
// 현재 가리키는 문자부터 끝까지 toks 이 있는지 확인한다
int skip_space_check_toks(char **out_ps, char *str_end, char *toks)
{
	char *str;

	str = *out_ps;
	while (str < str_end && strchr(whitespace, *str))
		str++;
	*out_ps = str;
	return *str && strchr(toks, *str);
}

struct cmd *parseline(char **, char *);
struct cmd *parsepipe(char **, char *);
struct cmd *parseexec(char **, char *);
struct cmd *nulterminate(struct cmd *);

struct cmd *parsecmd(char *str)
{
	char *str_end;
	struct cmd *cmd;

	// str_end = str + ft_strlen(str);
	str_end = str + strlen(str);
	cmd = parseline(&str, str_end);
	skip_space_check_toks(&str, str_end, "");
	if (str != str_end)
	{
		printf("leftovers: %s\n", str);
		panic("syntax");
	}
	nulterminate(cmd);
	return cmd;
}

struct cmd *parseline(char **str_ptr, char *str_end)
{
	struct cmd *cmd;

	cmd = parsepipe(str_ptr, str_end);
	while (skip_space_check_toks(str_ptr, str_end, "&"))
	{
		gettoken(str_ptr, str_end, 0, 0);
		cmd = backcmd(cmd);
	}
	return cmd;
}

struct cmd *parsepipe(char **out_str_ptr, char *str_end)
{
	struct cmd *cmd;

	cmd = parseexec(out_str_ptr, str_end);
	if (skip_space_check_toks(out_str_ptr, str_end, "|"))
	{
		gettoken(out_str_ptr, str_end, 0, 0);
		cmd = pipecmd(cmd, parsepipe(out_str_ptr, str_end));
	}
	return cmd;
}

struct cmd *parseredirs(struct cmd *cmd, char **str_ptr, char *str_end)
{
	int		tok;
	char	*q;
	char	*eq;

	while (skip_space_check_toks(str_ptr, str_end, "<>"))
	{
		// sym 인지, >> 인지, text 인지를 tok 에 저장
		tok = gettoken(str_ptr, str_end, 0, 0);
		if (gettoken(str_ptr, str_end, &q, &eq) != 'a')
			panic("missing file for redirection");
		if (tok == '<')
			cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
		else if (tok == '>')
			cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREAT, 1);
		// >>
		else if (tok == '+')
			cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREAT, 1);
		// <<
		else if (tok == 'h')
			cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREAT, 1);
	}
	return cmd;
}

struct cmd *parseblock(char **out_str_prt, char *str_end)
{
	struct cmd *cmd;

	if (!skip_space_check_toks(out_str_prt, str_end, "("))
		panic("parseblock");
	gettoken(out_str_prt, str_end, 0, 0);
	cmd = parseline(out_str_prt, str_end);
	if (!skip_space_check_toks(out_str_prt, str_end, ")"))
		panic("syntax - missing )");
	gettoken(out_str_prt, str_end, 0, 0);
	cmd = parseredirs(cmd, out_str_prt, str_end);
	return cmd;
}

struct cmd *parseexec(char **out_str_ptr, char *str_end)
{
	char *q, *eq;
	int tok, argc;
	struct execcmd *cmd;
	struct cmd *ret;

	if (skip_space_check_toks(out_str_ptr, str_end, "("))
		return parseblock(out_str_ptr, str_end);

	ret = init_execcmd();
	cmd = (struct execcmd *)ret;

	// issue 1
	argc = 0;
	ret = parseredirs(ret, out_str_ptr, str_end);
	// issue 2
	while (!skip_space_check_toks(out_str_ptr, str_end, "|)&"))
	{
		if ((tok = gettoken(out_str_ptr, str_end, &q, &eq)) == 0)
			break;
		if (tok != 'a')
			panic("syntax");
		cmd->argv[argc] = q;
		cmd->eargv[argc] = eq;
		argc++;
		if (argc >= MAXARGS)
			panic("too many args");
		ret = parseredirs(ret, out_str_ptr, str_end);
	}
	cmd->argv[argc] = 0;
	cmd->eargv[argc] = 0;
	return ret;
}

// NUL-terminate all the counted strings.
struct cmd *nulterminate(struct cmd *cmd)
{
	int i;
	struct backcmd *bcmd;
	struct execcmd *ecmd;
	struct pipecmd *pcmd;
	struct redircmd *rcmd;

	if (cmd == 0)
		return 0;

	if (cmd->type == EXEC)
	{
		ecmd = (struct execcmd *)cmd;
		for (i = 0; ecmd->argv[i]; i++)
			*ecmd->eargv[i] = 0;
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (struct redircmd *)cmd;
		nulterminate(rcmd->cmd);
		*rcmd->efile = 0;
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (struct pipecmd *)cmd;
		nulterminate(pcmd->left);
		nulterminate(pcmd->right);
	}
	else if (cmd->type == BACK)
	{
		bcmd = (struct backcmd *)cmd;
		nulterminate(bcmd->cmd);
	}
	return cmd;
}
