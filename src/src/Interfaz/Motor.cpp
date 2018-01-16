#include "Motor.h"
#include "SFML/Graphics.hpp"
#include <cmath>
#include "../Utilidades/Vector.h"
#include "../Personajes/Interpolacion.h"
#include "Objeto_Motor.h"

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

	std::string str = "models/Colisiones.obj";
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
	importarEscenario(cstr, 0,0,0);

    desp_x = desp_z = 0;
	camara = new Camara(smgr, device);
	angulo = 0;
	_velocidad = 1;
	_debug = false;
	_id_jugador = 0;
	//esto no debe ir aqui y se cambia despues de la presentacion
	_vida = 300;
	_maxvida=300;
}

void Motor::borrar_objeto(ISceneNode* _nodo, Interpolacion* _interpolacion, btRigidBody* _rigidbody){
	
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


Motor::~Motor(){
	//Bullet

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
	fileLoader->loadFile("models/Colisiones.bullet");
	
    world->setGravity(btVector3(0,-9.8*20,0));

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


unsigned short Motor::crear_objeto(BoundingBoxes tipo,char* ruta,float x, float y, float z, float _i_peso){
	ISceneNode *cubeNode = crearModelado(ruta, x,y,z);
	Interpolacion* interpolacion = crear_interpolacion(x,y,z);
	btRigidBody* cuerpo = 	crearRigidBody(tipo,ruta,x, y, z, _i_peso, cubeNode);
	return rigidbody.size()-1;
}

ISceneNode* Motor::crearModelado(char* ruta,float x, float y, float z){
	ISceneNode *cubeNode = smgr->addMeshSceneNode(smgr->getMesh(ruta));

	if(cubeNode){
		cubeNode->setMaterialFlag(EMF_LIGHTING, true);
	}
	
	cubeNode->setPosition(vector3df(x, y, z));
	
	cubeNode->getMaterial(0).AmbientColor.set(255,255,255,255); //r,g,b
	nodes.push_back(cubeNode);
	return cubeNode;
}

void Motor::crear_ObjetoMotor(Objeto_Motor* _i_objeto_motor){
	_objetos_motor.push_back(_i_objeto_motor);
}

btRigidBody* Motor::crearRigidBody(BoundingBoxes tipo,char* ruta,float x, float y, float z, float _i_peso, ISceneNode *cubeNode){
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

	btRigidBody *cubeBody = new btRigidBody(cubeMass, cubeMotionState, cubeShape, cubeLocalInertia);
	
	cubeBody->setAngularFactor(0);
	cubeBody->setUserPointer(cubeNode);
	cubeBody->setRestitution(0);
	cubeBody->setFriction(500);
	cubeBody->forceActivationState(DISABLE_DEACTIVATION );


	world->addRigidBody(cubeBody);
	rigidbody.push_back(cubeBody);
	return cubeBody;
}

Interpolacion* Motor::crear_interpolacion(float x, float y, float z){
	Vector3 posicion(x,y,z);
	Interpolacion* _interpolacion = new Interpolacion(posicion);
	_interpolaciones.push_back(_interpolacion);
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

void Motor::poner_camara_a_entidad(unsigned short id){
	ISceneNode *cubeNode = static_cast<ISceneNode *>(rigidbody[id]->getUserPointer());
	camara->Camara_setProta(cubeNode);
	_id_jugador = id;

	camara->set_posicion_inicial(_interpolaciones[_id_jugador]->get_direccion_actual());
}

btCollisionWorld::ClosestRayResultCallback Motor::trazaRayo(btVector3 start, btVector3 end){
	btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
	world->rayTest(start, end, rayCallback);

	return rayCallback;
}

void Motor::importarEscenario(char* rutaObj, float x, float y, float z){

	ISceneNode *windmillNode = smgr->addMeshSceneNode(smgr->getMesh(rutaObj));
	if(windmillNode) {
		windmillNode->setMaterialFlag(EMF_LIGHTING, false);
		windmillNode->setPosition(core::vector3df(x,y,z));
		nodes.push_back(windmillNode);
	}
}

void Motor::update(double dt){

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)){
		_debug = !_debug;
	}

	mdt = dt;
   	if(device->isWindowActive()) {

        world->stepSimulation(dt * 0.001f);

		short tamanio = rigidbody.size();
		for(short i=0; i<tamanio; i++){
			// Actualiza el cuerpo dinamico de la caja
			updateDynamicBody(rigidbody[i]);
			setVelocidad(i,desp_x,rigidbody[i]->getLinearVelocity()[1],desp_z);

			btVector3 pos = rigidbody[i]->getCenterOfMassPosition();
			Vector3 vector(pos[0], pos[1], pos[2]);
			_interpolaciones[i]->actualiza_posicion(vector);

			if(!_interpolaciones[i]->get_cambio_direccion()) {
				_interpolaciones[i]->actualiza_direccion(_interpolaciones[i]->get_direccion_actual());
			}

			_interpolaciones[i]->cambio_direccion(false);
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

	uint16_t _tam = rigidbody.size();
	for(uint16_t i=0; i<_tam; i++){
		Vector3 _posicion_interpolada = _interpolaciones[i]->interpola_posicion(_i_interpolacion);

		ISceneNode *node = static_cast<ISceneNode *>(rigidbody[i]->getUserPointer());
		
		node->setPosition(vector3df(_posicion_interpolada._x, _posicion_interpolada._y, _posicion_interpolada._z));

		node->setRotation(core::vector3df(0,_interpolaciones[i]->interpola_direccion(_i_interpolacion),0));

		if(i == _id_jugador) {
			camara->interpola_target(_posicion_interpolada);
		}	
	}
	camara->interpola_posicion(_i_interpolacion);
}

void Motor::updateCamaraColision(){
		btTransform t;
		btVector3 pos = rigidbody[0]->getCenterOfMassPosition();
		
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
	camara->Camara_reset(_interpolaciones[_id_jugador]->get_direccion_actual());
}

void Motor::updateDynamicBody(btRigidBody *body) {
	
	ISceneNode *node = static_cast<ISceneNode *>(body->getUserPointer());
	btVector3 pos = body->getCenterOfMassPosition();
		
	node->setPosition(vector3df(pos[0], pos[1], pos[2]));
	/*
	const btQuaternion &quat = body->getOrientation();
	quaternion q(quat.getX(), quat.getY(), quat.getZ(), quat.getW());
	vector3df euler;
	q.toEuler(euler);
	euler *= RADTODEG;
	node->setRotation(euler);
	*/
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

void Motor::haz_desaparecer(unsigned short _id){
	btTransform btt; 
	rigidbody[_id]->getMotionState()->getWorldTransform(btt);
	btt.setOrigin(btVector3(9999,-99999,9999)); // move body to the scene node new position

	rigidbody[_id]->getMotionState()->setWorldTransform(btt);
	rigidbody[_id]->setCenterOfMassTransform(btt);
}


void Motor::set_text_vida(int _i_vida){
	_GUI->set_text_vida(_i_vida);
	_vida = (_i_vida*300)/500;
}


//Metodos get
void Motor::setVelocidad(uint8_t id, float x, float y, float z){
	btVector3 mov(x,y,z);
    rigidbody[id]->setLinearVelocity(mov);
	desp_x = desp_z = 0;
}


IrrlichtDevice* Motor::getIrrlichtDevice(){
	return device;
}

void Motor::render(float _i_interpolacion){
	interpola_posiciones(_i_interpolacion);
	render();
}

unsigned short Motor::getId(){
	return rigidbody.size()-1;
}

float Motor::angulo_camara(){
	return camara->Camara_getAngle();
}


float Motor::angulo_camaraRAD(){
	return camara->Camara_getAngleRad();
}