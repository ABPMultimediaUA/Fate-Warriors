#ifndef SRC_Player_Online_H_
#define SRC_Player_Online_H_
#include "Player.h"
#include "../Input.h"


class Interfaz;
class Interfaz_Fisica;
class Input;
class Motor;
class Interfaz_sonido;


class Player_Online : public Player{
public:
	Player_Online(short _id, float _i_x, float _i_y, float _i_z, Input* _i_input,bool es_jugador_online);
	virtual ~Player_Online();
	void update() override;
	void render() override;
	void comprobar_input(Enum_Inputs key_press);

	void modificar_vida_en(short _i_vida)	override;
	void danyar(short _danyo) 				override;
	void set_vida(short _i_vida) 			override;

	bool _puede_actualizar;
	//ckeyboardman* _KeyMan;
private:
	short _nodoId; //ID del nodo del modelado del motor
	Motor* _motor;
	Interfaz_sonido* _sonido;
	uint8_t _especial;
	Interfaz* _interface;
	Interfaz_Fisica* _interface_fisica;
	//Time * _tiempo;
	Input* _input;
	bool es_jugador_online;
};

#endif /* SRC_Player_Online_H_ */
