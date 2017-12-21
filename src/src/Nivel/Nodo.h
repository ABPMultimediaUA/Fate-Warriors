#include "Vertice.h"
#include "Nodo_blackboard.h"
#ifndef NODO_H_
#define NODO_H_

class Objeto;

class Nodo: public Vertice {
public:
	
	Nodo(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id, Grafo *_i_grafo, int _i_zona);
	~Nodo();
	void nodo_crear_objeto(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id);
	

private:

	
};

#endif /* NODO_H_ */
