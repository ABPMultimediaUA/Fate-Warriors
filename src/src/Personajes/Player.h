#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_
#include "Character.h"

class Interfaz;
class Interfaz_Fisica;
class Input;
class Motor;
class Interfaz_sonido;
class Cono_Vision;

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

	void morir() override;

	void play_voces_ataque() override;
	void play_animaciones_ataque() override;
	void play_animaciones_recibir_danyo() override;

	void carga_animaciones();

private:
	short _nodoId; //ID del nodo del modelado del motor
	bool _hace_cinta;
	Motor* _motor;
	Interfaz_sonido* _sonido;
	uint8_t _especial;
	Interfaz* _interface;
	Interfaz_Fisica* _interface_fisica;
	//Time * _tiempo;
	Input* _input;
	// double _tiempobloqueo; BORRAME
	Cono_Vision* _cono_vision;
};

#endif /* SRC_PLAYER_H_ */
