#include "Grafo.h"
#include "Vertice.h"
#include "Arista.h"
#include "../Interfaz_Libs/Lib_Math.h"
#include "Nodo_blackboard.h"
#include "../IA/Blackboard.h"
#include "../Personajes/NPC.h"
#include "../Utilidades/Vector.h"
#include "../Interfaz/Motor.h"
#include <iostream>
#include "../Interfaz/EnumTiposColision.h"

Grafo::Grafo(){
	_h = nullptr;
	
}

Grafo::~Grafo(){
	this->grafo_anular();
}

void Grafo::grafo_set_lod(int _i_id){
	//TO DO
	if(_i_id!=0){
		int cont=0;
		/*Vertice * _aux;
		_aux=_h->get_vertice(_i_id);
		while(_aux->get_sig()!=nullptr){
			_aux=_aux->get_sig();
		}*/

		Vertice *_VertAux;
		Arista *_ArisAux;

		_VertAux = _h;

		while(_VertAux != nullptr){
			_ArisAux = _VertAux->get_ady();
			while(_ArisAux != nullptr){
				_ArisAux = _ArisAux->get_sig();
			}
			_VertAux->get_blackboard()->set_lod(5);
			_VertAux = _VertAux->get_sig();
		}
		_VertAux=grafo_get_vertice(_i_id);
		
		_VertAux->set_lod(cont);

		_VertAux->get_blackboard()->set_lod(1);
		//recorrer todos los nodos a partir del dado
		//el pasado y 1 siguiente = 1
		//uno mas al anterior = 2
		//dos mas al siguiente del pasado = 3
		//el resto 4
	}else{
		std::cout<<"ERROR SET_LOD: esta fuera del nivel"<<std::endl;
	}
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
		_aux=_aux->get_sig();
	}
	return _cont;
}

Vertice *Grafo::grafo_get_vertice(int _i_id){
	Vertice *_aux;
	_aux = _h;
	while(_aux!=nullptr){
		if(_aux->get_id() == _i_id){
			return _aux;
		}
		_aux=_aux->get_sig();
		
	}
	return nullptr;
}
int Grafo::grafo_get_id_vertice(float _i_x, float _i_y){
	Vertice *_aux;
	_aux = _h;
	while(_aux!=nullptr){
		if(_aux->pos2id(_i_x,_i_y)){
			return _aux->get_id();
		}
		_aux=_aux->get_sig();
		
	}
	return 0;
}
Vertice* Grafo::grafo_get_vertice(float _i_x, float _i_y){
	Vertice *_aux;
	_aux = _h;
	while(_aux!=nullptr){
		if(_aux->pos2id(_i_x,_i_y)){
			return _aux;
		}
		_aux=_aux->get_sig();
		
	}
	return nullptr;
}
Nodo_blackboard* Grafo::grafo_get_blackboard(float _i_x, float _i_y){
	Vertice *_aux;
	_aux = _h;
	while(_aux!=nullptr){
		if(_aux->pos2id(_i_x,_i_y)){
			return _aux->get_blackboard();
		}
		_aux=_aux->get_sig();
		
	}
	return 0;
}

