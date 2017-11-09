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


void Nivel::nivel_crear_pasillo(std::ifstream& _i_nivel_txt, std::string& _i_iteracion){
	float x,y,ancho,alto;
	Pasillo* _pasillo;
	_i_nivel_txt >> _i_iteracion;//obtiene el valor de la x
	x = std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de la y
	y = std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de ancho
	ancho = std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de alto
	alto = std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_pasillo = new Pasillo( x, y, ancho, alto);//creacion del nuevo pasillo
	_pasillos.push_back(_pasillo);//se guarda el nuevo pasillo en el vector de pasillos
	delete _pasillo;
	_i_nivel_txt >> _i_iteracion;//se guarda el siguiente valor de nombre
}
void Nivel::nivel_crear_nodo(std::ifstream& _i_nivel_txt, std::string& _i_iteracion){
	float x,y,ancho,alto;
	Nodo* _nodo;
	_i_nivel_txt >> _i_iteracion;//obtiene el valor de la x
	x = std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de la y
	y = std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de ancho
	ancho = std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de alto
	alto = std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float



	_nodo = new Nodo( x, y, ancho, alto);//creacion del nuevo pasillo
	_i_nivel_txt >> _i_iteracion;//se guarda el nombre del fichero para leer los objetos
	nivel_crear_objetos( _i_nivel_txt, _i_iteracion, _nodo);//creacion de todos los nodos
	_nodos.push_back(_nodo);//se guarda el nuevo pasillo en el vector de pasillos
	delete _nodo;

}
void Nivel::nivel_crear_objetos(std::ifstream& _i_nivel_txt, std::string& _i_iteracion, Nodo* _i_nodo){
	float x,y,ancho,alto;
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
			x = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
			std::cout << _iteracion << std::endl;
			_nodo_txt>>_iteracion;//obtiene el valor de la y
			y = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
			std::cout << _iteracion << std::endl;
			_nodo_txt>>_iteracion;//obtiene el valor de ancho
			ancho = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
			std::cout << _iteracion << std::endl;
			_nodo_txt>>_iteracion;//obtiene el valor de alto
			alto = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
			std::cout << _iteracion << std::endl;
			_i_nodo->nodo_crear_objeto( x, y, ancho, alto);
			_nodo_txt >> _iteracion;//se guarda el siguiente valor de nombre*/
		}
	}
	_i_nivel_txt >> _i_iteracion;//obtiene el siguiente valor de nombre
}
struct Tinstance2func{
	std::string _nombre_objeto;
	void (Nivel::*pmet)(std::ifstream&, std::string&);
};

/*Tinstance2func mapping[] = {
		{"PASILLO", &Nivel::nivel_crear_pasillo},
		{"NODO", &Nivel::nivel_crear_nodo},
		{0, 0}
};*/

Nivel::Nivel(std::string _i_fichero) {
	std::ifstream _nivel_txt;

	_nivel_txt.open("Nivel.txt");//apertura del fichero
	std::string _iteracion;
		if(_nivel_txt.fail()){//comprobacion de la apertura del fichero
			std::cout<<"Error al abrir el archivo"<<std::endl;
		}
	_nivel_txt >> _iteracion;//primera lectura de nombre de clase a introducir
	while(_iteracion!="Fin"){//bucle de lectura del fichero
		std::cout << _iteracion << std::endl;
		if(_iteracion=="NODO"){
			nivel_crear_nodo(_nivel_txt, _iteracion);
		}else if(_iteracion=="PASILLO"){
			nivel_crear_pasillo(_nivel_txt, _iteracion);//llamada a la funcion de crear un nuevo pasillo
		}
	}
	_nivel_txt.close();//cierre del fichero

}

Nivel::~Nivel() {
	// TODO Auto-generated destructor stub
	_nodos.clear();
	_pasillos.clear();
}

