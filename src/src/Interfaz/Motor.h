#include "irrlicht/irrlicht.h"
#include <cstdint>

class Entidad;

using namespace irr;

class Motor{
public:
      static Motor* Motor_GetInstance();
      ~Motor();
      void update(double _i_dt);
      void render();  
      IrrlichtDevice* getIrrlichtDevice();
      void Mover(uint8_t id, float x, float y, float z);
      //personaje prota
      void moverDireccion(unsigned short id, unsigned short _i_direccion);
      void poner_camara_a_entidad(unsigned short _i_direccion);
      void moverAdelante();
      void moverIzquierda();
      void moverDerecha();
      void moverAtras();
      float getX(short id);
      float getY(short id);
      float getZ(short id);
      void setPositionXZ(unsigned short id, float x, float z);
      uint8_t crearObjeto(char* rutaObj,float x, float y, float z);
      void saltar();
      
private:
      static Motor* _Motor;
      Entidad * _entidad;
      Motor();
};