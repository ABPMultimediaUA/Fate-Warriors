
#ifndef MOTOR_H_
#define MOTOR_H_

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

class Objeto_Motor;
class Objeto;
class Interpolacion;
class Time;
class Input;
class Objeto;
class Motor{

public:
    
    static Motor* Motor_GetInstance();

   ~Motor();
   
    void apagar();

    void configuracion_irlitch();
    void configuracion_bullet();
    void preparar_depuracion_mundo();
    void importarEscenario(const char* rutaObj, float x, float y, float z);

  
    unsigned short crear_objeto(BoundingBoxes tipo,const char*  ruta,float x, float y, float z, float _i_peso);
    void crear_ObjetoMotor(Objeto* _i_objeto_motor);
    btRigidBody* crearRigidBody(Objeto* _i_objeto, BoundingBoxes tipo,const char*  ruta,float x, float y, float z, float _i_peso, ISceneNode *cubeNode);
    ISceneNode* crearModelado(const char*  ruta,float x, float y, float z);
    Interpolacion* crear_interpolacion(float x, float y, float z);


    void poner_camara_a_entidad(Objeto_Motor* _objeto_motor);    //movimiento del prota
    btCollisionWorld::ClosestRayResultCallback trazaRayo(btVector3 start, btVector3 end);

    //void simulationUpdate();


      //bool    colision_entre_dos_puntos(Vector3 inicio, Vector3 fin);


    void update(double dt);
    void render(float _i_interpolacion);

    void update();
    void render();

    inline void asigna_input(Input* _i_input_jugador) { camara->asigna_input(_i_input_jugador);}
    
    void set_text_vida(int _i_vida);

    IrrlichtDevice* getIrrlichtDevice();    
    
    void updateCamaraColision();

    void interpola_posiciones(float _i_interpolacion);
    void resetear_camara();
    void getDimensiones(ISceneNode* node, float &anchura, float &altura, float &profundidad);

    void borrar_objeto(Objeto_Motor* _objeto_motor);
  
    float angulo_camara();
    float angulo_camaraRAD();
    
private:

      static Motor* _Motor;
      Motor();

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
      
      Time* _tiempo;
      uint8_t _numcubos;

      //Irlitch
      ISceneNode *mapa;
	IrrlichtDevice *device;
      IVideoDriver* driver;
	ISceneManager* smgr;
      GUI* _GUI;

      uint16_t _id_jugador;

      std::vector<Objeto_Motor*> _objetos_motor;
};


#endif /* MOTOR_H_ */
