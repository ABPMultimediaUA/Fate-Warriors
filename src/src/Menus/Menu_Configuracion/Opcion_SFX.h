#ifndef SRC_OPCION_SFX_H_
#define SRC_OPCION_SFX_H_

#include "Opcion_Volumen.h"

class Opcion_SFX : public Opcion_Volumen{
public:
	Opcion_SFX(Input* _i_input);
	~Opcion_SFX();

protected:
	void set_volumen(float _i_vol);
};

#endif /* SRC_OPCION_SFX_H_ */