/*
 * Engine.h
 *
 *  Created on: Nov 13, 2017
 *      Author: manu
 */

#ifndef SRC_CPP_ENGINE_H_
#define SRC_CPP_ENGINE_H_

#include <irrlicht.h>
#include "EventManager.h"
#include "camara.h"

#include <vector>
#include <iostream>

using namespace irr;
using namespace std;

class Engine{
	public:
		Engine(bool moose, unsigned short width, unsigned short height);    //inicializa el motor
		void cargaModelo(char* rutaModelo, bool enf_lightning, short x, short y, short z);								    //carga un modelo en la escena a partir de una ruta  || returns:
		void cargaModeloC(char* rutaFile, char* rutaModelo, bool enf_lightning, short x, short y, short z);				//carga un modelo en la escena a partir de una ruta  || returns:
		void crearProta(char* rutaModelo, bool enf_lightning,
						short x, short y, short z);
		void crearProtaC(char* rutaFile, char* rutaModelo, bool enf_lightning,
						short x, short y, short z);
		void Update();
		void Render();														//dibuja todos los nodos de smgr (scene manager)
		~Engine(); 															//destruye el motor
	private:
		EventManager eventManager;
		IrrlichtDevice* device; 	 //device de irrlicht
		video::IVideoDriver* driver; //driver de video (EDT_OPENGL)
		scene::ISceneManager* smgr;  //scene manager

		vector<scene::IAnimatedMesh*> meshes;
		vector<scene::ISceneNode*> nodes;
		scene::IAnimatedMesh* mesh;
		scene::ISceneNode* node;
		scene::ICameraSceneNode* camera;
		scene::ISceneNode* cameraTarget;
		/**** POSIBLES VARIABLES A COMENTAR CON EL PROFESOR DE TAG ****/
		//int meshCounter;
		//scene::IAnimatedMesh* mesh[100]; //array de meshes
		//int nodeCounter;
		//scene::ISceneNode* node[100]; //array de nodos

};


#endif /* SRC_CPP_ENGINE_H_ */
