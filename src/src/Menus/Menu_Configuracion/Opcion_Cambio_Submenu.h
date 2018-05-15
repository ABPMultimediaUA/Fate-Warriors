#ifndef SRC_OPCION_CAMBIO_SUBMENU_H_
#define SRC_OPCION_CAMBIO_SUBMENU_H_

#include "../Opcion.h"

class Opcion_Cambio_Submenu : public Opcion{
public:
	Opcion_Cambio_Submenu(Input* _i_input);
	virtual ~Opcion_Cambio_Submenu();

	Opcion* update_opcion(double _i_tiempo, Opcion* _this);

	void agrega_submenus(Opcion* _i_opcion_izq, Opcion* _i_opcion_der) override;

protected:
	Opcion* _submenu_izq;
	Opcion* _submenu_der;
};

#endif /* SRC_OPCION_CAMBIO_SUBMENU_H_ */