//PENDIENTE DE PRUEBA
Arista * Grafo::grafo_get_arista(int _i_id){
	Vertice *_VertAux;
	Arista *_ArisAux;

	_VertAux = _h;

	while(_VertAux != nullptr){
		_ArisAux = _VertAux->get_ady();
		while(_ArisAux != nullptr){
			if(_ArisAux->get_id()==_i_id){
				return _ArisAux;
			}
			_ArisAux = _ArisAux->get_sig();
		}
		_VertAux = _VertAux->get_sig();
	}
}
void Grafo::grafo_inserta_vertice(Vertice * _nuevo){

	
	if(grafo_vacio()){
		_h=_nuevo;
		//std::cout << "Vertice insertado"<< _nuevo->get_id() << std::endl;
	}
	else{
		
		Vertice *_aux;
		_aux=_h;
		while(_aux->get_sig()!=nullptr){
			_aux = _aux->get_sig();
		}
		_aux->set_sig(_nuevo);
		//std::cout << "Vertice insertado"<< _nuevo->get_id() << std::endl;
	}
	

}
void Grafo::grafo_crea_arista(int _i_origen, int _i_destino, int _i_id){
	Vertice* _origen=nullptr;
	Vertice* _destino=nullptr;
	Vertice* _aux=_h;
	//std::cout << "Arista"<< _i_origen <<"  "<< _i_destino <<"  "<< _i_id << std::endl;
	while(_aux!=NULL){	
			//bucle para recorrer todos los vertices del grafo
		if(_aux->get_id()==_i_origen){//id del origen encontrada
			_origen=_aux;
		}else if(_aux->get_id()==_i_destino){					//id del destino encontrada
			_destino=_aux;
		}
		_aux=_aux->get_sig();
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
		//std::cout <<_i_origen->get_ancho()/metro << " ANCHO/ALTOFDHSBNFGUYBFDASYFBDASUIVD " <<_i_origen->get_alto()/metro << std::endl;
		_nueva->set_peso(lib_math_distancia_2_puntos(_i_origen->get_coord_x()+(_i_origen->get_ancho()/2),_i_origen->get_coord_y()+(_i_origen->get_alto()/2),_i_destino->get_coord_x()+(_i_destino->get_ancho()/2),_i_destino->get_coord_y()+(_i_destino->get_alto()/2)));
		_nueva->set_sig(nullptr);
		_nueva->set_ady(nullptr);
		_nueva->set_id(_i_id);

		Arista *_aux;

		_aux=_i_origen->get_ady();

		if(_aux==nullptr){
			_i_origen->set_ady(_nueva);
			_nueva->set_ady(_i_destino);
		}
		else{
			while(_aux->get_sig()!=nullptr){
				_aux= _aux->get_sig();
			}
			_aux->set_sig(_nueva);
			_nueva->set_ady(_i_destino);
		}
	}else{
		std::cout << "no se crea arista por nulos Id: "<<_i_id << std::endl;
	}

}

void Grafo::grafo_lista_adyacencia(){
	Vertice *_VertAux;
	Arista *_ArisAux;

	_VertAux = _h;

	while(_VertAux != nullptr){
		std::cout << _VertAux->get_id() << " -> ";
		_ArisAux = _VertAux->get_ady();
		while(_ArisAux != nullptr){
			std::cout << _ArisAux->get_ady()->get_id() << " -> " ;
			_ArisAux = _ArisAux->get_sig();
		}
		_VertAux = _VertAux->get_sig();
		std::cout<<std::endl;
	}
}

void Grafo::grafo_anular(){

	Vertice *_aux;

	while(_h!=nullptr){
		
		_aux=_h;
		if(_h->get_sig()!=nullptr){
			grafo_eliminar_arista(_h,_h->get_sig());
		}
		
		_h=_h->get_sig();
		delete _aux;
	}
}


void Grafo::grafo_eliminar_arista(Vertice *_i_origen, Vertice *_i_destino){
	bool _flag=false;

	Arista *_actual, *_anterior;
	if(_i_origen!=nullptr && _i_destino!=nullptr){
		_actual = _i_origen->get_ady();
		if(_actual==nullptr){
			//std::cout << "Vertices no na" << std::endl;
		}
		else if(_actual->get_ady()==_i_destino){
			_i_origen->set_ady( _actual->get_sig());
			//std::cout << "Se ha eliminado la arista" << _actual->get_id() << std::endl;
			delete(_actual);
			grafo_eliminar_arista(_i_destino,_i_origen);
		}
		else
		{
			while(_actual->get_ady() != nullptr){
				if(_actual->get_ady()==_i_destino){

					_flag=true;
					_anterior->set_sig(_actual->get_sig());
					//std::cout << "Se ha eliminado la arista" << _actual->get_id() << std::endl;
					delete(_actual);
					
					grafo_eliminar_arista(_i_destino,_i_origen);
					break;
				}
				if(_actual->get_sig() != nullptr){
					_anterior=_actual;
					_actual=_actual->get_sig();
				}else{
					break;
				}
			}
			if(!_flag)
			{
				//std::cout << "Vertices no conectados Id_origen: " <<_i_origen->get_id()<<" Id_destino:" << _i_destino->get_id()<< std::endl;
			}

		}
	}else{
		std::cout << "Vertices no na por nulos" << std::endl;
	}

}

