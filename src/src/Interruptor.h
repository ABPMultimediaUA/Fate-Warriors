#ifndef INTERRUPTOR_H_
#define INTERRUPTOR_H_

#include "Objeto.h"
#include <vector>

class Puerta_Pincho;
class Time;

class Interruptor : public Objeto{
public:
	Interruptor(short _i_id, float _i_x, float _i_y, float _i_z, float _i_rotacion, Puerta_Pincho* _i_objeto_asociado,
			bool _i_es_generador, bool _i_activado, double _i_temporizador);
	virtual ~Interruptor();

	void set_activado(bool _i_activado);
	void update() override;
	void render() override;
	void set_desactivado_para_siempre();
	inline Puerta_Pincho* get_puerta(){
		return _objeto_asociado;
	}

	inline int get_npcs_persiguiendome(){
		return _npcs_persiguiendome;
	}
	inline void incrementar_npcs_persiguiendome(){
		_npcs_persiguiendome++;
	}
	inline void decrementar_npcs_persiguiendome(){
		_npcs_persiguiendome--;
	}
	inline void reiniciar_npcs_persiguiendome(){
		_npcs_persiguiendome = 0;
	}

	void set_desactivado();


private:
	Puerta_Pincho* _objeto_asociado; // Objeto asociado que activa/desactiva	//BORRAME esto debe de ser borrado porque a partir de ahora recibira un vector de las puertas a las que haga referencia sin importar la cantidad de elementos
	bool _es_generador; // si es generador, despues de su primer uso se debe destruir
	int _npcs_persiguiendome;
	std::vector<Puerta_Pincho*> _objetos_asociados;	//Vector con todas las puertas asociadas
};

#endif /* INTERRUPTOR_H_ */
