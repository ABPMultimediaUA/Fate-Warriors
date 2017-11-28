#ifndef ARMA_DISTANCIA_H_
#define ARMA_DISTANCIA_H_

#include "Equipable.h"
#include <list>

class Bala;
class Arma_distancia : public Equipable{
public:
	Arma_distancia(float _i_x, float _i_y, float _i_z,  float _i_ancho, float _i_alto, short _i_uses);
	virtual ~Arma_distancia();
	void render() override;
	void update(); 
	void recargar_arma();
	bool usar() override;

private:
	/*std::list<Bala> Balas;*/
	short _cargadores;
	short _balas_por_cargador;
	short _balas_totales;
	short _balas_actuales;
};

#endif /* ARMA_DISTANCIA_H_ */
