 
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "BulletWorldImporter/btBulletWorldImporter.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <vector>



#include "irrlicht/irrlicht.h"
#include "../Camara/Camara.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

class CAppReceiver : public IEventReceiver {
private:
	bool KeyDown[KEY_KEY_CODES_COUNT];
public:
	CAppReceiver() {
		for(int i=0;i<KEY_KEY_CODES_COUNT;i++) {
			KeyDown[i] = false;
		}
	}
	virtual bool OnEvent(const SEvent &event) {
		switch(event.EventType) {
		case EET_KEY_INPUT_EVENT:
		{
			KeyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		}
		break;
		default:
			break;
		}
		return false;
	}
	virtual bool isKeyDown(EKEY_CODE keyCode) const {
		return KeyDown[keyCode];
	}
	virtual bool isKeyUp(EKEY_CODE keyCode) const {
		return !KeyDown[keyCode];
	}
};

class DebugDraw : public btIDebugDraw {
private:

   int mode;
   IVideoDriver* const driver;
   ILogger* logger;

public:

   DebugDraw(IrrlichtDevice* const device) :
      mode(DBG_NoDebug), driver(device->getVideoDriver()), logger(device->getLogger())
   {

   }

   void drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
   {
      SColor newColor(255, color[0]*255.0, color[1]*255.0, color[2]*255.0);

      this->driver->draw3DLine(
         vector3df(from[0], from[1], from[2]),
         vector3df(to[0], to[1], to[2]),
         newColor);
   }

   void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
   {
      static const SColor CONTACTPOINT_COLOR(255, 255, 255, 0);

      const btVector3 to(PointOnB + normalOnB*distance);

      this->driver->draw3DLine(
         vector3df(PointOnB[0], PointOnB[1], PointOnB[2]),
         vector3df(to[0], to[1], to[2]),
         CONTACTPOINT_COLOR);
   }

   void reportErrorWarning(const char* text) {
      this->logger->log(text, ELL_ERROR);
   }

   void draw3dText(const btVector3& location, const char* text) { }
   void setDebugMode(int mode) { this->mode = mode; }
   int getDebugMode() const { return this->mode; }
};


class Time;
class Entidad{
public:
    
   Entidad();
   ~Entidad();

    void configuracion_irlitch();
    void configuracion_bullet();
    void preparar_depuracion_mundo();
    short crear_objeto(char* ruta,float x, float y, float z);
    void importarEscenario(char* rutaObj, float x, float y, float z);
    void poner_camara_a_entidad(unsigned short id);    //movimiento del prota
    btCollisionWorld::ClosestRayResultCallback trazaRayo(btVector3 start, btVector3 end);
    void moverDireccion(unsigned short _i_direccion);
    void moverAdelante();
    void moverIzquierda();
    void moverDerecha();
    void moverAtras();
    //void simulationUpdate();
    void saltar();
    void update(double dt);

    void update();
    void render();

    void Mover(uint8_t id, float x, float y, float z);

    IrrlichtDevice* getDevice();    
    
    void updateDynamicBody(btRigidBody *body);
    void moveKinematicBody(btRigidBody *body, btVector3 traslation);
    void moveKinematicObject(btCollisionObject *object, btVector3 traslation);
    bool hasCollision(btDynamicsWorld *world);
    bool hasCollision(btDynamicsWorld *world, btPairCachingGhostObject *ghostObject);
    float getX(short id);
    float getY(short id);
    float getZ(short id);

private:
      float desp_x, desp_z;
      float mult;
      bool moving;
      float angulo;
      float _velocidad;
      
      double mdt;

      u32 then;

      float x;
      float z;
      

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
	IGUIEnvironment* guienv;

};

