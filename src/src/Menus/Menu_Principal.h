#ifndef SRC_MENU_PRINCIPAL_H_
#define SRC_MENU_PRINCIPAL_H_

class Opcion;

#include <cstdint>

const uint8_t _n_opciones = 3;

class Menu_Principal {
public:
	Menu_Principal();
	~Menu_Principal();

	void update(double _i_tiempo);

private: 
	Opcion** _opciones;
	Opcion* _opcion_actual;
};

#endif /* SRC_MENU_PRINCIPAL_H_ */