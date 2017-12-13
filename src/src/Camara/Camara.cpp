/*
 * camara.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: manu
*/

#include "Camara.h"
#include <iostream> 

Camara::Camara(scene::ISceneManager * smgr, IrrlichtDevice * device) {
	_Camara = smgr-> addCameraSceneNode(0, 
										core::vector3df(0, 0, 0), 
										core::vector3df(1, 1, 1)
											); 
	//_Camara = smgr->addCameraSceneNodeFPS();
	
	_Cdevice = device; 
	_Cdevice->getCursorControl()->setVisible(false); 
	_inicial = core::vector3df(0,0,1);
	 _Prota = 0; 
	 _direction = 0; 
	 _zdirection = 0; 
	 _position = core::vector3df(0, 0, 0); 
	 _target = core::vector3df(1, 1, 1); 
	 _xf = 0; 
	 _yf = 0; 
	 _zf = 0; 
	 _sensibilidadX = 256; 
	 _sensibilidadY = 256; 
	 _changeX = 0; 
	 _changeY = 0; 			
	 _dot = _det = _angle = _angleRad = 0;			
}

void Camara::Camara_setPosition(core::vector3df position) {
	_position = position; 
	_Camara->setPosition(_position);
}

void Camara::Camara_setTarget(core::vector3df targetPos) {
	_target = targetPos; 
	_Camara->setTarget(_target); 
}

void Camara::Camara_setProta(scene::ISceneNode * prota) {
	_Prota = prota; 
	_ProtaBoundingCenter = _Prota-> getBoundingBox().getCenter(); 
}

core::vector3df Camara::Camara_getPosition(){
	return(_position);
}

core::vector3df Camara::Camara_getTarget(){
	return(_target);
}

core::vector3df Camara::Camara_getDirection(){
	return(_camaraDir);
}

void Camara::Camara_Update() {
	//desactivamos el cursor del raton
	
	//obtener la posicion del cursor
	cursorPos = _Cdevice-> getCursorControl()-> getRelativePosition(); 
	_changeX = (cursorPos.X - 0.5) * _sensibilidadX; 
	_changeY = (cursorPos.Y - 0.5) * _sensibilidadY; 

	_direction += _changeX; //rotacion de la camara en horizontal xrot
	_zdirection -= _changeY; //rotacion de la camara en vertical  yrot

	_gradosRotacion = 55; 

	if (_zdirection < -_gradosRotacion) {
		_zdirection = -_gradosRotacion; 
	}

	else if (_zdirection > _gradosRotacion) {
		_zdirection = _gradosRotacion; 
	}
	_Cdevice-> getCursorControl()-> setPosition(0.5f, 0.5f); 
	


	//antes de nada nos aseguramos de que el prota ha sido inicializado 
	if (_Prota != nullptr) {
		//posicion estándar del jugador que usaremos para el seguimiento de la camara
		core::vector3df playerPos = core::vector3df(
					_Prota-> getPosition().X, 
					_Prota-> getPosition().Y - _ProtaBoundingCenter.Y, 
					_Prota-> getPosition().Z); 
		
		float xf = playerPos.X - cos(_zdirection * irr::core::PI / 180.0f) * cos(_direction * irr::core::PI / 180.0f) * 128.0f; 
		
		float yf = playerPos.Y - sin(_zdirection * M_PI / 180.0f) * 128.0f; 

		float zf = playerPos.Z + cos(_zdirection * irr::core::PI / 180.0f) * sin(_direction * irr::core::PI / 180.0f) * 128.0f; 
		
		if (_Prota-> getPosition().Y >= 0) {//calculos de la camara para una Y positiva
			
		//std::cout<<"llego loko"<<std::endl;
			//std::cout << playerPos.Y << std::endl; 
			this->Camara_setPosition(
					core::vector3df(xf, 
							yf + _ProtaBoundingCenter.Y, 
							zf)); 
			
			this->Camara_setTarget(	
					core::vector3df(_Prota-> getPosition().X + _ProtaBoundingCenter.X, 
							_Prota-> getPosition().Y - _ProtaBoundingCenter.Y * 1.5f, 
							_Prota-> getPosition().Z + _ProtaBoundingCenter.Z)); 
				
		}

		else {//calculos de la camara para una Y negativa
			this->Camara_setPosition(
					core::vector3df(xf, 
							yf - _ProtaBoundingCenter.Y - _Prota->getPosition().Y, zf)); 
			
			this->Camara_setTarget(
					core::vector3df(_Prota-> getPosition().X + _ProtaBoundingCenter.X, 
							(_ProtaBoundingCenter.Y * 0.5), 
							_Prota-> getPosition().Z + _ProtaBoundingCenter.Z)); 
		}

		
		//calculo de la direccion de la camara
		_camaraDir = this->Camara_getTarget() - this->Camara_getPosition();
		_camaraDir = _camaraDir.normalize();

		core::vector3df inicial(0,0,1); //v1

        

        _dot = inicial.X*_camaraDir.X + inicial.Z*_camaraDir.Z;
        _det = inicial.X*_camaraDir.Z - inicial.Z*_camaraDir.X;

        _angle = -(atan2f(_det,_dot)/M_PI)*180;

        if(_angle<0){
            _angle+=360;
        }

        _angleRad = _angle*(M_PI/180);

	}

}

float Camara::Camara_getAngle(){
	return(_angle);
}

float Camara::Camara_getAngleRad(){
	return(_angleRad);
}

Camara::~Camara() {

}