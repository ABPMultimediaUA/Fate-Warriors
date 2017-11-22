/*
 * camara.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: manu
 */

#include "camara.h"

camara::camara(scene::ISceneNode* prota, scene::ISceneManager* smgr){
	this->pProta = prota;
	this->pCamara = smgr->addCameraSceneNode(0,
									  core::vector3df(0,0,0),
									  core::vector3df(prota->getPosition().X,
											  	  	  prota->getPosition().Y+180.f,
													  prota->getPosition().Z));
	zdirection = 0;
	direction = 0;
}

void camara::Update(IrrlichtDevice* device){
	device->getCursorControl()->setVisible(false); //desactivar la visibilidad del cursor del raton


	core::position2d<f32> cursorPos =
					device->getCursorControl()->getRelativePosition();
			this->pCamara =
					device->getSceneManager()->getActiveCamera();
			core::vector3df cameraPos = this->pCamara->getAbsolutePosition();

			float sensibilidadX = 256.0f; //sensibilidad de la camara en el eje X
			float sensibilidadY = 256.0f; //sensibilidad de la camara en el eje Y

			float change_x = (cursorPos.X - 0.5) * sensibilidadX;
			float change_y = (cursorPos.Y - 0.5) * sensibilidadY;

			direction += change_x; //rotacion de la camara en horizontal
			zdirection -= change_y; //rotacion de la camara en vertical

			unsigned short gradosRotacion = 55; //grados que puede rotar la camara en vertical

			if (zdirection < -gradosRotacion) {
				zdirection = -gradosRotacion;
			}

			else if (zdirection > gradosRotacion) {
				zdirection = gradosRotacion;
			}

			device->getCursorControl()->setPosition(0.5f, 0.5f);
			core::vector3df playerPos = core::vector3df(this->pProta->getPosition().X, this->pProta->getBoundingBox().getCenter().Y, this->pProta->getPosition().Z);
			//float xf = playerPos.X - cos(direction * M_PI / 180.0f) * 128.0f;
			float yf = playerPos.Y - sin(zdirection * M_PI / 180.0f) * 128.0f;
			//float zf = playerPos.Z + sin(direction * M_PI / 180.0f) * 128.0f;

			float xf = playerPos.X
					- cos(zdirection * irr::core::PI / 180.0f)
							* cos(direction * irr::core::PI / 180.0f) * 128.0f;
			float zf = playerPos.Z
					+ cos(zdirection * irr::core::PI / 180.0f)
							* sin(direction * irr::core::PI / 180.0f) * 128.0f;
			this->pCamara->setPosition(core::vector3df(xf, yf + this->pProta->getBoundingBox().getCenter().Y , zf));
			this->pCamara->setTarget(core::vector3df(this->pProta->getPosition().X,
					(this->pProta->getBoundingBox().getCenter().Y)*1.6f,
					this->pProta->getPosition().Z)
					);
			//this->pProta->setRotation(core::vector3df(0, direction+90, 0)); //usamos la rotacion del raton con un ajuste de 90 grados por el modelado de AC
			/**---------------------**/

}
