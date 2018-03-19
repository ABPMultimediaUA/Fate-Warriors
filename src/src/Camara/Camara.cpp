#include "Camara.h"

#include "../Input.h"
#include "../Interfaz_Libs/Lib_Math.h"
#include "../Personajes/Interpolacion.h"
#include "../Utilidades/Vector.h"
#include "../Moose_Engine/src/iNodoModelado.h"
#include <GLFW/glfw3.h>
#include "../Moose_Engine/src/TMooseEngine.h"
#include "../Moose_Engine/src/iNodoCamara.h"
#include "../Interfaz/Motor.h"

#include <iostream> 

Camara::Camara(scene::ISceneManager * smgr, IrrlichtDevice * device) {
	//_Camara = smgr-> addCameraSceneNode(0, 
	//									core::vector3df(0, 0, 0), 
	//									core::vector3df(1, 1, 1)
	//										); 
	//_Camara = smgr->addCameraSceneNodeFPS();
	
	_Cdevice = device; 
	_Cdevice->getCursorControl()->setVisible(false); 
	//_inicial = core::vector3df(0,0,1);
	//Vector3 _inicial_aux(_inicial.X,_inicial.Y,_inicial.Z);

	_Prota = 0; 
	_direction = 0; 
	_zdirection = -20;
	//_position = core::vector3df(0, 0, 0); 
	//_target = core::vector3df(1, 1, 1); 
	_xf = 0; 
	_yf = 0; 
	_zf = 0; 
	_sensibilidadX = 256; 
	_sensibilidadY = 256; 
	_changeX = 0; 
	_changeY = 0; 			
	_dot = _det = _angle = _angleRad = 0;
	//_interpolacion = new Interpolacion(_inicial_aux);		
	//_interpolacion_colision = new Interpolacion(_inicial_aux);
	_unlocked = false;	//angel busca esto	
}

Camara::Camara(bool activa, GLFWwindow* _i_window) {
	//_Camara = smgr-> addCameraSceneNode(0, 
	//									core::vector3df(0, 0, 0), 
	//									core::vector3df(1, 1, 1)
	//										); 
	//_Camara = smgr->addCameraSceneNodeFPS();

	_OGLWindow = Motor::Motor_GetInstance()->getEngine()->getWindow();
	
	//_Cdevice = device; 
	//_Cdevice->getCursorControl()->setVisible(false); 
	//_inicial = core::vector3df(0,0,1);
	_inicial = glm::vec3(0,0,1);
	Vector3 _inicial_aux(_inicial.x,_inicial.y,_inicial.z);

	_Prota = 0; 
	_direction = 0; 
	_zdirection = -20;
	_position = glm::vec3(0,0,0); 
	_target = glm::vec3(1,1,1);
	
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
	_unlocked = false;	//angel busca esto	
}

void Camara::Camara_setPosition(Vector3 position) {
	_position = glm::vec3(position._x, position._y, position._z); 
	_Camara->mover(position);

	Vector3 posicion(_position.x,_position.y,_position.z);
	_interpolacion->actualiza_posicion(posicion);

	if(!_hay_colision)
		_interpolacion_colision->actualiza_posicion(posicion);

	_hay_colision = false;
}

void Camara::Camara_setPositionColision(Vector3 position) {
	_hay_colision = true;
	_position = glm::vec3(position._x, position._y, position._z); 
	_Camara->mover(position);

	Vector3 posicion(_position.x,_position.y,_position.z);
	_interpolacion_colision->actualiza_posicion(posicion);
}

void Camara::set_position_interpolada(Vector3 position) {
	_position = glm::vec3(position._x, position._y, position._z); 
	_Camara->mover(position);
}

void Camara::Camara_setTarget(Vector3 targetPos) {
	_target = glm::vec3(targetPos._x, targetPos._y, targetPos._z); 
	_Camara->setTarget(targetPos);
	//this->setTarget(targetPos); 
}

void Camara::Camara_setProta(iNodoModelado* prota) {
	_Prota = prota; 
	//_ProtaBoundingCenter = 0;//_Prota-> getBoundingBox().getCenter(); 
}

Vector3 Camara::Camara_getPosition(){
	Vector3 retorno(_position.x, _position.y, _position.z);
	return retorno;
}

Vector3 Camara::Camara_getTarget(){
	Vector3 retorno(_target.x, _target.y, _target.z);
	return retorno;
}

