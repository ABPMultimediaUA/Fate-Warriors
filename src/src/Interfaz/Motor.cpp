#include "Motor.h"

#include "Entidad.h"
#include "../Input.h"


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

void Motor::apagar(){
	_entidad->apagar();
}

Motor::~Motor(){
	delete _entidad;
	_entidad = nullptr;
} 

uint8_t Motor::crearObjetoPeso(BoundingBoxes tipo, char* rutaObj,float x, float y, float z, float _i_peso){
	return _entidad->crear_objeto(tipo,rutaObj,x, y, z, _i_peso);
}

uint8_t Motor::crearObjeto(BoundingBoxes tipo, char* rutaObj,float x, float y, float z){
	return _entidad->crear_objeto(tipo,rutaObj,x, y, z, 70);
}

void Motor::poner_camara_a_entidad(unsigned short id){
	_entidad->poner_camara_a_entidad(id);
}   

void Motor::Mover(uint8_t id, float x, float y, float z){
	_entidad->setVelocidad(id,x,y,z);
}

void Motor::setVelocidad(uint8_t id, unsigned short _i_direccion, float x, float y, float z){
	_entidad->setVelocidad(id,_i_direccion,x,y,z);
}

void Motor::setPositionXZ(unsigned short id, float x, float z){
	_entidad->setPositionXZ(id,x,z);
}
void Motor::haz_desaparecer(unsigned short _id){
	_entidad->haz_desaparecer(_id);
}

void Motor::saltar(unsigned short _i_id){
	_entidad->saltar(_i_id);
}

void Motor::saltar(unsigned short _i_id,int force){
	_entidad->saltar(_i_id,force);
}

void Motor::abrir_puerta(unsigned short _i_id){
	_entidad->abrir_puerta(_i_id);
}

void Motor::Dash(unsigned short _i_direccion, unsigned short id){
	_entidad->Dash(_i_direccion,id);
}

void Motor::asigna_input(Input* _i_input_jugador) {
	_entidad->asigna_input(_i_input_jugador);
}

void Motor::update(double dt){
	_entidad->update(dt);
}

void Motor::render(float _i_interpolacion){
	_entidad->interpola_posiciones(_i_interpolacion);
	_entidad->render();
}

void Motor::VelocidadDireccion(unsigned short id, unsigned short _i_direccion, unsigned short _i_velocidad){
	_entidad->VelocidadDireccion(id,_i_direccion, _i_velocidad);
}

void Motor::set_text_vida(int vida){
	_entidad->set_text_vida(vida);
}

void Motor::resetear_camara(){
	_entidad->resetear_camara();
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
	return _entidad->getIrrlichtDevice();
}

void Motor::colorear_nodo(unsigned short id, short r, short g, short b){
	_entidad->colorear_nodo(id,r,g,b);
}
