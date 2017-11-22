/*
 * camara.h
 *
 *  Created on: Nov 15, 2017
 *      Author: manu
 */
#include <irrlicht.h>
using namespace irr;

#ifndef SRC_CPP_CAMARA_H_
#define SRC_CPP_CAMARA_H_

class camara{
public:
	camara(scene::ISceneNode* prota, scene::ISceneManager* smgr);
	void setTarget(core::vector3df targetPos);         //ajusta el target de la camara a una posicion
	void setTargetN(scene::ISceneNode* nodoObjetivo);  //ajusta el target de la camara a otro nodo
	void Update(IrrlichtDevice* device); //updatea la camara usando el device
	~camara();
private:
	scene::ISceneNode* pProta;        //personaje protagonista
	scene::ICameraSceneNode* pCamara; //camara de irrlicht
	core::vector3df posicion;		 //posicion de la camara
	float direction;	//desplazamiento del raton
	float zdirection;   //desplazamiento del raton
};



#endif /* SRC_CPP_CAMARA_H_ */
