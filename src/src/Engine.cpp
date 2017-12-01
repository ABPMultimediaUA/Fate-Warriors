/*
 * Engine.cpp
 *
 *  Created on: Nov 13, 2017
 *      Author: manu
 */

#include "Engine.h"

using namespace irr;

Engine::Engine(bool moose, unsigned short width, unsigned short height) {
	if (!moose) { //irrlicht engine initialization
		device = createDevice(video::E_DRIVER_TYPE::EDT_OPENGL,
				core::dimension2d<u32>(width, height), 16, false, false, false,
				&eventManager);
		driver = device->getVideoDriver();
		smgr = device->getSceneManager();
		if (device == 0) {
			std::cout
					<< "Error: no se pudo crear el dispositivo; inicialización de motor fallida"
					<< std::endl;
		}
		node = 0;
		mesh = 0;
		//smgr->addCameraSceneNodeFPS();
		camera = smgr->addCameraSceneNode();
		cameraTarget = 0;
		smgr->addCameraSceneNodeFPS();
	}
}

/*----cargaModelo----
 *descripcion: carga un modelo descomprimido a partir de una ruta
 *inputs:
 *	rutaModelo -> path al archivo del modelo
 *  x -> coordenada x del modelo
 *  z -> coordenada z del modelo
 */

void Engine::cargaModelo(char* rutaModelo, bool emf_lightning, short x, short y,
		short z) {
	scene::IAnimatedMesh* mesh = smgr->getMesh(rutaModelo);
	scene::ISceneNode* node;
	if (mesh) {
		meshes.push_back(mesh); //añadir mesh al vector meshes de la escena
		node = smgr->addOctTreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
		if (!emf_lightning) {
			node->setMaterialFlag(video::EMF_LIGHTING, false);
		}
		else{
			node->setMaterialFlag(video::EMF_LIGHTING, true);
		}
	}
	nodes.push_back(node);
	node->setPosition(core::vector3df(x, y, z));

}

/*----cargaModeloC----
 *descripcion: carga un modelo comprimido a partir de la ruta del modelo comprimido
 *			 : y su nombre una vez descomprimido
 *inputs:
 *	rutaFile -> path al archivo del modelo comprimido
 *	rutaModelo -> nombre del archivo descomprimido
 *  x -> coordenada x del modelo
 *  z -> coordenada z del modelo
 */

void Engine::cargaModeloC(char* rutaFile, char* rutaModelo, bool emf_lightning,
		short x, short y, short z) {
	device->getFileSystem()->addFileArchive(rutaFile);
	mesh = smgr->getMesh(rutaModelo);
	if (mesh) {
		meshes.push_back(mesh); //añadir mesh al vector meshes de la escena
		node = smgr->addOctTreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
	}

	if (!emf_lightning) {
		node->setMaterialFlag(video::EMF_LIGHTING, false);
	} else {
		node->setMaterialFlag(video::EMF_LIGHTING, true);
	}
	nodes.push_back(node);
	node->setPosition(core::vector3df(x, 0, z));
}

void Engine::crearProta(char* rutaModelo, bool enf_lightning,
		short x, short y, short z){
	scene::IAnimatedMesh* mesh = smgr->getMesh(rutaModelo);
	scene::ISceneNode* node;
	if (mesh) {
		meshes.push_back(mesh); //añadir mesh al vector meshes de la escena
		node = smgr->addOctTreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
		if (!enf_lightning) {
			node->setMaterialFlag(video::EMF_LIGHTING, false);
		}
		else{
			node->setMaterialFlag(video::EMF_LIGHTING, true);
		}
	}
	nodes.push_back(node);
	node->setPosition(core::vector3df(x, y, z));
	//asignacion de camara al prota
}

void Engine::crearProtaC(char* rutaFile, char* rutaModelo, bool enf_lightning,
		short x, short y, short z){

}

void Engine::Update(){

}

void Engine::Render() {
	while(this->device->run()){
		std::cout<<"ME METO"<<std::endl;
		driver->beginScene(true, true, video::SColor(255, 113, 113, 133));
		smgr->drawAll(); // draw the 3d scene
		//device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)
		driver->endScene();
	}
}

Engine::~Engine() {
	device->drop();
}
