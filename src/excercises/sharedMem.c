//escribir un programa que reciba la cantidad de procesos hijos que debe crear, cada proceso hijo debe dormir un numero aleatorio de segundos entre 0 y 30. 
//el proceso padre debe esperar la terminacion de cada uno de los hijos, a medida que los hijos van terminando el padre presentará en pantalla el pid de cada hijo y
//la cantidad de segundos que durmió.

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

long int rndom(){
	srand(getpid());
	long int result = rand()%5;
	return result;
}

int main(int argc, char* argv[]){
	int n_proc =atoi(argv[1]);
	key_t key = ftok("/bin/bash", 12);
	int mid = shmget(key, 1000, IPC_CREAT|0777);
	for(int i=0;i<n_proc;i++){
		pid_t id = fork();
		if (id == 0){
			void* shm = shmat(mid, NULL, 0);
			int time = (int)rndom();
			sleep(time);
			*(int*)shm = time;
			shmdt(shm);
			exit(time);
		}
	}
	void* shm = shmat(mid, NULL, 0);
	if(mid == -1) return -1;
	for(int i=0;i<n_proc;i++){
		int status = 0;
		pid_t pid = wait(&status);
		int durmio = *(int*)shm;
	//	printf("El hijo %d durmió %d segundos\n",pid,WEXITSTATUS(status));
		printf("El hijo %d durmió %d segundos\n",pid,durmio);
	}
	shmdt(shm);
	shmctl(mid,IPC_RMID ,NULL);
	return 0;
}