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

uint8_t Motor::crearObjeto(char* rutaObj,float x, float y, float z){
	return _entidad->crear_objeto(rutaObj,x, y, z);
}

void Motor::poner_camara_a_entidad(unsigned short id){
	_entidad->poner_camara_a_entidad(id);
}   

void Motor::Mover(uint8_t id, float x, float y, float z){
	_entidad->setVelocidad(id,x,y,z);
}

void Motor::setPositionXZ(unsigned short id, float x, float z){
	_entidad->setPositionXZ(id,x,z);
}

void Motor::saltar(unsigned short _i_id){
	_entidad->saltar(_i_id);
}

void Motor::Dash(unsigned short _i_direccion, unsigned short id){
	_entidad->Dash(_i_direccion,id);
}

void Motor::update(double dt){
	_entidad->update(dt);
}

void Motor::render(){
	_entidad->render();
}

void Motor::VelocidadDireccion(unsigned short id, unsigned short _i_direccion, unsigned short _i_velocidad){
	_entidad->VelocidadDireccion(id,_i_direccion, _i_velocidad);
}

void Motor::set_text_vida(int vida){
	_entidad->set_text_vida(vida);
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

float Motor::getVelocidadY(short id){
	return _entidad->getVelocidadY(id);
}

IrrlichtDevice* Motor::getIrrlichtDevice(){
	return _entidad->getDevice();
}

