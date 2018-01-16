#include "Objeto_Motor.h"
#include <cstdint>

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "BulletWorldImporter/btBulletWorldImporter.h"
//#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "DebugDraw.h"
#include "../Camara/Camara.h"
#include "GUI.h"
#include "../Personajes/Interpolacion.h"


Objeto_Motor::Objeto_Motor(BoundingBoxes tipo, char* rutaObj,float x, float y, float z, short peso){
	Motor* _motor = Motor::Motor_GetInstance();

   _nodo            = _motor->crearModelado(rutaObj, x, y, z);
   _interpolacion   = _motor->crear_interpolacion(x, y, z);
   _rigidbody       = _motor->crearRigidBody(tipo ,rutaObj ,x ,y ,z ,peso ,_nodo);
   _id              = _motor->getId();

   _motor->crear_ObjetoMotor(this);

	desp_z = 0;
    desp_x = 0;
}

Objeto_Motor::~Objeto_Motor(){
    Motor* _motor = Motor::Motor_GetInstance();
   _motor->borrar_objeto(_nodo, _interpolacion, _rigidbody);
} 

// Funcion de mover para los NPC
void Objeto_Motor::setVelocidad(unsigned short _i_direccion, float x, float y, float z, double mdt){
	float _cos, _sen;
	_cos = sin(_i_direccion*std::acos(-1)/180);
	_sen = cos(_i_direccion*std::acos(-1)/180);

	// Saca una nueva direccion, dado que _i_direccion no viene en el mismo sistema
	float _nueva_direccion = atan2(_sen, _cos) /std::acos(-1) * 180;

	// Actualiza la rotacion del personaje
	_interpolacion->actualiza_direccion(_nueva_direccion);

	// Agrega el desplazamiento del personaje
	desp_z = cos(_nueva_direccion*std::acos(-1)/180) * 1 * mdt;
    desp_x = sin(_nueva_direccion*std::acos(-1)/180) * 1 * mdt;
    setVelocidad(desp_x,_rigidbody->getLinearVelocity()[1],desp_z);
    	desp_z = 0;
    desp_x = 0;
}

void Objeto_Motor::setPositionXZ(float x, float z){
	btTransform btt; 
	_rigidbody->getMotionState()->getWorldTransform(btt);
	btt.setOrigin(btVector3(x,btt.getOrigin().getY(),z)); // move body to the scene node new position

	_rigidbody->getMotionState()->setWorldTransform(btt);
	_rigidbody->setCenterOfMassTransform(btt);

	ISceneNode *node = static_cast<ISceneNode *>(_rigidbody->getUserPointer());
	btVector3 pos = _rigidbody->getCenterOfMassPosition();
		
	node->setPosition(vector3df(x,btt.getOrigin().getY(),z));

	const btQuaternion &quat = _rigidbody->getOrientation();
	quaternion q(quat.getX(), quat.getY(), quat.getZ(), quat.getW());
	vector3df euler;
	q.toEuler(euler);
	euler *= RADTODEG;
	node->setRotation(euler);
}


// Funcion de mover para el jugador
void Objeto_Motor::VelocidadDireccion(unsigned short _i_direccion, unsigned short _i_velocidad, double mdt){  // Direccion
	
    Motor* _motor = Motor::Motor_GetInstance();
    float angulo = _motor->angulo_camara();

	// Direccion sumada de los movimientos
	int16_t _direccion_buena = _i_direccion + angulo;

	// Si la direccion es mayor de 360, se reduce al intervalo [0,360)
	while(_direccion_buena >= 360) _direccion_buena -= 360;

	// Actualiza la rotacion del personaje
	_interpolacion->actualiza_direccion(_direccion_buena);

	desp_z = cos(_direccion_buena*std::acos(-1)/180) * _i_velocidad * mdt;
    desp_x = sin(_direccion_buena*std::acos(-1)/180) * _i_velocidad * mdt;

    setVelocidad(desp_x,_rigidbody->getLinearVelocity()[1],desp_z);
}

void Objeto_Motor::setVelocidad(float x, float y, float z){
    _rigidbody->setLinearVelocity(btVector3(x,y,z));
}

void Objeto_Motor::saltar(){		
	if(std::abs (_rigidbody->getLinearVelocity()[1])<0.01){
		_rigidbody->applyCentralImpulse(btVector3( 0.f, 3000.f, 0.f ) );
	}
}

void Objeto_Motor::Dash(unsigned short _i_direccion, double mdt){
	short potencia = 300;
	Motor* _motor = Motor::Motor_GetInstance();
    float angulo = _motor->angulo_camaraRAD();
	
	desp_z = cos(angulo+(_i_direccion*std::acos(-1)/180)) * mdt;
    desp_x = sin(angulo+(_i_direccion*std::acos(-1)/180)) * mdt;
	_rigidbody->applyCentralImpulse(btVector3(desp_x*potencia, 0.f, desp_z*potencia)); //se multiplica por 100 pa volaaaar
}

unsigned short Objeto_Motor::getId(){
    return _id;
}

float Objeto_Motor::getX(){
	btVector3 pos = _rigidbody->getCenterOfMassPosition();
	return pos[0];
}

float Objeto_Motor::getY(){
	btVector3 pos = _rigidbody->getCenterOfMassPosition();
	return pos[1];
}

float Objeto_Motor::getZ(){
	btVector3 pos = _rigidbody->getCenterOfMassPosition();
	return pos[2];
}

void Objeto_Motor::colorear_nodo(short r,short g, short b){
	_nodo->getMaterial(0).AmbientColor.set(255,r,g,b); //brillo, r,g,b
}

//Manu mira esta cosa.com

void Objeto_Motor::abrir_puerta1(){
	
	_rigidbody->forceActivationState(DISABLE_SIMULATION);
	btTransform btt; 
	_rigidbody->getMotionState()->getWorldTransform(btt);
	btt.setOrigin(btVector3(btt.getOrigin().getX(),10,btt.getOrigin().getZ())); // move body to the scene node new position

	_rigidbody->getMotionState()->setWorldTransform(btt);
	_rigidbody->setCenterOfMassTransform(btt);


	btVector3 pos = _rigidbody->getCenterOfMassPosition();
	_nodo->setPosition(vector3df(btt.getOrigin().getX(),btt.getOrigin().getY(),btt.getOrigin().getZ()));
}

void Objeto_Motor::abrir_puerta2(){
	
	_rigidbody->forceActivationState(DISABLE_SIMULATION);
	btTransform btt; 
	_rigidbody->getMotionState()->getWorldTransform(btt);
	btt.setOrigin(btVector3(btt.getOrigin().getX(),20,btt.getOrigin().getZ())); // move body to the scene node new position

	_rigidbody->getMotionState()->setWorldTransform(btt);
	_rigidbody->setCenterOfMassTransform(btt);

	btVector3 pos = _rigidbody->getCenterOfMassPosition();
		
	_nodo->setPosition(vector3df(btt.getOrigin().getX(),btt.getOrigin().getY(),btt.getOrigin().getZ()));
}

void Objeto_Motor::abrir_puerta(){
	this->abrir_puerta1();
	this->abrir_puerta2();
}

float Objeto_Motor::getVelocidadY(){
	return  _rigidbody->getLinearVelocity()[1];
}