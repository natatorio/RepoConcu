#ifdef EJEMPLO_2

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

using namespace std;

unsigned int calcularRandom ();


int main () {

	pid_t id = fork ();

	if ( id == 0 ) {

		unsigned int tiempoAdormir = calcularRandom ();
		cout << "Hijo: Hola, soy el proceso hijo.  Voy a dormir " << tiempoAdormir << " segundos" << endl;
		sleep ( tiempoAdormir );
		cout << "Hijo: ya me desperte y termino" << endl;

		exit ( 0 );

	} else {

		cout << "Padre: Hola, soy el proceso padre.  Espero a que mi hijo se despierte" << endl;
		int estado;
		wait ( &estado );
		cout << "Padre: mi hijo se desperto y termino" << endl;

		exit ( 0 );
	}
}


unsigned int calcularRandom () {
	srand ( (unsigned int)time(NULL) );
	unsigned int resultado = (unsigned int)(rand() % 10 + 1);
	return resultado;
}

#endif
