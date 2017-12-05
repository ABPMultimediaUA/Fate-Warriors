#ifndef SRC_Enemy_H_
#define SRC_Enemy_H_
#include "Character.h"

class Time;
class Interfaz;

class Enemy : public Character{
public:
	Enemy(short _id, float _i_x, float _i_y, float _i_z);
	virtual ~Enemy();
	void update() override;
	void render() override;
	short get_vida();
	
	//ckeyboardman* _KeyMan;
private:
	short _nodoId; //ID del nodo del modelado del motor
	Interfaz* _interface;
	Time * _tiempo;
	unsigned short _variable_modelo;
};

#endif /* SRC_Enemy_H_ */
