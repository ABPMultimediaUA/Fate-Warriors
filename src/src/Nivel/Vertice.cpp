#include "Vertice.h"
#include "Arista.h"
#include "Nodo.h"
#include "Grafo.h"
#include <iostream>
#include "Nodo_blackboard.h"

Vertice::Vertice(float _i_posx, float _i_posy,float _i_ancho, float _i_alto, int _i_id, Grafo *_i_grafo_lod1):
_id(_i_id), _posx(_i_posx), _posy(_i_posy), _lod1(_i_grafo_lod1) , _sig(nullptr),
_ady(nullptr), _ancho(_i_ancho), _alto(_i_alto), _blackboard(nullptr), _tipo_vertice(Vertice_Vertice), _peso_tactico(0){
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
	_blackboard->set_lod(_i_cont);
	Arista* _ArisAux = _ady;
	while(_ArisAux != nullptr){
		if(_ArisAux->get_ady()->get_blackboard()->get_lod()>_i_cont){
			
			_ArisAux->get_ady()->set_lod(_i_cont+1);
		}
		
		_ArisAux = _ArisAux->get_sig();
	}
}
bool Vertice::pos2id(float _i_x, float _i_y){
	if(_posx<=_i_x && (_posx+_ancho)>=_i_x && _posy<=_i_y && (_posy+_alto)>=_i_y){
		return true;
	}else{
		return false;
	}
}
void Vertice::pathfinding(float _i_distancia, Arista* _i_arista_aux, int _i_destino){
	//la arista final no se cuenta en las distancias
	if(_id!=_i_destino){
	_i_distancia+=_i_arista_aux->get_peso();
	_peso=_i_distancia+_peso_tactico;
	_i_arista_aux=_ady;//arista del vertice en el que estamos(para no recorrer la del vertice anterior)
		while(_i_arista_aux!= nullptr){
				//std::cout << _ArisAux->_ady->_id << " -> " ;
				int algo=_i_arista_aux->get_ady()->get_peso();
				int algo2=_i_distancia+_i_arista_aux->get_peso();
			if(_i_arista_aux->get_ady()->get_peso()>=(_i_distancia+_i_arista_aux->get_peso())){
				//std::cout <<(int)_id <<" ----------> "<<_i_arista_aux->get_peso()/metro << " -----------------------> " <<(int)_i_arista_aux->get_ady()->get_id() << std::endl;
				_i_arista_aux->get_ady()->pathfinding(_i_distancia+_peso_tactico, _i_arista_aux, _i_destino);
			}
			_i_arista_aux = _i_arista_aux->get_sig();
		}
	}
}
uint8_t Vertice::get_lod(){
	return _blackboard->get_lod();
}
/*void Vertice::inserta_enemigo(NPC* _i_npc){
	for(uint8_t cont=0;cont<maximo_npc;++cont){
		if(_NPC[cont]==nullptr){
			_NPC[cont]=_i_npc;
		}
	}
}
void Vertice::elimina_enemigo(NPC* _i_npc){
	for(uint8_t cont=0;cont<maximo_npc;++cont){
		if(_NPC[cont]==_i_npc){
			_NPC[cont]=nullptr;
		}
	}
}*/
