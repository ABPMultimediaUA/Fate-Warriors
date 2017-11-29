#ifndef INVENTARIO_H_
#define INVENTARIO_H_

class Arma_distancia;
class Objeto;
class Arma_cerca;
class Consumible;

class Inventario{
public:
	Inventario();
	virtual ~Inventario();

	void update();
	void render();
	bool usar();
	
	/*SET*/
	void cambiar_objeto_cerca(Arma_cerca *_i_cerca);
	void cambiar_objeto_distancia (Arma_distancia *_i_distancia);
	void cambiar_seleccionado();
	void cambiar_consumbible(Consumible * _i_consumible);
	
	/*GET*/
	Objeto* get_seleccionado();
	Objeto* get_objeto_distancia();
	Objeto* get_objeto_cerca();
	Consumible* get_consumible();

private:
	Arma_distancia *_objeto_distancia;
	Arma_cerca *_objeto_cerca;
	Objeto *_seleccionado;
	Consumible * _consumible;
};

#endif /* INVENTARIO_H_ */
