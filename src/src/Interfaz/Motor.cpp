#include "Motor.h"
#include "SFML/Graphics.hpp"
#include <cmath>
#include "../Utilidades/Vector.h"
#include "../Personajes/Interpolacion.h"
#include "Objeto_Motor.h"
#include "../Objeto.h"
#include "../Personajes/Player.h"
#include "../Personajes/NPC.h"
#include "../Puerta.h"
/*
#include "Entidad.h"
#include "../Input.h"
#include "../Utilidades/Vector.h"
master*/

#define BIT(x) (1<<(x))
enum tipo_colision {
    COL_NADA = 0, //<Colision con nada
    COL_ESCENARIO = BIT(0), //<Colision con escenario
    COL_JUGADOR = BIT(1), //<Colision con jugador
    COL_NPC = BIT(2), //<Colision con NPC
	COL_RAY = BIT(3), //rayo del raytracing
	COL_OTRO = BIT(4) //<Colision con Otro (trampas, recogibles)
};

//relaciones de colision 
int jugador_colisiona_con = 	COL_JUGADOR | COL_NPC | COL_ESCENARIO;
int npc_colisiona_con = 		COL_JUGADOR | COL_ESCENARIO | COL_NPC;
int escenario_colisiona_con = 	COL_NADA | COL_JUGADOR | COL_OTRO | COL_NPC;
int otros_colisiona_con =		COL_NADA | COL_ESCENARIO;
int ray_colisiona_con =			COL_NPC | COL_ESCENARIO;

Motor* Motor::_Motor=0;

Motor* Motor::Motor_GetInstance(){
	if(_Motor==0){
		_Motor	=  new Motor();
	}
	return _Motor;
}



Motor::Motor(){
    configuracion_irlitch();
    configuracion_bullet();
    preparar_depuracion_mundo();

	const char* cstr = "models/MapaColision/ColisionesNivel1.obj";
	importarEscenario(cstr, 0,0,0);
    desp_x = desp_z = 0;
	camara = new Camara(smgr, device);
	angulo = 0;
	_velocidad = 1;
	_debug = false;
	_id_jugador = 0;
	//esto no debe ir aqui y se cambia despues de la presentacion
	_vida = 300;
	_maxvida = 300;
}

void Motor::borrar_objeto(Objeto_Motor* _objeto_motor){

	_objeto_motor->getNodo()->remove();

	world->removeRigidBody(_objeto_motor->getRigidBody());
	delete _objeto_motor->getRigidBody()->getCollisionShape();
	delete _objeto_motor->getInterpolacion();

	auto ite2 = std::find(_objetos_motor.begin(), _objetos_motor.end(), _objeto_motor);
    if ( ite2 != _objetos_motor.end()){
        _objetos_motor.erase(ite2);
    }

	/*
    auto ite = std::find(_interpolaciones.begin(), _interpolaciones.end(), _interpolacion);
    if ( ite != _interpolaciones.end()){
        _interpolaciones.erase(ite);
        delete _interpolacion;
    }


	_nodo->remove();
    auto ite2 = std::find(nodes.begin(), nodes.end(), _nodo);
    if ( ite2 != nodes.end()){
        nodes.erase(ite2);
        //delete _nodo;
    }

	world->removeRigidBody(_rigidbody);
	delete _rigidbody->getCollisionShape();

    std::vector<btRigidBody*>::iterator it;
    it = std::find(rigidbody.begin(), rigidbody.end(), _rigidbody);
    if ( it != rigidbody.end()){
        rigidbody.erase(it);
        delete _rigidbody;
    }



/*
    std::vector<ISceneNode*>::iterator it;
    it = std::find(nodes.begin(), nodes.end(), _nodo);
    if ( it != nodes.end()){
        nodes.erase(it);
        delete _nodo;
    }
	*/
}

/*bool Motor::colision_entre_dos_puntos(Vector3 inicio, Vector3 fin){
	return _entidad->colision_entre_dos_puntos(inicio,fin);
}*/ 


Motor::~Motor(){

	//Bullet
/*
	for(short a=0; a<rigidbody.size(); a++){
		world->removeRigidBody(rigidbody[a]);
	    delete rigidbody[a]->getCollisionShape();

		delete rigidbody[a];
		rigidbody[a] = nullptr;
	}
	rigidbody.clear();


	for(short a=0; a<nodes.size(); a++){
		delete nodes[a];
		nodes[a] = nullptr;
	}
	nodes.clear();
 
 */



	for(short a=0; a<_objetos_motor.size(); a++){
		_objetos_motor[a]->getNodo()->remove();
		world->removeRigidBody(_objetos_motor[a]->getRigidBody());
		delete _objetos_motor[a]->getRigidBody()->getCollisionShape();
		delete _objetos_motor[a]->getInterpolacion();
	}
	_objetos_motor.clear();

	

	delete mapa;
	
	delete world; 
	delete camara; 
	delete debugDraw; 
	delete collisionConfiguration; 
	delete broadPhase; 
	delete collisionDispatcher; 
	delete constraintSolver; 
	delete fileLoader; 

	//Irrlitch
	delete _GUI;
	driver->drop();
	device->drop();


	world = nullptr;
	camara = nullptr;
	debugDraw = nullptr;
	collisionConfiguration = nullptr;
	broadPhase = nullptr;
	collisionDispatcher = nullptr;
	constraintSolver = nullptr;
	fileLoader = nullptr;
}


