#ifndef OBJETO_ME_H
#define OBJETO_ME_H

#include "../../Utilidades/Vector.h"
#include "EnumTiposBoundingBox.h"

#include "iNodoModelado.h"

#include <cstdint>

class Objeto;
class Motor;
class Interpolacion;
class btRigidBody;
class btVector3;
class Character;

class Objeto_ME{

    public:
        Objeto_ME(Objeto* _objeto,BoundingBoxes tipo,const char* rutaObj,float x, float y, float z, int16_t peso);
        ~Objeto_ME();

        void setPositionXZ(float x, float z);
        void VelocidadDireccion(uint16_t _i_direccion, float _i_velocidad, double mdt);
        void setVelocidad(float x, float y, float z);
        Character* disparar(Objeto_ME* _i_objeto_origen, uint16_t _i_direccion, uint8_t _i_rango_disparo);
        
        float getX();
        float getY();
        float getZ();


    private:
        iNodoModelado* _nodo;
        Interpolacion* _interpolacion;
        btRigidBody*   _rigidbody;
        double desp_z;
        double desp_x;

        
};

#endif