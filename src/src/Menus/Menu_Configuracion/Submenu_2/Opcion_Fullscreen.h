#ifndef SRC_OPCION_FULLSCREEN_H_
#define SRC_OPCION_FULLSCREEN_H_

#include "../../Opcion.h"

class Interfaz_sonido;

class Opcion_Fullscreen : public Opcion{
public:
	Opcion_Fullscreen(Input* _i_input);
	virtual ~Opcion_Fullscreen();

	Opcion* update_opcion(double _i_tiempo, Opcion* _this);

	void set_fullscreen();
	void unset_fullscreen();

private:
	bool _fullscreen;
};

#endif /* SRC_OPCION_FULLSCREEN_H_ */