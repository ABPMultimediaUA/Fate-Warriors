/*
 * Nivel.h
 *
 *  Created on: 7 nov. 2017
 *      Author: francisco
 */

#include <string>
#include "Nodo.h"
#include "Pasillo.h"
#include <stack>
#include <vector>
#ifndef HEADERS_NIVEL_H_
#define HEADERS_NIVEL_H_

class Vertice;

class Nivel {
public:
	Nivel(std::string _i_fichero);
	~Nivel();
	void nivel_crear_pasillo(std::ifstream& _Nivel_txt, std::string& _iteracion);
	void nivel_crear_nodo(std::ifstream& _i_Nivel_txt, std::string& _i_iteracion);
	void nivel_crear_objetos(std::ifstream& _i_Nivel_txt, std::string& _i_iteracion, Nodo* _i_nodo);



	bool nivel_vacio();
	unsigned short nivel_tamano();
	Vertice * nivel_get_vertice(int _i_id);
	void nivel_inserta_arista_bi(Vertice *_i_origen, Vertice *i_i_destino, int _i_peso);	
	void nivel_inserta_vertice(Vertice* _i_vert);
	void nivel_lista_adyacencia();
	std::stack<Vertice*> nivel_camino_corto_l2(Vertice *_i_origen, Vertice *_i_destino);
	void nivel_eliminar_arista(Vertice *_i_origen, Vertice *_i_destino);
	void nivel_anular();
	void nivel_crear_arista(std::ifstream& _i_nivel_txt, std::string& _i_iteracion);
private:
	Vertice *_h;

	void inserta_arista(Vertice *_i_origen, Vertice *_i_destino, int _i_peso);

};
#endif /* HEADERS_NIVEL_H_ */
