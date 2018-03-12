#include "Interfaz_ME.h"
#include "TMooseEngine.h"
#include "TModelado.h"
#include "TTransform.h"
#include "TNodo.h"
#include "TCamara.h"
#include "TLuz.h"
#include "iNodoModelado.h"
#include "iNodoCamara.h"
#include "iNodoLuz.h"
#include "SFML/Graphics.hpp"
#include <cmath>
#include "../../Personajes/Interpolacion.h"
#include "../../Objeto.h"
#include "../../Personajes/Player.h"
#include "../../Personajes/NPC.h"
#include "../../Puerta.h"
#include "../../Interruptor.h"
#include "DebugDraw.h"
#include "EnumTiposColision.h"
#include "../../Puerta_Pincho.h"
#include "Objeto_ME.h"


Interfaz_ME* Interfaz_ME::_instancia = 0;

Interfaz_ME* Interfaz_ME::get_instancia(uint16_t width, uint16_t height){
    if(_instancia == 0){
        _instancia= new Interfaz_ME(width, height);
    }
    return _instancia;
}

Interfaz_ME::Interfaz_ME(uint16_t width, uint16_t height){
    configuracion_ME(width, height, false, false);
	rayOrigen = new Vector3(0,0,0);
	rayDestino = new Vector3(0,0,0);
}

Interfaz_ME::~Interfaz_ME(){
    for(uint16_t i=0; i<lista_i_nodo.size();i++){
        delete(lista_i_nodo[i]);
    }
}

void Interfaz_ME::configuracion_ME(uint16_t width, uint16_t height, bool fullscreen, bool v_sync){
    motor = TMooseEngine::get_instancia();
}

void Interfaz_ME::configuracion_bullet(){
    collisionConfiguration = new btDefaultCollisionConfiguration();
	broadPhase = new btDbvtBroadphase(new btHashedOverlappingPairCache());
	collisionDispatcher = new btCollisionDispatcher(collisionConfiguration);
	constraintSolver = new btSequentialImpulseConstraintSolver();

	world = new btDiscreteDynamicsWorld(collisionDispatcher, broadPhase, constraintSolver, collisionConfiguration);

	fileLoader = new btBulletWorldImporter(world);
	fileLoader->loadFile("models/MapaColision/ColisionesNivel1.bullet");
	btCollisionShape* escenario; 
	btRigidBody* esta_vez_si;
	int num = fileLoader->getNumRigidBodies();
	
	btTransform cubeTransform;
	cubeTransform.setIdentity();
	//cubeTransform.setOrigin(btVector3(x,y,z));
	btDefaultMotionState *cubeMotionState = new btDefaultMotionState(cubeTransform);
	for(short i = 0; i<num;i++){

		btTransform trans = fileLoader->getRigidBodyByIndex(i)->getWorldTransform();

		escenario = fileLoader->getRigidBodyByIndex(i)->getCollisionShape();
		cubeMotionState = new btDefaultMotionState(trans);
		btRigidBody* _objeto_esceario = new btRigidBody(0, cubeMotionState, escenario);
		_objeto_esceario->setFriction(0);
		world->addRigidBody(_objeto_esceario,COL_ESCENARIO, escenario_colisiona_con);

		//btBroadphaseProxy* proxy = esta_vez_si->getBroadphaseProxy();
		//proxy->m_collisionFilterGroup = 4;
		//proxy->m_collisionFilterMask = 4;
	}	
    world->setGravity(btVector3(0,-9.8*18,0));
}


iNodoModelado* Interfaz_ME::crearModelado(const char* ruta){
    iNodoModelado* nodo = new iNodoModelado(ruta);
    lista_i_nodo.push_back(nodo);
    return nodo;
}

iNodoModelado* Interfaz_ME::crearModelado(const char* ruta, float x, float y, float z){
    iNodoModelado* nodo = new iNodoModelado(ruta, x, y, z);
    lista_i_nodo.push_back(nodo);
    return nodo;
}

iNodoCamara* Interfaz_ME::crearCamara(bool activa){
    iNodoCamara* nodo = new iNodoCamara(activa);
    lista_i_nodo.push_back(nodo);
    return nodo;
}

iNodoCamara* Interfaz_ME::crearCamara(bool activa, float x, float y, float z){
    iNodoCamara* nodo = new iNodoCamara(activa, x, y, z);
    lista_i_nodo.push_back(nodo);
    return nodo;
}

iNodoLuz* Interfaz_ME::crearLuz(bool activa, float intensidad){
    iNodoLuz* nodo = new iNodoLuz(activa, intensidad);
    lista_i_nodo.push_back(nodo);
    return nodo;
}

iNodoLuz* Interfaz_ME::crearLuz(bool activa, float intensidad, float x, float y, float z){
    iNodoLuz* nodo = new iNodoLuz(activa, intensidad, x, y, z);
    lista_i_nodo.push_back(nodo);
    return nodo;
}

/*
uint16_t Interfaz_ME::crearLuz(){
    TLuz* luz = motor->crearLuz();
    TTransform* transTraslacion = motor->crearTransform();
    TTransform* transRotacion   = motor->crearTransform();

    TNodo* nodoRotacion   = motor->crearNodo(motor->nodoRaiz(), transRotacion);
    TNodo* nodoTraslacion = motor->crearNodo(nodoRotacion, transTraslacion);

    TNodo* nodoLuz = motor->crearNodoLuz(nodoTraslacion, luz);
}*/

