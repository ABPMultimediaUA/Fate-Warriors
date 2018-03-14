#include "Motor.h"
#include "SFML/Graphics.hpp"
#include <cmath>
#include "../Personajes/Interpolacion.h"
#include "Objeto_Motor.h"
#include "../Objeto.h"
#include "../Personajes/Player.h"
#include "../Personajes/NPC.h"
#include "../Puerta.h"
#include "../Interruptor.h"
#include "DebugDraw.h"
#include "EnumTiposColision.h"
#include "../Puerta_Pincho.h"
#include "../Moose_Engine/src/TMooseEngine.h"
#include "../Moose_Engine/src/TModelado.h"
#include "../Moose_Engine/src/TTransform.h"
#include "../Moose_Engine/src/TNodo.h"
#include "../Moose_Engine/src/TCamara.h"
#include "../Moose_Engine/src/TLuz.h"
#include "../Moose_Engine/src/iNodoModelado.h"
#include "../Moose_Engine/src/iNodoCamara.h"
#include "../Moose_Engine/src/iNodoLuz.h"

/*
#include "Entidad.h"
#include "../Input.h"
#include "../Utilidades/Vector.h"
master*/




Motor* Motor::_Motor=0;

Motor* Motor::Motor_GetInstance(){
	if(_Motor == 0){
        _Motor= new Motor(1280, 720);
    }
    return _Motor;
}


Motor::Motor(uint16_t width, uint16_t height){
    //configuracion_irlitch();
	configuracion_ME(width, height, false, false);
    configuracion_bullet();
    preparar_depuracion_mundo();

	const char* cstr = "models/MapaColision/ColisionesNivel1.obj";
	importarEscenario(cstr, 0,0,0);
    desp_x = desp_z = 0;

	//camara = new Camara(smgr, device);
	//crear camara

	angulo = 0;
	_velocidad = 1;
	_debug = false;
	_id_jugador = 0;

	rayOrigen = new Vector3(0,0,0);
	rayDestino = new Vector3(0,0,0);
/*
	rayOrigen._x = 0;
	rayOrigen._y = 0;
	rayOrigen._z = 0;

	rayDestino._x = 0;
	rayDestino._y = 0;
	rayDestino._z = 0;
	*/
	//esto no debe ir aqui y se cambia despues de la presentacion
	_vida = 300;
	_maxvida = 300;
}

//void Motor::crear_partida(){}

void Motor::borrar_objeto(Objeto_Motor* _objeto_motor){

	_objeto_motor->getNodo()->remove();

	world->removeRigidBody(_objeto_motor->getRigidBody());
	delete _objeto_motor->getRigidBody()->getCollisionShape();
	delete _objeto_motor->getInterpolacion();
	delete _objeto_motor->getRigidBody();

	auto ite2 = std::find(_objetos_motor.begin(), _objetos_motor.end(), _objeto_motor);
    if ( ite2 != _objetos_motor.end()){
        _objetos_motor.erase(ite2);
    }

	//std::cout << "cantidad de elementos en el motor" << _objetos_motor.size() << std::endl;
	

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
    std::vector<iNodoModelado*>::iterator it;
    it = std::find(nodes.begin(), nodes.end(), _nodo);
    if ( it != nodes.end()){
        nodes.erase(it);
        delete _nodo;
    }
	*/
}


void Motor::vaciar_motor(){
	for(short a=0; a<_objetos_motor.size();a++){
		delete _objetos_motor[a];
	}
	_objetos_motor.clear();
}

/*bool Motor::colision_entre_dos_puntos(Vector3 inicio, Vector3 fin){
	return _entidad->colision_entre_dos_puntos(inicio,fin);
}*/ 

void Motor::borrar_rb(btRigidBody* rb){ // Mejorar

	world->removeRigidBody(rb);
	delete rb->getCollisionShape();
	delete rb;
}


Motor::~Motor(){

_Motor=0;

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
	//delete _GUI;
	//driver->drop();
	//device->drop();


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
	//device->closeDevice();
}



void Motor::preparar_depuracion_mundo(){
	
}


