#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_
#include "Character.h"
#include "../Input.h"


class Interfaz;
class Interfaz_Fisica;
class Input;
class Motor;
class Interfaz_sonido;


class Player : public Character{
public:
	Player(short _id, float _i_x, float _i_y, float _i_z, Input* _i_input,bool es_jugador_online);
	virtual ~Player();
	void update() override;
	void update_online();
	void render() override;
	void comprobar_input(Enum_Inputs key_press);

	void modificar_vida_en(short _i_vida)	override;
	void danyar(short _danyo) 				override;
	void set_vida(short _i_vida) 			override;
	bool puede_subir_especial();
	void aumentar_especial();
	void disminuir_especial();
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

#endif /* SRC_PLAYER_H_ */
