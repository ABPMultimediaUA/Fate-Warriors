
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

//#include "../Moose_Engine/src/iNodoModelado.h"
#include "../Moose_Engine/src/Interfaz_Particulas.h"


class Objeto_Motor;
class Interpolacion;
class Time;
class Input;
class Objeto;
class DebugDraw;
class iNodo;  
class iNodoModelado;
class iNodoModeladoEscenario;  
class iNodoCamara;
class iNodoLuz;
class iNodoAnimacion;
class UI;
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
class TMooseEngine;


class Motor{

public:

    static Motor* Motor_GetInstance();
    void CargaMapa();
    void configuracion_ME(uint16_t width, uint16_t height, bool fullscreen, bool v_sync);
   ~Motor();
   void vaciar_motor();
   
    void apagar();

    void configuracion_irlitch();
    void configuracion_bullet();
    void preparar_depuracion_mundo();
    iNodoModelado* importarEscenario(const char* rutaObj, float x, float y, float z);

  
    unsigned short crear_objeto(BoundingBoxes tipo,const char*  ruta,float x, float y, float z, float _i_peso);
    void crear_ObjetoMotor(Objeto_Motor* _i_objeto_motor);
    btRigidBody* crearRigidBody(Objeto* _i_objeto, BoundingBoxes tipo,const char*  ruta,float x, float y, float z, float _i_peso, iNodoModelado *cubeNode);
    
    iNodoModelado* crearModelado(const char* ruta,float x, float y, float z);
    iNodoModelado* crearModeladoSinLista(const char* ruta,float x, float y, float z);
    iNodoModelado* crearModelado(const char* ruta);

    iNodoModeladoEscenario* crearModeladoEscenario(const char* ruta,float x, float y, float z);
    iNodoModeladoEscenario* crearModeladoEscenario(const char* ruta);
    
    iNodoAnimacion* crearAnimacion(bool bucle, const char* ruta,float x, float y, float z);
    iNodoAnimacion* crearAnimacion(bool bucle, const char* ruta);
    
    Interpolacion* crear_interpolacion(float x, float y, float z);
    Interpolacion* crear_interpolacion_palanca(float x, float y, float z, int16_t _rotacion);

    btRigidBody* crear_rb_ataque();
    btRigidBody* crear_rb_vision();
    void setCollisionMask(int mask, btRigidBody *_i_rigidbody);
    void setCollisionGroup(int group, btRigidBody *_i_rigidbody );
    void poner_camara_a_entidad(Objeto_Motor* _objeto_motor);    //movimiento del prota
    btCollisionWorld::ClosestRayResultCallback trazaRayo(btVector3 start, btVector3 end, int mascara_colision); //devuelve solo la primera colision del rayo
    btCollisionWorld::AllHitsRayResultCallback trazaRayoAll(btVector3 start, btVector3 end, int mascara_colision); //devuelve todas las colisiones del rayo
    bool x_ve_a_y(Vector3 x, Vector3 y, int mascara_colision); //traza un rayo entre dos posiciones X e Y y comprueba si pueden verse 
                                         //teniendo en cuenta unicamente el escenario (no el resto de objetos)

    iNodoLuz* crearLuz(bool activa, float intensidad, 
                                    Vector3 ambient,
                                    Vector3 specular,
                                    Vector3 diffuse);

    iNodoLuz* crearLuz(bool activa, float intensidad, 
                                    Vector3 ambient,
                                    Vector3 specular,
                                    Vector3 diffuse,  
                                    float x, float y, float z);

    bool ventana_abierta();
    inline TMooseEngine* getEngine(){ return _me;}
    //void simulationUpdate();
      //bool    colision_entre_dos_puntos(Vector3 inicio, Vector3 fin);


    void update(double dt);
    void render(float _i_interpolacion);

    void update();
    void render();


    void cambia_animaciones();
  
    inline void asigna_input(Input* _i_input_jugador) { camara->asigna_input(_i_input_jugador);}
    
    void set_text_vida(int _i_vida);
  
    void updateCamaraColision();

    void interpola_posiciones(float _i_interpolacion);
    void resetear_camara();
    void getDimensiones(iNodoModelado* node, float &anchura, float &altura, float &profundidad);

    void borrar_objeto(Objeto_Motor* _objeto_motor);
    void borrar_rb(btRigidBody* rb); // Mejorar
    float angulo_camara();
    float angulo_camaraRAD();
    
    bool comprobar_colision(btRigidBody *rb1, btRigidBody *rb2);
    void posicionar_rotar_y_escalar_rb(btRigidBody *rb, btVector3 posicion, btVector3 escala, uint16_t rotacion);
    void posicionar_rotar_y_escalar_rb_visor(btRigidBody *rb, btVector3 posicion, btVector3 escala, uint16_t rotacion);
    //bool comprobar_colision_ataque(btRigidBody *character_atacado);
    void gira_camara(short _rotacion_x, short _rotacion_en_y);

    void interpolar_altura(bool estado);
    void render_Menu();
    void render_Pausa();
    void render_Menu_Config();
    void recibir_Danyo(float vida, float vida_maxima);
     Interfaz_Particulas* _interfaz;
    void set_escala_music(uint8_t escala);
    void set_escala_sfx(uint8_t escala);
    void set_escala_voz(uint8_t escala);
    void set_escala_menu(uint8_t escala);

    void set_eje_x(bool ejeX);
    void set_eje_y(bool ejeY);

    void render_Menu_Win();
    void render_Menu_Lose();

    void pantalla_carga();
    void render_partida_cargada();

    void set_llave_hud(bool _i_tiene_llave);

    void resize_window(int _i_width, int _i_height);
    
private:

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

      
      
      //ME
      TMooseEngine* _me;
      iNodoModelado* mapa;
      uint16_t _id_jugador;
      std::vector<Objeto_Motor*> _objetos_motor;
      std::vector<iNodo*> lista_i_nodo;

      Objeto_Motor* _objeto_que_sigue_la_camara;
};


#endif /* MOTOR_H_ */
