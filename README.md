# 42Minishell

### 🍄 **parsing**

input: 비어있지 않은 문자열

output: 순차적으로 정렬된 명령(or syntex_error)

1. 토큰화
2. syntex_error 처리
3. 구조체 생성

**종류**

- argv_token
    - cat -e, ls -al …
- space_token
    - 공백을 나타내는 토큰
- pipeline_token
    - 명령어를 이어주는 파이프라인 ‘**|**’
- I/O_red_token
    - >, >>, <, <<

***input 된 string은 최소 하나 이상의 chunk 또는 토큰으로 분리될 가능성이 있다***

“”, ‘’를 해석

“와 ‘가 짝이 나올때 까지 내용을  argv_token 으로 만들기

“”의 경우 내용의 $으로 시작하는 환경변수 해석이 가능해야 한다

‘’는 $환경변수 해석이 안된다

$ 로 시작하는 환경변수 해석

공백을 찾아 space_token 으로 분리

파이프라인 기준으로 pipeline_token 으로 분리

>, >>, <, << 연산자를 I/O red_token 으로 분리

남은 chunk가 있다면 argv_token 으로 치환

연속한  argv_token 병합

space_token 소각




_허용 함수 정리_

# 프로세스 관련

`pipe`

- 
- 헤더 : `#include <unistd.h>`
- 형식 : `int pipe(int fd[2])`

`fork`

- 프로세스 자신을 복제해서 새로운 프로세스를 만드는 시스템 콜
- 헤더 : `#include <unistd.h>`
- 형식 : `pid_t fork(void)`

> 프로세스를 복제해서 두 개의 프로세스로 분리한다
> 
> 
> 원래 존재하는 프로세스 쪽을 부모 프로세스
> 
> 복제해서 만들어진 프로세스 쪽을 자식 프로세스
> 

부모 프로세스에서 fork() 의 반환값은 자식 프로세스의 PID

자식 프로세스에서 반환값은 0

실패할 경우 자식 프로세스가 생성되지 않고 부모 프로세스에 -1이 반환

`exit`

- 프로세스 자기 자신을 새로운 프로그램으로 덮어 쓰는 시스템 호출
- 현재 실행 중인 프로그램이 소멸하고 새로운 프로그램을 로드하여 실행
- 전형적인 사용으로 fork() 하고 즉시 exec
- 헤더 : `#include <unistd.h>`
- 형식 : `int execXX`

> 실패 했을 때는  -1을 반환하고 errno에 에러번호 설정
> 

`execve`

- 해당 프로세스는 종료하고 새로운 프로세스 생성 및 실행한다
- 종료되기 때문에 자식프로세스를 fork()로 생성하고 자식프로세스에서 exec를 하는게 일반적이다
- 형식 : `int execve(const char *path, char *const argv[], char *const envp[])`
- 인자 :
    - path : 실행파일 경로
    - argv : main과 흡사, 마지막에 NULL 필요
    - envp : 환경변수 문자열 배열리스트("key=value"형태로 저장), 마지막에 NULL 필요

- 반환값 : 성공 시 반환하지 않음, 실패 시 -1

`wait`

- fork()를 호출한 프로세스의 중료를 기다리려면 wait()나 waitpid()를 사용
- 헤더 : `#include <sys/wait.h>`
- 형식 : `pid_t wait(int *status)`

> wait()는 자식 프로세스의 종료를 부모 프로세스에서 기다린다는 개념으로 간단하게 이해할 수 있다
> 
> 
> 자식 프로세스가 sleep 상태가 되면 부모프로세스가 먼저 종료되는데,
> 
> 이때 자식 프로세스의 ppid 가 1이 되면서 고아 프로세스가 된다
> 
> 이와같은 현상을 막는 것이 wait()이다
> 
> wait()를 통해 부모 프로세스는 자식 프로세스가 종료될 때까지 기다린다
> 
> 그렇다면 자식 프로세스를 기다리지 않아도 되는 상태에서는 wait 함수를 안써도 될까?
> 