void Motor::configuracion_ME(uint16_t width, uint16_t height, bool fullscreen, bool v_sync){
    _me = TMooseEngine::get_instancia();
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
		btRigidBody* _objeto_esceario = new btRigidBody(0, cubeMotionState, escenario);
		_objeto_esceario->setFriction(0);
		world->addRigidBody(_objeto_esceario,COL_ESCENARIO, escenario_colisiona_con);

		//btBroadphaseProxy* proxy = esta_vez_si->getBroadphaseProxy();
		//proxy->m_collisionFilterGroup = 4;
		//proxy->m_collisionFilterMask = 4;
	}	
    world->setGravity(btVector3(0,-9.8*18,0));
}

void Motor::render(){
	_me->draw();
}

bool Motor::ventana_abierta(){
    return !_me->ventana_abierta();
}

/*
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
*/

unsigned short Motor::crear_objeto(BoundingBoxes tipo,const char* ruta,float x, float y, float z, float _i_peso){
	/*iNodoModelado *cubeNode = crearModelado(ruta, x,y,z);
	Interpolacion* interpolacion = crear_interpolacion(x,y,z);
	btRigidBody* cuerpo = 	crearRigidBody(tipo,ruta,x, y, z, _i_peso, cubeNode);
	*/

	return 1;
}

iNodoModelado* Motor::crearModelado(const char* ruta){
    iNodoModelado* nodo = new iNodoModelado(ruta);
    lista_i_nodo.push_back(nodo);
    return nodo;
}

iNodoModelado* Motor::crearModelado(const char* ruta, float x, float y, float z){
    iNodoModelado* nodo = new iNodoModelado(ruta, x, y, z);
    lista_i_nodo.push_back(nodo);
    return nodo;
}

iNodoCamara* Motor::crearCamara(bool activa){
    iNodoCamara* nodo = new iNodoCamara(activa);
    lista_i_nodo.push_back(nodo);
    return nodo;
}

iNodoCamara* Motor::crearCamara(bool activa, float x, float y, float z){
    iNodoCamara* nodo = new iNodoCamara(activa, x, y, z);
    lista_i_nodo.push_back(nodo);
    return nodo;
}

iNodoLuz* Motor::crearLuz(bool activa, float intensidad){
    iNodoLuz* nodo = new iNodoLuz(activa, intensidad);
    lista_i_nodo.push_back(nodo);
    return nodo;
}

iNodoLuz* Motor::crearLuz(bool activa, float intensidad, float x, float y, float z){
    iNodoLuz* nodo = new iNodoLuz(activa, intensidad, x, y, z);
    lista_i_nodo.push_back(nodo);
    return nodo;
}

void Motor::crear_ObjetoMotor(Objeto_Motor* _i_objeto_motor){
	_objetos_motor.push_back(_i_objeto_motor);
}

btRigidBody* Motor::crearRigidBody(Objeto* _i_objeto, BoundingBoxes tipo,const char* ruta,float x, float y, float z, float _i_peso, iNodoModelado *cubeNode){
		
	float altura,anchura,profundidad;
	btCollisionShape *cubeShape;
	this->getDimensiones(cubeNode,anchura,altura,profundidad);
	
	btTransform cubeTransform;
	cubeTransform.setIdentity();

	cubeTransform.setOrigin(btVector3(x,y+(altura/2),z));

	btDefaultMotionState *cubeMotionState = new btDefaultMotionState(cubeTransform);

	float cubeMass = _i_peso;

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
	
	cubeShape->setUserPointer(_i_objeto);


	btVector3 cubeLocalInertia;
	cubeShape->calculateLocalInertia(cubeMass, cubeLocalInertia);

	btRigidBody *cubeBody = new btRigidBody(cubeMass, cubeMotionState, cubeShape, cubeLocalInertia);
	
	cubeBody->setAngularFactor(0);
	cubeBody->setUserPointer(_i_objeto);
	cubeBody->setRestitution(0);
	cubeBody->setFriction(1);
	cubeBody->forceActivationState(DISABLE_DEACTIVATION );


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
		grupo_colision   = COL_PUERTA;
		mascara_colision = puerta_colisiona_con;
	}

	else if(dynamic_cast<Puerta_Pincho*>(_i_objeto)!=NULL){
		grupo_colision   = COL_PUERTA;
		mascara_colision = puerta_colisiona_con;
	}

	else if(dynamic_cast<Interruptor*>(_i_objeto)!=NULL){
		grupo_colision   = COL_PUERTA;
		mascara_colision = puerta_colisiona_con;
	}
	
		//si es otra cosa
	else{
		cubeBody->setCollisionFlags(cubeBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		grupo_colision   = COL_OTRO;
		mascara_colision = otros_colisiona_con;
	}
	

	cubeShape->setUserPointer(_i_objeto);

	world->addRigidBody(cubeBody,grupo_colision,mascara_colision);

	return cubeBody;
}

