#ifndef SRC_ARMA_H_
#define SRC_ARMA_H_

#include "../Objeto.h"
#include "../Tiempo/Time.h"
#include "../Personajes/Enum_Tipo_Ataque.h"

class Time;

class Arma : public Objeto{

public:	
	
	Arma(uint16_t _id, float _i_x, float _i_y, float _i_z, Enum_Nombre_Arma _tipo, uint8_t _i_uses, uint8_t _i_frecuencia, uint8_t _i_rango, 
	uint8_t _i_danyo);
	virtual ~Arma();
	virtual Character* usar(Objeto_Motor* _i_objeto_origen, uint16_t _i_direccion) = 0;

	bool 	preparado_siguiente_ataque();
	void 	actualizar_tiempo_siguiente_ataque();
	void  	decrementar_usos();
	
	Enum_Nombre_Arma 	get_nombre();
	uint8_t 	get_uses();
	uint8_t 	get_frecuencia();
	uint8_t 	get_rango();
	uint8_t		get_danyo();
	uint16_t	get_impulso();
	void 		set_ocupada(bool nuevo);
	bool		get_ocupada();


protected:
	
	bool _ocupada_por_character;
	Time*  _reloj;
	double 	_tiempo_siguiente_disponible;
	uint8_t 	_danyo;
	Enum_Nombre_Arma 	_nombre;
	uint8_t 	_uses;
	uint8_t 	_frecuencia;
	uint8_t 	_rango;
	uint16_t 	_impulso;


};

#endif /* SRC_ARMA_H_ */
