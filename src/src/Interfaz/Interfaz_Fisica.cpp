#include "Interfaz_Fisica.h"
#include <btBulletDynamicsCommon.h>
#include "../Utilidades/Vector.h"

Interfaz_Fisica* Interfaz_Fisica::_instancia=0;

Interfaz_Fisica* Interfaz_Fisica::Interfaz_Fisica_GetInstance(){
	if(_instancia==0){
		_instancia	=  new Interfaz_Fisica();
	}
	return _instancia;
}

Interfaz_Fisica::Interfaz_Fisica(){

	_broadphase 			= new btDbvtBroadphase();
	_collisionConfiguration = new btDefaultCollisionConfiguration();
	_dispatcher 			= new btCollisionDispatcher(_collisionConfiguration);
	_solver 				= new btSequentialImpulseConstraintSolver;
	_dynamicsWorld 			= new btDiscreteDynamicsWorld(_dispatcher,
														 _broadphase, _solver, _collisionConfiguration);

	_dynamicsWorld->setGravity(btVector3(0,-25,0));

	_groundShape 			= new btStaticPlaneShape(btVector3(0,1,0), 1);
	_fallShape 				= new btSphereShape(1);

	_groundMotionState 		= new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0,-1,0)));
	
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, _groundMotionState, _groundShape, btVector3(0,0,0));
	_groundRigidBody 		= new btRigidBody(groundRigidBodyCI);

	_dynamicsWorld->addRigidBody(_groundRigidBody);
	_rigidBodyCounter = 0;
}

void Interfaz_Fisica::update(){
	_dynamicsWorld->stepSimulation(1 / 60.f, 10);
	//this->Interfaz_collisionEnable();
	btTransform trans;
	//_fallRigidBody->getMotionState()->getWorldTransform(trans);
	
	//btVector3 pos =	trans.getOrigin();

	//float tx,ty,tz;
	//tx = pos.x();
	//ty = pos.y();
	//tz = pos.z();

	//this->moverProta(tx,ty,tz);
}

Vector3 Interfaz_Fisica::moverObjeto(Vector3 vec, unsigned short id){
	Vector3 vectorsito(0,0,50.0f);
	
	btTransform trans;
	
	btVector3 algo(vectorsito._x, vectorsito._y, vectorsito._z);
	
	_VRigidBodys.at(id)->applyCentralForce(algo);
	_VRigidBodys.at(id)->setWorldTransform(trans);
	
	Vector3 adevolver(0,0,0);
	btVector3 pos = trans.getOrigin();
	
	adevolver._x = pos.x();
	adevolver._y = pos.y();
	adevolver._z = pos.z();
	std::cout<<"adevolverX: "<<adevolver._x<<"adevolverY: "<<adevolver._y<<"adevolverZ: "<<adevolver._z<<std::endl;
	return(adevolver);
}

unsigned short Interfaz_Fisica::CargaRigidBody(int mass, float x, float y, float z){
	_fallMotionState 	= new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar Mymass 	= mass;
	btVector3 			fallInertia(0, 0, 0);
	
	_fallShape->calculateLocalInertia(mass, fallInertia);

	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, _fallMotionState,
															_fallShape, fallInertia);
				
	btRigidBody* rigidBody 		= new btRigidBody(fallRigidBodyCI);	
	_dynamicsWorld->addRigidBody(rigidBody);
	_VRigidBodys.push_back(rigidBody);
	unsigned short counter = _rigidBodyCounter;
	_rigidBodyCounter++;
	return(counter);
}

unsigned short Interfaz_Fisica::CargaRigidBodyProta(int mass, float x, float y, float z){
	_fallMotionState 	= new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar Mymass 	= mass;
	btVector3 			fallInertia(0, 0, 0);
	
	_fallShape->calculateLocalInertia(mass, fallInertia);

	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, _fallMotionState,
															_fallShape, fallInertia);
				
	btRigidBody* rigidBody 		= new btRigidBody(fallRigidBodyCI);	
	_dynamicsWorld->addRigidBody(rigidBody);
	_VRigidBodys.push_back(rigidBody);
	unsigned short counter = _rigidBodyCounter;
	_rigidBodyCounter++;
	return(counter);
}

Interfaz_Fisica::~Interfaz_Fisica(){

	delete _dynamicsWorld;
	_dynamicsWorld=nullptr;

	delete _broadphase;
	_broadphase=nullptr;

	delete _collisionConfiguration;
	_collisionConfiguration=nullptr;

	delete _dispatcher;
	_dispatcher=nullptr;

	delete _solver;
	_solver=nullptr;

	delete _groundShape;
	_groundShape = nullptr;

	delete _fallShape;
	_fallShape=nullptr;

	delete _groundMotionState;
	_groundMotionState=nullptr;

	delete _groundRigidBody;
	_groundRigidBody=nullptr;

	delete _fallMotionState;		
	_fallMotionState=nullptr;

//	delete _fallRigidBody;
//	_fallRigidBody=nullptr;

}