<aside>
💡 자식 프로세스가 return 혹은 exit 를 통해 종료되면 wait의 반환 값은 자식 프로세스의 pid가 되고
그렇지 않고 자식 프로세스가 시그널에 의해 종료되면 errno가 EINTR로 설정되면서 -1을 반환한다
이 때 wait 함수의 인자로 받은 status는 자식 프로세스가 종료되면서 반환한 다양한 정보들을 기록하게 된다
자식 프로세스와 부모 프로세스의 메모리 공간이 별도로 유지되기 때문에 자식 프로세스가 종료되면서 넘긴 정보들을 부모 프로세스가 취하면서 자식 프로세스의 종료 시점에 기록된다
status에 기록되는 정보들은 종료 코드와 시그널이다
wait 함수를 호출하는 주된 목적은 자식 프로세스의 종료를 기다리는 것 뿐만 아니라
부모 프로세스에서 생성된 자식 프로세스를 수거하는 데 있다
fork 이후 부모 프로세스가 무한 루프를 돈다면 이를 강제 종료하더라도 자식 프로세스가 좀비 프로세스로  여전히 유지되는 것을 확인할 수 있다
따라서 부모 프로세스는 꼭 wait 함수를 호출하면서 자식 프로세스를 수거하여 프로세스 테이블에서 삭제할 의무가 있다

</aside>

```c

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pid;
	pid_t	ret;

	pid = fork();
	if (pid == -1)
		return (1);
	else if (!pid)
		printf("Child: I will be exited\n");
	else
	{
		printf("Parent: I have a Child which pid is %d\n", pid);
		ret = wait(NULL);
		printf("Parent: %d Child has been retrieved\n", ret);
		while (1)
			;
	}
	return (0);
}

```

`waitpid`

- fork()를 호출한 프로세스의 중료를 기다리려면 wait()나 waitpid()를 사용
- 헤더 : `#include <sys/wait.h>`
- 형식 : `pid_t waitpid(pid_t pid, int *status, int options)`
- waitpid()는 첫 번째 인자로 지정한 pid에 해당하는 프로세스가 끝나는 것을 기다린다

wait 함수와 달리 pid_t 타입으로 된 pid와 int 타입의 option을 추가적으로 인자로 사용하는 것을 볼 수 있다

waitpid의 기능 자체는 wait 함수와 동일하게, 정상적으로 자식 프로세스의 상태를 획득하고 자원을 수거, 반환한다

- wait 와의 차이점
    
    > 만약 부모 프로세스에서 fork를 통해 생성한 자식 프로세스가 1개가 아니라 여러 개라면, wait 함수를 이용했을 때 부모 프로세스의 Context는 임의의 자식 프로세스의 종료를 기다렸다가 수거하게 된다
    > 
    > 
    > 즉, 특정 pid를 가진 자식 프로세스에 대한 wait이 불가능하다
    > 
    > 따라서 특정 프로세스에 대해서 수행할 수 있도록 waitpid 함수에는 pid라는 인자를 받는다
    > 
    > waitpid의 pid로 -1이라는 값을 주게 되면, wait과 동일하게 동작하여 임의의 프로세스를 수거한다
    > 
    > 또한 waitpid 함수에서 특정 option을 통해 wait 함수에서 수행하지 못하는 기능들을 수행하도록 만들 수 있다
    > 
    > waitpid의 option으로 사용할 수 있는 값들로 WUNTRACED, WCONTINUED, WNOHANG 가 있다
    > 
    - WUNTRACED → STOP 시그널을 통해 실행을 멈춘 자식 프로세스의 status에 대해서 반환
    - WCONTINUED → CONT 시그널을 통해 실행을 재개한 자식 프로세스의 status에 대해서 반환
    - WNOHANG → 자식 프로세스의 종료를 기다리지 않고 즉시 자식 프로세스의 status에 대해서 반환

wait3

wait4

# 파일디스크립터 관련

`dup`

- fd를 활용하는 함수이다
- 헤더 : `#include <unistd.h>`
- 형식 : `int dup(int fd)`

dup 함수의 목적이 fd의 복제이므로 반환 값은 복제된 fd의 값이된다

문제가 발생하면, dup 함수는 -1이라는 값을 반환한다

dup 함수를 수행하게 되면 해당 File Table의 entry에서 f_count 값이 증가하는 방식으로 동작하는데

f_count의 값이 0이 되어야 File Table의 entry가 삭제될 수 있어

동일한 파일을 참조하는 인자로 넣은 파일 디스크립터와 반환 값으로 받은 파일 디스크립터 둘 모두

close 함수를 각각 호출해줘야 한다는 점에 유의해야 한다

`dup2`

- fd를 활용하는 함수이다
- 헤더 : `#include <unistd.h>`
- 형식 : `int dup(int fd, int fd2)`

