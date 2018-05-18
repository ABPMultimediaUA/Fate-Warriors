#include "Nivel.h"
#include <iostream>
#include <fstream>
#include "Vertice.h"
#include "Arista.h"
#include <queue>
#include <list>

Nivel* Nivel::instancia = 0;

Nivel* Nivel::nivel_instancia(){
	if(instancia == 0){
		std::string nivel="txt/Nivel/Nivel1.txt";
		instancia= new Nivel(nivel);
	}

	return instancia;
}




/*Funcion de crear grafos
 * Crea todos los vertices y aristas correspondientes al grafo
 * Input:
 *  ifstream para ller el fichero
 *  string que se guarda los datos del fichero
 *  puntero al grafo dentro del cual se crean
 * */
void Nivel::nivel_crear_grafo(std::ifstream& _i_nivel_txt, std::string& _i_iteracion, Grafo* _i_grafo){
	float _x,_y;
	int _id;
	if(_i_iteracion!="null"){
		std::ifstream _grafo_txt;
		_grafo_txt.open(_i_iteracion);//apertura del fichero
		std::string _iteracion;
		if(_grafo_txt.fail()){//comprobacion de la apertura del fichero
			//std::cout << "Error al abrir el archivo del grafo " << _i_iteracion << std::endl;
			exit(0);
		}
		_grafo_txt >> _iteracion;//primera lectura de nombre de clase a introducir
		while(_iteracion!="Fin"){//bucle para crear todos los objetos del nodo
			if(_iteracion=="VERTICE"){
				
				_grafo_txt >> _iteracion;//obtiene el valor de la y
				_y = metro*std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

				_grafo_txt>>_iteracion;//obtiene el valor de la x
				_x = metro*std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

				_grafo_txt>>_iteracion;//obtiene el valor de la id
				_id = std::atoi(_iteracion.c_str());
				
				Vertice* vertice= new Vertice(_x, _y, 0, 0, _id, nullptr);
				_i_grafo->grafo_inserta_vertice(vertice);
			}else if(_iteracion=="ARISTA"){
				_grafo_txt >> _iteracion;//obtiene el valor de la id del origen
				_x = std::atoi(_iteracion.c_str());//se convierte a const* char para convertirse en un float
				
				_grafo_txt>>_iteracion;//obtiene el valor de la id del destino
				_y = std::atoi(_iteracion.c_str());//se convierte a const* char para convertirse en un float
				
				_grafo_txt>>_iteracion;//obtiene el valor de la id
				_id = std::atoi(_iteracion.c_str());
				_i_grafo->grafo_crea_arista(_x, _y, _id);
				
			}
			
			_grafo_txt >> _iteracion;//se guarda el siguiente valor de nombre*/
		}
		//std::cout << "cierro el txt del lod1 " <<_i_iteracion<< std::endl;
		_grafo_txt.close();
	}
	_i_nivel_txt >> _i_iteracion;//obtiene el siguiente valor de nombre
}


/* Funcion de crear pasillo
 * Crea los datos del pasillo y se guarda en el vector de pasillos del nivel
 * Input:
 * ifstream para leer el fichero
 * string para guardar los datos del fichero
 * */
void Nivel::nivel_crear_pasillo(std::ifstream& _i_nivel_txt, std::string& _i_iteracion){
	float _x,_y,_ancho,_alto;
	int _id;
	Pasillo* _pasillo;
	Grafo * _vacio = new Grafo();
	_i_nivel_txt >> _i_iteracion;//obtiene el valor de la y
	_y = metro*std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de la x
	_x = metro*std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de alto
	_alto = metro*std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
	
	_i_nivel_txt>>_i_iteracion;//obtiene el valor de ancho
	_ancho = metro*std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
	
	_i_nivel_txt>>_i_iteracion;//obtiene el valor de la id
	_id = std::atoi(_i_iteracion.c_str());

	_i_nivel_txt >> _i_iteracion;//se guarda el nombre del fichero 

	nivel_crear_grafo( _i_nivel_txt, _i_iteracion, _vacio);//creacion de todos los nodos
	_pasillo = new Pasillo( _x, _y, _ancho, _alto, _id, _vacio);//creacion del nuevo pasillo

	_lod2->grafo_inserta_vertice(_pasillo);//creacion del pasillo en el grafo
}


/* Funcion de crear nodo
 * Crea los datos del nodo y se guarda en el vector de pasillos del nivel
 * Input:
 * ifstream para leer el fichero
 * string para guardar los datos del fichero
 * */
