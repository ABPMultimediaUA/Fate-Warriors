#include "Camara.h"

#include "../Input/Input.h"
#include "../Interfaz_Libs/Lib_Math.h"
#include "../Personajes/Interpolacion.h"
#include "../Utilidades/Vector.h"
#include "../Moose_Engine/src/iNodoModelado.h"
#include <GLFW/glfw3.h>
#include "../Moose_Engine/src/TMooseEngine.h"
#include "../Moose_Engine/src/iNodoCamara.h"
#include "../Interfaz/Motor.h"
//asdasdsda
#include <iostream> 


Camara::Camara(bool activa) {
	//creamos el iNodoCamara que inicializa una TCamara en el arbol de escena
	_Camara = new iNodoCamara(activa);
	_inicial = glm::vec3(0,0,1);

	float fx = _inicial.x;
	float fy = _inicial.y;
	float fz = _inicial.z;
	
	_posicion_interpolable = true;
	Vector3 _inicial_aux(fx,fy,fz);

	_Prota = 0; 
	_direction = 0; 
	_zdirection = 20;
	_position = glm::vec3(0,0,0); 
	_target = glm::vec3(1,1,1);
	
	_xf = 0; 
	_yf = 0; 
	_zf = 0; 
	_sensibilidadX = 10; 
	_sensibilidadY = 10; 
	_changeX = 0; 
	_changeY = 0; 			
	_dot = _det = _angle = _angleRad = 0;
	_interpolacion = new Interpolacion(Vector3(_inicial_aux._x, _inicial_aux._y, _inicial_aux._z));		
	_interpolacion_colision = new Interpolacion(Vector3(_inicial_aux._x, _inicial_aux._y, _inicial_aux._z));
	_unlocked = false;	
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
		
		_position = glm::vec3(position._x, position._y+10, position._z); 
		_Camara->mover(position);

		Vector3 posicion(_position.x,_position.y+10,_position.z);
		_interpolacion_colision->actualiza_posicion(posicion);

}

void Camara::set_position_interpolada(Vector3 position) {
	_position = glm::vec3(position._x, position._y + 50, position._z); 
	_Camara->mover(position);
}

void Camara::Camara_setTarget(Vector3 targetPos){
	_target = glm::vec3(targetPos._x, targetPos._y + 50, targetPos._z); 
	_Camara->setTarget(targetPos);
}

void Camara::Camara_setProta(iNodoModelado* prota) {
	_Prota = prota; 
	_ProtaBoundingCenter = prota->getBB();//_Prota-> getBoundingBox().getCenter(); 
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
	_zdirection = 20;
}

