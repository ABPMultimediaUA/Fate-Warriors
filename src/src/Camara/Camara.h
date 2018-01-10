#include "irrlicht/irrlicht.h"
using namespace irr;

#ifndef SRC_CPP_CAMARA_H_
#define SRC_CPP_CAMARA_H_

class Vector3;

class Input;
class Interpolacion;
class Camara{

public:
	Camara(scene::ISceneManager* smgr, IrrlichtDevice* device);
	~Camara();
	
	void Camara_setPosition(core::vector3df position);
	void Camara_setPositionColision(core::vector3df position);
	void Camara_setTarget(core::vector3df targetPos);         //ajusta el target de la Camara a una posicion
	void Camara_setProta(scene::ISceneNode* prota);  //ajusta el target de la Camara a otro nodo
	core::vector3df Camara_getPosition();
	core::vector3df Camara_getTarget();
	core::vector3df Camara_getDirection();
	float Camara_getAngle();
	float Camara_getAngleRad();
	void Camara_Update(); //updatea la Camara usando el device
	void asigna_input(Input* _i_input_jugador);

	void interpola_posicion(float _i_interpolacion);
	void interpola_target(Vector3 _i_posicion_interpolada);
	void Camara_reset(short _i_direccion);
private:
	scene::ISceneNode* _Prota;         //personaje protagonista A.K.A Target
	core::vector3df _ProtaBoundingCenter; 	   //centro de la bounding box del personaje
	scene::ICameraSceneNode* _Camara;  //camara de irrlicht
	core::vector3df _position;		 	//posicion de la camara
	core::vector3df _target; 		   //target de la camara
	IrrlichtDevice* _Cdevice;

	core::vector3df _inicial; //vector de direccion inicial 
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
	core::vector3df _camaraDir; //direccion hacia la que mira la camara que se actualiza en el update
	core::position2d<f32> cursorPos;
	unsigned short _gradosRotacion;
	Input* _input; 	// Input del control de camara

	bool _hay_colision; // Dice si hay colision para interpolar con la posicion de colision
	Interpolacion* _interpolacion;
	Interpolacion* _interpolacion_colision;
	
	void set_position_interpolada(core::vector3df position); //Pone la nueva posicion interpolada para renderizar
};



#endif /* SRC_CPP_CAMARA_H_ */


