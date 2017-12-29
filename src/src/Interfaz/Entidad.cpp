#include "Entidad.h"
#include "SFML/Graphics.hpp"
#include <cmath>

Entidad::Entidad(){
    configuracion_irlitch();
    configuracion_bullet();
    preparar_depuracion_mundo();
	//importarEscenario("hola", 69 ,9 ,69);
	mult = 39.3701;

	//importarEscenario("models/Nodo1.obj",  5,0, 5);
	importarEscenario("models/Nivel1.obj",  0,0,0);
	//importarEscenario("models/Nodo5.obj",  35,0,38);
	//importarEscenario("models/Nodo7.obj",  27,0,3);
	//importarEscenario("models/Nodo10.obj", 49,0,3);
	//importarEscenario("models/Pasillo2.obj", 13,0,20);
	//importarEscenario("models/Pasillo4.obj", 36,0,36);
	//importarEscenario("models/Pasillo6.obj", 20,0,11);
	//importarEscenario("models/Pasillo8.obj", 30,0,18);
	//importarEscenario("models/Pasillo9.obj", 42,0,9); 
//

        desp_x = desp_z = 0;
	float x, y, z;
	x=0;
	y=10;
	z=0;

	moving = false;

	camara = new Camara(smgr, device);
	//crear_objeto(x*mult,y,z*mult);

	//x=20;
	//y=10;
	//z=20;
	crear_objeto("models/Personaje.obj",(x)*mult,y+50,z*mult);

	angulo = 0;
	_velocidad = 1;
	//then = device->getTimer()->getTime();
}

Entidad::~Entidad(){

	//Bullet
	std::cout << "cuidado aqui 0" << std::endl;

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

	std::cout << "cuidado aqui 1" << std::endl;
	delete world;
	std::cout << "cuidado aqui 2" << std::endl;
	delete camara;
	std::cout << "cuidado aqui 3" << std::endl;
	delete debugDraw;
	std::cout << "cuidado aqui 4" << std::endl;
	delete collisionConfiguration;
	std::cout << "cuidado aqui 5" << std::endl;
	delete broadPhase;
	std::cout << "cuidado aqui 6" << std::endl;
	delete collisionDispatcher;
	std::cout << "cuidado aqui 7" << std::endl;
	delete constraintSolver;
	std::cout << "cuidado aqui 8" << std::endl;
	delete fileLoader;
	std::cout << "cuidado aqui 9" << std::endl;

	//Irrlitch
	driver->drop();
	device->drop();


	std::cout << "cuidado aqui 10" << std::endl;

	//delete device;
	//delete guienv;
	


	world = nullptr;
	camara = nullptr;
	debugDraw = nullptr;
	collisionConfiguration = nullptr;
	broadPhase = nullptr;
	collisionDispatcher = nullptr;
	constraintSolver = nullptr;
	fileLoader = nullptr;

}

float Entidad::getX(short id){
	//return nodes[id]->getPosition().X;
	return 0;
}

float Entidad::getY(short id){
	//return nodes[id]->getPosition().Y;
	return 0;
}

float Entidad::getZ(short id){
	//return nodes[id]->getPosition().Z;
	return 0;
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
	fileLoader->loadFile("models/Colisiones.bullet");

    world->setGravity(btVector3(0,-9.8*20,0));
	//btTransform trans;
	//trans.setOrigin(24,0,33);
	//world->setWorldTransform(trans);
}

void Entidad::configuracion_irlitch(){
// Configuracion de Irrlicht
	device =
		createDevice( video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
			false, false, false);

	device->setWindowCaption(L"Con Bullet");

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
}

