#ifndef SRC_PATH_MANAGER_H_
#define SRC_PATH_MANAGER_H_

class Interfaz_Datos;

class Path_Manager {
public:
	Path_Manager(Interfaz_Datos& _i_interfaz_decision);
	virtual ~Path_Manager();

	unsigned short get_direccion_movimiento(unsigned short _i_n_enemigo);

private:
	Interfaz_Datos *_interfaz_decision;
};

#endif /* SRC_PATH_MANAGER_H_ */
