/*
1) Explicar que es un lock en un ambiente UNIX-Linux
Un lock es un mecanismo de sincronismo que funciona sobre archivos (en realidad cada lock se toma sobre una porcion de un archivo).
Los distintos procesos pueden solicitar un mismo lock (sobre la misma porción del mismo archivo) liberarlo y consultar si
está tomado. Por defecto los locks tienen un comportamiento bloqueante, es decir, si un proceso solicita un lock que está tomado
el proceso se bloquea hasta que el lock se libere y pueda tomarlo. De está manera se puede sincronizar la ejecución de
distintos procesos, lo que los procesos hagan mientras tengan el lock puede ser cualquier cosa no necesariamente debe ser
trabajar sobre la porción del archivo sobre el cual se aplica el lock.

2) Indicar cuales son las diferencias entre un lock exclusivo y un lock compartido.
La explicación del punto anterior está centrada en los locks exlusivos que son los más usados.
La diferencia fundamental entre los exclusivos y los compartidos es que un lock exclusivo solo puede tomarse si no hay
ningún otro lock tomado sobre la porción del archivo a lockear, mientras que un lock compartido puede tomarse aunque
haya otros locks compartidos tomados sobre la porción del archivo a lockear. Tambien se les llaman locks de ESCRITURA
a los exclusivos y de LECTURA a los compartidos ya que no hay conflicto en acceder a un recurso sin modificarlo de a
varios a la vez (LECTURA) mientras que si hay conflicto al modificarlo de a varios a la vez (ESCRITURA).

3) Mostrar como se puede crear y destruir un lock en ambiente Unix.
*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(){
  struct flock lock;
  lock.l_type = F_RDLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = 0;
  lock.l_len = 0;
  int fd = open("2017-1.c", O_RDONLY);
  if(fd < 0) printf("Error abriendo el archivo\n");
  pid_t pid = fork();
  fcntl(fd, F_SETLKW, &lock);
  if(pid){
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    lock.l_type = F_WRLCK;
    while(lock.l_type != F_UNLCK) fcntl(fd, F_GETLK, &lock);
    printf("Soy el padre\n");
  }else{
    printf("Soy el hijo\n");
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
  }
  close(fd);
  return 0;
}
