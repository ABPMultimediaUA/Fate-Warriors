#include "Interfaz_Fisica.h"
#include "Interfaz.h"

Interfaz_Fisica* Interfaz_Fisica::_instancia=0;

Interfaz_Fisica* Interfaz_Fisica::Interfaz_Fisica_GetInstance(){
	if(_instancia==0){
		_instancia	=  new Interfaz_Fisica();
	}
	return _instancia;
}

Interfaz_Fisica::Interfaz_Fisica():_interfaz(Interfaz::Interfaz_getInstance()){

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

}

void Interfaz_Fisica::update(){

	_dynamicsWorld->stepSimulation(1 / 60.f, 10);
	//this->Interfaz_collisionEnable();
	btTransform trans;
	_fallRigidBody->getMotionState()->getWorldTransform(trans);
	
	float posX = trans.getOrigin().getX();
	float posY = trans.getOrigin().getY();
	float posZ = trans.getOrigin().getZ();
	
	_interfaz->Interfaz_moverProta(posX,posY,posZ);	

		//std::cout<<"algo:     "<<pos<<std::endl;
}

void Interfaz_Fisica::CargaRigidBodyProta(int mass, float x, float y, float z){
	_fallMotionState 	= new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar Mymass 	= mass;
	btVector3 			fallInertia(0, 0, 0);
	
	_fallShape->calculateLocalInertia(mass, fallInertia);

	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, _fallMotionState,
															_fallShape, fallInertia);
				
	_fallRigidBody 		= new btRigidBody(fallRigidBodyCI);	
	_dynamicsWorld->addRigidBody(_fallRigidBody);
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

	delete _fallRigidBody;
	_fallRigidBody=nullptr;

}