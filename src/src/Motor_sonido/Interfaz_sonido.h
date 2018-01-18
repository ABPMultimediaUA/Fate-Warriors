#ifndef SRC_INTERFAZ_SONIDO_H_
#define SRC_INTERFAZ_SONIDO_H_

#include "FMOD/fmod_studio.hpp"

class Interfaz_sonido {
public:
	Interfaz_sonido(std::string &_i_fichero);
	~Interfaz_sonido();

    void CreateSound();
    void PasosCadena();
    void PasosArena();
    void PasosAsfalto();
    void Update();


private:

    FMOD::Studio::System* system = NULL;

    FMOD::System* lowLevelSystem = NULL;

    FMOD::Studio::Bank* masterBank = NULL;
    FMOD::Studio::Bank* stringsBank = NULL;
    

	FMOD::Studio::EventDescription* loopingAmbienceDescription = NULL;
    FMOD::Studio::EventInstance* loopingAmbienceInstance = NULL;

	
};

#endif /* SRC_INTERFAZ_SONIDO_H_ */