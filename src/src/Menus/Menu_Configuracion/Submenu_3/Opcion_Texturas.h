#ifndef SRC_OPCION_TEXTURAS_H_
#define SRC_OPCION_TEXTURAS_H_

#include "../../Opcion.h"

class Interfaz_sonido;

class Opcion_Texturas : public Opcion{
public:
	Opcion_Texturas(Input* _i_input);
	virtual ~Opcion_Texturas();

	Opcion* update_opcion(double _i_tiempo, Opcion* _this);

	void set_texturas();

	inline uint8_t get_texturas() { return _texturas;}

	void actualiza_valores();

private:
	uint8_t _texturas;								// De 0 a 2
};

#endif /* SRC_OPCION_TEXTURAS_H_ */