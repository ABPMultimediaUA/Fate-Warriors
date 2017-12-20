/*
#include "DebugDraw.h"

   DebugDraw(IrrlichtDevice* const device) :
      mode(DBG_NoDebug), driver(device->getVideoDriver()), logger(device->getLogger()) { }
   void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
      SColor newColor(255, color[0]*255.0, color[1]*255.0, color[2]*255.0);
      this->driver->draw3DLine(vector3df(from[0], from[1], from[2]),
                               vector3df(to[0], to[1], to[2]), newColor);
   }
   void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, 
                         btScalar distance, int lifeTime, const btVector3& color) {
      static const SColor CONTACTPOINT_COLOR(255, 255, 255, 0);
      const btVector3 to(PointOnB + normalOnB*distance);
      this->driver->draw3DLine(vector3df(PointOnB[0], PointOnB[1], PointOnB[2]),
         vector3df(to[0], to[1], to[2]), CONTACTPOINT_COLOR);
   }
   void reportErrorWarning(const char* text) {
      this->logger->log(text, ELL_ERROR);
   }
   void draw3dText(const btVector3& location, const char* text) { }
   void setDebugMode(int mode) { this->mode = mode; }
   int getDebugMode() const { return this->mode; }
};
*/