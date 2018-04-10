#ifndef SRC_CONO_VISION_H_
#define SRC_CONO_VISION_H_

#include <cstdint>

#include "../Utilidades/Vector.h"

class Character;
class btRigidBody;
class btVector3;

class Cono_Vision {
public:

	Cono_Vision(Character* _asociado);
	~Cono_Vision();

	void update_direccion(uint16_t _direccion);					//ACTUALIZA LA POSICION DEL CONO

	void rotar_en_funcion_de_un_character(Character* _objetivo); //ROTA EN FUNCION DE LA POSICION DEL CHARACTER QUE RECIBE
	void rotar_mirando_a_apuntando();
	
	float get_distancia_con_un_character(Character* _objetivo);	//DEVUELVE LA DISTANCIA A LA QUE SE ENCUENTRA EL PERSONAJE QUE SOLICITA
	float get_distancia_con_apuntado();

	uint16_t get_rotacion_con_objetivo(Character* _objetivo);	// RECIBE COMO PARAMETRO UN CHARACTER Y TE DEVUELVE LA ROTACION DEL JUGADOR CON RESPECTO A ESTE
	uint16_t get_rotacion_con_apuntando();						//DEVUELVE LA ROTACION CON EL CHARACTER FIJADO

	void preparar_ataque_objetivo_mas_proximo_con_impulso();	//REALIZA UN IMPULSO EN EL CASO DE QUE HAYA UN PERSONAJE SELECCIONADO HACE ESE IMPULSO TAMBIEN SOBRE ESTE
	void set_apuntando_a_objetivo_mas_proximo();				//MARCA DESMARCA EL OBJETIVO MAS PROXIMO

	Character* objetivo_mas_proximo_angulo();					//DEVUELVE EL ENEMIGO MAS CERCANO
	Character* get_apuntando();									//DEVULVE EL CHARACTER QUE ESTA FIJADO

private:

/*	------------------------  VARIABLES  ------------------------*/
	Character* _asociado;
	btRigidBody *_visor;				// Cono de vision para el jugador
	Character * _personaje_fijado;		// Jugador fijado
	btVector3* _tamanyocono;			// Dimensiones del cono

/*	------------------------  METODOS  ------------------------*/

	btVector3 get_posicion_para_el_cono();	//Da la posicion del cono con respecto al jugador

};

#endif /* SRC_CONO_VISION_H_ */