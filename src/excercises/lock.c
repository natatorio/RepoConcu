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
	int fd = open("archivoLock.txt", O_CREAT | O_RDWR | O_TRUNC);
	ssize_t writen_bytes = 0;
	while(writen_bytes < sizeof(int)){
	writen_bytes += write(fd, &cero + writen_bytes, sizeof(int) - writen_bytes);
	}
	pid_t pid = fork();
	for(int i = 0; i!=10000; i++){
		writen_bytes = 0;
		lock.l_type = F_WRLCK;
		fcntl(fd, F_SETLK, lock);
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
		fcntl(fd, F_SETLK, lock);
		if(i%2000 == 0){
			if(!pid) printf("Soy el padre y escribí: %d\n", num);
			else printf("Soy el hijo y escribí: %d\n", num);
		}
	}
	close(fd);
	if(!pid){
		wait(NULL);
		printf("El número final es: %d\n", num);
	}
	return 0;
}