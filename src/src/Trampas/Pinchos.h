#ifndef SRC_Pinchos_H_
#define SRC_Pinchos_H_

#include "Trampas.h"
#include "../Personajes/Character.h"

class Pinchos : public Trampas{
public:
	Pinchos(short _id, float _i_x, float _i_y, float _i_z);
	~Pinchos();

	void render() override;
	bool puede_quitar_vida();
private:
	double siguiente_tiempo_hace_danyo;
};

#endif /* SRC_Pinchos_H_ */
