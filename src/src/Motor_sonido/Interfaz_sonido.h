#ifndef SRC_INTERFAZ_SONIDO_H_
#define SRC_INTERFAZ_SONIDO_H_

#include <cstdint>
#include <string>

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
    void Play_musica(uint8_t _i_n);

    void Stop_pasos();
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


    inline uint8_t get_volumen_musica() { return _volumen_musica;}
    inline uint8_t get_volumen_sfx() { return _volumen_sfx;}
    inline uint8_t get_volumen_voces() { return _volumen_voces;}

    inline void guarda_volumen_musica(uint8_t _i_vol) { _volumen_musica = _i_vol;}
    inline void guarda_volumen_sfx(uint8_t _i_vol) { _volumen_sfx = _i_vol;}
    inline void guarda_volumen_voces(uint8_t _i_vol) { _volumen_voces = _i_vol;}

private:
    static Interfaz_sonido* instancia;

    int _n_canales,_n_musica,_n_ambiente,_n_armas,_n_consumibles,_n_escenario,_n_menu,_n_personaje,_n_voces,_n_pasos;
    FMOD::Studio::Bus * _bus_musica;
    FMOD::Studio::Bus * _bus_voces;
    FMOD::Studio::Bus * _bus_sfx;
    FMOD::Studio::Bus * _bus_menu;
    //FMOD::ChannelGroup _canal;
    
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

    FMOD::Studio::Bank* MusicaBank = NULL;
    Evento_musica **_eventos_musica;


    // Variables de la configuracion
    uint8_t _volumen_musica;
    uint8_t _volumen_sfx;
    uint8_t _volumen_voces;	

    // Variables de control de sonido
    bool _loop_pasos;
    uint8_t _pasos_actual;
};

#endif /* SRC_INTERFAZ_SONIDO_H_ */