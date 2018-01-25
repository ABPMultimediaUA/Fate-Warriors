
#ifndef OBJETO_MOTOR_H_
#define OBJETO_MOTOR_H_

#include "irrlicht/irrlicht.h"
#include "../Utilidades/Vector.h"
#include "EnumTiposBoundingBox.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Objeto;
class Motor;
class Interpolacion;
class btRigidBody;
class btVector3;

class Objeto_Motor{
public:

      Objeto_Motor(Objeto* _objeto,BoundingBoxes tipo,const char* rutaObj,float x, float y, float z, int16_t peso);
      ~Objeto_Motor();
    
      void setPositionXZ(float x, float z);
      
      void VelocidadDireccion(unsigned short _i_direccion, float _i_velocidad, double dt);
      void setVelocidad(float x, float y, float z);
      void setVelocidad(unsigned short _i_direccion, float x, float y, float z,double mdt, float _i_velocidad);

      void Dash(unsigned short _i_direccion);
      void saltar();

      void colorear_nodo(short r,short g, short b);
      Vector3 interpola_posiciones(float _i_interpolacion);

      void abrir_puerta();
      void abrir_puerta1();
      void abrir_puerta2();
      void updateDynamicBody();

      float getX();
      float getY();
      float getZ();

      ISceneNode*    getNodo();
      Interpolacion* getInterpolacion();
      btRigidBody*   getRigidBody();

      float getVelocidadY();
      btVector3 get_posicion_rb();

private:
      ISceneNode*       _nodo;
      Interpolacion*    _interpolacion;
      btRigidBody*      _rigidbody;
      double desp_z;
      double desp_x;
};

#endif /* OBJETO_MOTOR_H_ */
