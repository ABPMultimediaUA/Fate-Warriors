#ifndef INVENTARIO_H_
#define INVENTARIO_H_

#include <vector>

class Arma_distancia;
class Objeto;
class Arma_cerca;
class Arma;
class Llave;

enum arma_Actual{
	cuerpo_a_cuerpo = 1,
	distancia = 2,
	cerca = 3
};

class Inventario{
public:
	Inventario();
	virtual ~Inventario();

	void render();
	bool usar();
	
	/*SET*/
	void cambiar_objeto_cerca(Arma_cerca *_i_cerca);
	void cambiar_objeto_distancia (Arma_distancia *_i_distancia);
	void cambiar_seleccionado();

	void cambiar_arma_seleccionada_a_la_siguiente();
	void cambiar_arma_seleccionada_a_la_anterior();
	void seleccionar_arma_distancia();
	void seleccionar_arma_cerca();
	void seleccionar_cuerpo_a_cuerpo();
    
    void anadir_llave(Llave* _i_llave);
	void eliminar_llave(Llave* _i_llave);
	
	/*GET*/
	Objeto* get_seleccionado();
	Arma_distancia* get_objeto_distancia();
	Arma_cerca* get_objeto_cerca();
    std::vector<Llave*> get_llaves();



private:
	arma_Actual _arma;
	Arma_distancia *_objeto_distancia;
	Arma_cerca *_objeto_cerca;
	Arma *_seleccionado;
    std::vector<Llave*> _llaves;
};

#endif /* INVENTARIO_H_ */
