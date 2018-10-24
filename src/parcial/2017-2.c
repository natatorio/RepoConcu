#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(){
  mknod("12", S_IFIFO | 0666, 0);
  mknod("31", S_IFIFO | 0666, 0);
  pid_t pid2 = fork();
  if(!pid2){
    mknod("23", S_IFIFO | 0666, 0);
    pid_t pid3 = fork();
    if(!pid3){
      int fd23 = open("23", O_RDONLY);
      int fd31 = open("31", O_WRONLY);
      char r;
      for(int i = 0; i != 10; i++){
        read(fd23, &r, sizeof(char));
        write(fd31, &r, sizeof(char));
      }
      close(fd23);
      close(fd31);
      unlink("23");
    }else{
      int fd23 = open("23", O_WRONLY);
      int fd12 = open("12", O_RDONLY);
      char r;
      for(int i = 0; i != 10; i++){
        read(fd12, &r, sizeof(char));
        write(fd23, &r, sizeof(char));
      }
      close(fd12);
      close(fd23);
    }
  }else{
    int fd12 = open("12", O_WRONLY);
    int fd31 = open("31", O_RDONLY);
    const char a = 'A';
    char r;
    for(char i = a; i != a + 10; i++){
      write(fd12, &i, sizeof(char));
      read(fd31, &r, sizeof(char));
      printf("Envié %c Leí: %c\n", i, r);
    }
    close(fd12);
    close(fd31);
    unlink("12");
    unlink("31");
  }
  return 0;
}
//Nada, los procesos están relacionados entre si por lo tanto podrían compartir pipes
