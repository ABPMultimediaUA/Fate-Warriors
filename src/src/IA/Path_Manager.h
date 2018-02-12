#ifndef SRC_PATH_MANAGER_H_
#define SRC_PATH_MANAGER_H_
#include <cstdint>

class Path_Manager {
public:
	Path_Manager();
	virtual ~Path_Manager();

	uint16_t get_direccion_movimiento(float& _x_enemigo,float& _y_enemigo);

private:
};

#endif /* SRC_PATH_MANAGER_H_ */
