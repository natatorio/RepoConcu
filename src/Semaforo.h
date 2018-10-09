#ifndef SEMAFORO_H_
#define SEMAFORO_H_

#define INITIALIZE 1
#define NOT_INITIALIZE 0

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>

class Semaforo {

private:
	int id;
	int valorInicial;

	int inicializar () const;

public:
	Semaforo ( const std::string& nombre, const int valorInicial, int id, int init);
	~Semaforo();

	int p () const; // decrementa
	int v () const; // incrementa
	int getCont();
	void eliminar () const;
};

#endif /* SEMAFORO_H_ */
