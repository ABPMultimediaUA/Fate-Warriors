#ifndef INVENTARIO_H_
#define INVENTARIO_H_

#include "Enum_Tipo_Ataque.h"

#include <vector>
#include <cstdint>

class Objeto;
class Llave;
class Objeto_Motor;
class Character;

class Inventario{
public:
	Inventario();
	~Inventario();

	void render();
	Character* usar(Objeto_Motor* _i_objeto_origen, uint16_t _i_direccion);
	/*SET*/
    
    void anadir_llave(Llave* _i_llave);
	void eliminar_llave(Llave* _i_llave);
	
	/*GET*/
	Objeto* get_seleccionado();
    std::vector<Llave*> get_llaves();

private:
    std::vector<Llave*> _llaves;
};

#endif /* INVENTARIO_H_ */
