#include "Camara_aerea.h"

#include "../Input/Input.h"
#include "../Interfaz_Libs/Lib_Math.h"
#include "../Personajes/Interpolacion.h"
#include "../Utilidades/Vector.h"
#include "../Moose_Engine/src/iNodoModelado.h"
#include <GLFW/glfw3.h>
#include "../Moose_Engine/src/TMooseEngine.h"
#include "../Moose_Engine/src/iNodoCamara.h"
#include "../Interfaz/Motor.h"

void Camara_aerea::update_position() {
	
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

		if(!_unlocked){
			distancia = 25.0f;}
		else{
			distancia = 200.0f;}

		float xf = playerPos._x - cos(_zdirection * PIs / 180.0f) * cos(_direction * PIs / 180.0f) * distancia; 
		
		float yf = 100;

		float zf = playerPos._z + cos(_zdirection * PIs / 180.0f) * sin(_direction * PIs / 180.0f) * distancia; 

		if (_Prota-> getPosition()._y >= 0) {	// Calculos de la camara para una Y positiva
			
		//std::cout<<"llego loko"<<std::endl;
			//std::cout << playerPos.Y << std::endl; 
			if(_posicion_interpolable){
				this->Camara_setPosition(
						Vector3(xf, 
								yf, 
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
								yf, 
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

		/*std::cout << "X inicial " << inicial.x << "\ncamaraDir.x " << inicial.z << "\ncamaraDir.z" << _camaraDir.z << "\n";

		std::cout<<"_dot: " << _dot << "\n";
		std::cout<<"_det: " << _det << "\n";*/



        _angle = -(atan2f(_det,_dot)/PIs)*180;
		//std::cout<<"inicial X: "<< inicial.x << "Z: " << inicial.z << "\n";
		
		//std::cout<<"camaraDir X: "<< _camaraDir.x << "Z: " << _camaraDir.z << "\n";				 
        
		if(_angle<0){
            _angle+=360;
        }

        _angleRad = _angle * (PIs/180);
		//_angleRad = 2,5;
		//std::cout<<"ANGLE RAD: " << _angleRad << "\n";

	}
	
}

void Camara_aerea::Camara_Update(){
	
	// Desactivamos el cursor del raton
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
		//cursorPos = _Cdevice-> getCursorControl()-> getRelativePosition(); 

		//_changeX = (cursorPos.X - 0.5) * _sensibilidadX; 
		//_changeY = (cursorPos.Y - 0.5) * _sensibilidadY; 
//
		//_Cdevice-> getCursorControl()-> setPosition(0.5f, 0.5f); 
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

	
	/*std::cout << "Direction  " << _direction << "\n";
	std::cout << "Zdirection " << _zdirection << "\n";*/

	update_position();
}