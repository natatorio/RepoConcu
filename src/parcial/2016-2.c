//Describir todas las operaciones que realiza el kernel al crear un proceso.

/*
Reserva una entrada en la tabla de procesos.
Le asigna un process id
Realiza una copia del contexto del proceso padre (copía el addres space, los valores de los registros, la tabla
de archivos abiertos, las señales bloqueadas, directorio actual y raíz, valor de nice o prioridad, etc)
Retorna a la llamada de fork() un 0 al proceso nuevo y el process id del hijo al proceso padre (invocante)

*/
