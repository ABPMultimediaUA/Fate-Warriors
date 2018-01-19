#ifndef SRC_INTERFAZ_SONIDO_H_
#define SRC_INTERFAZ_SONIDO_H_

#include "FMOD/fmod_studio.hpp"
class Evento_pasos;
class Interfaz_sonido {
public:
	Interfaz_sonido(std::string _i_fichero);
	~Interfaz_sonido();

    void inicializacion(std::ifstream& _i_sonidos_txt, std::string& _i_iteracion);
    void crear_ambiente(std::ifstream& _i_sonidos_txt, std::string& _i_iteracion);
    void crear_armas(std::ifstream& _i_sonidos_txt, std::string& _i_iteracion);
    void crear_consumibles(std::ifstream& _i_sonidos_txt, std::string& _i_iteracion);
    void crear_escenario(std::ifstream& _i_sonidos_txt, std::string& _i_iteracion);
    void crear_menu(std::ifstream& _i_sonidos_txt, std::string& _i_iteracion);
    void crear_pasos(std::ifstream& _i_sonidos_txt, std::string& _i_iteracion);
    void crear_personaje(std::ifstream& _i_sonidos_txt, std::string& _i_iteracion);
    void crear_voces(std::ifstream& _i_sonidos_txt, std::string& _i_iteracion);


    void Play_pasos(u_int8_t _i_n);
    void system_update();


private:
    int _n_pasos;
    Evento_pasos **_eventos_pasos;
    FMOD::Studio::System* system = NULL;
    FMOD::Studio::Bank* banco;
    FMOD::System* lowLevelSystem = NULL;

    FMOD::Studio::Bank* masterBank = NULL;
    FMOD::Studio::Bank* stringsBank = NULL;



	
};

#endif /* SRC_INTERFAZ_SONIDO_H_ */