short Entidad::crear_objeto(char* ruta,float x, float y, float z){
	// Creamos un cubo rojo
	
		IMeshSceneNode *cubeNode = smgr->addCubeSceneNode(1);

	//ISceneNode *cubeNode = smgr->addMeshSceneNode(smgr->getMesh(ruta));

	if(cubeNode){
		cubeNode->setMaterialFlag(EMF_LIGHTING, false);
	}

	cubeNode->setPosition(vector3df(0, 30, 0));
	//smgr->getMeshManipulator()->setVertexColors(cubeNode->getMesh(), SColor(255,255,0,0));
	

	btTransform cubeTransform;
	cubeTransform.setIdentity();
	cubeTransform.setOrigin(btVector3(0,30,0));

	btDefaultMotionState *cubeMotionState = new btDefaultMotionState(cubeTransform);

	float cubeMass = 70.0f;
	


	core::vector3d<f32> * edges = new core::vector3d<f32>[8]; //Bounding BOX edges
	core::aabbox3d<f32> boundingbox ; //Mesh's bounding box
	boundingbox=cubeNode->getTransformedBoundingBox(); //Let's get BB...
	boundingbox.getEdges(edges);
	float altura = (edges[1].Y - edges[0].Y);
	delete edges;


	edges = new core::vector3d<f32>[8]; //Bounding BOX edges
	boundingbox=cubeNode->getTransformedBoundingBox(); //Let's get BB...
	boundingbox.getEdges(edges);
	float anchura = (edges[2].Z - edges[0].Z);

	delete edges;





	btCollisionShape *cubeShape = new btBoxShape(btVector3(0.5,0.5,0.5)); // new btSphereShape(0.5);
	btVector3 cubeLocalInertia;
	cubeShape->calculateLocalInertia(cubeMass, cubeLocalInertia);

	btRigidBody *cubeBody = new btRigidBody(cubeMass, cubeMotionState, cubeShape, cubeLocalInertia);
	
	// TODO 1.c Haz que el user pointer del cubo apunte al nodo de Irrlicht
	cubeBody->setAngularFactor(0);
	cubeBody->setUserPointer(cubeNode);
	cubeBody->setRestitution(0);
	cubeBody->setFriction(500);
	cubeBody->forceActivationState(DISABLE_DEACTIVATION );

	world->addRigidBody(cubeBody);
	
	rigidbody.push_back(cubeBody);

	return rigidbody.size()-1;
}

/*

short Entidad::crear_jugador(float x, float y, float z){
	IMeshSceneNode *cubeNode = crear_nodo("models/", x, y, z)
	crear_mesh(nodo, x, y, z)
}


void* Entidad::crear_nodo(std::string ruta, float x, float y, float z){
	IMeshSceneNode *cubeNode = smgr->addCubeSceneNode(1);

	if(cubeNode){
		cubeNode->setMaterialFlag(EMF_LIGHTING, false);
	}

	cubeNode->setPosition(vector3df(x, y, z));
	smgr->getMeshManipulator()->setVertexColors(cubeNode->getMesh(), SColor(255,255,0,0));
	return cubeNode;
}


void Entidad::crear_mesh(void* nodo, float x, float y, float z){
	btTransform cubeTransform;
	cubeTransform.setIdentity();
	cubeTransform.setOrigin(btVector3(x,y,z));

	btDefaultMotionState *cubeMotionState = new btDefaultMotionState(cubeTransform);

	float cubeMass = 1000.0f;
	btCollisionShape *cubeShape = new btBoxShape(btVector3(.5,.5,.5)); // new btSphereShape(0.5);
	btVector3 cubeLocalInertia;
	cubeShape->calculateLocalInertia(cubeMass, cubeLocalInertia);

	btRigidBody *cubeBody = new btRigidBody(cubeMass, cubeMotionState, cubeShape, cubeLocalInertia);
	
	// TODO 1.c Haz que el user pointer del cubo apunte al nodo de Irrlicht
	cubeBody->setAngularFactor(0);
	cubeBody->setUserPointer(nodo);
	cubeBody->setRestitution(0);
	cubeBody->setFriction(500);
	cubeBody->forceActivationState(DISABLE_DEACTIVATION);

	world->addRigidBody(cubeBody);
	
	rigidbody.push_back(cubeBody);
}
*/

void Entidad::poner_camara_a_entidad(unsigned short id){
	ISceneNode *cubeNode = static_cast<ISceneNode *>(rigidbody[id]->getUserPointer());
	camara->Camara_setProta(cubeNode);
}


void Entidad::importarEscenario(char* rutaObj, float x, float y, float z){
/*
	// Importa el escenario
	ISceneNode *windmillNode = smgr->addMeshSceneNode(smgr->getMesh("windmill.obj"));
	if(windmillNode) {
		windmillNode->setMaterialFlag(EMF_LIGHTING, false);
	}
*/
	// Importa el escenario
	ISceneNode *windmillNode = smgr->addMeshSceneNode(smgr->getMesh(rutaObj));
	if(windmillNode) {
		windmillNode->setMaterialFlag(EMF_LIGHTING, false);
		windmillNode->setPosition(core::vector3df(x,y,z));
		nodes.push_back(windmillNode);
	}
}

