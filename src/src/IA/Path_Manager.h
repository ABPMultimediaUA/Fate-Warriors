#ifndef SRC_PATH_MANAGER_H_
#define SRC_PATH_MANAGER_H_
#include <cstdint>

class Objeto;

class Path_Manager {
public:
	Path_Manager();
	virtual ~Path_Manager();

	uint16_t get_direccion_movimiento(float& _x_enemigo,float& _y_enemigo, float pos_x, float pos_y);

private:
};

#endif /* SRC_PATH_MANAGER_H_ */
