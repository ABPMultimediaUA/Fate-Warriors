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
class Evento_musica;
class Interfaz_sonido {
public:
    static Interfaz_sonido* GetInstancia();
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
    void crear_canales(std::string _i_iteracion);
    void crear_musica(std::string _i_iteracion);


    void Play_ambiente(uint8_t _i_n);
    void Play_armas(uint8_t _i_n);
    void Play_consumibles(uint8_t _i_n);
    void Play_escenario(uint8_t _i_n);
    void Play_menu(uint8_t _i_n);
    void Play_personaje(uint8_t _i_n);
    void Play_voces(uint8_t _i_n);
    void Play_pasos(uint8_t _i_n);

    void Stop_pasos(uint8_t _i_n);
    void Stop_ambiente(uint8_t _i_n);
    void Stop_musica(uint8_t _i_n);
    void Stop_game();
    /*void Stop_armas(uint8_t _i_n);
    void Stop_consumibles(uint8_t _i_n);
    void Stop_escenario(uint8_t _i_n);
    void Stop_menu(uint8_t _i_n);
    void Stop_personaje(uint8_t _i_n);
    void Stop_voces(uint8_t _i_n);*/

    void Pausa();
    void Quitar_pausa();

    void set_volumen_musica(float _i_v);
    void set_volumen_voces(float _i_v);
    void set_volumen_sfx(float _i_v);
    void set_volumen_menu(float _i_v);
    void system_update();


private:
    static Interfaz_sonido* instancia;

    int _n_canales,_n_musica,_n_ambiente,_n_armas,_n_consumibles,_n_escenario,_n_menu,_n_personaje,_n_voces,_n_pasos;
    
FMOD_STUDIO_BUS * _bus_musica;
    FMOD_STUDIO_BUS * _bus_voces;
    FMOD_STUDIO_BUS * _bus_sfx;
    FMOD_STUDIO_BUS * _bus_menu;
    //FMOD::ChannelGroup _canal;
    
    FMOD_STUDIO_SYSTEM* system = NULL;
    FMOD_SYSTEM* lowLevelSystem = NULL;

    FMOD_STUDIO_BANK* masterBank = NULL;
    FMOD_STUDIO_BANK* stringsBank = NULL;

    FMOD_STUDIO_BANK* AmbienteBank = NULL;
    Evento_ambiente **_eventos_ambiente;

    FMOD_STUDIO_BANK* ArmasBank = NULL;
    Evento_armas **_eventos_armas;

    FMOD_STUDIO_BANK* ConsumiblesBank = NULL;
    Evento_consumibles **_eventos_consumibles;

    FMOD_STUDIO_BANK* EscenarioBank = NULL;
    Evento_escenario **_eventos_escenario;

    FMOD_STUDIO_BANK* MenuBank = NULL;
    Evento_menu **_eventos_menu;

    FMOD_STUDIO_BANK* PersonajeBank = NULL;
    Evento_personaje **_eventos_personaje;

    FMOD_STUDIO_BANK* VocesBank = NULL;
    Evento_voces **_eventos_voces;

    FMOD_STUDIO_BANK* PasosBank = NULL;
    Evento_pasos **_eventos_pasos;

    FMOD_STUDIO_BANK* MusicaBank = NULL;
    Evento_musica **_eventos_musica;



	
};

#endif /* SRC_INTERFAZ_SONIDO_H_ */