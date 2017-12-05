#ifndef GAME_SCRIPTOR_H
#define GAME_SCRIPTOR_H

#include "Scriptor.h"

#define script Game_Scriptor::Instance()

class Game_Scriptor : public Scriptor{
private:
  static Game_Scriptor* instancia;
  Game_Scriptor();
  Game_Scriptor(const Game_Scriptor&);
  Game_Scriptor& operator=(const Game_Scriptor&);

public:
  static Game_Scriptor* Instance();
};

#endif