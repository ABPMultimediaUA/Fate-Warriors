#ifndef SRC_Minas_H_
#define SRC_Minas_H_

#include "Trampas.h"
#include "../Personajes/Character.h"

class Time;
class Minas : public Trampas{
public:
	Minas(short _id, float _i_x, float _i_y, float _i_z);
	~Minas();

	void	activar();
	void 	activar_explosion();
	bool 	explota();	

private:
	double _explota_en;
};

#endif /* SRC_Minas_H_ */
