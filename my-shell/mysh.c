
/*
 * Author: Anthony
 * 
 * mysh.c
 *
 */



#include <fcntl.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define COLOR_CYAN  "\x1b[36m"
#define COLOR_RESET "\x1b[0m"
#define INPUT_SIZE 4096

void get_user(char **user);
void shell();
void process(char *input);
int  execute(char *cmd[], int in, int out, bool piped); 
void print_cmd(char *args[]);

int main(int argc, char **argv) {
  shell();
  return 0;
}

/*
 * @user - reference to (char *)
 * allows to get owner of process
 */
void get_user(char **user) {
  uid_t uid = getuid();
  struct passwd *pwd;
  if((pwd = getpwuid(uid)) != NULL) {
    *user = (pwd->pw_name);
  }
}

/*
 * shell will prompt for/accept input at stdin and
 * process that input
 */
void shell() {
  char *user = "user";
  get_user(&user);
  while(1) {
    printf(COLOR_CYAN "[%s]$: " COLOR_RESET, user);
    char input[INPUT_SIZE];
    if(fgets(input, INPUT_SIZE, stdin) == NULL) {
      break;
    }
    if(strcmp(input, "exit\n") == 0) {
      break;
    } else {
      process(input);
    }
  }
  printf("User has exited the shell\n");
}

/*
 * @input - raw input that is
 * taken from fgets
 *
 * While tokenizing the input, determing if a given
 * token is an I/O redirection or if it is a pipe,
 * if so execute that command and set file descriptors
 * appropriately.
 *
 * In the case of piping save the result of the call
 * to execute. 
 */
void process(char *input) {
  int nwait = 0; // children to wait on

  int in = 0; 
  int out = 1;

  int i = 0; 
  char *cmd[11];
  cmd[i] = strtok(input, " \n");
  while(cmd[i] != NULL) {
    //check redirect output truncate
    if(strcmp(cmd[i], ">") == 0) {
      ++i;
      cmd[i] = strtok(NULL, " \n");
      if((out = open(cmd[i], O_RDWR | O_TRUNC | O_CREAT, 0666)) == -1) {
        perror("open truncate while parsing input");
        return;
      }
      // replace the > and file name with NULL
      // in the command list
      cmd[i-1] = NULL; 
      cmd[i] = NULL; 
      execute(cmd, in, out, false);
      nwait+=1;
      memset(cmd, 0, i+1);
      i = -1;
    }
    //check redirect output append
    else if(strcmp(cmd[i], ">>") == 0) {
      ++i;
      cmd[i] = strtok(NULL, " \n");
      if((out = open(cmd[i], O_RDWR | O_APPEND, 0666)) == -1) {
        perror("open append while parsing input");
        return;
      }
      // replace the >> and file name with NULL
      // in the command list
      cmd[i-1] = NULL; 
      cmd[i] = NULL; 
      execute(cmd, in, out, false);
      nwait += 1;
      memset(cmd, 0, i+1);
      i = -1;
    }
    //check input redirection and exec
    else if(strcmp(cmd[i], "<") == 0) {
      ++i;
      cmd[i] = strtok(NULL, " \n");
      if((in = open(cmd[i], O_RDONLY, 0666)) == -1) {
        perror("open read only while parsing input");
        return;
      }
      // replace the < and file name with NULL
      // in the command list
      cmd[i-1] = NULL;  
      cmd[i] = NULL;
      execute(cmd, in, out, false);
      nwait += 1;
      memset(cmd, 0, i+1);
      i = -1;
    } 
    //check for pipe, if one exists then exec!
    else if(strcmp(cmd[i], "|") == 0) {
      cmd[i] = NULL;
      if((in = execute(cmd, in, out, true))== -1) {
        perror("error execute pipe");
        return;
      }
      nwait += 1;
      memset(cmd, 0, i+1);
      i = -1; // i will be incremented in the subsequent step
    }
    // 
    ++i;
    cmd[i] = strtok(NULL, " \n");
  }
  //if all args have been executed then
  if(cmd[0] != NULL) {
    execute(cmd, in, out, false);
    nwait += 1;
  }
  while(nwait > 0) {
    if(wait(NULL) == -1) {
      break;
    }
    --nwait;
  }
}

/*
 * @cmd - the array of commands
 * @in - the read file descriptor
 * @out - the write file descriptor
 * 
 * Each time a call is made to the execute function th
 * if there will be an input and output file descriptor
 * that will be passed based on previous calls to the execute command
 */
int execute(char *cmd[], int in, int out, bool piped) {
  // before executing check if there is anything to execute
  if(cmd == NULL) {return 0;}
  int pipefd[2];
  if(pipe(pipefd) == -1) {
    perror("execute: pipe");
    return -1;
  }
  pid_t child_pid;
  if((child_pid = fork()) == -1) {
    printf("execute: fork");
    return -1;
  }
  if(child_pid == 0) {

    if(piped) {
      if(dup2(pipefd[1], 1) == -1) {
        perror("execute: dup2 write end pipe -- child");
        return -1;
      }
      if(close(pipefd[1]) == -1) {
        perror("execute: close write end pip -- child");
        return -1;
      }
    }

    // true when @cmd
    // has input redirection
    if(in != 0) {
      if(dup2(in, 0) == -1) {
        perror("execute: dup2 input redirection");
        return -1;
      }
      if(close(in) == -1) {
        perror("execute: close in filedes -- child");
        return -1;
      }
    }

    // true when @cmd
    // has output redirection
    if(out != 1) {
      if(dup2(out, 1) == -1) {
        perror("execute: dup2 output redirection");
        return -1;
      }
      if(close(out) == -1) {
        perror("execute: close out filedes -- child");
        return -1;
      }
    }

    // close the read end of pipe
    if(close(pipefd[0]) == -1) {
      perror("execute: close read end pipe -- child");
      return -1;
    }

    if((execvp(cmd[0], cmd)) == -1) {
      perror("execute: exec");
      return -1;
    }
    printf("bash: %s: command not found\n", cmd[0]);
  } else {
    if(close(pipefd[1]) == -1) {
      perror("execute: close write end pipe -- parent");
      return -1;
    }
  }
  return piped ? pipefd[0] : out;
}


/*
 * Used for debugging purposes 
 */
void print_cmd(char *args[]) {
  for(int i = 0; args[i] != NULL; ++i) {
    printf("print command: %s\n", args[i]);
  }
}