uint16_t Grafo::grafo_pathfinding(float &_i_xorigen, float &_i_yorigen, float _i_xdestino, float _i_ydestino){
	Vertice* origen;
	Vertice* destino;
	origen=grafo_get_vertice(_i_xorigen, _i_yorigen);
	destino=grafo_get_vertice(_i_xdestino, _i_ydestino);
	//comprobar que esta dentro del nivel
	if(origen==nullptr||destino==nullptr){
		float angulo=lib_math_angulo_2_puntos(_i_xorigen,_i_yorigen, _i_xdestino, _i_ydestino);
		return angulo;			//MANU WAS HERE BOIII
	}
	if(origen->get_lod()<=2&&destino->get_lod()<=2){
		return grafo_pathfindinglod1(_i_xorigen,_i_yorigen, _i_xdestino, _i_ydestino, origen, destino->get_id());
	}else{
		
		grafo_pathfindinglod2(_i_xorigen,_i_yorigen, _i_xdestino, _i_ydestino, origen, destino);
		return 362;
	}
}

void Grafo::set_peso_tactico_id(float _i_peso_tactico, int _i_id, float _i_x, float _i_y){
	Vertice* verticeaux = grafo_get_vertice(_i_id)->get_lod1()->grafo_get_vertice(_i_x,_i_y);
	verticeaux->set_peso_tactico(_i_peso_tactico);
}
void Grafo::set_peso_tactico_x_y(float _i_peso_tactico, float _i_x, float _i_y){
	Vertice* verticeaux = grafo_get_vertice(_i_x,_i_y)->get_lod1()->grafo_get_vertice(_i_x,_i_y);
	verticeaux->set_peso_tactico(_i_peso_tactico);
}
void Grafo::abrir_cerrar_pasillo(uint16_t peso, uint16_t _id){
	Vertice* verticeaux = grafo_get_vertice(_id);
	u_int8_t id=verticeaux->get_id();
	verticeaux->set_peso_tactico(peso);
	Arista* arista_aux=verticeaux->get_ady();
	uint16_t aux;
	bool flag=false;
	while(arista_aux!=nullptr){
		verticeaux=arista_aux->get_ady()->get_lod1()->get_h();
		while(verticeaux!=nullptr && !flag){
			aux=id;
			while(aux<4000){
				aux+=1000;
				if(aux==verticeaux->get_id()){					
					verticeaux->set_peso_tactico(peso);
					flag=true;//cuando se activa el flag se terminan los bucles y no vuelve a buscar el vertice destino
				}
				
			}
			aux=0;
			verticeaux=verticeaux->get_sig();
		}
		arista_aux=arista_aux->get_sig();
	}
}
void Grafo::grafo_pathfindinglod2(float &_i_xorigen, float &_i_yorigen, float _i_xdestino, float _i_ydestino, Vertice* vertice_origen, Vertice* vertice_destino){
	Vertice* verticeaux=_h;
	float distancia;
	Arista* arista_aux;
	int id_aux;
	bool flag = false;
	double algo=0;
		while(verticeaux!=nullptr){//sacar vertice origen y destino y poner todos los valores iniciales
		
			verticeaux->set_peso(60000);
			verticeaux->set_id_arista(0);
			verticeaux=verticeaux->get_sig();
		}

		distancia=0;
		arista_aux = vertice_destino->get_ady();
		while(arista_aux!= nullptr){

			if(arista_aux->get_ady()->get_peso()>=(distancia+arista_aux->get_peso())){
				
				arista_aux->get_ady()->pathfinding(distancia, arista_aux, vertice_destino->get_id());
			}
			arista_aux = arista_aux->get_sig();
		}verticeaux=_h;
		while(verticeaux!=nullptr){
			
			std::cout<<"añlskdjf  "<<verticeaux->get_id()<<"  "<<verticeaux->get_peso()<<std::endl;
			verticeaux=verticeaux->get_sig();
		}
		vertice_origen->set_peso(60000);
		//vuelta desde destino hacia origen
		verticeaux=vertice_origen;
		arista_aux=verticeaux->get_ady();
		id_aux=0;
		distancia=60000;
		while(arista_aux!= nullptr){//eleccion de la ariste a la cual ir
			if(arista_aux->get_ady()->get_peso()<distancia){
				id_aux=arista_aux->get_ady()->get_id();
				distancia=arista_aux->get_ady()->get_peso();
			}
			arista_aux = arista_aux->get_sig();
		}
		arista_aux=verticeaux->get_ady();
		while(arista_aux!= nullptr){//este while es para evitar llamar a la fucion get_vertice la cual recorre todo el grafo
		//se busca el vertice al que debe ir desde el origen
			if(arista_aux->get_ady()->get_id()==id_aux){
				verticeaux=arista_aux->get_ady();
				break;
			}
			arista_aux = arista_aux->get_sig();
		}
		_i_xorigen=verticeaux->get_lod1()->get_h()->get_coord_x();
		_i_yorigen=verticeaux->get_lod1()->get_h()->get_coord_y();
	/*}/*else{
		std::cout << "ERROR PATHFINDINGLOD2: no hay camino entre los dos vertices " << std::endl;
	}*/
}
unsigned short Grafo::grafo_pathfindinglod1(float _i_xorigen, float _i_yorigen, float _i_xdestino, float _i_ydestino, Vertice* origen, int destino){
	
	//TO DO comprobacion de la colision a partir del "raytracing"
	unsigned short angulo;

	Motor* motor = Motor::Motor_GetInstance();
	Vector3 inicio(_i_xorigen,2,_i_yorigen);
	Vector3 fin(_i_xdestino,2,_i_ydestino);
	
	if(motor->x_ve_a_y(inicio,fin, ray_colisiona_con)){
		angulo=lib_math_angulo_2_puntos(_i_xorigen,_i_yorigen,_i_xdestino,_i_ydestino);

		std::cout << "p:" << angulo << std::endl;
		return angulo;
	}
	

	int id_aux, aux;
	float distancia,distancia2,direccion;
	bool flag=false;
	Vertice* verticeaux;
	Vertice* vertice_origen;
	Vertice* vertice_destino;
	Arista* arista_aux;
	

	
	if(origen->get_id()!=destino){
		verticeaux=origen->get_lod1()->get_h();
		vertice_origen=verticeaux;
		vertice_destino=verticeaux;
		distancia=lib_math_distancia_2_puntos(_i_xorigen,_i_yorigen,verticeaux->get_coord_x(),verticeaux->get_coord_y())+verticeaux->get_peso_tactico();
		while(verticeaux!=nullptr){
			aux=destino;//igualar cada vez a la id del pasillo/nodo adyacente para despues ir sumandole 1000 en 1000 para buscar el nodo
			if(distancia>lib_math_distancia_2_puntos(_i_xorigen,_i_yorigen,verticeaux->get_coord_x(),verticeaux->get_coord_y())+verticeaux->get_peso_tactico()){
				vertice_origen=verticeaux;
				distancia=lib_math_distancia_2_puntos(_i_xorigen,_i_yorigen,verticeaux->get_coord_x(),verticeaux->get_coord_y())+verticeaux->get_peso_tactico();
			}
			
			while(aux<4000 && !flag){
				aux+=1000;
				if(aux==verticeaux->get_id()){
					
					vertice_destino=verticeaux;
					flag=true;//cuando se activa el flag se terminan los bucles y no vuelve a buscar el vertice destino
				}
				
			}
			verticeaux->set_peso(60000);
			verticeaux->set_id_arista(0);
			verticeaux=verticeaux->get_sig();
		}
		if(vertice_origen->get_id()==vertice_destino->get_id()){
			aux=vertice_origen->get_id();
			aux-=1000;
			int angulo=0;
			while(aux>1000){
				angulo+=90;

				aux-=1000;
			}
			return angulo;
		}
		
	}
	
	//se puede mirar (si la id es 1000 hacia la derecha, 2000 arriba etc.), poner mas nodos 
	//en las intersecciones con el pasillo de manera que cuando llegue al nodo como nodo origen que haga el movimiento por la id

	if(!flag){
		verticeaux=origen->get_lod1()->get_h();
		vertice_origen=verticeaux;
		vertice_destino=verticeaux;
		distancia=lib_math_distancia_2_puntos(_i_xorigen,_i_yorigen,verticeaux->get_coord_x(),verticeaux->get_coord_y());
		distancia2=lib_math_distancia_2_puntos(_i_xdestino,_i_ydestino,verticeaux->get_coord_x(),verticeaux->get_coord_y());
		
		while(verticeaux!=nullptr){//sacar vertice origen y destino y poner todos los valores iniciales
			if(distancia>lib_math_distancia_2_puntos(_i_xorigen,_i_yorigen,verticeaux->get_coord_x(),verticeaux->get_coord_y())){
				vertice_origen=verticeaux;
				distancia=lib_math_distancia_2_puntos(_i_xorigen,_i_yorigen,verticeaux->get_coord_x(),verticeaux->get_coord_y());
			}
			if(distancia2>lib_math_distancia_2_puntos(_i_xdestino,_i_ydestino,verticeaux->get_coord_x(),verticeaux->get_coord_y())){
				vertice_destino=verticeaux;
				distancia2=lib_math_distancia_2_puntos(_i_xdestino,_i_ydestino,verticeaux->get_coord_x(),verticeaux->get_coord_y());
			}
			verticeaux->set_peso(60000);
			verticeaux->set_id_arista(0);
			verticeaux=verticeaux->get_sig();
		}
	}
	if(vertice_origen->get_id()==vertice_destino->get_id()){//caso de que no se encuentren los nodos
		float angulo=lib_math_angulo_2_puntos(_i_xorigen,_i_yorigen, _i_xdestino, _i_ydestino);
		
		return angulo;
	}
	else{
		//recorrido del grafo
		distancia=0;
		arista_aux = vertice_origen->get_ady();
		while(arista_aux!= nullptr){

			if(arista_aux->get_ady()->get_peso()>=(distancia+arista_aux->get_peso())){
				
				arista_aux->get_ady()->pathfinding(distancia, arista_aux, vertice_destino->get_id());
			}
			arista_aux = arista_aux->get_sig();
		}

		//cout de pesos
		/*verticeaux=origen->_lod1->_h;
		while(verticeaux!=nullptr){//sacar vertice origen y destino y poner todos los valores iniciales
			verticeaux=verticeaux->get_sig();
		}*/


		vertice_origen->set_peso(0);
		//vuelta desde destino hacia origen
		verticeaux=vertice_destino;
		id_aux=0;
		while(verticeaux->get_id()!=vertice_origen->get_id()){
			arista_aux=verticeaux->get_ady();
			id_aux=arista_aux->get_ady()->get_id();
			distancia=arista_aux->get_ady()->get_peso();
			while(arista_aux!= nullptr){//eleccion de la ariste a la cual ir
				
				if(arista_aux->get_ady()->get_peso()<distancia){
					id_aux=arista_aux->get_ady()->get_id();
					distancia=arista_aux->get_ady()->get_peso();
				}
				arista_aux = arista_aux->get_sig();
			}
			arista_aux=verticeaux->get_ady();
			while(arista_aux!= nullptr){//este while es para evitar llamar a la fucion get_vertice la cual recorre todo el grafo
			//se busca el vertice origen y se le da valor a la id_arista de ese vertice
			
			if(arista_aux->get_ady()->get_id()==id_aux){
					verticeaux=arista_aux->get_ady();
					verticeaux->set_id_arista(arista_aux->get_id());
					break;
				}
				arista_aux = arista_aux->get_sig();
			}
		}
		arista_aux=verticeaux->get_ady();
		while(arista_aux!= nullptr){//este while es para evitar llamar a la fucion get_vertice la cual recorre todo el grafo
		//se busca el vertice al que debe ir desde el origen
			if(arista_aux->get_id()==-verticeaux->get_id_arista()){
				verticeaux=arista_aux->get_ady();
				break;
			}
			arista_aux = arista_aux->get_sig();
		}
		
		//360 y 0 es lo mismo, derechas
		angulo=lib_math_angulo_2_puntos(_i_xorigen,_i_yorigen, verticeaux->get_coord_x(), verticeaux->get_coord_y());
		//std::cout<<"angulo:" << angulo << "x_o:"<< _i_xorigen/metro << "y_o:"<< _i_yorigen/metro << "x_aux:"<< verticeaux->get_coord_x()/metro << "y_aux:"<<  verticeaux->get_coord_y()/metro << std::endl;
		return angulo;
		//return lib_math_angulo_2_puntos(verticeaux->get_coord_x(),verticeaux->get_coord_y(),_i_xorigen,_i_yorigen);
	}



	return 361;
}
void Grafo::actualiza_NPC(){
	Vertice* ver_aux=_h;
	Nodo_blackboard* black_aux;
	uint8_t cont=0;
	NPC* npc_aux;
	while(ver_aux!=nullptr){
		black_aux=ver_aux->get_blackboard();
		cont= black_aux->get_maximo_npc();
		while(cont){
			--cont;
			npc_aux=black_aux->get_NPC(cont);
			if(npc_aux!=nullptr){
				if(!ver_aux->pos2id(npc_aux->getX(),npc_aux->getY())){
					black_aux->elimina_NPC(npc_aux);
					grafo_inserta_NPC(npc_aux);
				}
			}
		}
		ver_aux=ver_aux->get_sig();
	}
}
void Grafo::grafo_inserta_NPC(NPC* _i_npc){//si el npc se sale del nivel se pierde
	Vertice * vertice_aux=grafo_get_vertice(_i_npc->getX(),_i_npc->getZ());
	if(vertice_aux!=nullptr){
		Nodo_blackboard* black_aux=grafo_get_vertice(_i_npc->getX(),_i_npc->getZ())->get_blackboard();
		black_aux->inserta_NPC(_i_npc);
		_i_npc->get_blackboard()->set_nodo_blackboard(black_aux);
	}else{
		std::cout<<"ERROR NPC_POSICION: npc fuera del mapa"<<std::endl;
		_i_npc->setPositionXZ(grafo_get_vertice(1)->get_coord_x()+1*metro,grafo_get_vertice(1)->get_coord_y()+1*metro);
	}
}
void Grafo::grafo_get_numero_posiciones_spawn_enemigos(uint16_t &_i_n_posiciones){
	Vertice* vert_aux=_h;
	Vertice* vert_aux_interno=nullptr;
	_i_n_posiciones=0;
	while(vert_aux!=nullptr){
		if(vert_aux->get_tipo_vertice()==Vertice_Nodo){
			vert_aux_interno=vert_aux->get_lod1()->get_h();
			while(vert_aux_interno!=nullptr){
				++_i_n_posiciones;
				vert_aux_interno=vert_aux_interno->get_sig();
			}
		}
		vert_aux=vert_aux->get_sig();
	}
}
void Grafo::grafo_get_posiciones_spawn_enemigos( float** _posiciones){
	Vertice* vert_aux=_h;
	Vertice* vert_aux_interno=nullptr;
	uint16_t cont=0;
	while(vert_aux!=nullptr){
		if(vert_aux->get_tipo_vertice()==Vertice_Nodo){
			vert_aux_interno=vert_aux->get_lod1()->get_h();
			while(vert_aux_interno!=nullptr){
				//std::cout<<"_id grande: "<<vert_aux->get_id()<<" id: "<<vert_aux_interno->get_id()<<" X: "<<vert_aux_interno->get_coord_x()/metro<<" Y: "<<vert_aux_interno->get_coord_y()/metro<<std::endl;
				_posiciones[cont][0]=vert_aux_interno->get_coord_x();
				_posiciones[cont][1]=vert_aux_interno->get_coord_y();
				vert_aux_interno=vert_aux_interno->get_sig();
				++cont;
			}
		}
		vert_aux=vert_aux->get_sig();
	}
}
void Grafo::Update(){

	actualiza_NPC();
}
void Grafo::set_tipo_zona(uint8_t _id, Enum_zonas _i_zona){
	Vertice* vert_aux=nullptr;
	vert_aux=grafo_get_vertice(_id);
	if(vert_aux==nullptr){
		std::cout<<"No existe vertice para poner el tipo de zona"<<std::endl;
	}
	vert_aux->set_tipo(_i_zona);
}
Enum_zonas Grafo::get_tipo_zona(uint8_t _id, Enum_zonas _i_zona){
	Vertice* vert_aux=nullptr;
	vert_aux=grafo_get_vertice(_id);
	if(vert_aux==nullptr){
		std::cout<<"No existe vertice para coger el tipo de zona"<<std::endl;
	}
	return vert_aux->get_tipo();
}
NPC** Grafo::get_array_NPC(uint8_t _id){
	Vertice* vert_aux=nullptr;
	vert_aux=grafo_get_vertice(_id);
	if(vert_aux==nullptr){
		std::cout<<"No existe vertice para coger el array de NPC"<<std::endl;
	}
	return vert_aux->get_blackboard()->get_array_NPC();
}