/*
 * Pasillo.h
 *
 *  Created on: 8 nov. 2017
 *      Author: francisco
 */
#include "Vertice.h"
#ifndef PASILLO_H_
#define PASILLO_H_

class Pasillo: public Vertice {
public:

	Pasillo(int _i_x, int _i_y, float _i_ancho, float _i_alto, int _i_id);
	~Pasillo();
private:
	float _pasillo_x;
	float _pasillo_y;
	float _pasillo_ancho;
	float _pasillo_alto;
	int _id;
};


#endif /* PASILLO_H_ */
