#ifndef SRC_INTERFAZ_SONIDO_H_
#define SRC_INTERFAZ_SONIDO_H_

#include "FMOD/fmod_studio.hpp"

class Interfaz_sonido {
public:
	Interfaz_sonido();
	~Interfaz_sonido();

    void CreateSound();
    void Disparar();
    void Ambiente();
    void Cancelar_ambiente();
    void Cancelar();
    void Update();


private:

    FMOD::Studio::System* system = NULL;

    FMOD::System* lowLevelSystem = NULL;

    FMOD::Studio::Bank* masterBank = NULL;
    FMOD::Studio::Bank* stringsBank = NULL;
    FMOD::Studio::Bank* ambienceBank = NULL;
    FMOD::Studio::Bank* menuBank = NULL;
    FMOD::Studio::Bank* weaponsBank = NULL;

	FMOD::Studio::EventDescription* loopingAmbienceDescription = NULL;
    FMOD::Studio::EventInstance* loopingAmbienceInstance = NULL;
    FMOD::Studio::EventDescription* cancelDescription = NULL;
    FMOD::Studio::EventInstance* cancelInstance = NULL;
    FMOD::Studio::EventDescription* explosionDescription = NULL;

	FMOD::Studio::EventInstance* eventInstance = NULL;
	
};

#endif /* SRC_INTERFAZ_SONIDO_H_ */