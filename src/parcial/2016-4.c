//Describa todas las consideraciones a tener, durante la implemntación de un signal handler.

/*
Hay que tener en cuenta cuando puede ser llamada la función, por defecto puede ser llamada en cualquier
momento, si se bloquea y desbloquea la señal a la que se le asoció el handler solo podrá ser llamado mientras la señal
está desbloqueada. Hay que tener en cuenta que si se recibe una señal estando bloqueda se ejecutará el handler al
ser desbloqueada. También hay que considerar que señales puede recibir el procesos durante la ejecución del handler, es
decir si el handler puede ser interrumpido.
*/
