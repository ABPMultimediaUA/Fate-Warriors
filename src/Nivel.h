/*
 * Nivel.h
 *
 *  Created on: 7 nov. 2017
 *      Author: francisco
 */
#include <string>
#include "Nodo.h"
#include "Pasillo.h"
#include <vector>
#ifndef HEADERS_NIVEL_H_
#define HEADERS_NIVEL_H_

class Nivel {
public:
	Nivel(std::string _i_fichero);
	~Nivel();
private:
	std::vector<Nodo*> _nodos;
	std::vector<Pasillo*> _pasillos;
};
#endif /* HEADERS_NIVEL_H_ */