Interpolacion* Motor::crear_interpolacion(float x, float y, float z){
	Vector3 posicion(x,y,z);
	Interpolacion* _interpolacion = new Interpolacion(posicion);
	return _interpolacion;
}

btRigidBody* Motor::crear_rb_ataque(){
	float mult = 4.9212625;

	btTransform ghostTransform;
	ghostTransform.setIdentity();
	ghostTransform.setOrigin(btVector3(1, 1 ,1));

	btDefaultMotionState *cubeMotionState = new btDefaultMotionState(ghostTransform);

	float cubeMass = 0;

	btBoxShape *cubeShape = new btBoxShape(btVector3(1,1,1));

	btVector3 cubeLocalInertia;
	cubeShape->calculateLocalInertia(cubeMass, cubeLocalInertia);

	btRigidBody* rb_ataque = new btRigidBody(cubeMass, cubeMotionState, cubeShape, cubeLocalInertia);
	
	rb_ataque->setCollisionFlags(rb_ataque->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	int grupo_colision   = COL_OTRO;
	int mascara_colision = otros_colisiona_con;
	
	world->addRigidBody(rb_ataque,grupo_colision,mascara_colision);

	return rb_ataque;
}

void Motor::getDimensiones(iNodoModelado* node, float &anchura, float &altura, float &profundidad){
	/*
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
	*/
	//de forma temporal hasta que el ME tenga forma de calcular bounding
	profundidad = anchura = altura = 2;
}

void Motor::setCollisionGroup(int group, btRigidBody *_i_rigidbody ) {
	btBroadphaseProxy* proxy = _i_rigidbody->getBroadphaseProxy();
	proxy->m_collisionFilterGroup = group;	
}

void Motor::setCollisionMask(int mask, btRigidBody *_i_rigidbody) {
	btBroadphaseProxy* proxy = _i_rigidbody->getBroadphaseProxy();
	proxy->m_collisionFilterMask = mask;
}

void Motor::poner_camara_a_entidad(Objeto_Motor* _objeto_motor){
	iNodoModelado *cubeNode = _objeto_motor->getNodo();
	camara->Camara_setProta(cubeNode);
	_id_jugador = 0;

	camara->set_posicion_inicial(_objeto_motor->getInterpolacion()->get_direccion_actual());
}

btCollisionWorld::ClosestRayResultCallback Motor::trazaRayo(btVector3 start, btVector3 end, int mascara_colision){
	btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
	rayCallback.m_collisionFilterMask  = mascara_colision;
	rayCallback.m_collisionFilterGroup = COL_RAY;
	world->rayTest(start, end, rayCallback);

	return rayCallback;
}

btCollisionWorld::AllHitsRayResultCallback Motor::trazaRayoAll(btVector3 start, btVector3 end, int mascara_colision){
	btCollisionWorld::AllHitsRayResultCallback rayCallback(start, end);
	rayOrigen->_x = start.getX();
	rayOrigen->_y = start.getY();
	rayOrigen->_z = start.getZ();

	rayDestino->_x = end.getX();
	rayDestino->_y = end.getY();
	rayDestino->_z = end.getZ();
	rayCallback.m_collisionFilterMask  = mascara_colision;
	rayCallback.m_collisionFilterGroup = COL_RAY;
	world->rayTest(start, end, rayCallback);


	return rayCallback;
}


iNodoModelado* Motor::importarEscenario(const char* rutaObj, float x, float y, float z){
	return crearModelado(rutaObj, x, y, z);
}

void Motor::update(double dt){

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)){
		_debug = !_debug;
	}

	mdt = dt;
   	//if(device->isWindowActive()) {

        world->stepSimulation(dt * 0.001f,5);

		short tamanio = _objetos_motor.size();
		for(short i=0; i<tamanio; i++){
			// Actualiza el cuerpo dinamico de la caja
			_objetos_motor[i]->updateDynamicBody();
			_objetos_motor[i]->setVelocidad(0,_objetos_motor[i]->getVelocidadY(),0);
		
		}

		// Update de la posicion de la camara (despues de actualizar la del jugador)
		updateCamaraColision();
    //} 

    //else {
    //    device->yield();
    //}
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

