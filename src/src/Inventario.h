#ifndef INVENTARIO_H_
#define INVENTARIO_H_

#include <vector>
#include "Personajes/Enum_Tipo_Ataque.h"

class Arma_distancia;
class Objeto;
class Arma_cerca;
class Arma;
class Llave;
class Objeto_Motor;
class Character;

class Inventario{
public:
	Inventario();
	virtual ~Inventario();

	void render();
	Character* usar(Objeto_Motor* _i_objeto_origen, uint16_t _i_direccion);
	bool borrar_si_se_puede(Arma * seleccionado_in);
	
	/*SET*/
	void cambiar_objeto_cerca(Arma_cerca *_i_cerca);
	void cambiar_objeto_distancia (Arma_distancia *_i_distancia);
	void cambiar_seleccionado();

	void cambiar_arma_seleccionada_a_la_siguiente();
	void cambiar_arma_seleccionada_a_la_anterior();
	enum Tipo_Arma seleccionar_arma_distancia();
	enum Tipo_Arma seleccionar_arma_cerca();
	enum Tipo_Arma seleccionar_cuerpo_a_cuerpo();
	enum Tipo_Arma get_tipo_arma();
    
    void anadir_llave(Llave* _i_llave);
	void eliminar_llave(Llave* _i_llave);
	
	/*GET*/
	Objeto* get_seleccionado();
	Arma_distancia* get_objeto_distancia();
	Arma_cerca* get_objeto_cerca();
    std::vector<Llave*> get_llaves();
	Enum_Nombre_Arma get_nombre_arma();



private:
	Tipo_Arma _arma;
	Arma_distancia *_objeto_distancia;
	Arma_cerca *_objeto_cerca;
	Arma *_seleccionado;
    std::vector<Llave*> _llaves;
};

#endif /* INVENTARIO_H_ */
