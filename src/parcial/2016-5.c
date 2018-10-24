/*
Se posee un archivo binario de registros de barcos piratas, donde cada registro está
representado por la siguiente estructura:
struct barco_pirata {
  char nombre[20];
  int peligrosidad;
  ...
};
Definir las siguientes funciones:

establecer_lock_escritura​(char* nombre_archivo, int numero_registro);
establecer_lock_lectura​(char* nombre_archivo, int numero_registro);
liberar_lock​(char* nombre_archivo, int numero_registro);

Los números de registro inician en 1. Es decir el primer registro tiene número de registro 1,
el segundo tiene número de registro 2, y así sucesivamente.
*/
#define REG_SIZE 24

#include <unistd.h>
#include <fcntl.h>

void establecer_lock_escritura​(char* nombre_archivo, int numero_registro){
  int fd = open(nombre_archivo, O_RDWR);
  struct flock lock;
  lock.l_type = F_WRLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = (numero_registro - 1) * REG_SIZE;
  lock.l_len = REG_SIZE;
  fcntl(fd, F_SETLKW, &lock);
  close(fd);
}

void establecer_lock_lectura​(char* nombre_archivo, int numero_registro){
  int fd = open(nombre_archivo, O_RDWR);
  struct flock lock;
  lock.l_type = F_RDLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = (numero_registro - 1) * REG_SIZE;
  lock.l_len = REG_SIZE;
  fcntl(fd, F_SETLKW, &lock);
  close(fd);
}

void liberar_lock​(char* nombre_archivo, int numero_registro){
  int fd = open(nombre_archivo, O_RDWR);
  struct flock lock;
  lock.l_type = F_UNLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = (numero_registro - 1) * REG_SIZE;
  lock.l_len = REG_SIZE;
  fcntl(fd, F_SETLK, &lock);
  close(fd);
}
