
#ifndef OBJETO_MOTOR_H_
#define OBJETO_MOTOR_H_


#include "Motor.h"


class Objeto_Motor{
public:
      Objeto_Motor(BoundingBoxes tipo, char* rutaObj,float x, float y, float z);
      ~Objeto_Motor();
      unsigned short getId();

private:
      ISceneNode*       _nodo;
      Interpolacion*    _interpolacion;
      btRigidBody*      _rigidbody;
      unsigned short    _id;
};

#endif /* OBJETO_MOTOR_H_ */
