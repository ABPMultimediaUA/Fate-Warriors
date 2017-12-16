#ifndef SRC_Charcos_electrificados_H_
#define SRC_Charcos_electrificados_H_

#include "Trampas.h"
#include "../Personajes/Character.h"

class Time;
class Charcos_electrificados : public Trampas{
public:
	Charcos_electrificados(short _id, float _i_x, float _i_y, float _i_z);
	virtual ~Charcos_electrificados();
	bool puede_quitar_vida();

	void render() override;

private:
	double siguiente_tiempo_hace_danyo;
};

#endif /* SRC_Charcos_electrificados_H_ */
