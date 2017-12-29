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
      void moverDireccion(unsigned short _i_direccion);
      void moverAdelante();
      void moverIzquierda();
      void moverDerecha();
      void moverAtras();
      uint8_t crearObjeto(char* rutaObj,float x, float y, float z);
      void saltar();

private:
      static Motor* _Motor;
      Entidad * _entidad;
      Motor();
};