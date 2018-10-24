#define M 100
#define N 15
#define MAX_NUM 5

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <string.h>


union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
};

int main(){
  key_t key = ftok("2017-4.c", 0);
  key_t key2 = ftok("2017-4.c", 1);
  int shmId = shmget(key, N * sizeof(int), 0644 | IPC_CREAT);
  int semConsId = semget(key, 1, 0644 | IPC_CREAT);
  int semProdId = semget(key2, 1, 0644 | IPC_CREAT);
  union semun su;
  memset(&su, 0, sizeof(union semun));
  semctl(semConsId, 0, SETVAL, su);
  memset(&su, 0, sizeof(union semun));
  su.val = N;
  semctl(semProdId, 0, SETVAL, su);
  pid_t pid = fork();
  int pos = 0;
  void* shMem = shmat(shmId, NULL, 0);
  struct sembuf sop;
  sop.sem_num = 0;
  sop.sem_flg = 0;
  if(pid){
    int sum = 0;
    for(int i = 0; i != M; i++){
      sop.sem_op = -1;
      semop(semConsId, &sop, 1);
      sum += ((int*)shMem)[pos * sizeof(int)];
      pos = (pos + 1) % N;
      sop.sem_op = 1;
      semop(semProdId, &sop, 1);
    }
    printf("La suma total es: %i\n", sum);
    shmdt(shMem);
    exit(0);
  }
  srand(getpid());
  for(int i = 0; i != M; i++){
    sop.sem_op = -1;
    semop(semProdId, &sop, 1);
    int num = rand() % MAX_NUM;
    printf("Insertado %i\n", num);
    ((int*)shMem)[pos * sizeof(int)] = num;
    pos = (pos + 1) % N;
    sop.sem_op = 1;
    semop(semConsId, &sop, 1);
  }
  shmdt(shMem);
  wait(NULL);
  shmctl(shmId, IPC_RMID, NULL);
  semctl(semConsId, 0, IPC_RMID);
  semctl(semProdId, 0, IPC_RMID);
  return 0;
}
