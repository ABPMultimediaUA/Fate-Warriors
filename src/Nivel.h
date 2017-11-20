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
	void nivel_crear_pasillo(std::ifstream& _Nivel_txt, std::string& _iteracion);
	void nivel_crear_nodo(std::ifstream& _i_Nivel_txt, std::string& _i_iteracion);
	void nivel_crear_objetos(std::ifstream& _i_Nivel_txt, std::string& _i_iteracion, Nodo* _i_nodo);
private:
	std::vector<Nodo*> _nodos;
	std::vector<Pasillo*> _pasillos;

};
#endif /* HEADERS_NIVEL_H_ */