dup2의 역할은 dup 함수와 동작 방식이 동일하다

인자로 넣은 fd를 복제하고 현재 사용하고 있지 않은 파일 디스크립터 중 가장 작은 값을 반환하는 것이 dup이었다면

dup2의 경우에는 반환 값이 사용자가 원하는 fd2라는 값이 나올 수 있도록 fd라는 인자를 사용하여 복제를 수행한다

문제가 생기지 않는다면 dup2의 반환 값은 fd2, 문제가 생긴다면 -1을 반환한다

만일 복제 과정에서 fd2가 기존에 이미 열려서 사용되고 있는 값이라면 이는 복제 과정에서의 오류로 처리하지 않고 기존의 파일 디스크립터를 close하여 File Table의 entry와 inode를 처리하여 File Table의 entry를 참조하고 있지 않은 상태의 파일 디스크립터로 만들어서 복제를 수행한다

dup2 함수는 주로 pipe 함수와 함께 많이 쓰이는데, pipe 함수에서 사용되는 파일 디스크립터를 표준 입력과 표준 출력을 참조하는 index가 복제할 수 있도록 주로 사용된다

`access`

- 헤더 : `#include <signal.h>`
- 형식 : `int access(const char *path, int mode)`
- path에 해당하는 파일을 mode에 따라서 확인한다
- path에는 일반 파일 외에 심볼릭 링크, 디렉토리 등을 포함하여 모든 파일을 인자로 사용할 수 있다
- mode는 <unistd.h> 에 매크로를 통해 값들이 정의되어있다

> 인자로 받은 mode에 만족하면 0을, 그렇지 않으면 -1을 반환한다
> 

mode를 통해서 파일의 존재 유무 및 파일의 권한을 확인할 수 있다

비트 마스킹을 활용하기 때문에 파일 존재 유무와 파일 실행 권한을 동시에 확인할 수도 있다

(mode = F_OK | X_OK);

cd, exit 와 같이 파일로 유지되는 명령어들은 exec 계열의 함수를 이용하여 

실행 전 access 함수를 통해 선행적으로 파일에 대한 검사를 수행할 수 있다

`unlink`

- 헤더 : `#include <unistd.h>`
- 형식 : `int unlink(const chart *path)`
- 파일을 삭제할 때 사용된다
- 정확하게는 하드 링크를 끊는데 이용된다

<aside>
💡 하드링크
일반적으로 말하는 파일은 실제로 디스크 상에 위치한 데이터에 불과하다
즉 파일을 생성, 삭제한다는 것은 디스크 상에서 데이터를 생성, 삭제한다는 것과 같은 말이다
유닉스 계열의 운영체제에서 파일이라고 불리는 이 데이터들은 inode 로 관리된다
사용자가 데이터를 실행하거나 읽고 쓰는 동작을 하고자 한다면
하드링크를 이용하여 inode 에 접근하고 원하는 작업을 수행하게 된다
즉, 일반적으로 사용자 공간에서 확인할 수 있는 파일들은 모두 하드링크이다
하드링크에 ln 명령어를 사용하면 하나의 파일이 추가적으로 생성되는데 inode 값은 동일하다

심볼릭링크
하드링크와 다르게 바로가기의 특성을 가진다
ln -s 명령어를 통해 생성되는데 하드링크와 동일하게 파일이 추가적으로 생성되지만 inode 값이 다르다
심볼릭링크로 생성된 파일은 어떤 하드링크를 참조하는 포인터 링크 이면서 하나의 하드링크이다

</aside>

위의 unlink를 통해 여러개의 하드링크 중 하나를 끊는데 이용한다

하드링크가 삭제될 뿐 파일은 여전히 존재한다

inode를 참조하는 모든 하드링크를 삭제해야 파일이 삭제된다

unlink 의 동작이 곧 사용자 공간에 존재하는 파일의 삭제와 동일하다

`kill`

- 쉘에서 프로세스를 죽이는 kill 명령과는 다르게 **프로세스에 시그널을 전송한다**
- 프로세스에 SIGKILL을 보내면 쉘 명령의 kill과 같은 역할을 한다
- 헤더 : `#include <signal.h>`
- 형식 : `int kill(pid_t pid, int sig)`
- 인자 :
    - pid_t pid : process id
    - int sig : 시그널 번호

