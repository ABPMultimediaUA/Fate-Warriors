
#ifndef OBJETO_MOTOR_H_
#define OBJETO_MOTOR_H_

#include "irrlicht/irrlicht.h"
#include "../Utilidades/Vector.h"
#include "EnumTiposBoundingBox.h"

#include <cstdint>

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
class Character;
class iNodoModelado;

class Objeto_Motor{
public:

      Objeto_Motor(bool ME, Objeto* _objeto,BoundingBoxes tipo,const char* rutaObj,float x, float y, float z, int16_t peso);
      ~Objeto_Motor();
    
      void setPositionXZ(float x, float z);
      
      void VelocidadDireccion(uint16_t _i_direccion, float _i_velocidad, double dt);
      void setVelocidad(float x, float y, float z);

      Character* disparar(Objeto_Motor* _i_objeto_origen, uint16_t _i_direccion, uint8_t _i_rango_disparo);
      void Dash(uint16_t _i_direccion);
      void Impulso_explosion(Vector3 vector);
      void Impulso(uint16_t _i_direccion, uint16_t potencia);
      void saltar();

      void colorear_nodo(short r,short g, short b);
      Vector3 interpola_posiciones(float _i_interpolacion);

      void abrir_puerta();
      void abrir_puerta1();
      void abrir_puerta2();
      void updateDynamicBody();

      void setPositionY(float y);

      float getX();
      float getY();
      float getZ();

      ISceneNode*    getNodo();
      iNodoModelado* getNodoME();
      Interpolacion* getInterpolacion();
      btRigidBody*   getRigidBody();

      float getVelocidadY();
      btVector3 get_posicion_rb();
      void rotar_nodo(uint16_t rotacion);

private:

      //irrlicht
      //ISceneNode*       _nodo;
      Interpolacion*    _interpolacion;
      btRigidBody*      _rigidbody;
      double desp_z;
      double desp_x;

      //Mouse Engine
      iNodoModelado* _nodo;
      
};

#endif /* OBJETO_MOTOR_H_ */
