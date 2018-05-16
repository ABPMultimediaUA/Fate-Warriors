#ifndef LLAVE_H_
#define LLAVE_H_

#include "../Objeto.h"

#include <tuple>

class iObjeto_Mapa;

class Llave : public Objeto{
public:
	Llave(short _i_id, float _i_x, float _i_y, float _i_z, short _i_id_puerta);
	~Llave();
    
    short get_id_puerta();

	std::tuple<float, float> get_posicion();
	void eliminar_del_minimapa();
	
private:
	short _id_puerta; // Puerta que puede abrir
	iObjeto_Mapa* _objeto_visual_mapa;
};

#endif /* LLAVE_H_ */
