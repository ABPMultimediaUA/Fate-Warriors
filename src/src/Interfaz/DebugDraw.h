/*#include "Interfaz_Fisica.h"
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include "../Utilidades/Vector.h"
#include "Interfaz.h"

class btTransform;
class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btCollisionShape;
class btCollisionShape;
class btDefaultMotionState;
class btRigidBody;	
class btDefaultMotionState;								
class btRigidBody;
class Interfaz; 
struct Vector3;

class Interfaz; 
struct Vector3;

class DebugDraw : public btIDebugDraw {
private:
   int mode;
   IVideoDriver* const driver;
   ILogger* logger;
public:
   DebugDraw(IrrlichtDevice* const device);
   void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
   void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, 
                         btScalar distance, int lifeTime, const btVector3& color);
   void reportErrorWarning(const char* text);
   void draw3dText(const btVector3& location, const char* text);
   void setDebugMode(int mode);
   int getDebugMode();
};
*/