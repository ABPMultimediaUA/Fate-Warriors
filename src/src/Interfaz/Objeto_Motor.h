
#ifndef OBJETO_MOTOR_H_
#define OBJETO_MOTOR_H_

#include "../Utilidades/Vector.h"
#include "EnumTiposBoundingBox.h"
#include <cstdint>

class Objeto;
class Motor;
class Interpolacion;
class btRigidBody;
class btVector3;
class Character;
class iNodoModelado;

class Objeto_Motor{
public:

      Objeto_Motor(Objeto* objeto,BoundingBoxes tipo,const char* rutaObj,float x, float y, float z, int16_t peso);
      Objeto_Motor(Objeto* objeto,BoundingBoxes tipo,const char* rutaObj,float x, float y, float z, int16_t peso, int16_t _rotacion_x);
      Objeto_Motor(bool bucle, Objeto* _objeto,BoundingBoxes tipo,const char* rutaObj, const char* rutaAnimfloat ,float x, float y, float z, int16_t peso);
      ~Objeto_Motor();
    
      void setPositionXZ(float x, float z);
      
      void VelocidadDireccion(uint16_t _i_direccion, float _i_velocidad, double dt);
      void VelocidadDireccion(uint16_t _i_direccion, float _i_velocidad, double mdt, uint16_t _i_direccion_mirar);
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
      void updateDynamicBodyCharacter();

      void setPositionY(float y);

      float getX();
      float getY();
      float getZ();

      iNodoModelado*    getNodo();
      Interpolacion* getInterpolacion();
      btRigidBody*   getRigidBody();

      float getVelocidadY();
      btVector3 get_posicion_rb();
      void rotar_nodo(uint16_t rotacion);                   // Interpola la rotacion
      void rotar_nodo_sin_interpolacion(uint16_t rotacion); // NO interpola la rotacion
      void cambiar_modelado(const char* _ruta, uint8_t _num_ruta);

private:
      iNodoModelado*       _nodo;
      Interpolacion*    _interpolacion;
      btRigidBody*      _rigidbody;
      double desp_z;
      double desp_x;
};

#endif /* OBJETO_MOTOR_H_ */
