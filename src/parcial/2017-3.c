/*
Describa los pasos que realiza el kernel durante las syscalls exit(), wait() y waitpid()

exit(status):
Cierra los archivos abiertos del proceso.
A los hijos del proceso, si tiene, se les asigna el proceso init como padre.
Se envía la señal SIGCHLD al proceso padre del proceso invocante.
Se devuelve status al padre que puede obtenerlo mediante wait().

wait(&status):
Se bloquea el proceso.
Se observa un cambio en el estado de algún proceso hijo (recibió señal de stop/continue o terminó).
Si el proceso hijo terminó se liberan los recursos asociados al proceso hijo.
Se desbloquea el proceso.

waitpid():
Es lo mismo pero se pueden agregar restricciones acerca de que proceso esperar.
Además permite agregar opciones como por ejemplo hacer la llamada no bloqueante.

*/
