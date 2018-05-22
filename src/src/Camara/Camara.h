#include "../Utilidades/Vector.h"
#include <glm/ext.hpp>

#ifndef SRC_CPP_CAMARA_H_
#define SRC_CPP_CAMARA_H_

class Vector3;

class Input;
class Interpolacion;
class iNodoModelado;
class GLFWwindow;
class iNodoCamara;
class Camara{

public:
	Camara(bool activa);
	~Camara();
	
	void Camara_setPosition(Vector3 position);
	void Camara_setPositionColision(Vector3 position);
	void Camara_setTarget(Vector3 targetPos);         //ajusta el target de la Camara a una posicion
	void Camara_setProta(iNodoModelado* prota);  //ajusta el target de la Camara a otro nodo
	Vector3 Camara_getPosition();
	Vector3 Camara_getTarget();
	Vector3 Camara_getDirection();
	float Camara_getAngle();		//devuelve el angulo entre la camara y la direccion del jugador en grados (para el calculo de movimiento)		
	float Camara_getAngleRad();		//devuelve el angulo entre la camara y la direccion del jugador en radianes (para el calculo de movimiento)
	void Camara_Update(); 			//updatea la Camara usando el device
	void update_position();			//actualiza la posicion teniendo en cuenta la colision de la camara con otros elementos del mundo
	void asigna_input(Input* _i_input_jugador);

	void set_posicion_inicial(short _i_direccion); 	// Pone la posicion inicial de la camara

	void interpola_posicion(float _i_interpolacion);
	void interpola_target(Vector3 _i_posicion_interpolada);
	void Camara_reset(short _i_direccion); //reajusta la camara para que mire justo hacia delante, hacia donde mira el personaje

	void rota_camara_sin_interpolacion(short _i_direccion_x, short _rotacion_en_y);		// Rota la camara a una posicion

	inline void set_posicion_interpolable(bool estado) { _posicion_interpolable = estado; };

private:
	//las nuevas variables de escena del ME
	GLFWwindow* _OGLWindow;
	glm::vec3 _inicial;
	glm::vec3 _position;		 	//posicion de la camara
	glm::vec3 _target; 		   //target de la camara
	iNodoCamara* _Camara;  //camara de irrlicht
	
	//GLFW mouse input
	float _lastX, _lastY, _xpos, _ypos;
	bool _firstMouse;

	//---//
	
	
	iNodoModelado* _Prota;         //personaje protagonista A.K.A Target
	Vector3 _ProtaBoundingCenter; 	   //centro de la bounding box del personaje
	
	//IrrlichtDevice* _Cdevice;

	
									//hacia donde mira la camara como referencia

	float _dot, _det, _angle, _angleRad;
	float _direction;	 //desplazamiento del raton
	float _zdirection;   //desplazamiento del raton
	float _xf;
	float _yf;
	float _zf;
	float _sensibilidadX;
	float _sensibilidadY;
	float _changeX;
	float _changeY;
	bool _posicion_interpolable;
	glm::vec3 _camaraDir; //direccion hacia la que mira la camara que se actualiza en el update
	float cursorPos;
	unsigned short _gradosRotacion;
	Input* _input; 	// Input del control de camara
	bool _unlocked; //para que se pueda desbloquear la camara y mandarla a cuenca si se quiere
	bool _hay_colision; // Dice si hay colision para interpolar con la posicion de colision
	Interpolacion* _interpolacion;
	Interpolacion* _interpolacion_colision;
	
	void set_position_interpolada(Vector3 position); //Pone la nueva posicion interpolada para renderizar
};



#endif /* SRC_CPP_CAMARA_H_ */


