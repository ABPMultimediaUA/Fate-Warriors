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


Interfaz_ME* Interfaz_ME::_instancia = 0;

Interfaz_ME* Interfaz_ME::get_instancia(uint16_t width, uint16_t height){
    if(_instancia == 0){
        _instancia= new Interfaz_ME(width, height);
    }
    return _instancia;
}

Interfaz_ME::Interfaz_ME(uint16_t width, uint16_t height){
    configuracion_ME(width, height, false, false);
}

Interfaz_ME::~Interfaz_ME(){
    for(uint16_t i=0; i<lista_i_nodo.size();i++){
        delete(lista_i_nodo[i]);
    }
}

void Interfaz_ME::configuracion_ME(uint16_t width, uint16_t height, bool fullscreen, bool v_sync){
    motor = TMooseEngine::get_instancia();
}
/*
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
*/

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