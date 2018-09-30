#ifdef EJEMPLO_5

#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main () {
	int* valor = new int;

	pid_t pid = fork ();

	if ( pid == 0 ) {
		*valor = getpid ();
		cout << "[Hijo] El valor del pid es " << *valor << endl;
		exit ( 0 );
	} else {
		*valor = getpid ();
		cout << "[Padre] El valor del pid es " << *valor << endl;
		delete valor;
		exit ( 0 );
	}
}

#endif
