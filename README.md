# 42Minishell

Mong-Shell Reference Manual

    ██╗   ██╗████████╗██╗   ██╗████████╗  ████████╗██╗   ██╗████████╗██╗      ██╗        
    ███╗ ███║██╔═══██║███╗  ██║██╔═════╝  ██╔═════╝██║   ██║██╔═════╝██║      ██║        
    ██╔██╗██║██║   ██║██╔██╗██║██║ ████╗  ████████╗████████║██████╗  ██║      ██║        
    ██║╚═╝██║██║   ██║██║╚═███║██║ ╚═██║  ╚═════██║██╔═══██║██╔═══╝  ██║      ██║        
    ██║   ██║████████║██║  ╚██║████████║  ████████║██║   ██║████████╗████████╗████████╗  
    ╚═╝   ╚═╝╚═══════╝╚═╝   ╚═╝╚═══════╝  ╚═══════╝╚═╝   ╚═╝╚═══════╝╚═══════╝╚═══════╝
    
    M O N G S H E L L $

This project is about creating a simple shell.

learn: a lot about processes and file descriptors.

<img src="https://github.com/ejaee/42Minishell/assets/87407504/6530b56e-08e2-418a-865f-edf4b64203bf">


### Install

```
$ git clone https://github.com/ejaee/42Minishell
```

### Usage

```
$ ./minishell
```

# Mong-Shell Features

### **Base version**

- GNU bash, version 3.2.57

#  **Quote**

- "command"

    $bash-shell: [Run] command
    
    $mong-shell: [Run] command

- "'command'"

    $bash-shell: [Error] bash: 'command': command not found
    
    $mong-shell: [Error] mong: 'command': command not found

- '"command"'

    $bash-shell: [Error] bash: "command": command not found
    
    $mong-shell: [Error] mong: "command": command not found


- ""'command'""

    $bash-shell: [Run] command 
    
    $mong-shell: [Error] mong: 'command': command not found

- ''"command"''

    $bash-shell: [Run] command 
    
    $mong-shell: [Error] mong: "command": command not found

- """'command'"""

    $bash-shell: [Error] bash: 'command': command not found
    
    $mong-shell: [Error] mong: 'command': command not found

- "command

    $bash-shell: [Pause] >
    
    $mong-shell: [Error] fail: Wrong input(quote)

- "'command"'

    $bash-shell: [Pause] >
    
    $mong-shell: [Error] fail: Wrong input(quote)


## **env($) echo by Quote**

- echo "$key"

    $bash-shell: [env] $value
    
    $mong-shell: [env] $value

- echo '$key'

    $bash-shell: [String] $key
    
    $mong-shell: [String] $key

- echo "'$key'"

    $bash-shell: [env] '$value'
    
    $mong-shell: [env] '$value'

- echo '"$key"'

    $bash-shell: [String] "$key"
    
    $mong-shell: [String] "$key"

- echo '"$key"'

    $bash-shell: [env] '$value'
    
    $mong-shell: [env] '$value'  

- echo "'"$key"'"

    $bash-shell: [env] '$value'
    $mong-shell: [env] '$value'  

- echo ""'"$key"'""

    $bash-shell: [String] "$key"
    
    $mong-shell: [env] '$value'  

## **Quote Logic**

when first 'quote char' find, saved to config.arr and erase another quote char in buf.

when echo run, config.arr's value is the criterion for print enf.

when quote not enough, mong-shell don't wait for input.

print message "fail: Wrong input(quote)" and get input again.

# **Built-in**

Mong shell must implement the following builtins:

- `echo` with option -n
- `cd` with only a relative or absolute path ◦ pwd with no options
- `export` with no options
- `unset` with no options
- `env` with no options or arguments
- `exit` with no options

# Document

- [Allowance function theorem)][] - private
- [bash reference](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html)
