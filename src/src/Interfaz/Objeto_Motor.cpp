#include "Objeto_Motor.h"
#include <cstdint>

#include "Motor.h"

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "BulletWorldImporter/btBulletWorldImporter.h"
//#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "DebugDraw.h"
#include "../Camara/Camara.h"
#include "../Personajes/Interpolacion.h"
#include "../Personajes/Character.h"
#include "../Moose_Engine/src/iNodoModelado.h"
#include "../Moose_Engine/src/iNodoAnimacion.h"

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
Objeto_Motor::Objeto_Motor(Objeto* objeto, BoundingBoxes tipo,const char* rutaObj,float x, float y, float z, int16_t peso, int16_t _rotacion_x){
   Motor* _motor = Motor::Motor_GetInstance();
   _nodo            = _motor->crearModelado(rutaObj, x, y, z);
   _interpolacion   = _motor->crear_interpolacion_palanca(x, y, z, _rotacion_x);
   _rigidbody       = _motor->crearRigidBody(objeto, tipo ,rutaObj ,x ,y ,z ,peso ,_nodo);

   _motor->crear_ObjetoMotor(this);

	desp_z = 0;
    desp_x = 0;
}
Objeto_Motor::Objeto_Motor(bool bucle, Objeto* _objeto,BoundingBoxes tipo,const char* rutaObj, const char* rutaAnim, float x, float y, float z, int16_t peso){
	Motor* _motor = Motor::Motor_GetInstance();
   _nodo            = _motor->crearModeladoSinLista(rutaObj, x, y, z);
   _interpolacion   = _motor->crear_interpolacion(x, y, z);
   _rigidbody       = _motor->crearRigidBody(_objeto, tipo ,rutaObj ,x ,y ,z ,peso ,_nodo);
   _nodo->borrarNodo();
   _nodo 			= _motor->crearAnimacion(true, rutaAnim, x, y, z);
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
		
	_nodo->mover(x,btt.getOrigin().getY(),z);

	btScalar xx, yy, zz;
	_rigidbody->getCenterOfMassTransform().getBasis().getEulerZYX(zz, yy, xx);
	Vector3 euler(zz,yy,xx);
	euler *= 180.0f / SIMD_PI;

	_nodo->rotacionDirecta(1, 0, 0, euler._x);
	_nodo->rotacionDirecta(0, 1, 0, euler._y);
	_nodo->rotacionDirecta(0, 0, 1, euler._z);
}


void Objeto_Motor::setPositionY(float y){

	btTransform btt; 
	_rigidbody->getMotionState()->getWorldTransform(btt);
	btt.setOrigin(btVector3(btt.getOrigin().getX(),y,btt.getOrigin().getZ())); // move body to the scene node new position
	btt.setRotation(_rigidbody->getOrientation());

	_rigidbody->getMotionState()->setWorldTransform(btt);
	_rigidbody->setCenterOfMassTransform(btt);

	btVector3 pos = _rigidbody->getCenterOfMassPosition();
		
	_nodo->mover(Vector3(btt.getOrigin().getX(),btt.getOrigin().getY(),btt.getOrigin().getZ()));
}






// Funcion de mover para los personajes
void Objeto_Motor::VelocidadDireccion(uint16_t _i_direccion, float _i_velocidad, double mdt){  // Direccion

	// Actualiza la rotacion del personaje
	_interpolacion->actualiza_direccion(_i_direccion);

	desp_z = cos(_i_direccion*std::acos(-1)/180) * _i_velocidad * mdt;
    desp_x = sin(_i_direccion*std::acos(-1)/180) * _i_velocidad * mdt;

    setVelocidad(desp_x,_rigidbody->getLinearVelocity()[1],desp_z);
}

// Funcion de mover para los personajes
void Objeto_Motor::VelocidadDireccion(uint16_t _i_direccion, float _i_velocidad, double mdt, uint16_t _i_direccion_mirar){  // Direccion

	// Actualiza la rotacion del personaje
	_interpolacion->actualiza_direccion(_i_direccion_mirar);

	desp_z = cos(_i_direccion*std::acos(-1)/180) * _i_velocidad * mdt;
    desp_x = sin(_i_direccion*std::acos(-1)/180) * _i_velocidad * mdt;

    setVelocidad(desp_x,_rigidbody->getLinearVelocity()[1],desp_z);
}

/*Rango muy corto 20 normal 40 y largo 80*/
Character* Objeto_Motor::disparar(Objeto_Motor* _i_objeto_origen,uint16_t _i_direccion, uint8_t _i_rango_disparo){


    _i_direccion = _i_direccion + (rand() % 10) - 5;

	desp_z = cos(_i_direccion*std::acos(-1)/180);
    desp_x = sin(_i_direccion*std::acos(-1)/180);
	
	btVector3 origen(_i_objeto_origen->getX(), _i_objeto_origen->getY(), _i_objeto_origen->getZ());
	btVector3 destino(_i_objeto_origen->getX()+desp_x*_i_rango_disparo, _i_objeto_origen->getY(), _i_objeto_origen->getZ()+desp_z*_i_rango_disparo);

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
	VelocidadDireccion(_i_direccion,1.5,80);
	float potencia = 0.1;
	Impulso(_i_direccion, potencia);
}

