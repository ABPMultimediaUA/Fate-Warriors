#ifndef SRC_OPCION_SONIDO_MENU_H_
#define SRC_OPCION_SONIDO_MENU_H_

#include "Opcion_Volumen.h"

class Opcion_Sonido_Menu : public Opcion_Volumen{
public:
	Opcion_Sonido_Menu(Input* _i_input);
	~Opcion_Sonido_Menu();
	
	void actualiza_valores();

protected:
	void set_volumen(float _i_vol);
	void guarda_volumen();
};

#endif /* SRC_OPCION_SONIDO_MENU_H_ */