#ifndef PUERTA_H_
#define PUERTA_H_

#include "../Objeto.h"

#include <tuple>

class Interfaz_sonido;

class Puerta : public Objeto{
public:
	Puerta(short _i_id, float _i_x, float _i_y, float _i_z, float _i_rotacion, bool _i_abierta, uint16_t _i_id_pasillo_que_abre);
	~Puerta();

	void set_abierta();
	bool get_abierta();

	std::tuple<float, float> get_posicion_cerrojo();
	float get_rotacion_cerrojo(); 

private:
	bool _abierta;
	uint8_t _id_pasillo_que_abre;
	Interfaz_sonido* _sonido;
	uint8_t _rotacion;
};

#endif /* PUERTA_H_ */