void Entidad::update(double dt){

   // while(device->run()){
	mdt = dt;
   	if(device->isWindowActive()) {
			//if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
			//	
			//}
		btTransform t;
		rigidbody[1]->getMotionState()->getWorldTransform(t);
	    btVector3 origin = t.getOrigin();
	    t.setOrigin(origin);
		ISceneNode *node = static_cast<ISceneNode *>(rigidbody[1]->getUserPointer());
	    rigidbody[1]->getMotionState()->setWorldTransform(t); //movimiento fisico
	    node->setPosition(vector3df(origin.getX(), origin.getY(), origin.getZ())); //movimiento grafico
   
        float miX = origin.getX();
        float miY = origin.getY();
        float miZ = origin.getZ();

    
            
			camara->Camara_Update();
			angulo = camara->Camara_getAngleRad();
				//	std::cout << rigidbody[1]->getLinearVelocity()[0]<< "  velocidad en y  ->   " << rigidbody[1]->getLinearVelocity()[1]<< "   "<< rigidbody[1]->getLinearVelocity()[2]<< "sssssss1S " << std::endl;
            world->stepSimulation(dt * 0.001f);

		//btVector3 vel(desp_x,rigidbody[1]->getLinearVelocity()[1],desp_z);

        //desp_x = desp_z = 0;
       	 //rigidbody[1]->setLinearVelocity(vel);
				//	std::cout << rigidbody[1]->getLinearVelocity()[0]<< "  velocidad en y  ->   " << rigidbody[1]->getLinearVelocity()[1]<< "   "<< rigidbody[1]->getLinearVelocity()[2]<< "sssssss2 " << std::endl;

			for(short i=0; i<rigidbody.size(); i++){
				// Actualiza el cuerpo dinamico de la caja

            	updateDynamicBody(rigidbody[i]);
			}

        } else {
            device->yield();
        }

		if(desp_x==0&&desp_z==0){
			Mover(1,desp_x,rigidbody[1]->getLinearVelocity()[1],desp_z);
		}
       // device->drop();
}

void Entidad::moverDireccion(unsigned short _i_direccion){  // Direccion
	//std::cout << "Angulo = " << (int)_i_direccion << std::endl;

    desp_z += cos(angulo+(_i_direccion*std::acos(-1)/180)) * _velocidad * mdt;
    desp_x += sin(angulo+(_i_direccion*std::acos(-1)/180)) * _velocidad * mdt;
    moving = true;
    Mover(1,desp_x,rigidbody[1]->getLinearVelocity()[1],desp_z);
}

void Entidad::moverAdelante(){  //W
	//miZ += cos(angulo) * _velocidad * dt;
    //miX += sin(angulo) * _velocidad * dt;
    desp_z += cos(angulo+(270*std::acos(-1)/180)) * _velocidad * mdt;
    desp_x += sin(angulo+(270*std::acos(-1)/180)) * _velocidad * mdt;
	//std::cout<<"-------------ANGULO: "<<angulo<<std::endl;
	//std::cout<<"-------------velocidad: "<<_velocidad<<std::endl;
	//std::cout<<"-------------dt: "<<dt<<std::endl;
    //interface->Interfaz_rotarProta(0);
    moving = true;
    Mover(1,desp_x,rigidbody[1]->getLinearVelocity()[1],desp_z);
}

void Entidad::moverIzquierda(){ //A
	//miZ += sin(angulo) * _velocidad * dt;
    //miX -= cos(angulo) * _velocidad * dt;
    //interface->Interfaz_rotarProta(-90);
    desp_z += sin(angulo) * _velocidad * mdt;
    desp_x -= cos(angulo) * _velocidad * mdt;
    moving = true;
    Mover(1,desp_x,rigidbody[1]->getLinearVelocity()[1],desp_z);
}

void Entidad::moverDerecha(){   //D
	//miZ -= sin(angulo) * _velocidad * dt;
    //miX += cos(angulo) * _velocidad * dt;
    //interface->Interfaz_rotarProta(90);
    desp_z -= sin(angulo) * _velocidad * mdt;
    desp_x += cos(angulo) * _velocidad * mdt;
    moving = true;
    Mover(1,desp_x,rigidbody[1]->getLinearVelocity()[1],desp_z);
}

void Entidad::moverAtras(){     //S
	//miZ -= cos(angulo) * _velocidad * dt;
    //miX -= sin(angulo) * _velocidad * dt;
    //interface->Interfaz_rotarProta(180);    
    desp_z -= cos(angulo) * _velocidad * mdt;
    desp_x -= sin(angulo) * _velocidad * mdt;
    moving = true;
    Mover(1,desp_x,rigidbody[1]->getLinearVelocity()[1],desp_z);
}

void Entidad::saltar(){		   //Space

	std::cout<<"entra" << std::endl;
	std::cout<< rigidbody[1]->getLinearVelocity()[1] << std::endl;
		
	if(rigidbody[1]->getLinearVelocity()[1]==0){
		rigidbody[1]->applyCentralImpulse( btVector3( 0.f, 2000.f, 0.f ) );
		//exit(0);
	}
}

