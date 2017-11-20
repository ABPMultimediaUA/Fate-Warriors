/*
 * objeto.h
 *
 *  Created on: 7 nov. 2017
 *      Author: francisco
 */

#ifndef HEADERS_OBJETO_H_
#define HEADERS_OBJETO_H_

class Objeto {
public:
	Objeto(float _i_x, float _i_y, float _i_ancho, float _i_alto);
	~Objeto();
private:
	float _objeto_x;
	float _objeto_y;
	float _objeto_ancho;
	float _objeto_alto;
};

#endif /* HEADERS_OBJETO_H_ */
