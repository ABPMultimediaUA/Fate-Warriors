
#include "DebugDraw.h"
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../Camara/Camara.h"
#include "GUI.h"

#include "EnumTiposBoundingBox.h"



#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


class Interpolacion;
class Time;
class Input;
class Entidad{
public:
    
   Entidad();
   ~Entidad();
   
    void apagar();

    void configuracion_irlitch();
    void configuracion_bullet();
    void preparar_depuracion_mundo();
    short crear_objeto(BoundingBoxes tipo, char* ruta, float x, float y, float z);
    void importarEscenario(char* rutaObj, float x, float y, float z);
    void poner_camara_a_entidad(unsigned short id);    //movimiento del prota
    btCollisionWorld::ClosestRayResultCallback trazaRayo(btVector3 start, btVector3 end);
    void VelocidadDireccion(unsigned short id, unsigned short _i_direccion, unsigned short _i_velocidad);

    //void simulationUpdate();
    void saltar(unsigned short _i_id);
    void update(double dt);

    void update();
    void render();

    inline void asigna_input(Input* _i_input_jugador) { camara->asigna_input(_i_input_jugador);}

    void setVelocidad(uint8_t id, float x, float y, float z);
    void setVelocidad(uint8_t id, unsigned short _i_direccion, float x, float y, float z);
    void set_text_vida(int _i_vida);

    IrrlichtDevice* getDevice();    
    
    void updateCamaraColision();
    void updateDynamicBody(btRigidBody *body);
    void interpola_posiciones(float _i_interpolacion);
    void setPositionXZ(unsigned short id, float x, float z);
    float getX(short id);
    float getY(short id);
    float getZ(short id);
    float getVelocidadY(short _i_id);
    void Dash(unsigned short _i_direccion, unsigned short id);
    void    colorear_nodo(unsigned short id, short r,short g, short b);
    void resetear_camara();
    ISceneNode* crearModelado(char* ruta,float x, float y, float z);
    void getDimensiones(ISceneNode* node, float &anchura, float &altura);

private:
      int _vida; //salud para la barra de salud
      int _maxvida; //vida maxima (barra negra)
      float desp_x, desp_z;
      float mult;
      bool moving;
      float angulo;
      float _velocidad;
      
      double mdt;

      u32 then;

      float x;
      float z;
      
      bool _debug;

      //Camara
      Camara* camara;

      //Draw
      DebugDraw* debugDraw;    
      
      //Bullet
    	btCollisionConfiguration *collisionConfiguration;
    	btBroadphaseInterface *broadPhase;
    	btDispatcher *collisionDispatcher;
    	btConstraintSolver *constraintSolver;
    	btDynamicsWorld *world;
    	btBulletWorldImporter* fileLoader;
      std::vector<btRigidBody*> rigidbody;
      
      Time* _tiempo;
      uint8_t _numcubos;

      //Irlitch
	 IrrlichtDevice *device;
      IVideoDriver* driver;
	ISceneManager* smgr;
      std::vector<ISceneNode*> nodes;
      GUI* _GUI;

      std::vector<Interpolacion*> _interpolaciones;
      uint16_t _id_jugador;
};

