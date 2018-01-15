#include "irrlicht/irrlicht.h"
#include <cstdint>

#include "EnumTiposBoundingBox.h"



class Entidad;
class Input;

using namespace irr;

class Motor{
public:
      static Motor* Motor_GetInstance();
      ~Motor();
      
      uint8_t crearObjeto(BoundingBoxes _i_tipo,char* rutaObj,float x, float y, float z);
      uint8_t crearObjetoPeso(BoundingBoxes _i_tipo,char* rutaObj,float x, float y, float z, float _i_peso);
      void    poner_camara_a_entidad(unsigned short _i_direccion);

      void    update(double _i_dt);
      void    render(float _i_interpolacion);  

      void    Mover(uint8_t id, float x, float y, float z);
      void    setVelocidad(uint8_t id, unsigned short _i_direccion, float x, float y, float z); //mover con rotacion
      void    VelocidadDireccion(unsigned short id, unsigned short _i_direccion, unsigned short _i_velocidad);
      void    setPositionXZ(unsigned short id, float x, float z);
      void    haz_desaparecer(unsigned short _id);
      void    saltar(unsigned short _i_id);
      void    saltar(unsigned short _i_id,int force);
      void    abrir_puerta(unsigned short _i_id);
      void    set_text_vida(int _vida);
      void    Dash(unsigned short _i_direccion, unsigned short id);
      float   getX(short id);
      float   getY(short id);
      float   getZ(short id);
      void    resetear_camara();
      void    apagar(); //poh eso

      void    colorear_nodo(unsigned short id, short r,short g, short b);

      void    asigna_input(Input* _i_input_jugador);

      float   getVelocidadY(short id);
      IrrlichtDevice* getIrrlichtDevice();


private:
      static Motor* _Motor;
      Entidad * _entidad;
      Motor();
};