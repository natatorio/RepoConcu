//lanzar 2 procesos : leer un número de archivo (empieza en 0), incrementar en 1 y escribirlo incrementado (repetir 10000 veces cada proceso)

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

int main(){
	struct flock lock;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	const int cero = 0;
	int num = 0;
	int fd = open("archivoLock.txt", O_RDWR | O_CREAT | O_TRUNC);
	ssize_t writen_bytes = 0;
	while(writen_bytes < sizeof(int)){
	writen_bytes += write(fd, &cero + writen_bytes, sizeof(int) - writen_bytes);
	}
	fork();
	for(int i = 0; i!=10000; i++){
		writen_bytes = 0;
		lock.l_type = F_WRLCK;
		fcntl(fd, F_SETLKW, &lock);
		lseek(fd ,0 , SEEK_SET);
		while(writen_bytes < sizeof(int)){
		writen_bytes += read(fd, &num + writen_bytes, sizeof(int) - writen_bytes);
		}
		num++;
		writen_bytes = 0;
		lseek(fd ,0 , SEEK_SET);
		while(writen_bytes < sizeof(int)){
		writen_bytes += write(fd, &num + writen_bytes, sizeof(int) - writen_bytes);
		}
		lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);
	}
	close(fd);
	wait(NULL);
	printf("%d\n",num);
	unlink("archivoLock.txt");
	return 0;
}