> pid 에 sig 신호를 전송한다
> 

`signal`

- 시그널 처리를 설정한다
- 헤더 : `#include <signal.h>`
- 형식 : `void (*signal(int sig, void (*func)(int)))(int)`
- 인자 :
    - int sig : 시그널 번호
    - void (*func)(int) : 시그널을 처리할 핸들러
- 반환값 : void *()(int) 이전에 설정된 시그널 핸들러

> sig 신호가 오면 func 를 실행한다
> 

`sigaction`

*signal 함수와 유사한 sigaction*

sigaction은 signal 함수를 대체할 뿐만 아니라 훨씬 안정적

- signal 함수는 유닉스 계열의 운영체제 별로 동작 방식의 차이가 있음
- sigaction 함수는 차이가 없음

`sigemptyset`

sigaddset

# 폴더 관련

`getcwd`

- 현재 작업 디렉터리 이름을 얻는다 (절대 경로)
- 헤더 : `#include <unistd.h>`
- 형식 : `char *getcwd(char *buf, size_t size)`
- 인자 :
    - **char *buf** : 현재 경로가 담길 공간
    - **size_t size** : buf의 사이즈
- 반환값 : 성공 시 buf의 포인터, 실패 시 NULL

`chdir`

- 현재 작업 디렉터리를 변경한다
- 헤더 : `````````#include <direct.h>`````````
- 형식 : `int chdir(const char *path)`
- 인자 :
    - **const char *path**: 변경할  디렉토리 경로
- 반환값 : 성공 시 0, 실패 시 1

`opendir`

- 디렉토리를 연다
- 헤더 : `#include <direct.h>`
- 형식 : `DIR **opendir(const char* name)*`
- 인자 :
    - const char *name : 파일 경로
- 반환값 : 성공 시 열린 디렉터리 스트림 포인터, 실패 시 NULL

`readdir`

- 디렉토리를 읽는다
- 헤더 : `#include <direct.h>`
- 형식 :  `struct dirent *redder*(DIR *dirp)*`
- 인자 :
    - DIR *dirp : 디렉터리 스트림 포인터
- 반환값 : 성공 시 디렉터리 엔트리 포인터, 실패 시 NULL
    
    디렉터리 스트림의 끝에 도달해도 NULL
    
    - NULL을 리턴했는데 디렉토리 끝인지 에러인지를 구분하고 싶다면 호출전에 errno를 0으로 지우고 호출하면 디렉토리 끝으로 NULL을 리턴한 경우에는 errno값이 0으로 유지되므로 에러를 구분할 수 있다

cf) dirent 구조체에서 d_type과 d_name을 가지고 놀 것

- > dirent와 d_type같은 경우는 man dirent에서 확인할 것
- 순서대로 하나씩 dirent를 뱉으므로 NULL일 때까지 읽어주면 됨

`closedir`

- 디렉토리를 닫는다
- 헤더 : `#include <direct.h>`
- 형식 :  `int closedir*(DIR *dirp)*`
- 인자 :
    - DIR *dirp : 디렉터리 스트림 포인터
- 반환값 : 성공 시 0, 실패 시 -1

<aside>
💡 DIR

```
DIR * opendir (const char *dirname);
struct dirent * readdir (DIR *dirstream);
int closedir (DIR *dirstream);

struct dirent
{
	long		    d_ino;		
	unsigned short	d_reclen;	
	unsigned short	d_namlen;	/* Length of name in d_name. */
	char		    d_name[260]; /* [FILENAME_MAX] */ /* File name. */
};

typedef struct
{
	
	struct _finddata_t	dd_dta; /* disk transfer area for this dir */
	struct dirent		dd_dir;
	
	intptr_t		dd_handle;  /* _findnext handle */

	/*
	 * Status of search:
	 *   0 = not started yet (next entry to read is first entry)
	 *  -1 = off the end
	 *   positive = 0 based index of next entry
	 */
	int			dd_stat;

	char			dd_name[1];
} DIR;
```

</aside>

디렉터리 연관 라이브러리 함수들은 DIR 구조체를 사용한다

# 파일 관련

`stat`

`lstat`

`fstat`

- 파일의 정보를 읽어오는 함수
- 헤더 :
    - `#include <sys/types.h>`
    - `#include <sys/stat.h>`
    - `#include <unistd.h>`
