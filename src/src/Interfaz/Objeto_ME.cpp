#include "Objeto_ME.h"
#include "Interfaz_ME.h"

#include <cstdint>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "BulletWorldImporter/btBulletWorldImporter.h"
//#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "DebugDraw.h"
#include "../../Camara/Camara.h"
//#include "GUI.h"
#include "../../Personajes/Interpolacion.h"
#include "../../Personajes/Character.h"

#include "EnumTiposColision.h"

#include "../../Interfaz_Libs/Lib_Math.h"

Objeto_ME::Objeto_ME(Objeto* _objeto,BoundingBoxes tipo,const char* rutaObj,float x, float y, float z, int16_t peso){
    Interfaz_ME* _motor = Interfaz_ME::get_instancia(1280,720);
   _nodo            = _motor->crearModelado(rutaObj, x, y, z);
   _interpolacion   = _motor->crear_interpolacion(x, y, z);
   _rigidbody       = _motor->crearRigidBody(_objeto, tipo ,rutaObj ,x ,y ,z ,peso ,_nodo);

   _motor->crear_ObjetoMotor(this);

   desp_z = 0;
   desp_x = 0;
}
Objeto_ME::~Objeto_ME(){

}

void Objeto_ME::setPositionXZ(float x, float z){
    btTransform btt; 
	_rigidbody->getMotionState()->getWorldTransform(btt);
	btt.setOrigin(btVector3(x,btt.getOrigin().getY(),z)); // move body to the scene node new position

	_rigidbody->getMotionState()->setWorldTransform(btt);
	_rigidbody->setCenterOfMassTransform(btt);

	btVector3 pos = _rigidbody->getCenterOfMassPosition();

    _nodo->mover(x,btt.getOrigin().getY(),z);	
	//_nodo->setPosition(vector3df(x,btt.getOrigin().getY(),z));

	const btQuaternion &quat = _rigidbody->getOrientation();
	quaternion q(quat.getX(), quat.getY(), quat.getZ(), quat.getW());
	vector3df euler;
	q.toEuler(euler);
	euler *= RADTODEG;
	_nodo->rotar(1, 0, 0, euler.X); //rotacion eje X
    _nodo->rotar(0, 1, 0, euler.Y); //rotacion eje Y
    _nodo->rotar(0, 0, 1, euler.Z); //rotacion eje Z    
}

// Funcion de mover para los personajes
void Objeto_ME::VelocidadDireccion(uint16_t _i_direccion, float _i_velocidad, double mdt){  // Direccion

	// Actualiza la rotacion del personaje
	_interpolacion->actualiza_direccion(_i_direccion);

	desp_z = cos(_i_direccion*std::acos(-1)/180) * _i_velocidad * mdt;
    desp_x = sin(_i_direccion*std::acos(-1)/180) * _i_velocidad * mdt;

    setVelocidad(desp_x,_rigidbody->getLinearVelocity()[1],desp_z);
}

void Objeto_ME::setVelocidad(float x, float y, float z){
    _rigidbody->setLinearVelocity(btVector3(x,y,z));
}

Character* Objeto_ME::disparar(Objeto_ME* _i_objeto_origen,uint16_t _i_direccion, uint8_t _i_rango_disparo){
    _i_direccion = _i_direccion + (rand() % 10) - 5;

	desp_z = cos(_i_direccion*std::acos(-1)/180);
    desp_x = sin(_i_direccion*std::acos(-1)/180);
	
	btVector3 origen(_i_objeto_origen->getX(), _i_objeto_origen->getY(), _i_objeto_origen->getZ());
	btVector3 destino(_i_objeto_origen->getX()+desp_x*_i_rango_disparo, _i_objeto_origen->getY(), _i_objeto_origen->getZ()+desp_z*_i_rango_disparo);

	btCollisionWorld::AllHitsRayResultCallback rayResult = Interfaz_ME::get_instancia(1280,720)->trazaRayoAll(origen,destino,escenario_colisiona_con);
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

float Objeto_ME::getX(){
	btVector3 pos = _rigidbody->getCenterOfMassPosition();
	return pos[0];
}

float Objeto_ME::getY(){
	btVector3 pos = _rigidbody->getCenterOfMassPosition();
	return pos[1];
}

float Objeto_ME::getZ(){
	btVector3 pos = _rigidbody->getCenterOfMassPosition();
	return pos[2];
}

iNodoModelado* Objeto_ME::getNodo(){
	return _nodo;
}

Interpolacion* Objeto_ME::getInterpolacion(){
	return _interpolacion;
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

float Objeto_ME::getVelocidadY(){
	return  _rigidbody->getLinearVelocity()[1];
}

btRigidBody* Objeto_Motor::getRigidBody(){
	return _rigidbody;
}