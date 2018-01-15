#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_
#include "Character.h"

class Interfaz;
class Interfaz_Fisica;
class Input;
class Motor;


class Player : public Character{
public:
	Player(short _id, float _i_x, float _i_y, float _i_z, Input* _i_input);
	virtual ~Player();
	void update() override;
	void render() override;

	void modificar_vida_en(short _i_vida)	override;
	void danyar(short _danyo) 				override;
	void set_vida(short _i_vida) 			override;
	bool puede_subir_especial();
	void aumentar_especial();
	void disminuir_especial();
	//ckeyboardman* _KeyMan;
private:
	Objeto_Motor* _objeto;
	short _nodoId; //ID del nodo del modelado del motor
	uint8_t _especial;
	Interfaz* _interface;
	Interfaz_Fisica* _interface_fisica;
	//Time * _tiempo;
	double _otro_tiempo;
	double _tiempo_anterior;
	Input* _input;
};

#endif /* SRC_PLAYER_H_ */
