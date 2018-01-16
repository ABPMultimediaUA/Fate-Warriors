
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
class Interpolacion;
class Time;
class Input;
class Motor{

public:
    
    static Motor* Motor_GetInstance();

   ~Motor();
   
    void apagar();

    void configuracion_irlitch();
    void configuracion_bullet();
    void preparar_depuracion_mundo();
    void importarEscenario(char* rutaObj, float x, float y, float z);

  
    unsigned short crear_objeto(BoundingBoxes tipo,char* ruta,float x, float y, float z, float _i_peso);
    void crear_ObjetoMotor(Objeto_Motor* _i_objeto_motor);
    btRigidBody* crearRigidBody(BoundingBoxes tipo,char* ruta,float x, float y, float z, float _i_peso, ISceneNode *cubeNode);
    ISceneNode* crearModelado(char* ruta,float x, float y, float z);
    Interpolacion* crear_interpolacion(float x, float y, float z);

    void poner_camara_a_entidad(unsigned short id);    //movimiento del prota
    btCollisionWorld::ClosestRayResultCallback trazaRayo(btVector3 start, btVector3 end);

    //void simulationUpdate();

    void update(double dt);
    void render(float _i_interpolacion);

    void update();
    void render();

    inline void asigna_input(Input* _i_input_jugador) { camara->asigna_input(_i_input_jugador);}
    
    void set_text_vida(int _i_vida);
    void haz_desaparecer(unsigned short _id);

    IrrlichtDevice* getIrrlichtDevice();    
    
    void updateCamaraColision();
    void updateDynamicBody(btRigidBody *body);
    void interpola_posiciones(float _i_interpolacion);
    void setVelocidad(uint8_t id, float x, float y, float z);
    void resetear_camara();
    void getDimensiones(ISceneNode* node, float &anchura, float &altura, float &profundidad);
    unsigned short getId();
    void borrar_objeto(ISceneNode* _nodo, Interpolacion* _interpolacion, btRigidBody* _rigidbody);
  
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

      std::vector<Objeto_Motor*> _objetos_motor;


};


#endif /* MOTOR_H_ */