Vector3 Camara::Camara_getDirection(){
	Vector3 retorno(_camaraDir.x, _camaraDir.y, _camaraDir.z);
	return retorno;
}

void Camara::Camara_reset(short _i_direccion){
	_direction = _i_direccion-90;
	_zdirection = -20;
}

void Camara::Camara_Update() {
	// Desactivamos el cursor del raton
	_changeX = 0;
	_changeY = 0;
	
	//input de raton de openGL BOIIIII
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
	//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	//glfwSetCursorPosCallback(window, mouse_callback); 

	

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

	if(!_unlocked){
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
	}
	else{
		if(_direction >= 360)
			_direction -= 360;
		if(_direction < 0)
			_direction += 360;
	}
	/*std::cout << "Direction  " << _direction << "\n";
	std::cout << "Zdirection " << _zdirection << "\n";*/

	update_position();
}


void Camara::update_position() {
	// Antes de nada nos aseguramos de que el prota ha sido inicializado 
	if (_Prota != nullptr) {
		// Posicion estándar del jugador que usaremos para el seguimiento de la camara
		core::vector3df playerPos = core::vector3df(
					_Prota-> getPosition()._x, 
					_Prota-> getPosition()._y,  //falta el -protaboundingcenter Y 
					_Prota-> getPosition()._z); 
		
		float distancia;

		if(!_unlocked){
			distancia = 20.0f;}
		else{
			distancia = 200.0f;
		}

		float xf = playerPos.X - cos(_zdirection * irr::core::PI / 180.0f) * cos(_direction * irr::core::PI / 180.0f) * distancia; 
		
		float yf = playerPos.Y - sin(_zdirection * irr::core::PI / 180.0f) * distancia; 

		float zf = playerPos.Z + cos(_zdirection * irr::core::PI / 180.0f) * sin(_direction * irr::core::PI / 180.0f) * distancia; 

		if (_Prota-> getPosition()._y >= 0) {	// Calculos de la camara para una Y positiva
			
		//std::cout<<"llego loko"<<std::endl;
			//std::cout << playerPos.Y << std::endl; 
			this->Camara_setPosition(
					Vector3(xf, 
							yf + _ProtaBoundingCenter.Y, 
							zf)); 
			
			this->Camara_setTarget(	
					Vector3(_Prota-> getPosition()._x + _ProtaBoundingCenter.X, 
							_Prota-> getPosition()._y + _ProtaBoundingCenter.Y * 1.5f, 
							_Prota-> getPosition()._z + _ProtaBoundingCenter.Z)); 
				
		}
		
		else {	// Calculos de la camara para una Y negativa
			this->Camara_setPosition(
					Vector3(xf, 
							yf - _ProtaBoundingCenter.Y - _Prota->getPosition()._y, zf)); 
			
			this->Camara_setTarget(
					Vector3(_Prota-> getPosition()._x + _ProtaBoundingCenter.X, 
							(_ProtaBoundingCenter.Y * 0.5), 
							_Prota-> getPosition()._z + _ProtaBoundingCenter.Z)); 
		}
		
		
		// Calculo de la direccion de la camara
		_camaraDir = _target - _position;
		_camaraDir = glm::normalize(_camaraDir);

		glm::vec3 inicial(0,0,1); //v1

        
		// Angulo entre el vector inicial de referencia
		// y el vector de direccion actual 
        _dot = inicial.x * _camaraDir.x + inicial.z * _camaraDir.z;
        _det = inicial.x * _camaraDir.z - inicial.z * _camaraDir.x;

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

void Camara::set_posicion_inicial(short _i_direccion) {
	_direction = _i_direccion-90;
	update_position();
	Vector3* _posicion = _interpolacion->get_posicion_actual();
	_interpolacion->actualiza_posicion(Vector3(_posicion->_x,_posicion->_y,_posicion->_z));
}


void Camara::interpola_posicion(float _i_interpolacion) {
	if(!_hay_colision) {
		Vector3 _posicion_interpolada = _interpolacion->interpola_posicion(_i_interpolacion);
		set_position_interpolada(_posicion_interpolada);
	}
	else {
		Vector3 _posicion_interpolada = _interpolacion_colision->interpola_posicion(_i_interpolacion);
		set_position_interpolada(_posicion_interpolada);
	}
}

void Camara::interpola_target(Vector3 _i_posicion_interpolada) {
	Camara_setTarget(_i_posicion_interpolada);
}