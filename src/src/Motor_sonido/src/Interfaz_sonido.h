#ifndef SRC_INTERFAZ_SONIDO_H_
#define SRC_INTERFAZ_SONIDO_H_

#include "FMOD/fmod_studio.hpp"
class Evento_pasos;
class Evento_ambiente;
class Evento_armas;
class Evento_consumibles;
class Evento_escenario;
class Evento_menu;
class Evento_personaje;
class Evento_voces;
class Interfaz_sonido {
public:
	Interfaz_sonido(std::string _i_fichero);
	~Interfaz_sonido();

    void crear_ambiente(std::string _i_iteracion);
    void crear_armas(std::string _i_iteracion);
    void crear_consumibles(std::string _i_iteracion);
    void crear_escenario(std::string _i_iteracion);
    void crear_menu(std::string _i_iteracion);
    void crear_pasos(std::string _i_iteracion);
    void crear_personaje(std::string _i_iteracion);
    void crear_voces(std::string _i_iteracion);


    void Play_ambiente(u_int8_t _i_n);
    void Play_armas(u_int8_t _i_n);
    void Play_consumibles(u_int8_t _i_n);
    void Play_escenario(u_int8_t _i_n);
    void Play_menu(u_int8_t _i_n);
    void Play_personaje(u_int8_t _i_n);
    void Play_voces(u_int8_t _i_n);
    void Play_pasos(u_int8_t _i_n);

    void Stop_pasos(u_int8_t _i_n);
    void Stop_ambiente(u_int8_t _i_n);
    void Stop_armas(u_int8_t _i_n);
    void Stop_consumibles(u_int8_t _i_n);
    void Stop_escenario(u_int8_t _i_n);
    void Stop_menu(u_int8_t _i_n);
    void Stop_personaje(u_int8_t _i_n);
    void Stop_voces(u_int8_t _i_n);

    void set_volumen_musica(float _i_v);
    void set_volumen_voces(float _i_v);
    void set_volumen_sfx(float _i_v);
    void set_volumen_menu(float _i_v);
    void system_update();


private:
    int _n_ambiente,_n_armas,_n_consumibles,_n_escenario,_n_menu,_n_personaje,_n_voces,_n_pasos;
    FMOD::ChannelControl *chanel_control;
    
    FMOD::Studio::System* system = NULL;
    FMOD::System* lowLevelSystem = NULL;

    FMOD::Studio::Bank* masterBank = NULL;
    FMOD::Studio::Bank* stringsBank = NULL;

    FMOD::Studio::Bank* AmbienteBank = NULL;
    Evento_ambiente **_eventos_ambiente;

    FMOD::Studio::Bank* ArmasBank = NULL;
    Evento_armas **_eventos_armas;

    FMOD::Studio::Bank* ConsumiblesBank = NULL;
    Evento_consumibles **_eventos_consumibles;

    FMOD::Studio::Bank* EscenarioBank = NULL;
    Evento_escenario **_eventos_escenario;

    FMOD::Studio::Bank* MenuBank = NULL;
    Evento_menu **_eventos_menu;

    FMOD::Studio::Bank* PersonajeBank = NULL;
    Evento_personaje **_eventos_personaje;

    FMOD::Studio::Bank* VocesBank = NULL;
    Evento_voces **_eventos_voces;

    FMOD::Studio::Bank* PasosBank = NULL;
    Evento_pasos **_eventos_pasos;



	
};

#endif /* SRC_INTERFAZ_SONIDO_H_ */