void Nivel::nivel_crear_nodo(std::ifstream& _i_nivel_txt, std::string& _i_iteracion){
	float _x,_y,_ancho,_alto;
	int _id;
	uint8_t n_npc;
	Nodo* _nodo;
	Grafo * _vacio = new Grafo();
	_i_nivel_txt >> _i_iteracion;//obtiene el valor de la y
	_y = metro*std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de la x
	_x = metro*std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de alto
	_alto = metro*std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
	
	_i_nivel_txt>>_i_iteracion;//obtiene el valor de ancho
	_ancho = metro*std::strtof(_i_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
	
	_i_nivel_txt>>_i_iteracion;//obtiene el valor de la id
	_id = std::atoi(_i_iteracion.c_str());

	_i_nivel_txt >> _i_iteracion;//se guarda el nombre del fichero 

	//cantidad maxima de npc por nodo
	for(n_npc=0;n_npc<_ancho/metro;++n_npc){

	}
	n_npc-=3;
	int zona;

	nivel_crear_grafo( _i_nivel_txt, _i_iteracion, _vacio);//creacion de todos los nodos
	
	zona=std::atoi(_i_iteracion.c_str());
	_nodo = new Nodo( _x, _y, _ancho, _alto, _id, _vacio, zona, n_npc);//creacion del nuevo nodo
	
	_i_nivel_txt>>_i_iteracion;//obtiene el valor del siguiente nombre
	
	_lod2->grafo_inserta_vertice(_nodo);//creacion del nodo en el grafo

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
	int _id;
	if(_i_iteracion!="null"){
		std::ifstream _nodo_txt;
		_nodo_txt.open(_i_iteracion);//apertura del fichero
		std::string _iteracion;
		if(_nodo_txt.fail()){//comprobacion de la apertura del fichero
			//std::cout << "Error al abrir el archivo de nodo" << _i_iteracion << std::endl;
			exit(0);
		}
		_nodo_txt >> _iteracion;//primera lectura de nombre de clase a introducir
		while(_iteracion=="OBJETO"){//bucle para crear todos los objetos del nodo
			_nodo_txt >> _iteracion;//obtiene el valor de la x
			_x = metro*std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
			
			_nodo_txt>>_iteracion;//obtiene el valor de la y
			_y = metro*std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
			
			_nodo_txt>>_iteracion;//obtiene el valor de ancho
			_ancho = metro*std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
			
			_nodo_txt>>_iteracion;//obtiene el valor de alto
			_alto = metro*std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
			
			_nodo_txt>>_iteracion;//obtiene el valor de la id
			_id = std::atoi(_iteracion.c_str());
			
			_i_nodo->nodo_crear_objeto( _x, _y, _ancho, _alto, _id);
			_nodo_txt >> _iteracion;//se guarda el siguiente valor de nombre*/
		}
		_nodo_txt.close();
	}
	_i_nivel_txt >> _i_iteracion;//obtiene el siguiente valor de nombre

}
/*
*Crea la relacion entre dos nodos (nodo-pasillo), con un peso.
* Input: ifstream para ller el fichero
*  	     string que se guarda los datos del fichero
* Output:~
*/
void Nivel::nivel_crear_arista(std::ifstream& _i_nivel_txt, std::string& _i_iteracion){
	int _id_o, _id_d, _i_peso, _id_a;
	
	_i_nivel_txt>>_i_iteracion;//obtiene el valor de la id del origen
	_id_o = std::atoi(_i_iteracion.c_str());

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de la id del destino
	_id_d = std::atoi(_i_iteracion.c_str());

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de la id de la arista
	_id_a = std::atoi(_i_iteracion.c_str());
	
	_lod2->grafo_crea_arista(_id_o, _id_d, _id_a);
	
	_i_nivel_txt >> _i_iteracion;//obtiene el siguiente valor de nombre
	
}

void Nivel::nivel_crear_adyacentes(std::ifstream& _i_nivel_txt, std::string& _i_iteracion){
	int _id_o, _id_a;
	int tamano;

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de la cantidad de nodos adyacentes
	tamano = std::atoi(_i_iteracion.c_str());
	_i_nivel_txt>>_i_iteracion;//obtiene el valor de la id del origen
	_id_o = std::atoi(_i_iteracion.c_str());

	Nodo* nodo=static_cast<Nodo*>(_lod2->grafo_get_vertice(_id_o));
	
	nodo->get_blackboard()->declarar_zonas_ady(tamano);
	while(_i_iteracion!="-1"){
		_i_nivel_txt>>_i_iteracion;//obtiene el valor de la id del adyacente
		_id_a = std::atoi(_i_iteracion.c_str());
		nodo->get_blackboard()->anyadir_zona(_id_a);
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
		{"ARISTA", &Nivel::nivel_crear_arista},
		{"ADYACENTE", &Nivel::nivel_crear_adyacentes},
		{0, 0}
};
/*Constructor del nivel, lee el fichero y le pone sus valores a los nodos, pasillos y objetos
 * Input: string con el nombre del fichero de nivel
 *
 * */
Nivel::Nivel(std::string &_i_fichero) {
	std::ifstream _nivel_txt;
	Tinstance2func *_next;
	_lod2 = new Grafo();//nodo inicial del nivel

	_nivel_txt.open(_i_fichero);//apertura del fichero
	std::string _iteracion;
		if(_nivel_txt.fail()){//comprobacion de la apertura del fichero
			//std::cout<<"Error al abrir el archivo " << _i_fichero <<std::endl;
			exit(0);
		}
	_nivel_txt >> _iteracion;//primera lectura de nombre de clase a introducir
	while(_iteracion!="Fin"){//bucle de lectura del fichero
		_next=mapping;
		while (_next->_nombre_objeto){
			if(_iteracion==_next->_nombre_objeto){
				(this->*_next->pmet)(_nivel_txt,_iteracion);
			}

			++_next;
		}
	}
	_nivel_txt.close();//cierre del fichero

}


Nivel::~Nivel() {
	instancia = 0;
	delete _lod2;
}

void Nivel::Update(){
	_lod2->Update();
}