bool Motor::x_ve_a_y(Vector3 x, Vector3 y, int mascara_colision){
	//conversion de vector3 a bullet vector3
	btVector3 mX(x._x,x._y,x._z);
	btVector3 mY(y._x,y._y,y._z);

	btCollisionWorld::ClosestRayResultCallback rayCallback = this->trazaRayo(mX, mY,mascara_colision);

	//if(dynamic_cast<Character*>(rayCallback)!=null){
	//	std::cout<<"colisiona con personaje/npc  \n";
	//}
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
	//std::cout<<"colisiona: "<<rayCallback.hasHit()<<std::endl;
	return(!rayCallback.hasHit());
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
		btCollisionWorld::ClosestRayResultCallback rayCallback = this->trazaRayo(pos, camaraPos,ray_colisiona_con);
		//dynamic_cast<const btRigidBody*>(rayCallback.m_collisionObject)->getUserPointer();
		//->getUserPointer();
		if(rayCallback.hasHit()){
			btVector3 point = rayCallback.m_hitPointWorld;
			btVector3 normal = rayCallback.m_hitNormalWorld;
			const btCollisionObject *object = rayCallback.m_collisionObject;
			camara->Camara_setPositionColision(core::vector3df(point[0],point[1],point[2]));
				
			//for(short i = 0; i<fileLoader->getNumRigidBodies();i++){
			//	if(fileLoader->getRigidBodyByIndex(i) == object){
			//		// Set posicion colision
			//		//camara->Camara_setPositionColision(core::vector3df(point[0],point[1],point[2]));
			//	}
			//}
		}

		angulo = camara->Camara_getAngleRad();
}



void Motor::resetear_camara(){
	camara->Camara_reset(_objetos_motor[0]->getInterpolacion()->get_direccion_actual());
}

/*
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
		float mult = 4.9212625;
		btVector3 a(rayOrigen->_x,rayOrigen->_y,rayOrigen->_z);
		btVector3 b(rayDestino->_x,rayDestino->_y,rayDestino->_z);
		debugDraw->drawLine(a,b,btVector4(0,0,0,1));
	
	}

	//guienv->drawAll();
	_GUI->draw();
    driver->endScene();
}
*/
//Metodos set

void Motor::set_text_vida(int _i_vida){
	//_GUI->set_text_vida(_i_vida);
	_vida = (_i_vida*300)/500;
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

bool Motor::comprobar_colision(btRigidBody *rb1, btRigidBody *rb2){

	btManifoldArray manifoldArray;

	manifoldArray.clear();

	btBroadphasePair* collisionPair = world->getPairCache()->findPair(rb1->getBroadphaseProxy(), rb2->getBroadphaseProxy());

	if (collisionPair){

		if (collisionPair->m_algorithm)
			collisionPair->m_algorithm->getAllContactManifolds(manifoldArray);

		for (int j = 0; j < manifoldArray.size(); j++)
		{
			btPersistentManifold* manifold = manifoldArray[j];
			
			if(manifold->getNumContacts() > 0){
				return true;
			}
		}
	}
	return false;
}

void Motor::posicionar_rotar_y_escalar_rb(btRigidBody *rb, btVector3 posicion, btVector3 escala, uint16_t rotacion){
	float mult = 4.9212625;
	btScalar gTilt = rotacion*SIMD_PI / (180.0f); 
	btTransform rbTransform;

	// Rotacion
	rbTransform.setIdentity();
	rbTransform.setOrigin(rb->getCenterOfMassPosition());
	btQuaternion incline;
	incline.setRotation(btVector3(0, 1, 0), gTilt);
	rbTransform.setRotation(incline);
	//std::cout << rotacion << std::endl;

	// Escalado
	rb->getCollisionShape()->setLocalScaling(escala);

	// Traslacion
	rbTransform.setOrigin(posicion);

//Se aplican las transformaciones
	rb->setWorldTransform(rbTransform);
}
