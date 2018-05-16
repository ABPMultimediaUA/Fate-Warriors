#ifndef INTERRUPTOR_H_
#define INTERRUPTOR_H_

#include "../Objeto.h"

#include <vector>
#include "../Moose_Engine/src/Enum_Texturas.h"

class Puerta_Pincho;
class Time;
class Interfaz_sonido;
class iObjeto_Mapa;


class Interruptor : public Objeto{
public:
	Interruptor(short _i_id, float _i_x, float _i_z, float _i_rotacion, short _rotacion_x, short _rotacion_y, short _distancia);
	virtual ~Interruptor();

	virtual void iniciar_interruptor();			// Inicia el cambio de objetivo de camara del interruptor
	virtual void accionar() = 0;				// Acciona el interruptor y le cambia el estado (si es posible)
	virtual void accionar_sin_propagar();		// Acciona el interruptor sin propagar

	void agregar_puerta(Puerta_Pincho* _puerta);					// Agrega una puerta a sus asociadas
	virtual void agregar_interruptor(Interruptor* _interruptor);	// Solo para la propagadora

	virtual void update();

	Puerta_Pincho* get_puerta_asociada();

	void cambia_palito();		// Inclina el palito para el otro lado

	short get_rotacion_x();
	short get_rotacion_y();
	short get_distancia();

	void eliminar_del_minimapa();


protected:
	Time* _reloj;
	std::vector<Puerta_Pincho*> _puertas_asociadas;		// Vector con todas las puertas asociadas
	bool _estado;										// Estado del interruptor (false = no activado / true = activado)
    short _rotacion_x;
    short _rotacion_y;
    short _distancia;
    Interfaz_sonido* _sonido;
	iObjeto_Mapa* _objeto_visual_mapa;

private:

	Objeto_Motor* _palito;								// Modelado del Palo del interruptor (hay que animarlo)
	int16_t _inclinacion_palito;						// Inclinacion del palito
};

#endif /* INTERRUPTOR_H_ */



/*

// BASE
Interruptor(short _i_id, float _i_x, float _i_z, float _i_rotacion);
private: 
	bool _estado;
	Puerta_Pincho** _puertas;

*/