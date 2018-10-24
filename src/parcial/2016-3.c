/*
Ejercicio de Pipes y Fifos
1. Describir las diferencias entre pipes y fifos.
2. Describir todas las system calls utilizadas para operar con fifos.
3. Utilizando las system calls definidas en el punto anterior, escribir un fragmento de
código que muestre su utilización para escribir en un fifo.

1)  La diferencia fundamental entre pipes y fifos es que estos últimos tienen un archivo asociado (nombre)
lo que significa que puede ser utilizado por cualquier proceso que conozca su nombre. Mientras que los pipes
solo pueden ser utilizados por el procesos invocante, es decir el proceso que lo creó, y por sus descendientes.
El ciclo de vida de un pipe termina cuando todos los procesos o bien cierran los file descriptors asociados a él
o bien terminan. Mientras que el de un fifo termina recién cuando se elimina el archivo, esto quiere decir
que puede sobrevivir aunque todos los procesos hayan cerrado el archivo u hayan terminado.

2)  mknod(const char *pathname, mode_t mode, dev_t dev):
Se utiliza para crear un fifo (también se pueden crear otras cosas...) modo => S_IFIFO
open():
Se utiliza para abrir el archivo fifo, devuelve un file descriptor
read()/write():
Se utilizan para ecribir y leer del archivo fifo
close():
Se utiliza para cerrar el archivo fifo
unlink():
Se utiliza para destruir el archivo fifo
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
  mknod("fifo", 0666 | S_IFIFO, 0);
  int fd;
  const char* str = "PUTO";
  if(fork()){
    fd = open("fifo", O_WRONLY);
    write(fd, str, sizeof(str));
    close(fd);
    exit(0);
  }
  fd = open("fifo", O_RDONLY);
  char msg[100];
  read(fd, &msg, sizeof(str));
  printf("%s\n", msg);
  close(fd);
  unlink("fifo");
  return 0;
}
