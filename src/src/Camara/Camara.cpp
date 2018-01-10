#include "Camara.h"

#include "../Input.h"
#include "../Interfaz_Libs/Lib_Math.h"
#include "../Personajes/Interpolacion.h"
#include "../Utilidades/Vector.h"

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
	Vector3 _inicial_aux(_inicial.X,_inicial.Y,_inicial.Z);

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
	_interpolacion = new Interpolacion(_inicial_aux);		
	_interpolacion_colision = new Interpolacion(_inicial_aux);		
}

void Camara::Camara_setPosition(core::vector3df position) {
	_position = position; 
	_Camara->setPosition(_position);

	Vector3 posicion(_position.X,_position.Y,_position.Z);
	_interpolacion->actualiza_posicion(posicion);

	if(!_hay_colision)
		_interpolacion_colision->actualiza_posicion(posicion);

	_hay_colision = false;
}

void Camara::Camara_setPositionColision(core::vector3df position) {
	_hay_colision = true;
	_position = position; 
	_Camara->setPosition(_position);

	Vector3 posicion(_position.X,_position.Y,_position.Z);
	_interpolacion_colision->actualiza_posicion(posicion);
}

void Camara::set_position_interpolada(core::vector3df position) {
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

void Camara::Camara_reset(short _i_direccion){
	_direction = _i_direccion-90;
	_zdirection = -20;
}

void Camara::Camara_Update() {
	// Desactivamos el cursor del raton
	_changeX = 0;
	_changeY = 0;
	
	// Esto se hace hasta que se pueda usar el de Input sin que se choque con los bordes de pantalla y se quede atascado el raton
	if(_input->get_posiciona_camara() && _input->get_mover_camara()) {
		// Obtener la posicion del cursor
		cursorPos = _Cdevice-> getCursorControl()-> getRelativePosition(); 

		_changeX = (cursorPos.X - 0.5) * _sensibilidadX; 
		_changeY = (cursorPos.Y - 0.5) * _sensibilidadY; 

		_Cdevice-> getCursorControl()-> setPosition(0.5f, 0.5f); 

		//std::cout << "Por Irrlicht\n";
	}

	else {
		if(_input->get_mover_camara()) {
			Vector2* _vector_movimiento = _input->get_vector_camara();
			_changeX = 10 * (_vector_movimiento->_x * _vector_movimiento->_x) * lib_math_sgn(_vector_movimiento->_x);
			_changeY = 10 * (_vector_movimiento->_y * _vector_movimiento->_y) * lib_math_sgn(_vector_movimiento->_y);

			/*std::cout << "Vector X " << _vector_movimiento->_x << "\n";
			std::cout << "Vector Y " << _vector_movimiento->_y << "\n";*/

			/*std::cout << "El signo de X es " << (int)lib_math_sgn(_vector_movimiento->_x) << "\n";
			std::cout << "El signo de Y es " << (int)lib_math_sgn(_vector_movimiento->_y) << "\n";*/

			//std::cout << "Por input de Pablo \n";
		}
	}

	_direction += _changeX; 	// Rotacion de la camara en horizontal xrot
	_zdirection -= _changeY; 	// Rotacion de la camara en vertical  yrot

	_gradosRotacion = 35; 

	if (_zdirection < -60) {
		_zdirection = -60; 
	}

	else if (_zdirection > -5) {
		_zdirection = -5; 
	}

	if(_direction >= 360)
		_direction -= 360;
	if(_direction < 0)
		_direction += 360;
	
	/*std::cout << "Direction  " << _direction << "\n";
	std::cout << "Zdirection " << _zdirection << "\n";*/

	// Antes de nada nos aseguramos de que el prota ha sido inicializado 
	if (_Prota != nullptr) {
		// Posicion estándar del jugador que usaremos para el seguimiento de la camara
		core::vector3df playerPos = core::vector3df(
					_Prota-> getPosition().X, 
					_Prota-> getPosition().Y - _ProtaBoundingCenter.Y, 
					_Prota-> getPosition().Z); 
		
		float xf = playerPos.X - cos(_zdirection * irr::core::PI / 180.0f) * cos(_direction * irr::core::PI / 180.0f) * 20.0f; 
		
		float yf = playerPos.Y - sin(_zdirection * irr::core::PI / 180.0f) * 20.0f; 

		float zf = playerPos.Z + cos(_zdirection * irr::core::PI / 180.0f) * sin(_direction * irr::core::PI / 180.0f) * 20.0f; 

		if (_Prota-> getPosition().Y >= 0) {	// Calculos de la camara para una Y positiva
			
		//std::cout<<"llego loko"<<std::endl;
			//std::cout << playerPos.Y << std::endl; 
			this->Camara_setPosition(
					core::vector3df(xf, 
							yf + _ProtaBoundingCenter.Y, 
							zf)); 
			
			this->Camara_setTarget(	
					core::vector3df(_Prota-> getPosition().X + _ProtaBoundingCenter.X, 
							_Prota-> getPosition().Y + _ProtaBoundingCenter.Y * 1.5f, 
							_Prota-> getPosition().Z + _ProtaBoundingCenter.Z)); 
				
		}
		
		else {	// Calculos de la camara para una Y negativa
			this->Camara_setPosition(
					core::vector3df(xf, 
							yf - _ProtaBoundingCenter.Y - _Prota->getPosition().Y, zf)); 
			
			this->Camara_setTarget(
					core::vector3df(_Prota-> getPosition().X + _ProtaBoundingCenter.X, 
							(_ProtaBoundingCenter.Y * 0.5), 
							_Prota-> getPosition().Z + _ProtaBoundingCenter.Z)); 
		}
		
		
		// Calculo de la direccion de la camara
		_camaraDir = this->Camara_getTarget() - this->Camara_getPosition();
		_camaraDir = _camaraDir.normalize();

		core::vector3df inicial(0,0,1); //v1

        
		// Angulo entre el vector inicial de referencia
		// y el vector de direccion actual 
        _dot = inicial.X * _camaraDir.X + inicial.Z*_camaraDir.Z;
        _det = inicial.X * _camaraDir.Z - inicial.Z*_camaraDir.X;

        _angle = -(atan2f(_det,_dot)/M_PI)*180;

        if(_angle<0){
            _angle+=360;
        }

        _angleRad = _angle * (M_PI/180);

	}

}

float Camara::Camara_getAngle(){
	return(_angle);
}

float Camara::Camara_getAngleRad(){
	return(_angleRad);
}

Camara::~Camara() {
	delete _interpolacion;
	delete _interpolacion_colision;
}

void Camara::asigna_input(Input* _i_input_jugador){
	_input = _i_input_jugador;
}

void Camara::interpola_posicion(float _i_interpolacion) {
	if(!_hay_colision) {
		Vector3 _posicion_interpolada = _interpolacion->interpola_posicion(_i_interpolacion);
		set_position_interpolada(core::vector3df(_posicion_interpolada._x, _posicion_interpolada._y, _posicion_interpolada._z));
	}
	else {
		Vector3 _posicion_interpolada = _interpolacion_colision->interpola_posicion(_i_interpolacion);
		set_position_interpolada(core::vector3df(_posicion_interpolada._x, _posicion_interpolada._y, _posicion_interpolada._z));
	}
}

void Camara::interpola_target(Vector3 _i_posicion_interpolada) {
	Camara_setTarget(core::vector3df(_i_posicion_interpolada._x, _i_posicion_interpolada._y, _i_posicion_interpolada._z));
}