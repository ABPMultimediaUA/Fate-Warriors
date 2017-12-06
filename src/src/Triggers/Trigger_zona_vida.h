#ifndef HEALTH_GIVER_H
#define HEALTH_GIVER_H

#include "TriggerRegion_space.h"
#include <iosfwd>
#include "../Personajes/Player.h"


class Trigger_zona_vida : public TriggerRegion_space{

private:

  //the amount of health an entity receives when it runs over this trigger
  short   _iHealthGiven;
  
public:

  Trigger_zona_vida(Vector2 _i_posicion);

  //Si lo tiene se le va a rellenar la vida
  void Trys(Character* personaje);

  //dibuja la zona
  void Render();


};



#endif