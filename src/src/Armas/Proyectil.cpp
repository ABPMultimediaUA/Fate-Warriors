#include "Proyectil.h"
#include <iostream>

Proyectil::Proyectil(short _id, float _i_x, float _i_y, float _i_z, short _i_danyo, short _i_id_shooter) 
: Objeto_Movil(_id, _i_x, _i_y, _i_z), _impacted(false), _danyo(_i_danyo), _origenx(_i_x), _origeny(_i_y), _origenz(_i_z), _id_shooter(_i_id_shooter) {}

Proyectil::~Proyectil(){}


void Proyectil::set_direction(float _i_x, float _i_y, float _i_z){
	_directionx= _i_x;
	_directiony= _i_y;
	_directionz= _i_z;
}

void Proyectil::set_has_impacted(){
	_impacted=true;	
}

bool Proyectil::get_has_impacted(){
	return _impacted;
}

short Proyectil::get_danyo(){
	return _danyo;
}

/*  Depende de como sea la estructura del juego

Character* Proyectil::GetClosestIntersectingBot(Vector2D From, Vector2D To)const{
  Character* ClosestIntersectingBot = 0;
  double ClosestSoFar = MaxDouble;

  //iterate through all entities checking against the line segment FromTo
  std::list<Character*>::const_iterator characters;
  for (characters =  _pWorld->DameTodosPersonajes().begin();
       characters != _pWorld->DameTodosPersonajes().end();
       ++characters)
  {
    //make sure we don't check against the shooter of the projectile
    if ( ((*characters)->get_id() != _iShooterID))
    {
      //if the distance to FromTo is less than the entity's bounding radius then
      //there is an intersection
      if (DistToLineSegment(From, To, (*characters)->Pos()) < (*characters)->BRadius())
      {
        //test to see if this is the closest so far
        double Dist = Vec2DDistanceSq((*characters)->Pos(), _vOrigin);

        if (Dist < ClosestSoFar)
        {
          Dist = ClosestSoFar;
          ClosestIntersectingBot = *characters;
        }
      }
    }

  }
  return ClosestIntersectingBot;
}


std::list<Character*> Proyectil::GetListOfIntersectingBots(Vector2D From, Vector2D To)const{
  //this will hold any bots that are intersecting with the line segment
  std::list<Character*> hits;

  //iterate through all entities checking against the line segment FromTo
  std::list<Character*>::const_iterator characters;
  for (characters =  _pWorld->DameTodosPersonajes().begin();
       characters != _pWorld->DameTodosPersonajes().end();
       ++characters)
  {
    //make sure we don't check against the shooter of the projectile
    if ( ((*characters)->get_id() != _iShooterID))
    {
      //if the distance to FromTo is less than the entities bounding radius then
      //there is an intersection so add it to hits
      if (DistToLineSegment(From, To, (*characters)->Pos()) < (*characters)->BRadius())
      {
        hits.push_back(*characters);
      }
    }

  }

  return hits;
}
*/