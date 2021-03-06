#ifndef MEMORIACOMPARTIDA_H_
#define MEMORIACOMPARTIDA_H_

#define SHM_OK			 0
#define	ERROR_FTOK		-1
#define ERROR_SHMGET	-2
#define	ERROR_SHMAT		-3
#define LIBERADA 0
#define NO_LIBERADA 1

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>


template <class T> class MemoriaCompartida {

private:
	int shmId;
	T*	ptrDatos;

	int cantidadProcesosAdosados () const;

public:
	MemoriaCompartida ();
	~MemoriaCompartida ();
	int crear ( const std::string& archivo,const char letra, int len );
	int liberar ();
	void escribir ( const T& dato, int pos );
	T leer (int pos) const;

};

template <class T> MemoriaCompartida<T> :: MemoriaCompartida() : shmId(0), ptrDatos(NULL) {
}

template <class T> MemoriaCompartida<T> :: ~MemoriaCompartida() {
}

template <class T> int MemoriaCompartida<T> :: crear ( const std::string& archivo,const char letra, int len ) {

	// generacion de la clave
	key_t clave = ftok ( archivo.c_str(),letra );
	if ( clave == -1 )
		return ERROR_FTOK;
	else {
		// creacion de la memoria compartida
		this->shmId = shmget ( clave, len * sizeof(T),0644|IPC_CREAT );

		if ( this->shmId == -1 )
			return ERROR_SHMGET;
		else {
			// attach del bloque de memoria al espacio de direcciones del proceso
			void* ptrTemporal = shmat ( this->shmId,NULL,0 );

			if ( ptrTemporal == (void *) -1 ) {
				return ERROR_SHMAT;
			} else {
				this->ptrDatos = static_cast<T*> (ptrTemporal);
				return SHM_OK;
			}
		}
	}
}


template <class T> int MemoriaCompartida<T> :: liberar () {
	// detach del bloque de memoria
	shmdt ( static_cast<void*> (this->ptrDatos) );

	int procAdosados = this->cantidadProcesosAdosados ();

	if ( procAdosados == 0 ) {
		shmctl ( this->shmId,IPC_RMID,NULL );
		return LIBERADA;
	}
	return NO_LIBERADA;
}

template <class T> void MemoriaCompartida<T> :: escribir ( const T& dato, int pos ) {

	* ((this->ptrDatos) + pos * sizeof(T)) = dato;
}

template <class T> T MemoriaCompartida<T> :: leer (int pos) const {
	return ( *((this->ptrDatos) + pos * sizeof(T)) );
}

template <class T> int MemoriaCompartida<T> :: cantidadProcesosAdosados () const {
	shmid_ds estado;
	shmctl ( this->shmId,IPC_STAT,&estado );
	return estado.shm_nattch;
}


#endif /* MEMORIACOMPARTIDA_H_ */