void Motor::apagar(){
	device->closeDevice();
}



void Motor::preparar_depuracion_mundo(){
	debugDraw = new DebugDraw(device);
	debugDraw->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	world->setDebugDrawer(debugDraw);
}

void Motor::configuracion_bullet(){	
	collisionConfiguration = new btDefaultCollisionConfiguration();
	broadPhase = new btDbvtBroadphase(new btHashedOverlappingPairCache());
	collisionDispatcher = new btCollisionDispatcher(collisionConfiguration);
	constraintSolver = new btSequentialImpulseConstraintSolver();

	world = new btDiscreteDynamicsWorld(collisionDispatcher, broadPhase, constraintSolver, collisionConfiguration);

	fileLoader = new btBulletWorldImporter(world);
	fileLoader->loadFile("models/MapaColision/ColisionesNivel1.bullet");
	btCollisionShape* escenario; 
	btRigidBody* esta_vez_si;
	int num = fileLoader->getNumRigidBodies();
	
	btTransform cubeTransform;
	cubeTransform.setIdentity();
	//cubeTransform.setOrigin(btVector3(x,y,z));
	btDefaultMotionState *cubeMotionState = new btDefaultMotionState(cubeTransform);
	for(short i = 0; i<num;i++){

		btTransform trans = fileLoader->getRigidBodyByIndex(i)->getWorldTransform();

		escenario = fileLoader->getRigidBodyByIndex(i)->getCollisionShape();
		cubeMotionState = new btDefaultMotionState(trans);
		world->addRigidBody(new btRigidBody(0, cubeMotionState, escenario),COL_ESCENARIO, escenario_colisiona_con);

		//btBroadphaseProxy* proxy = esta_vez_si->getBroadphaseProxy();
		//proxy->m_collisionFilterGroup = 4;
		//proxy->m_collisionFilterMask = 4;
	}	
	
	
    world->setGravity(btVector3(0,-9.8,0));

}

void Motor::configuracion_irlitch(){
// Configuracion de Irrlicht
	device = createDevice( video::EDT_OPENGL, dimension2d<u32>(640, 480), 16, 
    					  false, false, false); 

	device->setWindowCaption(L"Feito Güarriorusuu");

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	smgr->setAmbientLight(video::SColorf(1,1,1,1));
	smgr->addSkyBoxSceneNode(
		driver->getTexture("media/irrlicht2_up.jpg"),
		driver->getTexture("media/irrlicht2_dn.jpg"),
		driver->getTexture("media/irrlicht2_lf.jpg"),
		driver->getTexture("media/irrlicht2_rt.jpg"),
		driver->getTexture("media/irrlicht2_ft.jpg"),
		driver->getTexture("media/irrlicht2_bk.jpg"));
	_GUI = new GUI(device);
	
}


unsigned short Motor::crear_objeto(BoundingBoxes tipo,const char* ruta,float x, float y, float z, float _i_peso){
	/*ISceneNode *cubeNode = crearModelado(ruta, x,y,z);
	Interpolacion* interpolacion = crear_interpolacion(x,y,z);
	btRigidBody* cuerpo = 	crearRigidBody(tipo,ruta,x, y, z, _i_peso, cubeNode);
	*/

	return 1;
}

ISceneNode* Motor::crearModelado(const char* ruta,float x, float y, float z){
	ISceneNode *cubeNode = smgr->addMeshSceneNode(smgr->getMesh(ruta));

	if(cubeNode){
		cubeNode->setMaterialFlag(EMF_LIGHTING, true);
	}
	
	cubeNode->setPosition(vector3df(x, y, z));
	
	cubeNode->getMaterial(0).AmbientColor.set(255,255,255,255); //r,g,b
	return cubeNode;
}

void Motor::crear_ObjetoMotor(Objeto_Motor* _i_objeto_motor){
	_objetos_motor.push_back(_i_objeto_motor);
}

