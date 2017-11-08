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


Nivel::Nivel(std::string _i_fichero) {
	std::ifstream _Nivel_txt;
	float x,y,ancho,alto;
	Nodo* _nodo;
	Pasillo* _pasillo;
	_Nivel_txt.open("Nivel.txt");//apertura del fichero
	std::string _iteracion;
		if(_Nivel_txt.fail()){//comprobacion de la apertura del fichero
			std::cout<<"Error al abrir el archivo"<<std::endl;
		}
	_Nivel_txt >> _iteracion;//primera lectura de nombre de clase a introducir
	while(_iteracion!="Fin"){//bucle de lectura del fichero
		std::cout << _iteracion << std::endl;

		if(_iteracion=="NODO"){
			_Nivel_txt >> _iteracion;//obtiene el valor de la x
			x = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

			_Nivel_txt>>_iteracion;//obtiene el valor de la y
			y = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

			_Nivel_txt>>_iteracion;//obtiene el valor de ancho
			ancho = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

			_Nivel_txt>>_iteracion;//obtiene el valor de alto
			alto = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
			_nodo = new Nodo(x , y, ancho, alto);//creacion del nuevo nodo

			_Nivel_txt >> _iteracion;//se guarda el siguiente valor de nombre


			while(_iteracion=="OBJETO"){//bucle para crear todos los objetos del nodo
				_Nivel_txt >> _iteracion;//obtiene el valor de la x
				x = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

				_Nivel_txt>>_iteracion;//obtiene el valor de la y
				y = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

				_Nivel_txt>>_iteracion;//obtiene el valor de ancho
				ancho = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

				_Nivel_txt>>_iteracion;//obtiene el valor de alto
				alto = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float


				_Nivel_txt >> _iteracion;//se guarda el siguiente valor de nombre
			}
			_nodos.push_back(_nodo);//se guarda el nuevo nodo en el vector de nodos
			delete _nodo;//borra el nodo
		}else if(_iteracion=="PASILLO"){
			_Nivel_txt >> _iteracion;//obtiene el valor de la x
			x = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

			_Nivel_txt>>_iteracion;//obtiene el valor de la y
			y = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

			_Nivel_txt>>_iteracion;//obtiene el valor de ancho
			ancho = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

			_Nivel_txt>>_iteracion;//obtiene el valor de alto
			alto = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

			_pasillo = new Pasillo( x, y, ancho, alto);//creacion del nuevo pasillo
			_pasillos.push_back(_pasillo);//se guarda el nuevo pasillo en el vector de pasillos
			delete _pasillo;
			_Nivel_txt >> _iteracion;//se guarda el siguiente valor de nombre
		}
	}

}

Nivel::~Nivel() {
	// TODO Auto-generated destructor stub
	_nodos.clear();
	_pasillos.clear();
}

