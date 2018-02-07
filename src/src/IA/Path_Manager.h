#ifndef SRC_PATH_MANAGER_H_
#define SRC_PATH_MANAGER_H_
#include <cstdint>
class Interfaz_Datos;

class Path_Manager {
public:
	Path_Manager(Interfaz_Datos& _i_interfaz_decision);
	virtual ~Path_Manager();

	uint16_t get_direccion_movimiento(float& _x_enemigo,float& _y_enemigo);

private:
	Interfaz_Datos *_interfaz_decision;
};

#endif /* SRC_PATH_MANAGER_H_ */
