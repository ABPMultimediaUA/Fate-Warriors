/*
 * Nivel.cpp
 *
 *  Created on: 7 nov. 2017
 *      Author: francisco
 */

#include "Nivel.h"
#include <iostream>
#include <fstream>
#include "Vertice.h"
#include "Arista.h"
#include <queue>
#include <list>

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
	_i_nivel_txt >> _i_iteracion;//se guarda el siguiente valor de nombre
	nivel_inserta_vertice(_pasillo);//creacion del pasillo en el grafo
}
/* Funcion de crear nodo
 * Crea los datos del nodo y se guarda en el vector de pasillos del nivel
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

	_nodo = new Nodo( _x, _y, _ancho, _alto, _id);//creacion del nuevo nodo
	_i_nivel_txt >> _i_iteracion;//se guarda el nombre del fichero para leer los objetos
	nivel_crear_objetos( _i_nivel_txt, _i_iteracion, _nodo);//creacion de todos los nodos
	nivel_inserta_vertice(_nodo);//creacion del nodo en el grafo
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
			
			_nodo_txt>>_iteracion;//obtiene el valor de la y
			_y = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
			
			_nodo_txt>>_iteracion;//obtiene el valor de ancho
			_ancho = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
			
			_nodo_txt>>_iteracion;//obtiene el valor de alto
			_alto = std::strtof(_iteracion.c_str(),0);//se convierte a const* char para convertirse en un float
			
			_i_nodo->nodo_crear_objeto( _x, _y, _ancho, _alto);
			_nodo_txt >> _iteracion;//se guarda el siguiente valor de nombre*/
		}
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
	int _id_o, _id_d, _i_peso;

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de la id
	_id_o = std::strtoul(_i_iteracion.c_str(),NULL,0);

	_i_nivel_txt>>_i_iteracion;//obtiene el valor de la id
	_id_d = std::strtoul(_i_iteracion.c_str(),NULL,0);

	Vertice* _i_origen;
	Vertice* _i_destino;
	Vertice* _aux=_h;
	while(_aux!=NULL){								//bucle para recorrer todos los vertices del grafo
		if(_aux->_id==_id_o){						//id del origen encontrada
			_i_origen=_aux;
		}else if(_aux->_id==_id_d){					//id del destino encontrada
			_i_destino=_aux;
		}
		_aux=_aux->_sig;
	}
	_i_peso=10;
	nivel_inserta_arista_bi(_i_origen, _i_destino,  _i_peso);
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
		{0, 0}
};
/*Constructor del nivel, lee el fichero y le pone sus valores a los nodos, pasillos y objetos
 * Input: string con el nombre del fichero de nivel
 *
 * */
Nivel::Nivel(std::string _i_fichero) {
	std::ifstream _nivel_txt;
	Tinstance2func *_next;
	_h = NULL;					//nodo inicial del nivel

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
	this->nivel_anular();
}

/*Comprueba si el grafo esta vacio o no.
 * Input: ~
 * Output: booleana que devuelve cierto si esta vacio.
 * */
bool Nivel::nivel_vacio(){
	if(_h==NULL){
		return true;
	}
	else{
		return false;
	}
}
/*Comprueba el tamano del grafo.
 * Input: ~
 * Output: numero de rooms y pasillos del nivel.
 * */
unsigned short Nivel::nivel_tamano(){
	unsigned short _cont=0;
	Vertice *_aux;
	_aux = _h;
	while(_aux!=NULL){
		_cont++;
		_aux=_aux->_sig;
	}
	return _cont;
}
/*Da un vertice dependiendo de su nombre.
 * Input: Id del vertice.
 * Output: puntero del vertice.
 * */
Vertice *Nivel::nivel_get_vertice(int _i_id){
	Vertice *_aux;
	_aux = _h;
	while(_aux!=NULL){
		if(_aux->_id == _i_id){
			return _aux;
		}
		_aux=_aux->_sig;
		
	}
	return NULL;
}
/*Inserta un nodo en el grafo.
 * Input: id del nodo.
 * Output: ~.
 * */
void Nivel::nivel_inserta_vertice(Vertice* _i_vert){


	if(nivel_vacio()){
		_h=_i_vert;
	}
	else{
		Vertice *_aux;
		_aux=_h;
		while(_aux->_sig!=NULL){
			_aux = _aux->_sig;
		}
		_aux->_sig=_i_vert;
	}

}
/*Establece la conexcion bidireccional con dos nodos.
 * Input: nodo origen y nodo destino, y su peso.
 * Output: ~.
 * */
void Nivel::nivel_inserta_arista_bi(Vertice *_i_origen, Vertice *_i_destino, int _i_peso){
	inserta_arista(_i_origen,_i_destino,_i_peso);
	inserta_arista(_i_destino,_i_origen,_i_peso);
}
/*Establece la conexcion con dos nodos.
 * Input: nodo origen y nodo destino, y su peso.
 * Output: ~.
 * */