bool Interfaz_ME::ventana_abierta(){
    return !motor->ventana_abierta();
}

void Interfaz_ME::render(){
    motor->draw();
}

//--------METODOS DE LA VERSION VIEJA DE LA INTERFAZ----------
iNodoModelado* Interfaz_ME::importarEscenario(const char* rutaObj, float x, float y, float z){
    return crearModelado(rutaObj, x, y, z);
}

Interpolacion* Interfaz_ME::crear_interpolacion(float x, float y, float z){
    Vector3 posicion(x,y,z);
	Interpolacion* _interpolacion = new Interpolacion(posicion);
	return _interpolacion;
}

void Interfaz_ME::getDimensiones(iNodoModelado* _i_nodo, float &anchura, float &altura, float &profundidad){
    altura = 2;
    anchura = 2;
    profundidad = 2;
}

btRigidBody* Interfaz_ME::crearRigidBody(Objeto* _i_objeto, BoundingBoxes tipo,const char*  ruta,float x, float y, float z, float _i_peso, iNodoModelado* _i_nodo){
    	
	float altura,anchura,profundidad;
	btCollisionShape *cubeShape;
	this->getDimensiones(_i_nodo,anchura,altura,profundidad);
	
	btTransform cubeTransform;
	cubeTransform.setIdentity();

	cubeTransform.setOrigin(btVector3(x,y+(altura/2),z));

	btDefaultMotionState *cubeMotionState = new btDefaultMotionState(cubeTransform);

	float cubeMass = _i_peso;

	switch(tipo){
		case E_BoundingCapsule: 
			cubeShape = new btCapsuleShape(anchura*0.7,altura*0.5); // new btSphereShape(0.5);

					break;
		case E_BoundingBox:
			cubeShape = new btBoxShape(btVector3(profundidad*0.5,altura*0.5,anchura*0.5)); // new btSphereShape(0.5);

					break;	
		default:
			cubeShape = new btBoxShape(btVector3(profundidad*0.7,altura*0.5,anchura*0.7)); // new btSphereShape(0.5);

					break;
	}
	
	cubeShape->setUserPointer(_i_objeto);

	btVector3 cubeLocalInertia;
	cubeShape->calculateLocalInertia(cubeMass, cubeLocalInertia);

	btRigidBody *cubeBody = new btRigidBody(cubeMass, cubeMotionState, cubeShape, cubeLocalInertia);
	
	cubeBody->setAngularFactor(0);
	cubeBody->setUserPointer(_i_objeto);
	cubeBody->setRestitution(0);
	cubeBody->setFriction(1);
	cubeBody->forceActivationState(DISABLE_DEACTIVATION );


	//CREACION DE MASCARA DE RIGIDBODY
	int mascara_colision = COL_NADA;
	int grupo_colision 	 = COL_NADA;

	//si es un personaje
	if(dynamic_cast<Player*>(_i_objeto)!=NULL){
		grupo_colision   = COL_JUGADOR;
		mascara_colision = jugador_colisiona_con;
	}

	//si es un npc
	else if(dynamic_cast<NPC*>(_i_objeto)!=NULL){
		grupo_colision   = COL_NPC;
		mascara_colision = npc_colisiona_con;
	}

	else if(dynamic_cast<Puerta*>(_i_objeto)!=NULL){
		grupo_colision   = COL_PUERTA;
		mascara_colision = puerta_colisiona_con;
	}

	else if(dynamic_cast<Puerta_Pincho*>(_i_objeto)!=NULL){
		grupo_colision   = COL_PUERTA;
		mascara_colision = puerta_colisiona_con;
	}

	else if(dynamic_cast<Interruptor*>(_i_objeto)!=NULL){
		grupo_colision   = COL_PUERTA;
		mascara_colision = puerta_colisiona_con;
	}
	
		//si es otra cosa
	else{
		cubeBody->setCollisionFlags(cubeBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		grupo_colision   = COL_OTRO;
		mascara_colision = otros_colisiona_con;
	}
	

	cubeShape->setUserPointer(_i_objeto);

	world->addRigidBody(cubeBody,grupo_colision,mascara_colision);

	return cubeBody;
}

void Interfaz_ME::crear_ObjetoMotor(Objeto_ME* _i_objeto_me){
    _objetos_me.push_back(_i_objeto_me);
}

btCollisionWorld::ClosestRayResultCallback Interfaz_ME::trazaRayo(btVector3 start, btVector3 end, int mascara_colision){
	btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
	rayCallback.m_collisionFilterMask  = mascara_colision;
	rayCallback.m_collisionFilterGroup = COL_RAY;
	world->rayTest(start, end, rayCallback);

	return rayCallback;
}

btCollisionWorld::AllHitsRayResultCallback Interfaz_ME::trazaRayoAll(btVector3 start, btVector3 end, int mascara_colision){
	btCollisionWorld::AllHitsRayResultCallback rayCallback(start, end);
	rayOrigen->_x = start.getX();
	rayOrigen->_y = start.getY();
	rayOrigen->_z = start.getZ();

	rayDestino->_x = end.getX();
	rayDestino->_y = end.getY();
	rayDestino->_z = end.getZ();
	rayCallback.m_collisionFilterMask  = mascara_colision;
	rayCallback.m_collisionFilterGroup = COL_RAY;
	world->rayTest(start, end, rayCallback);

	return rayCallback;
}