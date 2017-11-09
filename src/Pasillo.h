/*
 * Pasillo.h
 *
 *  Created on: 8 nov. 2017
 *      Author: francisco
 */

#ifndef PASILLO_H_
#define PASILLO_H_

class Pasillo {
public:

	Pasillo(float _i_x, float _i_y, float _i_ancho, float _i_alto);
	~Pasillo();
private:
	float _pasillo_x;
	float _pasillo_y;
	float _pasillo_ancho;
	float _pasillo_alto;
};


#endif /* PASILLO_H_ */
