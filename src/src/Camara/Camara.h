/*
 * camara.h
 *
 *  Created on: Nov 15, 2017
 *      Author: manu
 */

#include "irrlicht/irrlicht.h"
using namespace irr;

#ifndef SRC_CPP_CAMARA_H_
#define SRC_CPP_CAMARA_H_

class Camara{

public:
	Camara(scene::ISceneManager* smgr, IrrlichtDevice* device);
	void Camara_setPosition(core::vector3df position);
	void Camara_setTarget(core::vector3df targetPos);         //ajusta el target de la Camara a una posicion
	void Camara_setProta(scene::ISceneNode* prota);  //ajusta el target de la Camara a otro nodo
	core::vector3df Camara_getPosition();
	core::vector3df Camara_getTarget();
	core::vector3df Camara_getDirection();
	void Camara_Update(); //updatea la Camara usando el device
	~Camara();

private:
	scene::ISceneNode* _Prota;         //personaje protagonista A.K.A Target
	float _ProtaBoundingCenter; 	   //centro de la bounding box del personaje
	scene::ICameraSceneNode* _Camara;  //camara de irrlicht
	core::vector3df _position;		 	//posicion de la camara
	core::vector3df _target; 		   //target de la camara
	IrrlichtDevice* _Cdevice;
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
};



#endif /* SRC_CPP_CAMARA_H_ */


