#include "Grafo.h"
#include "Vertice.h"
#include "Arista.h"
#include <queue>
#include <list>
#include <iostream>
Grafo::Grafo(){
	_h = NULL;
}

Grafo::~Grafo(){
	this->grafo_anular();
}

bool Grafo::grafo_vacio(){
	if(_h==NULL){
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
	while(_aux!=NULL){
		_cont++;
		_aux=_aux->_sig;
	}
	return _cont;
}

Vertice *Grafo::grafo_get_vertice(int _i_id){
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

void Grafo::grafo_inserta_vertice(int _i_id){
	Vertice *_nuevo = new Vertice;
	_nuevo->_id=_i_id;
	_nuevo->_sig=NULL;
	_nuevo->_ady=NULL;

	if(grafo_vacio()){
		_h=_nuevo;
	}
	else{
		Vertice *_aux;
		_aux=_h;
		while(_aux->_sig!=NULL){
			_aux = _aux->_sig;
		}
		_aux->_sig=_nuevo;
	}

}
void Grafo::grafo_inserta_arista_bi(Vertice *_i_origen, Vertice *_i_destino, int _i_peso){
	inserta_arista(_i_origen,_i_destino,_i_peso);
	inserta_arista(_i_destino,_i_origen,_i_peso);
}
void Grafo::inserta_arista(Vertice *_i_origen, Vertice *_i_destino, int _i_peso){
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

void Grafo::grafo_lista_adyacencia(){
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
			while(aux!=NULL){
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

			while(aux!=NULL){
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

	while(_h!=NULL){
		_aux=_h;
		grafo_eliminar_arista(_h,_h->_sig);
		//std::cout<< aux->_id << std::endl;
		_h=_h->_sig;
		//std::cout<< h->_id << std::endl;
		
		delete(_aux);
	}
}


void Grafo::grafo_eliminar_arista(Vertice *_i_origen, Vertice *_i_destino){

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
		grafo_eliminar_arista(_i_destino,_i_origen);
	}
	else
	{
		while(_actual->_ady != NULL){
			if(_actual->_ady==_i_destino){

				_flag=true;
				_anterior->_sig=_actual->_sig;
				delete(_actual);
				std::cout << "Se ha eliminado la arista" << std::endl;
				grafo_eliminar_arista(_i_destino,_i_origen);
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

//TO-DO: devolver la lista de vertices a seguir DONE

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
