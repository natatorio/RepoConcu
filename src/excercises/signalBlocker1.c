#include <stdio.h>
#include <stdlib.h> 
#include <signal.h>
#include <unistd.h>
       #include <sys/types.h>
       #include <sys/wait.h>

void handle_signal(int signal){
	printf("Handler executado.\n");	
}

int main() {
    struct sigaction sa;

    // Print pid, so that we can send signals from other shells
    		printf("My pid is: %d\n", getpid());


    // Block every signal during the handler
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	//sigprocmask(0, &sa.sa_mask, NULL);
	sa.sa_handler = &handle_signal;
	pid_t id = fork();
	if(id == 0){
		printf("My pid, hijoo is: %d\n", getpid());
		char *argv[3] = {"Command-line", ".", NULL};
		execve("execForSigBlock",argv, NULL);
	}else{
		wait(NULL);
	}
	return 0;
}