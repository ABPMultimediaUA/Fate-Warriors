#include "Grafo.h"
#include "Vertice.h"
#include "Arista.h"
#include "../Interfaz_Libs/Lib_Math.h"
#include <queue>
#include <list>
#include <iostream>
Grafo::Grafo(){
	_h = nullptr;
}

Grafo::~Grafo(){
	this->grafo_anular();
}

void Grafo::grafo_set_lod(int _i_id){
	//TO DO
	int cont=0;
	/*Vertice * _aux;
	_aux=_h->get_vertice(_i_id);
	while(_aux->_sig!=nullptr){
		_aux=_aux->_sig;
	}*/

	Vertice *_VertAux;
	Arista *_ArisAux;

	_VertAux = _h;

	while(_VertAux != nullptr){
		//std::cout << _VertAux->_id << " -> ";
		_ArisAux = _VertAux->_ady;
		while(_ArisAux != nullptr){
			//std::cout << _ArisAux->_ady->_id << " -> " ;
			_ArisAux = _ArisAux->_sig;
		}
		_VertAux->_lod=5;
		_VertAux = _VertAux->_sig;
		//std::cout<<std::endl;
	}
	_VertAux=grafo_get_vertice(_i_id);
	
	_VertAux->set_lod(cont);

	_VertAux->_lod=1;
	//recorrer todos los nodos a partir del dado
	//el pasado y 1 siguiente = 1
	//uno mas al anterior = 2
	//dos mas al siguiente del pasado = 3
	//el resto 4
}

bool Grafo::grafo_vacio(){
	if(_h==nullptr){
		return true;
	}
	else{
		return false;
	}
}

int Grafo::grafo_tamano(){
	int _cont=0;
	Vertice *_aux;
	_aux = _h;
	while(_aux!=nullptr){
		_cont++;
		_aux=_aux->_sig;
	}
	return _cont;
}

Vertice *Grafo::grafo_get_vertice(int _i_id){
	Vertice *_aux;
	_aux = _h;
	while(_aux!=nullptr){
		if(_aux->_id == _i_id){
			return _aux;
		}
		_aux=_aux->_sig;
		
	}
	return nullptr;
}
int Grafo::grafo_get_id_vertice(float _i_x, float _i_y){
	Vertice *_aux;
	_aux = _h;
	while(_aux!=nullptr){
		if(_aux->pos2id(_i_x,_i_y)){
			return _aux->_id;
		}
		_aux=_aux->_sig;
		
	}
	return 0;
}

//PENDIENTE DE PRUEBA
Arista * Grafo::grafo_get_arista(int _i_id){
	Vertice *_VertAux;
	Arista *_ArisAux;

	_VertAux = _h;

	while(_VertAux != nullptr){
		_ArisAux = _VertAux->_ady;
		while(_ArisAux != nullptr){
			if(_ArisAux->_id==_i_id){
				return _ArisAux;
			}
			_ArisAux = _ArisAux->_sig;
		}
		_VertAux = _VertAux->_sig;
		std::cout<<std::endl;
	}
}
void Grafo::grafo_inserta_vertice(Vertice * _nuevo){

	
	if(grafo_vacio()){
		_h=_nuevo;
		
	}
	else{
		
		Vertice *_aux;
		_aux=_h;
		while(_aux->_sig!=nullptr){
			_aux = _aux->_sig;
		}
		_aux->_sig=_nuevo;
	}
	

}
void Grafo::grafo_crea_arista(int _i_origen, int _i_destino, int _i_id){
	Vertice* _origen=nullptr;
	Vertice* _destino=nullptr;
	Vertice* _aux=_h;
	while(_aux!=NULL){	
			//bucle para recorrer todos los vertices del grafo
		if(_aux->_id==_i_origen){//id del origen encontrada
			_origen=_aux;
		}else if(_aux->_id==_i_destino){					//id del destino encontrada
			_destino=_aux;
		}
		_aux=_aux->_sig;
	}
	grafo_inserta_arista_bi(_origen, _destino, _i_id);
}
void Grafo::grafo_inserta_arista_bi(Vertice *_i_origen, Vertice *_i_destino, int _i_id){
	inserta_arista(_i_origen,_i_destino,_i_id);
	inserta_arista(_i_destino,_i_origen,-_i_id);
}
void Grafo::inserta_arista(Vertice *_i_origen, Vertice *_i_destino, int _i_id){
	if(_i_origen!=nullptr && _i_destino!=nullptr){

		
		Arista *_nueva = new Arista;

		_nueva->_peso=lib_math_distancia_2_puntos(_i_origen->_posx,_i_origen->_posy,_i_destino->_posx,_i_destino->_posy);
		_nueva->_sig=nullptr;
		_nueva->_ady=nullptr;
		_nueva->_id=_i_id;

		Arista *_aux;

		_aux=_i_origen->_ady;

		if(_aux==nullptr){
			_i_origen->_ady=_nueva;
			_nueva->_ady=_i_destino;
		}
		else{
			while(_aux->_sig!=nullptr){
				_aux= _aux->_sig;
			}
			_aux->_sig=_nueva;
			_nueva->_ady=_i_destino;
		}
	}else{
		std::cout << "no se crea arista por nulos" << std::endl;
	}

}

