// Shell.
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"

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

// Execute cmd.  Never returns.
void runcmd(struct cmd *cmd)
{
	int status;
	int	result;
	int p[2];
	struct backcmd *bcmd;
	struct execcmd *ecmd;
	struct pipecmd *pcmd;
	struct redircmd *rcmd;

	if (cmd == 0)
		exit(0);

	if (cmd->type == EXEC)
	{
		ecmd = (struct execcmd *)cmd;
		if (ecmd->argv[0] == 0)
			exit(1);

		// if (ft_strnstr(ecmd->argv[0], "echo", 5))
		// 	builtin_echo(ecmd->argv);
		// else if (ft_strnstr(ecmd->argv[0], "cd", 3))
		// 	builtin_cd(ecmd->argv);
		if (ft_strnstr(ecmd->argv[0], "pwd", 4))
			result = builtin_pwd(ecmd->argv);
		// else if (ft_strnstr(ecmd->argv[0], "export", 7))
		// 	builtin_export(ecmd->argv);
		// else if (ft_strnstr(ecmd->argv[0], "unset", 6))
		// 	builtin_unset(ecmd->argv);
		// else if (ft_strnstr(ecmd->argv[0], "env", 4))
		// 	builtin_env(ecmd->argv);
		// else if (ft_strnstr(ecmd->argv[0], "exit", 5))
		// 	builtin_exit(ecmd->argv);
		
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
		runcmd(rcmd->cmd);
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
			runcmd(pcmd->left);
		}
		if (fork() == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->right);
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
			runcmd(bcmd->cmd);
	}
	else
		panic("runcmd");
	exit(0);
}

int getcmd(char *buf, int nbuf)
{
	write(1, "$ ", 2);
	memset(buf, 0, nbuf);
	ft_gets(buf, nbuf);
	if (buf[0] == 0)
		return -1;
	return 0;
}

// 1. init_env
// 2. 히어독 추가
// 3. 시그널 처리 (ctrl-C, ctrl-D, ctrl-\)
// 4. 빌트인 함수 만들기
//		4-1. echo
//		4-2. cd
//		4-3. pwd
//		4-4. export
//		4-5. unset
//		4-6. env
//		4-7. exit
// 5. exit() 코드($?)
// 6. add_history();
// 7. parsing 에서 argc[] 이해
// 8. $
// 9. quoting " '
// 10. 

int main(int argc, char **argv, char **env)
{
	static char	buf[100];
	int			fd;
	int			status;

	while (getcmd(buf, sizeof(buf)) >= 0)
	{
		if (fork() == 0)
			runcmd(parsecmd(buf));
		wait(&status);
	}
	exit(0);
}

void panic(char *s)
{
	printf("%s\n", s);
	exit(1);
}

// PAGEBREAK!
//  Constructors

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
