#ifndef INTERFAZ_ME_H
#define INTERFAZ_ME_H


#include <cstdint>
#include <cstdlib>
#include "iNodoModelado.h"
#include "iNodoCamara.h"
#include "../../Camara/Camara.h"
#include "iNodoLuz.h"
#include <vector>
#include "EnumTiposBoundingBox.h"
#include <btBulletCollisionCommon.h>
#include "../../Utilidades/Vector.h"


class TMooseEngine;

    //primer motor
class Objeto_ME;
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

class Interfaz_ME{

    public:    
        ~Interfaz_ME();
        static Interfaz_ME* get_instancia(uint16_t width, uint16_t height);

        iNodoModelado* crearModelado(const char* ruta);
        iNodoModelado* crearModelado(const char* ruta, float x, float y, float z);
        iNodoCamara* crearCamara(bool activa); 
        iNodoCamara* crearCamara(bool activa, float x, float y, float z);
        iNodoLuz* crearLuz(bool activa, float intensidad);
        iNodoLuz* crearLuz(bool activa, float intensidad, float x, float y, float z);

        iNodoModelado* importarEscenario(const char* rutaObj, float x, float y, float z);

        // METODOS DE LA VIEJA INTERFAZ //
        Interpolacion* crear_interpolacion(float x, float y, float z);
        btRigidBody* crearRigidBody(Objeto* _i_objeto, BoundingBoxes tipo,const char*  ruta,float x, float y, float z, float _i_peso, iNodoModelado* _i_nodo);
        void getDimensiones(iNodoModelado* _i_nodo, float &anchura, float &altura, float &profundidad);
        void crear_ObjetoMotor(Objeto_ME* _i_objeto_me);
        
        btCollisionWorld::ClosestRayResultCallback trazaRayo(btVector3 start, btVector3 end, int mascara_colision); //devuelve solo la primera colision del rayo
        btCollisionWorld::AllHitsRayResultCallback trazaRayoAll(btVector3 start, btVector3 end, int mascara_colision); //devuelve todas las colisiones del rayo



        void render();
        bool ventana_abierta();
        TMooseEngine* getEngine();

        

    private:
        static Interfaz_ME* _instancia;
        TMooseEngine* motor;
        Interfaz_ME(uint16_t width, uint16_t height);
        void configuracion_ME(uint16_t width, uint16_t height, bool fullscreen, bool v_sync);
        void configuracion_bullet();
        std::vector<iNodo*> lista_i_nodo;

        //COSAS DE LA VIEJA INTERFAZ//
        std::vector<Objeto_ME*> _objetos_me;

        //Bullet
    	btCollisionConfiguration *collisionConfiguration;
    	btBroadphaseInterface *broadPhase;
    	btDispatcher *collisionDispatcher;
    	btConstraintSolver *constraintSolver;
    	btDynamicsWorld *world;
    	btBulletWorldImporter* fileLoader;
        Time* _tiempo;
        uint8_t _numcubos;

        Vector3* rayOrigen;
        Vector3* rayDestino;
};

#endif