void Grafo::grafo_lista_adyacencia(){
	Vertice *_VertAux;
	Arista *_ArisAux;

	_VertAux = _h;

	while(_VertAux != nullptr){
		std::cout << _VertAux->_id << " -> ";
		_ArisAux = _VertAux->_ady;
		while(_ArisAux != nullptr){
			std::cout << _ArisAux->_ady->_id << " -> " ;
			_ArisAux = _ArisAux->_sig;
		}
		_VertAux = _VertAux->_sig;
		std::cout<<std::endl;
	}
}
/*void Grafo::RecorridoAnchura(Vertice *_origen){
	
	int band, band2;

	Vertice *actual;

	std::queue<Vertice*> cola;
	std::list<Vertice*> lista;
	std::list<Vertice*>::iterator i;

	cola.push(_origen);
	while(!cola.empty()){
		
		band=0;
		actual=cola.front();
		cola.pop();

		for(i=lista.begin();i!=lista.end();i++){
			if(*i==actual){
				band=1;
				break;

			}
		}
		if(band==0){
			std::cout << actual->nombre << ", ";
			lista.push_back(actual);

			Arista *aux;
			aux = actual->_ady;
			while(aux!=nullptr){
				band2=0;
				
				for(i=lista.begin();i!=lista.end();i++){
					
					if(aux->_ady == *i){
						
						band2=1;
					}
				}
				if(band2==0){
					
					cola.push(aux->_ady);
				}
				aux=aux->_sig;
			}
		}
	}
	std::cout << std::endl;
}

void Grafo::RecorridoProfundidad(Vertice *_origen){

	Vertice *actual;
	std::stack<Vertice*> pila;
	std::list<Vertice*> lista;
	std::list<Vertice*>::iterator i;
	pila.push(_origen);
	int band=0,band2=0;

	while(!pila.empty()){
		band=0;
		actual=pila.top();
		pila.pop();
		for(i=lista.begin(); i!=lista.end();i++){
			if(*i==actual){
				band=1;
			}
		}
		if(band==0){
			std::cout << actual->nombre<<", ";
			lista.push_back(actual);

			Arista *aux;
			aux=actual->_ady;

			while(aux!=nullptr){
				band2=0;
				for(i=lista.begin();i!=lista.end();i++){
					if(*i==aux->_ady){
						band2=1;
					}
				}
				if(band2==0){
					pila.push(aux->_ady);
				}
				aux=aux->_sig;
			}
		}
	}
	std::cout << std::endl;

}*/

void Grafo::grafo_anular(){

	Vertice *_aux;

	while(_h!=nullptr){
		_aux=_h;
		grafo_eliminar_arista(_h,_h->_sig);
		
		_h=_h->_sig;
		//std::cout<< h->_id << std::endl;
		delete _aux;
	}
}


