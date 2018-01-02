#include "Vertice.h"
#include "Arista.h"
#include "Nodo.h"
#include "Grafo.h"
#include <iostream>
#include "Nodo_blackboard.h"

Vertice::Vertice(float _i_posx, float _i_posy,float _i_ancho, float _i_alto, int _i_id, Grafo *_i_grafo_lod1):
_id(_i_id), _posx(_i_posx), _posy(_i_posy), _lod1(_i_grafo_lod1) , _sig(nullptr),
_ady(nullptr), _ancho(_i_ancho), _alto(_i_alto), _blackboard(nullptr){

}

Vertice::~Vertice(){
	delete _lod1;
	_sig = nullptr;
	_ady = nullptr;
	_lod1 = nullptr; //grafo level of detail
}



void Vertice::set_lod(unsigned short _i_cont){
	if(_i_cont>4){
		_i_cont=4;
	}
	if(Nodo * n = dynamic_cast<Nodo*>(this)){
		n->_blackboard->set_lod(_i_cont);
	}
	_lod=_i_cont;
	Arista* _ArisAux = _ady;
	while(_ArisAux != nullptr){//recorrer nivel 1
		if(_ArisAux->_ady->_lod>_i_cont){
			
			_ArisAux->_ady->set_lod(_i_cont+1);
		}
		
		_ArisAux = _ArisAux->_sig;
	}
}
bool Vertice::pos2id(float _i_x, float _i_y){
	//std::cout<<_id<<"   "<<_posx <<"  "<<_i_x <<std::endl;
	if(_posx<_i_x && (_posx+_ancho)>_i_x && _posy<_i_y && (_posy+_alto)>_i_y){
		return true;
	}else{
		return false;
	}
}
void Vertice::pathfinding(float _i_distancia, Arista* _i_arista_aux, int _i_destino){
	//la arista final no se cuenta en las distancias
	if(_id!=_i_destino){
	_i_distancia+=_i_arista_aux->_peso;
	_peso=_i_distancia;
	_i_arista_aux=_ady;//arista del vertice en el que estamos(para no recorrer la del vertice anterior)
		while(_i_arista_aux!= nullptr){
				//std::cout << _ArisAux->_ady->_id << " -> " ;
			if(_i_arista_aux->_ady->_peso>=(_i_distancia+_i_arista_aux->_peso)){
				_i_arista_aux->_ady->pathfinding(_i_distancia, _i_arista_aux, _i_destino);
			}
			_i_arista_aux = _i_arista_aux->_sig;
		}
	}
}
u_int8_t Vertice::get_lod(){
	return _blackboard->get_lod();
}
/*void Vertice::inserta_enemigo(NPC* _i_npc){
	for(u_int8_t cont=0;cont<maximo_npc;++cont){
		if(_NPC[cont]==nullptr){
			_NPC[cont]=_i_npc;
		}
	}
}
void Vertice::elimina_enemigo(NPC* _i_npc){
	for(u_int8_t cont=0;cont<maximo_npc;++cont){
		if(_NPC[cont]==_i_npc){
			_NPC[cont]=nullptr;
		}
	}
}*/