void Nivel::inserta_arista(Vertice *_i_origen, Vertice *_i_destino, int _i_peso){
	Arista *_nueva = new Arista;

	_nueva->_peso=_i_peso;
	_nueva->_sig=NULL;
	_nueva->_ady=NULL;

	Arista *_aux;

	_aux=_i_origen->_ady;

	if(_aux==NULL){
		_i_origen->_ady=_nueva;
		_nueva->_ady=_i_destino;
	}
	else{
		while(_aux->_sig!=NULL){
			_aux= _aux->_sig;
		}
		_aux->_sig=_nueva;
		_nueva->_ady=_i_destino;
	}

}
/*Muestra la conexion entre un nodo y el resto sucesivamente.
 * Input: ~.
 * Output: ~.
 * */
void Nivel::nivel_lista_adyacencia(){
	Vertice *_VertAux;
	Arista *_ArisAux;

	_VertAux = _h;

	while(_VertAux != NULL){
		std::cout << _VertAux->_id << " -> ";
		_ArisAux = _VertAux->_ady;
		while(_ArisAux != NULL){
			std::cout << _ArisAux->_ady->_id << " -> " ;
			_ArisAux = _ArisAux->_sig;
		}
		_VertAux = _VertAux->_sig;
		std::cout<<std::endl;
	}
}

/*Vacia todo el grafo.
 * Input: ~.
 * Output: ~.
 * */
void Nivel::nivel_anular(){

	Vertice *_aux;

	while(_h!=NULL){
		_aux=_h;
		nivel_eliminar_arista(_h,_h->_sig);
		//std::cout<< aux->_id << std::endl;
		_h=_h->_sig;
		//std::cout<< h->_id << std::endl;
		
		delete(_aux);
	}
}

/*Elimina una arista.
 * Input: el origen y el destino de la arista.
 * Output: ~.
 * */
void Nivel::nivel_eliminar_arista(Vertice *_i_origen, Vertice *_i_destino){

	bool _flag=false;

	Arista *_actual, *_anterior;

	_actual = _i_origen->_ady;

	if(_actual==NULL){
		std::cout << "Vertices no na" << std::endl;
	}
	else if(_actual->_ady==_i_destino){
std::cout << "Vertices no naasdf" << std::endl;
		_i_origen->_ady = _actual->_sig;
		delete(_actual);
		nivel_eliminar_arista(_i_destino,_i_origen);
	}
	else
	{
		while(_actual->_ady != NULL){
			if(_actual->_ady==_i_destino){

				_flag=true;
				_anterior->_sig=_actual->_sig;
				delete(_actual);
				std::cout << "Se ha eliminado la arista" << std::endl;
				nivel_eliminar_arista(_i_destino,_i_origen);
				break;
			}
			if(_actual->_sig != NULL){
				_anterior=_actual;
				_actual=_actual->_sig;
			}else{
				break;
			}
		}
		if(!_flag)
		{
			std::cout << "Vertices no conectados" << std::endl;
		}

	}

}
/*Devuelve el mejor camino (LOD2) entre dos nodos dados.
 * Input: un origen y un destino.
 * Output: pila con el recorrido.
 * */
std::stack<Vertice*> Nivel::nivel_camino_corto_l2(Vertice *_i_origen, Vertice *_i_destino){

	Vertice *_VerticeActual;
	Vertice *_i_destinoActual;

	Arista *_aux;

	typedef std::pair<Vertice*, Vertice*> VerticeVertice;
	std::queue<Vertice*> _cola;
	std::stack<VerticeVertice> _pila;
	std::stack<Vertice*> _recorrido;
	std::list<Vertice*> _lista;
	std::list<Vertice*>::iterator _i;

	bool _band,_band2,_band3=false;

	_cola.push(_i_origen);

	while(!_cola.empty()){
		_band=false;
		_VerticeActual=_cola.front();
		_cola.pop();
		for(_i=_lista.begin();_i!=_lista.end();_i++){
			if(_VerticeActual == *_i){
				_band=true;
			}
		}
		if(_band==false){
			if(_VerticeActual==_i_destino){
				_band3=true;
				_i_destinoActual=_i_destino;
				while(!_pila.empty()){
					//pila que sera la que se devuelva
					_recorrido.push(_i_destinoActual);
					while(!_pila.empty() && _pila.top().second!=_i_destinoActual){
						_pila.pop();
					}
					if(!_pila.empty()){
						_i_destinoActual=_pila.top().first;
					}
				}
			}
			_lista.push_back(_VerticeActual);

			_aux=_VerticeActual->_ady;

			while(_aux!=NULL){
				_band2=false;
				for(_i=_lista.begin();_i!=_lista.end();_i++){
					if(_aux->_ady == *_i){
						_band2=true;
					}
				}
				if(_band2==false){
					_cola.push(_aux->_ady);
					_pila.push(VerticeVertice(_VerticeActual, _aux->_ady));
				}
				_aux=_aux->_sig;
			}

		}
	}

	if(_band3==false){
		std::cout << "no hay na entre esos dos " << std::endl;
	}
	return _recorrido;
}




