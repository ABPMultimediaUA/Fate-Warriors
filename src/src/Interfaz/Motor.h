
#ifndef MOTOR_H_
#define MOTOR_H_

#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <vector>


#include "../Camara/Camara.h"
#include "GUI.h"

#include "EnumTiposBoundingBox.h"
#include <btBulletCollisionCommon.h>
#include "../Utilidades/Vector.h"




#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

class Objeto_Motor;
class Interpolacion;
class Time;
class Input;
class Objeto;
class DebugDraw;    
      
      //Bullet
class btCollisionConfiguration;
class btBroadphaseInterface;
class btDispatcher;
class btConstraintSolver;
class btDynamicsWorld;
class btBulletWorldImporter;
class btPairCachingGhostObject;
class btRigidBody;
class btVector3;
class iNodoModelado;
class iNodo;


class Motor{

public:

    static Motor* Motor_GetInstance();

   ~Motor();
   void vaciar_motor();
   
    void apagar();

    void configuracion_irlitch();
    void configuracion_bullet();
    void preparar_depuracion_mundo();
    void importarEscenario(const char* rutaObj, float x, float y, float z);

  
    unsigned short crear_objeto(BoundingBoxes tipo,const char*  ruta,float x, float y, float z, float _i_peso);
    void crear_ObjetoMotor(Objeto_Motor* _i_objeto_motor);
    btRigidBody* crearRigidBody(Objeto* _i_objeto, BoundingBoxes tipo,const char*  ruta,float x, float y, float z, float _i_peso, iNodoModelado *cubeNode);
    ISceneNode* crearModelado(const char* ruta,float x, float y, float z);
    iNodoModelado* crearModelado(float x, float y, float z, const char* ruta);
    Interpolacion* crear_interpolacion(float x, float y, float z);
    btRigidBody* crear_rb_ataque();
    void setCollisionMask(int mask, btRigidBody *_i_rigidbody);
    void setCollisionGroup(int group, btRigidBody *_i_rigidbody );
    void poner_camara_a_entidad(Objeto_Motor* _objeto_motor);    //movimiento del prota
    btCollisionWorld::ClosestRayResultCallback trazaRayo(btVector3 start, btVector3 end, int mascara_colision); //devuelve solo la primera colision del rayo
    btCollisionWorld::AllHitsRayResultCallback trazaRayoAll(btVector3 start, btVector3 end, int mascara_colision); //devuelve todas las colisiones del rayo
    bool x_ve_a_y(Vector3 x, Vector3 y, int mascara_colision); //traza un rayo entre dos posiciones X e Y y comprueba si pueden verse 
                                         //teniendo en cuenta unicamente el escenario (no el resto de objetos)

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
    void getDimensiones(iNodoModelado* node, float &anchura, float &altura, float &profundidad);

    void borrar_objeto(Objeto_Motor* _objeto_motor);
    void borrar_rb(btRigidBody* rb); // Mejorar
    IVideoDriver* getDriver();
    float angulo_camara();
    float angulo_camaraRAD();
    
      bool comprobar_colision(btRigidBody *rb1, btRigidBody *rb2);
      void posicionar_rotar_y_escalar_rb(btRigidBody *rb, btVector3 posicion, btVector3 escala, uint16_t rotacion);
      //bool comprobar_colision_ataque(btRigidBody *character_atacado);

    

private:

      std::vector<iNodo*> lista_i_nodo;


      static Motor* _Motor;
      Motor();
      Vector3* rayOrigen;
      Vector3* rayDestino;
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
