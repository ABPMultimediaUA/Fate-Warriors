#ifndef HEADER_GAME_H_
#define HEADER_GAME_H_

class Datos_Partida;
class Action_Manager;
class Datos_Partida;
class Interfaz;
class Interfaz_Fisica;
class Game{

public:

	~Game();
	static Game* game_instancia();	
	void crea_partida();
	void fin_partida();
 	void update(double _i_tiempo_desde_ultimo_update);
	void render(float _i_interpolacion);
	void run();
  	Datos_Partida* game_get_datos();

private:

	Game();
	static Game* instancia;
	Datos_Partida *_datos;
	Action_Manager *_action_manager;
	Interfaz *_interfaz_grafica;
	Interfaz_Fisica* _interfaz_fisica;
};


#endif /* HEADER_GAME_H_ */
