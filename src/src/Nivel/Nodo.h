#include <vector>
#include "Vertice.h"
#include "Enum_zona.h"
#ifndef NODO_H_
#define NODO_H_

class Objeto;

class Nodo: public Vertice {
public:

	Nodo(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id, Grafo *_i_grafo, int _i_zona);
	~Nodo();
	void nodo_crear_objeto(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id);
	

private:
	float _ancho;
	float _alto;
	std::vector<Objeto*> _objetos;
	unsigned short _tipo;
	int _id;
	Enum_zonas _zona;

};

#endif /* NODO_H_ */
