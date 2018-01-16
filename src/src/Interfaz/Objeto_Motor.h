
#ifndef OBJETO_MOTOR_H_
#define OBJETO_MOTOR_H_


#include "Motor.h"


class Objeto_Motor{
public:
      Objeto_Motor(BoundingBoxes tipo, char* rutaObj,float x, float y, float z, short peso);
      ~Objeto_Motor();
      unsigned short getId();
      void VelocidadDireccion(unsigned short _i_direccion, unsigned short _i_velocidad, double dt);
      void setPositionXZ(float x, float z);
      
      void setVelocidad(float x, float y, float z);
      void setVelocidad(unsigned short _i_direccion, float x, float y, float z,double mdt);
      void Dash(unsigned short _i_direccion, double mdt);
      void saltar();

      float getX();
    float getY();
    float getZ();


private:
      ISceneNode*       _nodo;
      Interpolacion*    _interpolacion;
      btRigidBody*      _rigidbody;
      unsigned short    _id;
      double desp_z;
      double desp_x;
};

#endif /* OBJETO_MOTOR_H_ */
