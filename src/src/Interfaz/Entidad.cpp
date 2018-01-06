#include "Entidad.h"
#include "SFML/Graphics.hpp"
#include <cmath>

Entidad::Entidad(){
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

}

void Entidad::configuracion_irlitch(){
// Configuracion de Irrlicht
	device =
		createDevice( video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
			false, false, false);

	device->setWindowCaption(L"Feito Güarriorusuu");

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	//guienv = device->getGUIEnvironment();
	_GUI = new GUI(device);
}

short Entidad::crear_objeto(char* ruta,float x, float y, float z){
	// Creamos un cubo rojo
	
	//IMeshSceneNode *cubeNode = smgr->addCubeSceneNode(1);

	ISceneNode *cubeNode = smgr->addMeshSceneNode(smgr->getMesh(ruta));

	if(cubeNode){
		cubeNode->setMaterialFlag(EMF_LIGHTING, false);
	}
	
	cubeNode->setPosition(vector3df(x, y, z));

	//smgr->getMeshManipulator()->setVertexColors(cubeNode->getMesh(), SColor(255,255,0,0));
	

	btTransform cubeTransform;
	cubeTransform.setIdentity();

	cubeTransform.setOrigin(btVector3(x,y+50,z));


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



	btCollisionShape *cubeShape = new btBoxShape(btVector3(anchura*0.5,altura*0.5,anchura*0.5)); // new btSphereShape(0.5);
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
	return rigidbody.size()-1;
}

void Entidad::poner_camara_a_entidad(unsigned short id){
	ISceneNode *cubeNode = static_cast<ISceneNode *>(rigidbody[id]->getUserPointer());
	camara->Camara_setProta(cubeNode);
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

	mdt = dt;
   	if(device->isWindowActive()) {

		updateCamaraColision();

        world->stepSimulation(dt * 0.001f);

			short tamanio = rigidbody.size();
			for(short i=0; i<tamanio; i++){
				// Actualiza el cuerpo dinamico de la caja
				updateDynamicBody(rigidbody[i]);
				if(desp_x==0&&desp_z==0){
					setVelocidad(i,desp_x,rigidbody[i]->getLinearVelocity()[1],desp_z);
				}
			}

        } else {
            device->yield();
        }
	
       // device->drop();
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
					camara->Camara_setPosition(core::vector3df(point[0],point[1],point[2]));	
				}
			}
		}

		angulo = camara->Camara_getAngleRad();
}


void Entidad::saltar(unsigned short _i_id){		   //Space

	std::cout<<"entra" << std::endl;
	std::cout<< rigidbody[_i_id]->getLinearVelocity()[1] << std::endl;
		
	if(rigidbody[_i_id]->getLinearVelocity()[1]==0){
		rigidbody[_i_id]->applyCentralImpulse( btVector3( 0.f, 3000.f, 0.f ) );
		//exit(0);
	}
}



void Entidad::updateDynamicBody(btRigidBody *body) {
	
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

void Entidad::render(){

	driver->beginScene(true, true, SColor(255,100,101,140));
    smgr->drawAll();

    SMaterial debugMat;
    debugMat.Lighting = false;
    driver->setMaterial(debugMat);
    driver->setTransform(ETS_WORLD, IdentityMatrix);
    
	world->debugDrawWorld();

	//guienv->drawAll();
	_GUI->draw();
    driver->endScene();
}

void Entidad::apagar(){
	//device->close();
}

//Metodos set

void Entidad::VelocidadDireccion(unsigned short id, unsigned short _i_direccion){  // Direccion
    desp_z += cos(angulo+(_i_direccion*std::acos(-1)/180)) * _velocidad * mdt;
    desp_x += sin(angulo+(_i_direccion*std::acos(-1)/180)) * _velocidad * mdt;
    moving = true;
    setVelocidad(id,desp_x,rigidbody[id]->getLinearVelocity()[1],desp_z);
}

void Entidad::setVelocidad(uint8_t id, float x, float y, float z){
	btVector3 mov(x,y,z);
    rigidbody[id]->setLinearVelocity(mov);
	desp_x = desp_z = 0;
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

void Entidad::set_text_vida(int _i_vida){
	_GUI->set_text_vida(_i_vida);
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
