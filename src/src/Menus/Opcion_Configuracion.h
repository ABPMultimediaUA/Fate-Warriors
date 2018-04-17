#ifndef SRC_OPCION_CONFIGURACION_H_
#define SRC_OPCION_CONFIGURACION_H_

#include "Opcion.h"

class Menu_Configuracion;

class Opcion_Configuracion : public Opcion{
public:
	Opcion_Configuracion(Input* _i_input);
	~Opcion_Configuracion();

	Opcion* comprueba_cambio_opcion(Opcion* _this) override;
	Opcion* update_opcion(double _i_tiempo, Opcion* _this);

	bool get_dentro();

private:
	bool _dentro_menu;	// Indica si está dentro del menu de configuración

	Menu_Configuracion* _configuracion;
};

#endif /* SRC_OPCION_CONFIGURACION_H_ */