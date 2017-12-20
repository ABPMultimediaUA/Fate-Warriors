#ifndef INVENTARIO_H_
#define INVENTARIO_H_

#include <vector>

class Arma_distancia;
class Objeto;
class Arma_cerca;
class Arma;
class Llave;

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
    
    void anadir_llave(Llave* _i_llave);
	void eliminar_llave(Llave* _i_llave);
	
	/*GET*/
	Objeto* get_seleccionado();
	Objeto* get_objeto_distancia();
	Objeto* get_objeto_cerca();
    std::vector<Llave*> get_llaves();

private:
	Arma_distancia *_objeto_distancia;
	Arma_cerca *_objeto_cerca;
	Arma *_seleccionado;
    std::vector<Llave*> _llaves;
};

#endif /* INVENTARIO_H_ */
