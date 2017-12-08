#ifndef Interfaz_Fisica_H_
#define Interfaz_Fisica_H_

#include <iostream>
#include <btBulletDynamicsCommon.h>

class Interfaz;

class Interfaz_Fisica{
public:

	
	void CargaRigidBodyProta(int mass, float x, float y, float z);
	void update();
	~Interfaz_Fisica();
	static Interfaz_Fisica* Interfaz_Fisica_GetInstance();

private:
	Interfaz_Fisica();
	Interfaz* _interfaz;
	btBroadphaseInterface* _broadphase;
	btDefaultCollisionConfiguration* _collisionConfiguration;
	btCollisionDispatcher* _dispatcher;
	btSequentialImpulseConstraintSolver* _solver;
	btDiscreteDynamicsWorld* _dynamicsWorld;
	btCollisionShape* _groundShape;
	btCollisionShape* _fallShape;
	btDefaultMotionState* _groundMotionState;
	btRigidBody* _groundRigidBody;	
	btDefaultMotionState* _fallMotionState;								
	btRigidBody* _fallRigidBody;
	static Interfaz_Fisica* _instancia; 
};

#endif