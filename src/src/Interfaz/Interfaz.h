/*
 * Interfaz.h
 *
 *  Created on: Nov 26, 2017
 *      Author: manu
 */

#ifndef SRC_CPP_INTERFAZ_H_
#define SRC_CPP_INTERFAZ_H_

class Camara;
class irrlicht;
class InputKey;


#include <vector>
#include <iostream>
#include "irrlicht/irrlicht.h"


using namespace irr;
using namespace std;

class Interfaz{
	public:

		
		unsigned short Interfaz_cargaModelo(char* rutaModelo, bool enf_lightning, 
						short x, short y, short z);								    //carga un modelo en la escena a partir de una ruta  || returns:
		unsigned short Interfaz_cargaModeloZip(char* rutaFile, char* rutaModelo, bool enf_lightning,
						short x, short y, short z);				//carga un modelo en la escena a partir de una ruta  || returns:
		unsigned short Interfaz_cargaCaja(short x, short y, short z);

		unsigned short Interfaz_cargaMapa(char* rutaModelo, bool enf_lightning, 
						short x, short y, short z);								    //carga un modelo en la escena a partir de una ruta  || returns:
		unsigned short Interfaz_cargaMapaZip(char* rutaFile, char* rutaModelo, bool enf_lightning, 
						short x, short y, short z);				//carga un modelo en la escena a partir de una ruta  || returns:
		unsigned short Interfaz_crearProta(char* rutaModelo, bool enf_lightning,
						short x, short y, short z);
		unsigned short Interfaz_crearProtaZip(char* rutaFile, char* rutaModelo, bool enf_lightning,
						short x, short y, short z);

		void Interfaz_moverModelo(unsigned short id, float x, float y, float z);
		void Interfaz_moverProta(float x, float z);
		void Interfaz_moverProta(float x, float y, float z);
		void Interfaz_rotarProta(float angulo);
		
		
		float Interfaz_GetCamaraAngle();
		float Interfaz_GetCamaraAngleRad();

		scene::ISceneNode* Interfaz_GetProta();
		scene::ISceneNode* Interfaz_GetNode(unsigned short id);
		
		void Interfaz_collisionEnable(); //recorre el vector de nodos y les añade la colision y gravedad a todos
		void Interfaz_Apagar(); //cierra la ventana grafica
		void Interfaz_Update();
		void Interfaz_Render();

		Camara* Interfaz_getCamara();

		static Interfaz* Interfaz_getInstance();

		IrrlichtDevice* Interfaz_getDevice();
																				//dibuja todos los nodos de smgr (scene manager)
		~Interfaz(); 															//destruye el motor

	private:
		void Interfaz_ProtaCollisionEnable();
		Interfaz(bool moose, unsigned short width, unsigned short height);    //inicializa el motor
		IrrlichtDevice* _device; 	 //device de irrlicht
		video::IVideoDriver* _driver; //driver de video (EDT_OPENGL)
		scene::ISceneManager* _smgr;  //scene manager
		vector<scene::IAnimatedMesh*> _meshes;
		vector<scene::ISceneNode*> _nodes;
		scene::IAnimatedMesh* _mesh;
		scene::ISceneNode* _node;
		scene::ITriangleSelector* _selector; //triangle selector para las colisiones
		scene::ISceneNode* _Prota;

		float _direction;
		float _zdirection;
		const f32 MOVEMENT_SPEED = 200.f;
		int _lastFPS;
		core::vector3df _nodeRotation;
		//scene::ICameraSceneNode* _camera;
		Camara* _micamara;
		//scene::ISceneNode* _cameraTarget;
		u32 _then;
		/**** POSIBLES VARIABLES A COMENTAR CON EL PROFESOR DE TAG ****/
		int _meshCounter;
		int _nodeCounter;

		//scene::IAnimatedMesh* mesh[100]; //array de meshes

		unsigned short _height;
		unsigned short _width;

		//scene::ISceneNode* node[100]; //array de nodos
		static Interfaz* _instancia; //instancia de la interfaz
};



#endif /* SRC_CPP_INTERFAZ_H_ */