void Camara::Camara_Update() {
	float offX = 0;
	float offY = 0;
	_changeX = 0;
	_changeY = 0;
	


	// Esto se hace hasta que se pueda usar el de Input sin que se choque con los bordes de pantalla y se quede atascado el raton
	if(_input->get_posiciona_camara() && _input->get_mover_camara()) {
		// Obtener la posicion del cursor
		 offX = TMooseEngine::get_instancia()->getMouseOffsetX();
		 offY = TMooseEngine::get_instancia()->getMouseOffsetY();

		_changeX = (offX) * _sensibilidadX;
		_changeY = (offY) * _sensibilidadY;
	}
	else {
		if(_input->get_mover_camara()) {
			Vector2* _vector_movimiento = _input->get_vector_camara();
			_changeX = 10 * (_vector_movimiento->_x * _vector_movimiento->_x) * lib_math_sgn(_vector_movimiento->_x);
			_changeY = 10 * (_vector_movimiento->_y * _vector_movimiento->_y) * lib_math_sgn(_vector_movimiento->_y);
		}
	}

	_direction += _changeX; 	// Rotacion de la camara en horizontal xrot
	_zdirection -= _changeY; 	// Rotacion de la camara en vertical  yrot

	_gradosRotacion = 35; 

	if(!_unlocked){

		if (_zdirection < -10) { 
		_zdirection = -10;  
		} 
		else if (_zdirection > 20) { 
		_zdirection =20;  
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

	update_position();
}




void Camara::update_position() {
//codigo hecho a base de mirar diversos métodos en varios foros y libros
	
	// Antes de nada nos aseguramos de que el prota ha sido inicializado 
	if (_Prota != nullptr) {
		// Posicion estándar del jugador que usaremos para el seguimiento de la camara
			float ax = _Prota-> getPosition()._x;
			float ay = _Prota-> getPosition()._y;
			float az = _Prota-> getPosition()._z; 
			Vector3 playerPos(
					_Prota-> getPosition()._x, 
					_Prota-> getPosition()._y + 20,  //falta el -protaboundingcenter Y 
					_Prota-> getPosition()._z); 
		
		float distancia;

		//esta variable permite desbloquear la limitacion de distancia de la camara para algunas pruebas
		if(!_unlocked){
			distancia = 25.0f;}
		else{
			distancia = 200.0f;}

		//calculamos la posicion de la camara en funcion de los vectores de direccion y la posicion del jugador
		//esto genera las posiciones para un movimiento orbital en tercera persona alrededor del jugador
		float xf = playerPos._x - cos(_zdirection * PIs / 180.0f) * cos(_direction * PIs / 180.0f) * distancia; 
		
		float yf = playerPos._y - sin(_zdirection * PIs / 180.0f) * distancia; 

		float zf = playerPos._z + cos(_zdirection * PIs / 180.0f) * sin(_direction * PIs / 180.0f) * distancia; 

		if (_Prota-> getPosition()._y >= 0) {	// Calculos de la camara para una Y positiva
			
		
			if(_posicion_interpolable){
				this->Camara_setPosition(
						Vector3(xf, 
								yf + _ProtaBoundingCenter._y - 10, 
								zf));
				this->Camara_setTarget(	
					Vector3(_Prota-> getPosition()._x, 
							_Prota-> getPosition()._y + _ProtaBoundingCenter._y + 25.0f, 
							_Prota-> getPosition()._z)); 

			}
			else{
				this->Camara_setPosition(
						Vector3(xf,
								40,
								zf)
				);
				this->Camara_setTarget(	
					Vector3(_Prota-> getPosition()._x, 
								40, 
							_Prota-> getPosition()._z)); 
			}	
		}
		
		else {	// Calculos de la camara para una Y negativa
			
			//this->Camara_setPosition(
			//		Vector3(xf, 
			//				yf - _ProtaBoundingCenter._y - _Prota->getPosition()._y - 10, zf)); 
			//
			//this->Camara_setTarget(
			//		Vector3(_Prota-> getPosition()._x + _ProtaBoundingCenter._x, 
			//				(_ProtaBoundingCenter._y + 25.0f), 
			//				_Prota-> getPosition()._z + _ProtaBoundingCenter._z)); 
			if(_posicion_interpolable){
				this->Camara_setPosition(
						Vector3(xf, 
								yf + _ProtaBoundingCenter._y - 10, 
								zf));
				 //std::cout<< "Entra"
				this->Camara_setTarget(	
					Vector3(_Prota-> getPosition()._x, 
							_Prota-> getPosition()._y + _ProtaBoundingCenter._y + 25.0f, 
							_Prota-> getPosition()._z));
			}
			else{
				this->Camara_setPosition(
						Vector3(xf,
								40,
								zf)
				);
				this->Camara_setTarget(	
					Vector3(_Prota-> getPosition()._x, 
								40, 
							_Prota-> getPosition()._z)); 
			}
		}
		
		
		// Calculo de la direccion de la camara
		_camaraDir = _target - _position;
		/*std::cout << "target " << _target.x << "\n";
		std::cout << "position " << _position.x << "\n";*/
		//_camaraDir = glm::normalize(_camaraDir);

		glm::vec3 inicial(0,0,1); //v1

        
		// Angulo entre el vector inicial de referencia
		// y el vector de direccion actual 

        _dot = inicial.x * _camaraDir.x + inicial.z * _camaraDir.z;
        _det = inicial.x * _camaraDir.z - inicial.z * _camaraDir.x;


        _angle = -(atan2f(_det,_dot)/PIs)*180;
			 
        
		if(_angle<0){
            _angle+=360;
        }

        _angleRad = _angle * (PIs/180);

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

void Camara::rota_camara_sin_interpolacion(short _rotacion_en_x, short _rotacion_en_y){
	_direction = _rotacion_en_x;
	_zdirection = _rotacion_en_y * -1; // DEbe ir entre -5 (abajo) y -60 (arriba)

	//limitaciones del valor zdirection. Esto establece los limites entre los cuales se puede levantar/bajar la camara para evitar
	//que se desplace demasiado o provoque errores de visualizacion 
	if (_zdirection < -10) {
		_zdirection = -10; 
	}
	else if (_zdirection > 35) {
		_zdirection = 35; 
	}

	Vector3* _posicion = _interpolacion->get_posicion_actual();
	_interpolacion->actualiza_posicion(Vector3(_posicion->_x,_posicion->_y,_posicion->_z));
	_interpolacion->actualiza_posicion(Vector3(_posicion->_x,_posicion->_y,_posicion->_z));
}