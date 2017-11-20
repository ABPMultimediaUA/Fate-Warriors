/*
 * Nivel.cpp
 *
 *  Created on: 7 nov. 2017
 *      Author: francisco
 */

#include "Nivel.h"
#include "Pasillo.h"
#include <iostream>
#include <fstream>

/* Funcion de crear pasillo
 * Crea los datos del pasillo y se guarda en el vector de pasillos del nivel
 * Input:
 * ifstream para leer el fichero
 * string para guardar los datos del fichero
 * */
void Nivel::nivel_crear_pasillo(std::ifstream& _i_nivel_txt, std::string& _i_iteracion){
	float _x,_y,_ancho,_alto;
	unsigned short _id;
	Pasillo* _pasillo;
	_i_nivel_txt >> _i_iteracion;//obtiene el valor de la x
	_x = std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de la y
	_y = std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de ancho
	_ancho = std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de alto
	_alto = std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de la id
	_id = std::strtoul(_i_iteracion.c_str(),NULL,0);

	_pasillo = new Pasillo( _x, _y, _ancho, _alto, _id);//creacion del nuevo pasillo
	_pasillos.push_back(_pasillo);//se guarda el nuevo pasillo en el vector de pasillos
	delete _pasillo;
	_i_nivel_txt >> _i_iteracion;//se guarda el siguiente valor de nombre
}
/* Funcion de crear nodo
 * Crea los datos del pasillo y se guarda en el vector de pasillos del nivel
 * Input:
 * ifstream para leer el fichero
 * string para guardar los datos del fichero
 * */
void Nivel::nivel_crear_nodo(std::ifstream& _i_nivel_txt, std::string& _i_iteracion){
	float _x,_y,_ancho,_alto;
	unsigned short _id;
	Nodo* _nodo;

	_i_nivel_txt >> _i_iteracion;//obtiene el valor de la x
	_x = std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de la y
	_y = std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de ancho
	_ancho = std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de alto
	_alto = std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de la id
	_id = std::strtoul(_i_iteracion.c_str(),NULL,0);

	_nodo = new Nodo( _x, _y, _ancho, _alto, _id);//creacion del nuevo pasillo
	_i_nivel_txt >> _i_iteracion;//se guarda el nombre del fichero para leer los objetos
	nivel_crear_objetos( _i_nivel_txt, _i_iteracion, _nodo);//creacion de todos los nodos
	_nodos.push_back(_nodo);//se guarda el nuevo pasillo en el vector de pasillos
	delete _nodo;

}
/*Funcion de crear objetos
 * Crea los datos de todos los objetos propios del nodo
 *  y se guarda en el vector de pasillos del nivel
 * Input:
 *  ifstream para ller el fichero
 *  string que se guarda los datos del fichero
 *  puntero al nodo dentro del cual se crean
 * */
void Nivel::nivel_crear_objetos(std::ifstream& _i_nivel_txt, std::string& _i_iteracion, Nodo* _i_nodo){
	float _x,_y,_ancho,_alto;
	if(_i_iteracion!="null"){
		std::ifstream _nodo_txt;
		_nodo_txt.open(_i_iteracion);//apertura del fichero
		std::string _iteracion;
		if(_nodo_txt.fail()){//comprobacion de la apertura del fichero
			std::cout<<"Error al abrir el archivo de nodo"<<std::endl;
		}
		_nodo_txt >> _iteracion;//primera lectura de nombre de clase a introducir
		while(_iteracion=="OBJETO"){//bucle para crear todos los objetos del nodo
			_nodo_txt >> _iteracion;//obtiene el valor de la x
			_x = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
			std::cout << _iteracion << std::endl;
			_nodo_txt>>_iteracion;//obtiene el valor de la y
			_y = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
			std::cout << _iteracion << std::endl;
			_nodo_txt>>_iteracion;//obtiene el valor de ancho
			_ancho = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
			std::cout << _iteracion << std::endl;
			_nodo_txt>>_iteracion;//obtiene el valor de alto
			_alto = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
			std::cout << _iteracion << std::endl;
			_i_nodo->nodo_crear_objeto( _x, _y, _ancho, _alto);
			_nodo_txt >> _iteracion;//se guarda el siguiente valor de nombre*/
		}
	}
	_i_nivel_txt >> _i_iteracion;//obtiene el siguiente valor de nombre
}

/*Funciones para guardar los datos
 * */
struct Tinstance2func{//declaracion de los parametros
	const char* _nombre_objeto;
	void (Nivel::*pmet)(std::ifstream&, std::string&);
};

Tinstance2func mapping[] = {//definicion de los parametros
		{"PASILLO", &Nivel::nivel_crear_pasillo},
		{"NODO", &Nivel::nivel_crear_nodo},
		{0, 0}
};
/*Constructor del nivel, lee el fichero y le pone sus valores a los nodos, pasillos y objetos
 * Input: string con el nombre del fichero de nivel
 *
 * */
Nivel::Nivel(std::string _i_fichero) {
	std::ifstream _nivel_txt;
	Tinstance2func *_next;
	//(this.*pmet)(_nivel_txt,_iteracion);
	_nivel_txt.open("Nivel.txt");//apertura del fichero
	std::string _iteracion;
		if(_nivel_txt.fail()){//comprobacion de la apertura del fichero
			std::cout<<"Error al abrir el archivo"<<std::endl;
		}
	_nivel_txt >> _iteracion;//primera lectura de nombre de clase a introducir
	while(_iteracion!="Fin"){//bucle de lectura del fichero
		std::cout << _iteracion << std::endl;
		_next=mapping;
		while (_next->_nombre_objeto){
			if(_iteracion==_next->_nombre_objeto){
				(this->*_next->pmet)(_nivel_txt,_iteracion);
			}

			++_next;
		}
		/*if(_iteracion=="NODO"){
			nivel_crear_nodo(_nivel_txt, _iteracion);
		}else if(_iteracion=="PASILLO"){
			nivel_crear_pasillo(_nivel_txt, _iteracion);//llamada a la funcion de crear un nuevo pasillo
		}*/
	}
	_nivel_txt.close();//cierre del fichero

}

Nivel::~Nivel() {
	// TODO Auto-generated destructor stub
	_nodos.clear();
	_pasillos.clear();
}

