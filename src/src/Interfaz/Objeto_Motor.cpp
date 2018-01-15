#include "Objeto_Motor.h"
#include <cstdint>

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "BulletWorldImporter/btBulletWorldImporter.h"
//#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "DebugDraw.h"
#include "../Camara/Camara.h"
#include "GUI.h"



Objeto_Motor::Objeto_Motor(BoundingBoxes tipo, char* rutaObj,float x, float y, float z){
	Motor* _motor = Motor::Motor_GetInstance();
    /*
   _nodo            = _motor->crearModelado(rutaObj,x,y,z);
   _interpolacion   = _motor->crear_interpolacion(x,y,z);
   _rigidbody       = _motor->crearRigidBody(tipo,rutaObj,x,y,z,666666,_nodo);
   _id              = _motor->getId();
   */
}

Objeto_Motor::~Objeto_Motor(){
    Motor* _motor = Motor::Motor_GetInstance();
    //_motor->borrar_objeto(_nodo,_interpolacion,_rigidbody);
} 


unsigned short Objeto_Motor::getId(){
    return _id;
}