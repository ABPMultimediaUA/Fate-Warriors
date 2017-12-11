
#include "Vertice.h"
#ifndef PASILLO_H_
#define PASILLO_H_

class Pasillo: public Vertice {
public:

	Pasillo(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id, Grafo *_i_grafo);
	~Pasillo();
	

private:
	unsigned short _id;
};


#endif /* PASILLO_H_ */
