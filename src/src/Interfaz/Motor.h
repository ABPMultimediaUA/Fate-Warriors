#include "irrlicht/irrlicht.h"
#include <cstdint>

class Entidad;

using namespace irr;

class Motor{
public:
      static Motor* Motor_GetInstance();
      ~Motor();
      
      uint8_t crearObjeto(char* rutaObj,float x, float y, float z);
      void    poner_camara_a_entidad(unsigned short _i_direccion);

      void    update(double _i_dt);
      void    render();  

      void    Mover(uint8_t id, float x, float y, float z);
      void    Mover(uint8_t id, unsigned short _i_direccion, float x, float y, float z); //mover con rotacion
      void    VelocidadDireccion(unsigned short id, unsigned short _i_direccion, unsigned short _i_velocidad);
      void    setPositionXZ(unsigned short id, float x, float z);
      void    saltar(unsigned short _i_id);
      void    set_text_vida(int _vida);
      void Dash(unsigned short _i_direccion, unsigned short id);
      float   getX(short id);
      float   getY(short id);
      float   getZ(short id);

      float   getVelocidadY(short id);
      IrrlichtDevice* getIrrlichtDevice();


private:
      static Motor* _Motor;
      Entidad * _entidad;
      Motor();
};