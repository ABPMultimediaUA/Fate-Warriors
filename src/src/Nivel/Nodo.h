/*
 * Nodo.h
 *
 *  Created on: 7 nov. 2017
 *      Author: francisco
 */
#include <vector>
#include "Vertice.h"
#ifndef NODO_H_
#define NODO_H_

class Objeto;

class Nodo: public Vertice {
public:

	Nodo(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id, Grafo *_i_grafo);
	~Nodo();
	void nodo_crear_objeto(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id);

private:
	float _ancho;
	float _alto;
	std::vector<Objeto*> _objetos;
	unsigned short _estado;
	unsigned short _id;

};

#endif /* NODO_H_ */
