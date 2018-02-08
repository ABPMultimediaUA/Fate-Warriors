#include "Objeto_Motor.h"
#include <cstdint>

#include "Motor.h"

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "BulletWorldImporter/btBulletWorldImporter.h"
//#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "DebugDraw.h"
#include "../Camara/Camara.h"
#include "GUI.h"
#include "../Personajes/Interpolacion.h"
#include "../Personajes/Character.h"

#include "EnumTiposColision.h"

#include "../Interfaz_Libs/Lib_Math.h"

Objeto_Motor::Objeto_Motor(Objeto* objeto, BoundingBoxes tipo,const char* rutaObj,float x, float y, float z, int16_t peso){
   Motor* _motor = Motor::Motor_GetInstance();
   _nodo            = _motor->crearModelado(rutaObj, x, y, z);
   _interpolacion   = _motor->crear_interpolacion(x, y, z);
   _rigidbody       = _motor->crearRigidBody(objeto, tipo ,rutaObj ,x ,y ,z ,peso ,_nodo);

   _motor->crear_ObjetoMotor(this);

	desp_z = 0;
    desp_x = 0;
}

Objeto_Motor::~Objeto_Motor(){
	Motor* _motor = Motor::Motor_GetInstance();
   _motor->borrar_objeto(this);
}

void Objeto_Motor::setPositionXZ(float x, float z){
	btTransform btt; 
	_rigidbody->getMotionState()->getWorldTransform(btt);
	btt.setOrigin(btVector3(x,btt.getOrigin().getY(),z)); // move body to the scene node new position

	_rigidbody->getMotionState()->setWorldTransform(btt);
	_rigidbody->setCenterOfMassTransform(btt);

	btVector3 pos = _rigidbody->getCenterOfMassPosition();
		
	_nodo->setPosition(vector3df(x,btt.getOrigin().getY(),z));

	const btQuaternion &quat = _rigidbody->getOrientation();
	quaternion q(quat.getX(), quat.getY(), quat.getZ(), quat.getW());
	vector3df euler;
	q.toEuler(euler);
	euler *= RADTODEG;
	_nodo->setRotation(euler);
}


// Funcion de mover para los personajes
void Objeto_Motor::VelocidadDireccion(uint16_t _i_direccion, float _i_velocidad, double mdt){  // Direccion

	// Actualiza la rotacion del personaje
	_interpolacion->actualiza_direccion(_i_direccion);

	desp_z = cos(_i_direccion*std::acos(-1)/180) * _i_velocidad * mdt;
    desp_x = sin(_i_direccion*std::acos(-1)/180) * _i_velocidad * mdt;

    setVelocidad(desp_x,_rigidbody->getLinearVelocity()[1],desp_z);
}

/*Rango muy corto 20 normal 40 y largo 80*/
Character* Objeto_Motor::disparar(uint16_t _i_direccion, uint8_t _i_rango_disparo){
	desp_z = cos(_i_direccion*std::acos(-1)/180);
    desp_x = sin(_i_direccion*std::acos(-1)/180);
	
	btVector3 origen(this->getX(), this->getY(), this->getZ());
	btVector3 destino(getX()+desp_x*_i_rango_disparo, this->getY(), getZ()+desp_z*_i_rango_disparo);

	btCollisionWorld::AllHitsRayResultCallback rayResult = Motor::Motor_GetInstance()->trazaRayoAll(origen,destino,escenario_colisiona_con);
	SColor newColor(255, 255.0, 255.0, 255.0);

	if(rayResult.hasHit()) {
	//	for(int i=0;i<rayResult.m_collisionObjects.size();i++){
		//	std::cout << rayResult.m_collisionObjects[i]->getCollisionShape()->getUserPointer() << " tamanio -> " << rayResult.m_collisionObjects.size() << " i " << i <<std::endl;
			if(rayResult.m_collisionObjects[0]->getCollisionShape()->getUserPointer()!=0)
				return ((Character*)rayResult.m_collisionObjects[0]->getCollisionShape()->getUserPointer());
			else {
				return 0;
			}
			
		//}
	}
	return 0;
}

void Objeto_Motor::setVelocidad(float x, float y, float z){
    _rigidbody->setLinearVelocity(btVector3(x,y,z));
}

void Objeto_Motor::saltar(){		
	if(std::abs (_rigidbody->getLinearVelocity()[1])<0.01){
		_rigidbody->applyCentralImpulse(btVector3( 0.f, 4000.f, 0.f ) );
	}
}

void Objeto_Motor::Dash(uint16_t _i_direccion){
	short potencia = 6000;
	Motor* _motor = Motor::Motor_GetInstance();
    //float angulo = _motor->angulo_camaraRAD();
	
	desp_z = cos((_i_direccion*std::acos(-1)/180));
    desp_x = sin((_i_direccion*std::acos(-1)/180));
	_rigidbody->applyCentralImpulse(btVector3(desp_x*potencia, 0.f, desp_z*potencia)); //se multiplica por 100 pa volaaaar
}

void Objeto_Motor::Impulso_explosion(Vector3 vector){
	_rigidbody->applyCentralImpulse(btVector3(vector._x,vector._y, vector._z)); //se multiplica por 100 pa volaaaar
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

void Objeto_Motor::updateDynamicBody() {
	btVector3 pos = _rigidbody->getCenterOfMassPosition();
	_nodo->setPosition(vector3df(pos[0], pos[1], pos[2]));

	Vector3 vector(pos[0], pos[1], pos[2]);
	_interpolacion->actualiza_posicion(vector);

	if(!_interpolacion->get_cambio_direccion()) {
		_interpolacion->actualiza_direccion(_interpolacion->get_direccion_actual());
	}

	_interpolacion->cambio_direccion(false);

}

Vector3 Objeto_Motor::interpola_posiciones(float _i_interpolacion){
	Vector3 _posicion_interpolada = _interpolacion->interpola_posicion(_i_interpolacion);
	
	_nodo->setPosition(vector3df(_posicion_interpolada._x, _posicion_interpolada._y, _posicion_interpolada._z));

	_nodo->setRotation(core::vector3df(0,_interpolacion->interpola_direccion(_i_interpolacion),0));

	return _posicion_interpolada;
}

ISceneNode* Objeto_Motor::getNodo(){
	return _nodo;
}

Interpolacion* Objeto_Motor::getInterpolacion(){
	return _interpolacion;
}

btRigidBody* Objeto_Motor::getRigidBody(){
	return _rigidbody;
}


btVector3 Objeto_Motor::get_posicion_rb(){
	return _rigidbody->getCenterOfMassPosition();
}