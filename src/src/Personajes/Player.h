#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_
#include "Character.h"

class Interfaz;
class Interfaz_Fisica;
class Time;
class Matcher;

class Player : public Character{
public:
	Player(short _id, float _i_x, float _i_y, float _i_z);
	virtual ~Player();
	void update() override;
	void render() override;
	short get_vida();
	
	//ckeyboardman* _KeyMan;
private:
	short _nodoId; //ID del nodo del modelado del motor
	Interfaz* _interface;
	Interfaz_Fisica* _interface_fisica;
	Time * _tiempo;
	double _otro_tiempo;
	double _tiempo_anterior;
	Matcher* _matcher;
};

#endif /* SRC_PLAYER_H_ */
