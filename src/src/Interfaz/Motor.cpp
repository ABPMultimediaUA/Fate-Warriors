#include "Motor.h"
#include "Entidad.h"

Motor* Motor::_Motor=0;

Motor* Motor::Motor_GetInstance(){
	if(_Motor==0){
		_Motor	=  new Motor();
	}
	return _Motor;
}

Motor::Motor(){
   _entidad = new Entidad();
}

Motor::~Motor(){
	delete _entidad;
	_entidad = nullptr;
} 

float Motor::getX(short id){
	return _entidad->getX(id);
}

float Motor::getY(short id){
	return _entidad->getY(id);
}

float Motor::getZ(short id){
	return _entidad->getZ(id);
}

void Motor::Mover(uint8_t id, float x, float y, float z){
	_entidad->Mover(id,x,y,z);
}

void Motor::poner_camara_a_entidad(unsigned short id){
	_entidad->poner_camara_a_entidad(id);
}    //movimiento del prota

void Motor::setPositionXZ(unsigned short id, float x, float z){
	_entidad->setPositionXZ(id,x,z);
}

void Motor::saltar(){
	
	_entidad->saltar();
}

void Motor::moverAdelante(){
	_entidad->moverAdelante();
}

void Motor::moverIzquierda(){
	_entidad->moverIzquierda();
}

void Motor::moverDerecha(){
	_entidad->moverDerecha();
}

void Motor::moverAtras(){
	_entidad->moverAtras();
}

void Motor::update(double dt){
	_entidad->update(dt);
}

void Motor::render(){
	_entidad->render();
}

uint8_t Motor::crearObjeto(char* rutaObj,float x, float y, float z){
	return _entidad->crear_objeto(rutaObj,x, y, z);
}

void Motor::moverDireccion(unsigned short id, unsigned short _i_direccion){
	_entidad->moverDireccion(id,_i_direccion);
}

IrrlichtDevice* Motor::getIrrlichtDevice(){
	return _entidad->getDevice();
}