- 호출 성공시 0을 반환하면서 두번째 인자인 stat 구조체에 파일 정보들로 채워진다
- 실패 혹은 error 시 -1을 리턴하고 errno 변수에 에러 상태가 setting

int stat(const char *path, struct stat * buf);

int lstat(const char *path, struct stat * buf);

- stat과 lstat함수는 첫번째 인자로, 절대경로를 넘겨주어야 하고, 두번째 인자로 stat구조체 주소를 넘겨 주어야 한다
- 차이점
    - lstat함수는 path가 심볼릭 링크 파일 경우, 심볼릭 링크 파일에 대한 정보를 구조제에 채운다
    - stat함수는  원본의 정보를 채운다

int fstat(int fd, struct stat * buf);

- 첫번째 인자로 파일 디스크립터 번호를 인자로 받고 stat와 동일한 기능을 수행한다
- 

`strerror`

- errono 를 정수 값이 아닌 메세지 형태로 뽑아준다
- 헤더 : `#include <errno.h>`
- 형식 :  `char *strerror(int errno)`
- 인자 :
    - int errno
- 반환값 : 정상적일 경우 메세지, 비정상적일 경우 unknown error message

errono 0은 에러가 없는 것을 뜻한다

strerror 보다 간편한 perror

`perror`

- 오류 메서지를 출력한다
- 헤더 : `#include <stdio.h>`
- 형식 : `void perror(const char* str)`
- 인자 :
    - const char *str : error message prefix

# readline 관련

`readline`

- str를 출력하고 프롬프트를 열어서 표준입력으로 문자열을 입력받는다
- 개행(엔터)를 받으면 지금까지 입력된 문자열을 리턴한다
- 형식 : `char *readline(const char str*)`
- `rl_replace_line`, `rl_redisplay` 등으로 프롬프트가 비워져도 계속 문자열을 받는 상태가 된다.

`rl_replace_line`

- 현재까지 입력된 프롬프트의 문자열을 str로 바꿔준다
- 형식 : `void rl_replace_line(const char str*, int)`
- ctrl + C 처럼 프롬프트를 입력하지는 않고 새로운 프롬프트를 출력해야 할 때 `rl_replace_line(””, 1)`처리를 해준다면 새로운 프롬프트를 비워줄 수 있게 된다

rl_on_new_line

- `rl_redisplay` 를 실행하기 위해 필요한 함수이다

rl_redisplay

- rl_replace_line를 출력하지 않으면 작동하지 않는다
- `readline` 함수의 인자로 넣은 문자열을 다시 출력한다
- 형식 : `void rl_redisplay(void)`
- 

rl_clear_history

**[뼈대 구현]**

```c
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int signum)
{
    if (signum != SIGINT)
        return;
    printf("ctrl + c\n");
    rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
}

int main(void)
{
    int ret;
    char *line;

    signal(SIGINT, handler);
    while (1)
    {
        line = readline("input> ");
        if (line)
        {
            if (ret)
                printf("output> %s\n", line);
            add_history(line);
            free(line);
            line = NULL;
        }
        else
        {
            printf("ctrl + d\n");
        }
    }
    return (0);
}
```

`add_history`

- 매개변수 char *str을 히스터리 목록에 넣는다
- 헤더 :
    - `#include <readline/readline.h>`
    - `#include <readline/history.`
- 형식 : `void add_history (char *str)`
- 이렇게 넣어진 문자열은 readline에서 방향키로 확인해볼 수 있다

왜이걸쓸끼?

# 터미널 관련

`isatty`

- fd에 해당하는 파일 디스크립터가 터미널에 연결되어 있는지 확인한다
- 헤더 : `#include <``unistd.h>`
- 형식 : `int isatty(int fd)`
- 이렇게 넣어진 문자열은 readline에서 방향키로 확인해볼 수 있다
- 반환값 : 연결되어 있다면 1, 없다면 0 리턴함녀서 errno 표시

`ttyname`

- fd에 연결된 터미널의 이름을 리턴한다
- 헤더 : `#include <``unistd.h>`
- 형식 : `char *ttyname(int fd)`
- 인자 :
    - fd : 확인할  fd
- 반환값 : 연결되어 있다면 터미널의 이름을 리턴, 없다면 NULL 리턴함녀서 errno 표시

`ttyslot`

