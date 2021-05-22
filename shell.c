#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>

#define MAX_LEN_LINE    100
#define LEN_HOSTNAME	30

int main(void)
{
    char command[MAX_LEN_LINE];
    char *arg;
    char *args[] = {command, arg, NULL};
    int ret, status;
    pid_t pid, cpid;
  
    char hostname[LEN_HOSTNAME + 1];
    memset(hostname, 0x00, sizeof(hostname));
    gethostname(hostname, LEN_HOSTNAME);
    
    while (true) {
        char *s;
        int len;
        
        char pwd[100];
        getcwd(pwd, 100);

        printf("\033[92;1m%s@%s\033[0m:\033[94;1m%s\033[0m$ ",getpwuid(getuid())->pw_name,hostname,pwd);
        
        s = fgets(command, MAX_LEN_LINE, stdin);            
        
        if (s == NULL) {
            fprintf(stderr, "fgets failed\n");
            exit(1);
        }
        
        
        len = strlen(command);
        if (command[len - 1] == '\n') {
            command[len - 1] = '\0'; 
        }
        
        arg = strtok(command, " ");
        
        if (strcmp(arg, "cd") == 0){ // cd
            arg = strtok(NULL, " ");
            if (chdir(arg) != 0){
                printf("Can't Change Directory\n");
                continue;
            }
            else continue;
        }
                        
        else if (strcmp(arg, "exit") == 0){ // exit
            printf("Exit Shell\n");
            exit(0);
        }

        pid = fork();
        
        if (pid < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } 
        if (pid != 0) {  /* parent */
            cpid = waitpid(pid, &status, 0);
            if (cpid != pid) {
                fprintf(stderr, "waitpid failed\n");        
            }
            printf("Child process terminated\n");
            if (WIFEXITED(status)) {
                printf("Exit status is %d\n", WEXITSTATUS(status)); 
            }
        }
        else {  /* child */	    
            if (strcmp(arg, "ls") == 0){  // ls
                arg = strtok(NULL, " ");
                args[0] = "/bin/ls";
                args[1] = arg;
            }	    
	    	else if (strcmp(arg, "pwd") == 0){ // pwd
	    		args[0] = "/bin/pwd";
	    		args[1] = NULL;
	    	}
	    	else if (strcmp(arg, "date") == 0){ // date
	    		args[0] = "/bin/date";
	    		args[1] = NULL;
	    	}
	    	else if (strcmp(arg, "echo") == 0){ // echo
	    	    arg = strtok(NULL, " ");
	    	    args[0] = "/bin/echo";
	    	    args[1] = arg;
	    	}
	    	else if (strcmp(arg, "vi") == 0){ // vi
	    	    arg = strtok(NULL, " ");
	    	    args[0] = "/usr/bin/vi";
	    	    args[1] = arg;
	    	}    	
	    	else if (strcmp(arg, "cat") == 0){ // cat
	    	    arg = strtok(NULL, " ");
	    	    args[0] = "/bin/cat";
	    	    args[1] = arg;
	    	} 
	    	
	    	ret = execve(args[0], args, NULL);
	    	if (strcmp(arg, "clear") == 0){ // clear
	    	    system("clear");
	    	    ret = 0;
	    	}
	    	
	    	if (ret < 0) {
	    	    fprintf(stderr, "execve failed\n");   
	            return 1;
            	}
        }
    }
    return 0;
}