void Grafo::grafo_eliminar_arista(Vertice *_i_origen, Vertice *_i_destino){

	bool _flag=false;

	Arista *_actual, *_anterior;
	if(_i_origen!=nullptr && _i_destino!=nullptr){
		_actual = _i_origen->_ady;
		if(_actual==nullptr){
			std::cout << "Vertices no na" << std::endl;
		}
		else if(_actual->_ady==_i_destino){
			_i_origen->_ady = _actual->_sig;
			delete(_actual);
			grafo_eliminar_arista(_i_destino,_i_origen);
		}
		else
		{
			while(_actual->_ady != nullptr){
				if(_actual->_ady==_i_destino){

					_flag=true;
					_anterior->_sig=_actual->_sig;
					std::cout << "Se ha eliminado la arista" << _actual->_id << std::endl;
					delete(_actual);
					
					grafo_eliminar_arista(_i_destino,_i_origen);
					break;
				}
				if(_actual->_sig != nullptr){
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
	}else{
		std::cout << "Vertices no na por nulos" << std::endl;
	}

}

//TO-DO: rehacerlo con posiciones x e y y ANCHO Y ALTO

std::stack<Vertice*> Grafo::grafo_camino_corto_l2(Vertice *_i_origen, Vertice *_i_destino){

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

			while(_aux!=nullptr){
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
unsigned short Grafo::grafo_pathfindinglod1(float _i_xorigen, float _i_yorigen, float _i_xdestino, float _i_ydestino){
	//TO DO comprobacion de la colision a partir del "raytracing"
	
	int origen,destino,id_aux;
	float distancia,distancia2,direccion;
	Vertice* verticeaux;
	Vertice* vertice_origen;
	Vertice* vertice_destino;
	Arista* arista_aux;
	origen=grafo_get_id_vertice(_i_xorigen, _i_yorigen);
	destino=grafo_get_id_vertice(_i_xdestino, _i_ydestino);
	//se puede mirar (si la id es 1000 hacia la iquierda, 2000 derecha etc.), poner mas nodos 
	//en las intersecciones con el pasillo de manera que cuando llegue al noco como nodo origen que haga el movimiento por la id

	
	verticeaux=grafo_get_vertice(origen)->_lod1->_h;
	distancia=lib_math_distancia_2_puntos(_i_xorigen,_i_yorigen,verticeaux->_posx,verticeaux->_posy);
	distancia2=lib_math_distancia_2_puntos(_i_xdestino,_i_ydestino,verticeaux->_posx,verticeaux->_posy);
	
	while(verticeaux!=nullptr){//sacar vertice origen y destino y poner todos los valores iniciales
	//std::cout << "while1" <<std::endl;
		if(distancia>lib_math_distancia_2_puntos(_i_xorigen,_i_yorigen,verticeaux->_posx,verticeaux->_posy)){
			vertice_origen=verticeaux;
			distancia=lib_math_distancia_2_puntos(_i_xorigen,_i_yorigen,verticeaux->_posx,verticeaux->_posy);
		}
		if(distancia2>lib_math_distancia_2_puntos(_i_xdestino,_i_ydestino,verticeaux->_posx,verticeaux->_posy)){
			vertice_destino=verticeaux;
			distancia2=lib_math_distancia_2_puntos(_i_xdestino,_i_ydestino,verticeaux->_posx,verticeaux->_posy);
		}
		verticeaux->_peso=10000;
		verticeaux->_id_arista=0;
		verticeaux=verticeaux->_sig;
	}
	if(vertice_origen->_id==vertice_destino->_id){//caso de que no se encuentren los nodos
		return 361;
	}
	else{//recorrido del grafo
		distancia=0;
		arista_aux = vertice_origen->_ady;
		while(arista_aux!= nullptr){std::cout << "while2"<< arista_aux->_ady->_id<<"  "<<vertice_origen->_id<<"   "<< distancia+arista_aux->_peso <<std::endl;
			if(arista_aux->_ady->_peso>=(distancia+arista_aux->_peso)){
				arista_aux->_ady->pathfinding(distancia, arista_aux, vertice_destino->_id);
			}
			arista_aux = arista_aux->_sig;
		}
		vertice_origen->_peso=0;
		verticeaux=grafo_get_vertice(origen)->_lod1->_h;
		//vuelta desde destino hacia origen
		verticeaux=vertice_destino;
		id_aux=0;
		while(verticeaux->_id!=vertice_origen->_id){std::cout << "while3    "<<verticeaux->_id <<std::endl;
			arista_aux=verticeaux->_ady;
			id_aux=arista_aux->_ady->_id;
			distancia=arista_aux->_ady->_peso-1;
			while(arista_aux!= nullptr){//eleccion de la ariste a la cual ir
				std::cout << "while4     "<<distancia<<"   "<<arista_aux->_ady->_id<< "   "  <<arista_aux->_ady->_peso<<std::endl;
				if(arista_aux->_ady->_peso<distancia){
					
					id_aux=arista_aux->_ady->_id;
					distancia=arista_aux->_ady->_peso;
				}
				arista_aux = arista_aux->_sig;
			}
			arista_aux=verticeaux->_ady;
			while(arista_aux!= nullptr){//este while es para evitar llamar a la fucion get_vertice la cual recorre todo el grafo
			//se busca el vertice origen y se le da valor a la id_arista de ese vertice
			std::cout << "while5" <<std::endl;
				if(arista_aux->_ady->_id==id_aux){
					verticeaux=arista_aux->_ady;
					verticeaux->_id_arista=arista_aux->_id;
					break;
				}
				arista_aux = arista_aux->_sig;
			}
		}
		arista_aux=verticeaux->_ady;
		while(arista_aux!= nullptr){//este while es para evitar llamar a la fucion get_vertice la cual recorre todo el grafo
		//se busca el vertice al que debe ir desde el origen
		std::cout<<arista_aux->_id<<"      " <<verticeaux->_id_arista<<std::endl;
			if(arista_aux->_id==-verticeaux->_id_arista){
				std::cout<<"_id vertice final" <<verticeaux->_id<<std::endl;
				verticeaux=arista_aux->_ady;
				break;
			}std::cout << "while6" <<std::endl;
			arista_aux = arista_aux->_sig;
		}
		std::cout<<"_id vertice final" <<verticeaux->_posx<<"   "<<verticeaux->_posy<<"   "<<_i_xorigen<<"  "<<_i_yorigen<<std::endl;
		//return lib_math_angulo_2_puntos(_i_xorigen,_i_yorigen, verticeaux->_posx, verticeaux->_posy);
		return lib_math_angulo_2_puntos(_i_xorigen,_i_yorigen,verticeaux->_posx,verticeaux->_posy);
	}





	return 361;
}