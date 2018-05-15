#ifndef SRC_OPCION_VOZ_H_
#define SRC_OPCION_VOZ_H_

#include "Opcion_Volumen.h"

class Opcion_Voz : public Opcion_Volumen{
public:
	Opcion_Voz(Input* _i_input);
	~Opcion_Voz();
	
	void actualiza_valores();

protected:
	void set_volumen(float _i_vol);
	void guarda_volumen();
};

#endif /* SRC_OPCION_VOZ_H_ */