btRigidBody* Motor::crearRigidBody(Objeto* _i_objeto, BoundingBoxes tipo,const char* ruta,float x, float y, float z, float _i_peso, ISceneNode *cubeNode){
	btTransform cubeTransform;
	cubeTransform.setIdentity();

	cubeTransform.setOrigin(btVector3(x,y,z));

	btDefaultMotionState *cubeMotionState = new btDefaultMotionState(cubeTransform);

	float cubeMass = _i_peso;
	
	float altura,anchura,profundidad;
	btCollisionShape *cubeShape;
	this->getDimensiones(cubeNode,anchura,altura,profundidad);
	switch(tipo){
		case E_BoundingCapsule: 
			cubeShape = new btCapsuleShape(anchura*0.7,altura*0.5); // new btSphereShape(0.5);

					break;
		case E_BoundingBox:
			cubeShape = new btBoxShape(btVector3(profundidad*0.5,altura*0.5,anchura*0.5)); // new btSphereShape(0.5);

					break;	
		default:
			cubeShape = new btBoxShape(btVector3(profundidad*0.7,altura*0.5,anchura*0.7)); // new btSphereShape(0.5);

					break;
	}

	btVector3 cubeLocalInertia;
	cubeShape->calculateLocalInertia(cubeMass, cubeLocalInertia);

	
	//CREACION DE MASCARA DE RIGIDBODY
	int mascara_colision = COL_NADA;
	int grupo_colision 	 = COL_NADA;

	//si es un personaje
	if(dynamic_cast<Player*>(_i_objeto)!=NULL){
		grupo_colision   = COL_JUGADOR;
		mascara_colision = jugador_colisiona_con;
	}

	//si es un npc
	else if(dynamic_cast<NPC*>(_i_objeto)!=NULL){
		grupo_colision   = COL_NPC;
		mascara_colision = npc_colisiona_con;
	}

	else if(dynamic_cast<Puerta*>(_i_objeto)!=NULL){
		grupo_colision   = COL_OTRO;
		mascara_colision = otros_colisiona_con;
	}

	//si es otra cosa
	else{
		grupo_colision   = COL_ESCENARIO;
		mascara_colision = escenario_colisiona_con;
	}

	btRigidBody *cubeBody = new btRigidBody(cubeMass, cubeMotionState, cubeShape, cubeLocalInertia);
	
	cubeBody->setAngularFactor(0);
	cubeBody->setUserPointer(_i_objeto);
	cubeBody->setRestitution(0);
	cubeBody->setFriction(1);
	cubeBody->forceActivationState(DISABLE_DEACTIVATION );

	world->addRigidBody(cubeBody,grupo_colision,mascara_colision);

	return cubeBody;
}

Interpolacion* Motor::crear_interpolacion(float x, float y, float z){
	Vector3 posicion(x,y,z);
	Interpolacion* _interpolacion = new Interpolacion(posicion);
	return _interpolacion;
}

void Motor::getDimensiones(ISceneNode* node, float &anchura, float &altura, float &profundidad){
	core::vector3d<f32> * edges = new core::vector3d<f32>[8]; //Bounding BOX edges
	core::aabbox3d<f32> boundingbox ; //Mesh's bounding box
	boundingbox=node->getTransformedBoundingBox(); //Let's get BB...
	boundingbox.getEdges(edges);
	altura = (edges[1].Y - edges[0].Y);
	delete edges;


	edges = new core::vector3d<f32>[8]; //Bounding BOX edges
	boundingbox=node->getTransformedBoundingBox(); //Let's get BB...
	boundingbox.getEdges(edges);
	anchura = (edges[2].Z - edges[0].Z);

	delete edges;


	edges = new core::vector3d<f32>[8]; //Bounding BOX edges
	boundingbox=node->getTransformedBoundingBox(); //Let's get BB...
	boundingbox.getEdges(edges);
	profundidad = (edges[6].X - edges[2].X);

	delete edges;
}

void Motor::poner_camara_a_entidad(Objeto_Motor* _objeto_motor){
	ISceneNode *cubeNode = _objeto_motor->getNodo();
	camara->Camara_setProta(cubeNode);
	_id_jugador = 0;

	camara->set_posicion_inicial(_objeto_motor->getInterpolacion()->get_direccion_actual());
}

btCollisionWorld::ClosestRayResultCallback Motor::trazaRayo(btVector3 start, btVector3 end){
	btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
	world->rayTest(start, end, rayCallback);

	return rayCallback;
}

void Motor::importarEscenario(const char* rutaObj, float x, float y, float z){

	mapa = smgr->addMeshSceneNode(smgr->getMesh(rutaObj));
	if(mapa) {
		mapa->setMaterialFlag(EMF_LIGHTING, false);
		mapa->setPosition(core::vector3df(x,y,z));
	}
}