void Entidad::updateDynamicBody(btRigidBody *body) {
	// TODO 1.d Actualiza la posicion del cuerpo en el motor grafico

	ISceneNode *node = static_cast<ISceneNode *>(body->getUserPointer());
	btVector3 pos = body->getCenterOfMassPosition();
		
	node->setPosition(vector3df(pos[0], pos[1], pos[2]));


	const btQuaternion &quat = body->getOrientation();
	quaternion q(quat.getX(), quat.getY(), quat.getZ(), quat.getW());
	vector3df euler;
	q.toEuler(euler);
	euler *= RADTODEG;
	node->setRotation(euler);
}

void Entidad::moveKinematicBody(btRigidBody *body, btVector3 traslation) {
// TODO 1.g Mover cuerpo cinematico segun el vector de traslacion proporcionado
// TODO 1.g Actualizar el nodo de la escena correspondiente
	ISceneNode *node = static_cast<ISceneNode *>(body->getUserPointer());

	btTransform t;
	body->getMotionState()->getWorldTransform(t);
	btVector3 origin = t.getOrigin() + traslation;
	t.setOrigin(origin);
	body->getMotionState()->setWorldTransform(t);
	node->setPosition(vector3df(origin.getX(), origin.getY(), origin.getZ()));
}


// TODO 2.d Mover objeto cinematico segun el vector de traslacion proporcionado (no usa motion state, se pone directamente la transformacion)
// TODO 2.d Actualizar el nodo de la escena correspondiente
void Entidad::moveKinematicObject(btCollisionObject *object, btVector3 traslation) {
	ISceneNode *node = static_cast<ISceneNode *>(object->getUserPointer());
	btTransform t = object->getWorldTransform();
	btVector3 origin = t.getOrigin() + traslation;
	t.setOrigin(origin);
	object->setWorldTransform(t);
	node->setPosition(vector3df(origin.getX(), origin.getY(), origin.getZ()));
}


// TODO 2.a Comprueba si existe algun contacto en el mundo. Si al menos existe uno devuelve true, en caso contrario false
bool Entidad::hasCollision(btDynamicsWorld *world) {

	int numManifolds = world->getDispatcher()->getNumManifolds();
	for (int i=0;i<numManifolds;i++)
	{
		btPersistentManifold* contactManifold =  world->getDispatcher()->getManifoldByIndexInternal(i);
		const btCollisionObject* obA = static_cast<const btCollisionObject*>(contactManifold->getBody0());
		const btCollisionObject* obB = static_cast<const btCollisionObject*>(contactManifold->getBody1());

		int numContacts = contactManifold->getNumContacts();
		for (int j=0;j<numContacts;j++)
		{
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if(pt.getDistance()<=0.0f) {
				return true;
			}
		}
	}
	return false;
}

bool Entidad::hasCollision(btDynamicsWorld *world, btPairCachingGhostObject *ghostObject) {

	// TODO 1.n Comprueba si existe algun contacto con el ghost object. Si al menos existe uno devuelve true, en caso contrario false
	btManifoldArray manifoldArray;
	btBroadphasePairArray &pairs = ghostObject->getOverlappingPairCache()->getOverlappingPairArray();
	int numPairs = pairs.size();

	for(int i=0;i<numPairs;i++) {

		manifoldArray.clear();

		const btBroadphasePair &pair = pairs[i];

		btBroadphasePair *collisionPair = world->getPairCache()->findPair(pair.m_pProxy0, pair.m_pProxy1);
		if(!collisionPair)
			continue;

		if(collisionPair->m_algorithm) {
			collisionPair->m_algorithm->getAllContactManifolds(manifoldArray);
		}

		for(int j=0;j<manifoldArray.size();j++) {
			btPersistentManifold *manifold = manifoldArray[j];
			for(int p=0;p<manifold->getNumContacts();p++) {
				return true;
			}
		}
	}
	return false;
}

void Entidad::Mover(uint8_t id, float x, float y, float z){
	//std::cout<<"borrame -----------------X: "<< x <<"--Y: "<< y << "--Z: "<< z <<std::endl; 
	btRigidBody* cuerpo;
	cuerpo = rigidbody[id];
	btVector3 mov(x,y,z);
	//this->moveKinematicBody(cuerpo,mov);
    rigidbody[id]->setLinearVelocity(mov);
	desp_x = desp_z = 0;
}

IrrlichtDevice* Entidad::getDevice(){
	return device;
}

void Entidad::render(){

	driver->beginScene(true, true, SColor(255,100,101,140));
    smgr->drawAll();
    // Dibuja maya de depuracion
    // TODO 1.f Establece el material para la maya sin iluminacion
    SMaterial debugMat;
    debugMat.Lighting = false;
    driver->setMaterial(debugMat);
    // TODO 1.f Establece la transformacion identidad en el driver
    driver->setTransform(ETS_WORLD, IdentityMatrix);
    // TODO 1.f Dibuja la maya de depuracion del mundo
    
	world->debugDrawWorld();

	//guienv->drawAll();
    driver->endScene();
}