void Objeto_Motor::Impulso(uint16_t _i_direccion, uint16_t potencia){
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
	//_nodo->getMaterial(0).AmbientColor.set(255,r,g,b); //brillo, r,g,b
}


void Objeto_Motor::abrir_puerta(){
	setPositionY(20);
	_rigidbody->forceActivationState(DISABLE_SIMULATION);
}

void Objeto_Motor::abrir_puerta(uint8_t _direccion){
	if(_direccion == 0) {
		setPositionXZ(getX()-6.9, getZ()+6.9);
		rotar_nodo(270);
	}
	else if(_direccion == 1) {
		setPositionXZ(getX()+6.9, getZ()-6.9);
		rotar_nodo(90);
	}
	_rigidbody->forceActivationState(DISABLE_SIMULATION);
}

float Objeto_Motor::getVelocidadY(){
	return  _rigidbody->getLinearVelocity()[1];
}

void Objeto_Motor::updateDynamicBody() {
	btVector3 pos = _rigidbody->getCenterOfMassPosition();
	_nodo->mover(pos[0], pos[1], pos[2]);

	Vector3 vector(pos[0], pos[1], pos[2]);
	_interpolacion->actualiza_posicion(vector);

	if(!_interpolacion->get_cambio_direccion()) {
		_interpolacion->actualiza_direccion(_interpolacion->get_direccion_actual());
	}

	_interpolacion->cambio_direccion(false);


	if(_interpolacion->get_cambio_rotacion()) {
		_interpolacion->actualiza_rotacion_palanca(_interpolacion->get_rotacion_palanca());
		_interpolacion->set_cambio_rotacion(false);
	}

}


void Objeto_Motor::updateDynamicBodyCharacter() {
	btVector3 pos = _rigidbody->getCenterOfMassPosition();
	_nodo->mover(pos[0], pos[1]-(3), pos[2]);

	float _altura_interpolacion = pos[1]-(3);
	if(_altura_interpolacion < 10)
		_altura_interpolacion = -0.4;
	Vector3 vector(pos[0], _altura_interpolacion, pos[2]);
	_interpolacion->actualiza_posicion(vector);

	if(!_interpolacion->get_cambio_direccion()) {
		_interpolacion->actualiza_direccion(_interpolacion->get_direccion_actual());
	}

	_interpolacion->cambio_direccion(false);

}

Vector3 Objeto_Motor::interpola_posiciones(float _i_interpolacion){
	Vector3 _posicion_interpolada = _interpolacion->interpola_posicion(_i_interpolacion);
	
	_nodo->mover(_posicion_interpolada._x, _posicion_interpolada._y, _posicion_interpolada._z);
	_nodo->rotacionDirecta(0, 1, 0, _interpolacion->interpola_direccion(_i_interpolacion));
	//if(_interpolacion->interpola_rotacion_palanca(_i_interpolacion) != 0)
		//std::cout << "Rotacion Palanca : " << (int)_interpolacion->interpola_rotacion_palanca(_i_interpolacion) << "\n";
	_nodo->rotar(1, 0, 0, _interpolacion->interpola_rotacion_palanca(_i_interpolacion));
	return _posicion_interpolada;
}

iNodoModelado* Objeto_Motor::getNodo(){
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

void Objeto_Motor::rotar_nodo(uint16_t rotacion){
	rotar_nodo_sin_interpolacion(rotacion);
	
	_interpolacion->actualiza_direccion(rotacion);
}

void Objeto_Motor::rotar_nodo_sin_interpolacion(uint16_t rotacion) {
	float mult = 4.9212625;
	btScalar gTilt = rotacion*SIMD_PI / 180.0f; 
	btTransform rbTransform;

	// Rotacion
	rbTransform.setIdentity();
	rbTransform.setOrigin(_rigidbody->getCenterOfMassPosition());
	btQuaternion incline;
	incline.setRotation(btVector3(0, 1, 0), gTilt);
	rbTransform.setRotation(incline);
	_rigidbody->setWorldTransform(rbTransform);

	btVector3 pos = _rigidbody->getCenterOfMassPosition();
	_nodo->mover(Vector3(pos[0], pos[1], pos[2]));

}

void Objeto_Motor::cambiar_modelado(const char* _ruta, uint8_t _num_ruta){
	_nodo->cambiar_modelado(_ruta, _num_ruta);
}

void Objeto_Motor::rota_palanca(int16_t _i_rotacion_actual) {
	_interpolacion->actualiza_rotacion_palanca(_i_rotacion_actual);
}