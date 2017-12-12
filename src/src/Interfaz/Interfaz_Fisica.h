#ifndef Interfaz_Fisica_H_
#define Interfaz_Fisica_H_

#include <iostream>
#include <vector>

class btTransform;
class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btCollisionShape;
class btCollisionShape;
class btDefaultMotionState;
class btRigidBody;	
class btDefaultMotionState;								
class btRigidBody;
class Interfaz; 
struct Vector3;

class Interfaz_Fisica{
public:
	unsigned short CargaRigidBodyProta(int mass, float x, float y, float z);
	unsigned short CargaRigidBody(int mass, float x, float y, float z);
	Vector3 moverObjeto(Vector3 vec, unsigned short id);
	void update();
	~Interfaz_Fisica();
	static Interfaz_Fisica* Interfaz_Fisica_GetInstance();

private:
	Interfaz_Fisica();
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
	std::vector<btRigidBody*> _VRigidBodys;
	unsigned short _rigidBodyCounter;
	static Interfaz_Fisica* _instancia; 
	Interfaz* _interfaz_graficos;
	int _gravity;
};

#endif