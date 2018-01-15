#include "Entidad.h"
#include "SFML/Graphics.hpp"
#include <cmath>
#include "../Utilidades/Vector.h"
#include "../Personajes/Interpolacion.h"

Entidad::Entidad(){
    configuracion_irlitch();
    configuracion_bullet();
    preparar_depuracion_mundo();

	std::string str = "models/MapaColision/ColisionesNivel1.obj";
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

Entidad::~Entidad(){
	//Bullet

	for(short a=0; a<rigidbody.size(); a++){
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


void Entidad::apagar(){
	device->closeDevice();
}



void Entidad::preparar_depuracion_mundo(){
	debugDraw = new DebugDraw(device);
	debugDraw->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	world->setDebugDrawer(debugDraw);
}

void Entidad::configuracion_bullet(){	
	collisionConfiguration = new btDefaultCollisionConfiguration();
	broadPhase = new btDbvtBroadphase(new btHashedOverlappingPairCache());
	collisionDispatcher = new btCollisionDispatcher(collisionConfiguration);
	constraintSolver = new btSequentialImpulseConstraintSolver();

	world = new btDiscreteDynamicsWorld(collisionDispatcher, broadPhase, constraintSolver, collisionConfiguration);

	fileLoader = new btBulletWorldImporter(world);
	fileLoader->loadFile("models/MapaColision/ColisionesNivel1.bullet");
	
    world->setGravity(btVector3(0,-9.8*20,0));

}

void Entidad::configuracion_irlitch(){
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

ISceneNode* Entidad::crearModelado(char* ruta,float x, float y, float z){
	ISceneNode *cubeNode = smgr->addMeshSceneNode(smgr->getMesh(ruta));

	if(cubeNode){
		cubeNode->setMaterialFlag(EMF_LIGHTING, true);
	}
	
	cubeNode->setPosition(vector3df(x, y, z));
	
	cubeNode->getMaterial(0).AmbientColor.set(255,255,255,255); //r,g,b
	nodes.push_back(cubeNode);
	return cubeNode;
}


short Entidad::crear_objeto(BoundingBoxes tipo,char* ruta,float x, float y, float z, float _i_peso){
	ISceneNode *cubeNode=crearModelado(ruta,x,y,z);
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
	//btCollisionShape *cubeShape = new btCapsuleShape(anchura*0.7,altura*0.5); // new btSphereShape(0.5);
	btVector3 cubeLocalInertia;
	cubeShape->calculateLocalInertia(cubeMass, cubeLocalInertia);

	btRigidBody *cubeBody = new btRigidBody(cubeMass, cubeMotionState, cubeShape, cubeLocalInertia);
	
	cubeBody->setAngularFactor(0);
	cubeBody->setUserPointer(cubeNode);
	cubeBody->setRestitution(0);
	cubeBody->setFriction(500);
	cubeBody->forceActivationState(DISABLE_DEACTIVATION );
	Vector3 posicion(x,y,z);
	_interpolaciones.push_back(new Interpolacion(posicion));

	world->addRigidBody(cubeBody);
	rigidbody.push_back(cubeBody);
	return rigidbody.size()-1;
}



void Entidad::getDimensiones(ISceneNode* node, float &anchura, float &altura, float &profundidad){
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

void Entidad::colorear_nodo(unsigned short id, short r,short g, short b){
	nodes[id+1]->getMaterial(0).AmbientColor.set(255,r,g,b); //brillo, r,g,b
}

void Entidad::poner_camara_a_entidad(unsigned short id){
	ISceneNode *cubeNode = static_cast<ISceneNode *>(rigidbody[id]->getUserPointer());
	camara->Camara_setProta(cubeNode);
	_id_jugador = id;

	camara->set_posicion_inicial(_interpolaciones[_id_jugador]->get_direccion_actual());
}

btCollisionWorld::ClosestRayResultCallback Entidad::trazaRayo(btVector3 start, btVector3 end){
	btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
	world->rayTest(start, end, rayCallback);

	return rayCallback;
}

void Entidad::importarEscenario(char* rutaObj, float x, float y, float z){

	ISceneNode *windmillNode = smgr->addMeshSceneNode(smgr->getMesh(rutaObj));
	if(windmillNode) {
		windmillNode->setMaterialFlag(EMF_LIGHTING, false);
		windmillNode->setPosition(core::vector3df(x,y,z));
		nodes.push_back(windmillNode);
	}
}

void Entidad::update(double dt){

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
			if(desp_x==0&&desp_z==0){
				setVelocidad(i,desp_x,rigidbody[i]->getLinearVelocity()[1],desp_z);
			}
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

void Entidad::interpola_posiciones(float _i_interpolacion) {

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

void Entidad::updateCamaraColision(){
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


void Entidad::saltar(unsigned short _i_id){		   //Space

	std::cout<<"entra" << std::endl;
	std::cout<< rigidbody[_i_id]->getLinearVelocity()[1] << std::endl;
		
	if(std::abs (rigidbody[_i_id]->getLinearVelocity()[1])<0.01){
		rigidbody[_i_id]->applyCentralImpulse( btVector3( 0.f, 3000.f, 0.f ) );
		//exit(0);
	}
}

void Entidad::saltar(unsigned short _i_id,int force){		   //Space

	std::cout<<"entra" << std::endl;
	std::cout<< rigidbody[_i_id]->getLinearVelocity()[1] << std::endl;
		
	if(std::abs (rigidbody[_i_id]->getLinearVelocity()[1])<0.01){
		rigidbody[_i_id]->applyCentralImpulse( btVector3( 0.f, force, 0.f ) );
		//exit(0);
	}
}

void Entidad::abrir_puerta1(unsigned short _i_id){
	
	rigidbody[_i_id]->forceActivationState(DISABLE_SIMULATION);
	btTransform btt; 
	rigidbody[_i_id]->getMotionState()->getWorldTransform(btt);
	btt.setOrigin(btVector3(btt.getOrigin().getX(),10,btt.getOrigin().getZ())); // move body to the scene node new position

	rigidbody[_i_id]->getMotionState()->setWorldTransform(btt);
	rigidbody[_i_id]->setCenterOfMassTransform(btt);


	ISceneNode *node = static_cast<ISceneNode *>(rigidbody[_i_id]->getUserPointer());
	btVector3 pos = rigidbody[_i_id]->getCenterOfMassPosition();
		
	node->setPosition(vector3df(btt.getOrigin().getX(),btt.getOrigin().getY(),btt.getOrigin().getZ()));
}

void Entidad::abrir_puerta2(unsigned short _i_id){
	
	rigidbody[_i_id]->forceActivationState(DISABLE_SIMULATION);
	btTransform btt; 
	rigidbody[_i_id]->getMotionState()->getWorldTransform(btt);
	btt.setOrigin(btVector3(btt.getOrigin().getX(),20,btt.getOrigin().getZ())); // move body to the scene node new position

	rigidbody[_i_id]->getMotionState()->setWorldTransform(btt);
	rigidbody[_i_id]->setCenterOfMassTransform(btt);


	ISceneNode *node = static_cast<ISceneNode *>(rigidbody[_i_id]->getUserPointer());
	btVector3 pos = rigidbody[_i_id]->getCenterOfMassPosition();
		
	node->setPosition(vector3df(btt.getOrigin().getX(),btt.getOrigin().getY(),btt.getOrigin().getZ()));
}

void Entidad::abrir_puerta(unsigned short _i_id){
	this->abrir_puerta1(_i_id);
	this->abrir_puerta2(_i_id);
}

void Entidad::resetear_camara(){
	camara->Camara_reset(_interpolaciones[_id_jugador]->get_direccion_actual());
}

void Entidad::updateDynamicBody(btRigidBody *body) {
	
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

void Entidad::render(){

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


// Funcion de mover para el jugador
void Entidad::VelocidadDireccion(unsigned short id, unsigned short _i_direccion, unsigned short _i_velocidad){  // Direccion
	// Angulo de la camara
	angulo = camara->Camara_getAngle();

	/*
	std::cout << "Direccion: " << _i_direccion << "\n";
	std::cout << "Angulo: " << angulo << "\n";
	*/

	// Nodo del personaje
	ISceneNode *personaje = static_cast<ISceneNode *>(rigidbody[id]->getUserPointer());

	// Direccion sumada de los movimientos
	int16_t _direccion_buena = _i_direccion + angulo;

	// Si la direccion es mayor de 360, se reduce al intervalo [0,360)
	while(_direccion_buena >= 360) _direccion_buena -= 360;

	// Actualiza la rotacion del personaje
	_interpolaciones[id]->actualiza_direccion(_direccion_buena);

	//std::cout << "Direccion " << _direccion_buena << "\n";

	// Version antigua en caso de que no funcione bien
	//angulo = camara->Camara_getAngleRad();
	//desp_z += cos(_angulo+(_i_direccion*std::acos(-1)/180)) * _i_velocidad * mdt;

	// Agrega el desplazamiento del personaje
	desp_z += cos(_direccion_buena*std::acos(-1)/180) * _i_velocidad * mdt;
    desp_x += sin(_direccion_buena*std::acos(-1)/180) * _i_velocidad * mdt;
    moving = true;
    setVelocidad(id,desp_x,rigidbody[id]->getLinearVelocity()[1],desp_z);
}

void Entidad::setVelocidad(uint8_t id, float x, float y, float z){
	btVector3 mov(x,y,z);
    rigidbody[id]->setLinearVelocity(mov);
	desp_x = desp_z = 0;
}

// Funcion de mover para los NPC
void Entidad::setVelocidad(uint8_t id, unsigned short _i_direccion, float x, float y, float z){
	float _cos, _sen;
	_cos = sin(_i_direccion*std::acos(-1)/180);
	_sen = cos(_i_direccion*std::acos(-1)/180);

	// Saca una nueva direccion, dado que _i_direccion no viene en el mismo sistema
	float _nueva_direccion = atan2(_sen, _cos) /std::acos(-1) * 180;

	//std::cout << "Direccion: " << _nueva_direccion << "\n";

	// Nodo del personaje
	ISceneNode *personaje = static_cast<ISceneNode *>(rigidbody[id]->getUserPointer());

	// Actualiza la rotacion del personaje
	_interpolaciones[id]->actualiza_direccion(_nueva_direccion);

	// Agrega el desplazamiento del personaje
	desp_z += cos(_nueva_direccion*std::acos(-1)/180) * 1 * mdt;
    desp_x += sin(_nueva_direccion*std::acos(-1)/180) * 1 * mdt;
    setVelocidad(id,desp_x,rigidbody[id]->getLinearVelocity()[1],desp_z);
}

void Entidad::setPositionXZ(unsigned short id, float x, float z){
	btTransform btt; 
	rigidbody[id]->getMotionState()->getWorldTransform(btt);
	btt.setOrigin(btVector3(x,btt.getOrigin().getY(),z)); // move body to the scene node new position

	rigidbody[id]->getMotionState()->setWorldTransform(btt);
	rigidbody[id]->setCenterOfMassTransform(btt);


	ISceneNode *node = static_cast<ISceneNode *>(rigidbody[id]->getUserPointer());
	btVector3 pos = rigidbody[id]->getCenterOfMassPosition();
		
	node->setPosition(vector3df(x,btt.getOrigin().getY(),z));


	const btQuaternion &quat = rigidbody[id]->getOrientation();
	quaternion q(quat.getX(), quat.getY(), quat.getZ(), quat.getW());
	vector3df euler;
	q.toEuler(euler);
	euler *= RADTODEG;
	node->setRotation(euler);
}

void Entidad::haz_desaparecer(unsigned short _id){
	btTransform btt; 
	rigidbody[_id]->getMotionState()->getWorldTransform(btt);
	btt.setOrigin(btVector3(9999,-99999,9999)); // move body to the scene node new position

	rigidbody[_id]->getMotionState()->setWorldTransform(btt);
	rigidbody[_id]->setCenterOfMassTransform(btt);
}


void Entidad::set_text_vida(int _i_vida){
	_GUI->set_text_vida(_i_vida);
	_vida = (_i_vida*300)/500;
}

void Entidad::Dash(unsigned short _i_direccion, unsigned short id){
	short potencia = 1000;
	angulo = camara->Camara_getAngleRad();
	desp_z += cos(angulo+(_i_direccion*std::acos(-1)/180)) * _velocidad * mdt;
    desp_x += sin(angulo+(_i_direccion*std::acos(-1)/180)) * _velocidad * mdt;
	rigidbody[id]->applyCentralImpulse(btVector3(desp_x*potencia, 0.f, desp_z*potencia)); //se multiplica por 100 pa volaaaar
	desp_z = desp_x = 0;
}

//Metodos get

float Entidad::getX(short id){
	btVector3 pos = rigidbody[id]->getCenterOfMassPosition();
	return pos[0];
}

float Entidad::getY(short id){
	btVector3 pos = rigidbody[id]->getCenterOfMassPosition();
	return pos[1];
}

float Entidad::getZ(short id){
	btVector3 pos = rigidbody[id]->getCenterOfMassPosition();
	return pos[2];
}

float Entidad::getVelocidadY(short _i_id){
	return  rigidbody[_i_id]->getLinearVelocity()[1];
}

IrrlichtDevice* Entidad::getDevice(){
	return device;
}