- /etc/ttys파일에 있는 항목 중 호출 프로세스에서 사용중인 터미널의 인덱스를 반환하며, 일반적으로 이 값은 /etc/파일에 있는 현재 사용자에 대한 항목의 인덱스와 동일하다
- 헤더 : `#include <``unistd.h>`
- 형식 : `int ttyslot(void)`
- 반환값 : 사용중인 터미널의 인덱스를 리턴, 없다면 0

`tcgetattr`

- 현재 터미널의 속성을 받아온다
- 헤더 : `#include <termios.h>`
- 형식 : `int tcgetattr(int fildes, struct termios *termios_p)`
- 인자 :
    - fildes : 속성을 받아올 터미널
    - termios_p : 터미널의 속성이 저장될 구조체
- 반환값 : 성공 시 0, 실패 시 -1

```c
struct termios {
	tcflag_t        c_iflag;        /* input flags */
	tcflag_t        c_oflag;        /* output flags */
	tcflag_t        c_cflag;        /* control flags */
	tcflag_t        c_lflag;        /* local flags */
	cc_t            c_cc[NCCS];     /* control chars */
	speed_t         c_ispeed;       /* input speed */
	speed_t         c_ospeed;       /* output speed */
};
```

`tcsetattr`

- fildes에 해당하는 터미널의 설정을 변경할 수 있다
- 헤더 : `#include <termios.h>`
- 형식 : `int tcsetattr(int fildes, int optional_actions, const struct termios *termios_p)`
- 인자 :
    - fildes : 설정을 변경할 터미널
    - optional_actions : 변경될 터미널의 설정이 언제 적용될지 설정할 수 있음
        - TCSANOW : 즉시 적용
        - TCSADRAIN : fildes에 관한 모든 출력이 이루어진 뒤 동작
        - TCSAFLUSH : fildes에 관한 모든 출력 및 입력이 이루어진 뒤 동작
    - termios_p : 터미널의 속성이 들어있는 구조체
- 반환값 : 성공 시 0, 실패 시 -1

`tgetent`

- name에 대한 항목을 가져온다
- 헤더 : `#include <term.h>`
- 형식 : `int tgetent(char *bp, const char *name)`
- 반환값 : 성공 시 1, 해당 항목이 없는 경우 0, terminfo 데이터베이스를 찾을 수 없는 경우 -1

`tgetflag`

- id가 사용 가능한지 알려준다
- 헤더 : `#include <term.h>`
- 형식 : `int tgetflag(char *id)`
- 반환값 : 사용가능하면 1, 아니면 0을 리턴한다

`tgetnum`

- tgetflag와 동일한 역할을 수행한다
- 헤더 : `#include <term.h>`
- 형식 : `int tgetnum(char *id)`
- 반환값 : 사용이 불가능하면 -1을 리턴한다

`tgetstr`

- tgetflag 와 동일한 역할을 수행하지만 해당 내용을 문자열로 출력하고 area 에도 저장한다
- 헤더 : `#include <term.h>`
- 형식 : `char *tgetstr(char *id, char **area)`
- 반환값 : 실패 시 NULL 을 리턴한다

tgoto

- 현재 터미널의 속성을 받아온다
- 헤더 : `#include <term.h>`
- 형식 : `char *tgoto(const char *cap, int col, int row)`
- 반환값 : 출력할 문자열을 리턴한다

tputs

- 패딩 인포메이션을 str에 적용한다
- 헤더 : `#include <term.h>`
- 형식 :  `int tputs(const char *str, int affcnt, int (*putc)(int))`
- 반환값 :  str이 NULL이면 에러를 반환한다

# 환경변수 관련

`getenv`

- name에 해당하는 환경변수를 찾은 뒤 해당 환경변수의 값을 리턴해온다
- 헤더 : `#include <stdlib.h>`
- 형식 : `char *getenv(const char *name)`
- 인자 :
    - 찾고싶은 환경변수 명
- 반환값 : name에 해당하는 환경변수의 값을 리턴, 만약 찾지 못 한다면 NULL을 리턴

# 제어 관련

`ioctl`

- 하드웨어의 제어나 정보를 얻기위해서 사용된다
- 헤더 : `#include <sys/ioctl.h>`
- 형식 : `int ioctl(int fd, unsigned long request, ...)`
- 인자 :
    - fd : open 한 디바이스 드라이버의 fd값
    - request : 디바이스에 전달할 값
    - … :
- 반환값 : 성공 시 0, 실패 시 -1이 리턴되고 errno가 설정
