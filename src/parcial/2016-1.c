/*
Escribir un programa en C o C++ que reciba por parámetro la cantidad de procesos a
crear. El programa debe lanzar esos procesos, cada proceso duerme un número aleatorio
de segundos entre 1 y 100, una vez que despiertan todos los procesos, cada uno imprime
su pid y termina.
Utilizar únicamente semáforos.
*/

#define MAX_SLEEPTIME 3

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
};

int main(int argc, char* argv[]){
  if(argc != 2){
    printf("Usage: ./2016-1 {n_procs}");
    return 0;
  }
  int n_procs = atoi(argv[1]);
  key_t semKey = ftok("2016-1.c", 0);
  int semId = semget(semKey, 1, 0644 | IPC_CREAT);
  union semun su;
  memset(&su, 0, sizeof(union semun));
  su.val = n_procs;
  semctl(semId, 0, SETVAL, su);
  struct sembuf sop;
  sop.sem_num = 0;
  sop.sem_flg = 0;
  for(int i = 0; i != n_procs; i++){
    if(!fork()){
      srand(getpid());
      int sleepTime = 1 + (rand() % MAX_SLEEPTIME);
      sleep(sleepTime);
      sop.sem_op = -1;
      semop(semId, &sop, 1);
      sop.sem_op = 0;
      semop(semId, &sop, 1);
      printf("Mi pid es: %i. Dormí %i segundos.\n", (int)getpid(), sleepTime);
      exit(0);
    }
  }
  while(wait(NULL) > 0);
  semctl(semId, 0, IPC_RMID);
  return 0;
}
