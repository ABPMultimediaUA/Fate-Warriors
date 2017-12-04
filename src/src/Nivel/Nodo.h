/*
 * Nodo.h
 *
 *  Created on: 7 nov. 2017
 *      Author: francisco
 */
#include "../Skewers.h"
#include <vector>
#include "Vertice.h"
#ifndef NODO_H_
#define NODO_H_



class Nodo: public Vertice {
public:

	Nodo(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id);
	~Nodo();
	void nodo_crear_objeto(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id);

private:
	float _nodo_x;
	float _nodo_y;
	float _nodo_ancho;
	float _nodo_alto;
	std::vector<Objeto*> _objetos;
	unsigned short _estado;
	unsigned short _id;

};

#endif /* NODO_H_ */
