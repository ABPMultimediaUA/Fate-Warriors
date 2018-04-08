#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_
#include "Character.h"

class Interfaz;
class Interfaz_Fisica;
class Input;
class Motor;
class Interfaz_sonido;


class Player : public Character{
public:
	Player(short _id, float _i_x, float _i_y, float _i_z, Input* _i_input);
	virtual ~Player();
	void update();

	void modificar_vida_en(short _i_vida)	override;
	void danyar(short _danyo) 				override;
	void set_vida(short _i_vida) 			override;
	bool puede_subir_especial();
	void aumentar_especial();
	void disminuir_especial();
	void gestion_dash()					override;
	void preparar_ataque_objetivo_mas_proximo_con_impulso();

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
	btRigidBody *_rb_apuntado;
	Character * _apuntando;
	// double _tiempobloqueo; BORRAME


	Character* objetivo_mas_proximo_angulo();

	void rotar_en_funcion_de_un_punto(Character* _objetivo);

	//uint16_t rotar_en_funcion_de_un_punto_direccion(Character* _objetivo);
	void set_apuntando_a_objetivo_mas_proximo();
	void rotar_en_funcion_de_ese_objetivo();

};

#endif /* SRC_PLAYER_H_ */
