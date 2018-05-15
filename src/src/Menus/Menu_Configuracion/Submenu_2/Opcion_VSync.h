#ifndef SRC_OPCION_VSYNC_H_
#define SRC_OPCION_VSYNC_H_

#include "../../Opcion.h"

class Interfaz_sonido;

class Opcion_VSync : public Opcion{
public:
	Opcion_VSync(Input* _i_input);
	virtual ~Opcion_VSync();

	Opcion* update_opcion(double _i_tiempo, Opcion* _this);

	void set_vsync();
	void unset_vsync();

private:
	bool _vsync;
};

#endif /* SRC_OPCION_VSYNC_H_ */