void Motor::update(double dt){

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)){
		_debug = !_debug;
	}

	mdt = dt;
   	if(device->isWindowActive()) {

        world->stepSimulation(dt * 0.001f,5);

		short tamanio = _objetos_motor.size();
		for(short i=0; i<tamanio; i++){
			// Actualiza el cuerpo dinamico de la caja
			_objetos_motor[i]->updateDynamicBody();
			_objetos_motor[i]->setVelocidad(0,_objetos_motor[i]->getVelocidadY(),0);
		
		}

		// Update de la posicion de la camara (despues de actualizar la del jugador)
		updateCamaraColision();
    } 

    else {
        device->yield();
    }
       // device->drop();
}

void Motor::interpola_posiciones(float _i_interpolacion) {

	uint16_t _tam = _objetos_motor.size();
	for(uint16_t i=0; i<_tam; i++){
		
		Vector3 _posicion_interpolada = _objetos_motor[i]->interpola_posiciones(_i_interpolacion);

		if(i == _id_jugador) {
			camara->interpola_target(_posicion_interpolada);
		}	
	}
	camara->interpola_posicion(_i_interpolacion);
}

bool Motor::x_ve_a_y(Vector3 x, Vector3 y){
	//conversion de vector3 a bullet vector3
	btVector3 mX(x._x,x._y,x._z);
	btVector3 mY(y._x,y._y,y._z);
	
	btCollisionWorld::ClosestRayResultCallback rayCallback = this->trazaRayo(mX, mY);

	rayCallback.m_collisionFilterMask = ray_colisiona_con;
    rayCallback.m_collisionFilterGroup = COL_RAY;
	//como no se quien es quito el control PD: HOLA FRAN :)
	/*
	if(rayCallback.hasHit()){
		btVector3 point = rayCallback.m_hitPointWorld;
		btVector3 normal = rayCallback.m_hitNormalWorld;
		const btCollisionObject *object = rayCallback.m_collisionObject;
		for(short i = 0; i<fileLoader->getNumRigidBodies();i++){
			if(fileLoader->getRigidBodyByIndex(i) == object){
				
			}
		}
	}
	*/
	std::cout<<"colisiona: "<<rayCallback.hasHit()<<std::endl;
	return(rayCallback.hasHit());
}

void Motor::updateCamaraColision(){
		btTransform t;
		btVector3 pos = _objetos_motor[0]->getRigidBody()->getCenterOfMassPosition();
		
        float miX = pos[0];
        float miY = pos[1];
        float miZ = pos[2];
        
		camara->Camara_Update();

		core::vector3df camPosI(camara->Camara_getPosition().X,camara->Camara_getPosition().Y,camara->Camara_getPosition().Z);
		btVector3 camaraPos(camPosI.X, camPosI.Y, camPosI.Z);

		btCollisionWorld::ClosestRayResultCallback rayCallback = this->trazaRayo(pos, camaraPos);

		if(rayCallback.hasHit()){
			btVector3 point = rayCallback.m_hitPointWorld;
			btVector3 normal = rayCallback.m_hitNormalWorld;
			const btCollisionObject *object = rayCallback.m_collisionObject;
			for(short i = 0; i<fileLoader->getNumRigidBodies();i++){
				if(fileLoader->getRigidBodyByIndex(i) == object){
					// Set posicion colision
					camara->Camara_setPositionColision(core::vector3df(point[0],point[1],point[2]));
				}
			}
		}

		angulo = camara->Camara_getAngleRad();
}



void Motor::resetear_camara(){
	camara->Camara_reset(_objetos_motor[0]->getInterpolacion()->get_direccion_actual());
}


void Motor::render(){

	driver->beginScene(true, true, SColor(255,100,101,140));
    smgr->drawAll();

    SMaterial debugMat;
    debugMat.Lighting = false;
    driver->setMaterial(debugMat);
    driver->setTransform(ETS_WORLD, IdentityMatrix);

	driver->draw2DImage( driver->getTexture( "media/barra_muerte.png" ), core::position2d<s32>( 50, 50 ), core::rect<s32>( 50, 50, 350, 80), 0 );
	driver->draw2DImage( driver->getTexture( "media/barra_vida.png" ), core::position2d<s32>( 50, 50 ), core::rect<s32>( 50, 50, 50+_vida, 80), 0 );
	

    if(_debug){
		world->debugDrawWorld();
    }

	//guienv->drawAll();
	_GUI->draw();
    driver->endScene();
}

//Metodos set

void Motor::set_text_vida(int _i_vida){
	_GUI->set_text_vida(_i_vida);
	_vida = (_i_vida*300)/500;
}


IrrlichtDevice* Motor::getIrrlichtDevice(){
	return device;
}

void Motor::render(float _i_interpolacion){
	interpola_posiciones(_i_interpolacion);
	render();
}



float Motor::angulo_camara(){
	return camara->Camara_getAngle();
}


float Motor::angulo_camaraRAD(){
	return camara->Camara_getAngleRad();
}