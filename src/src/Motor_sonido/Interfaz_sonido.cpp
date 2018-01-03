#include <iostream>
#include "fmod_studio.hpp"
//#include "fmod.hpp"
#include "fmod_errors.h"

void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line)
{
    if (result != FMOD_OK)
    {
        std::cerr << file << "(" << line << "): FMOD error " << result << " - " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}


#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)


Interfaz_sonido::Interfaz_sonido(){

    char wavfile[] = "";//variable donde depositar el wav(en el caso de que se hiciera)

    FMOD::Studio::System* system = NULL;
    ERRCHECK( FMOD::Studio::System::create(&system) );

    // The example Studio project is authored for 5.1 sound, so set up the system output mode to match
    FMOD::System* lowLevelSystem = NULL;
    ERRCHECK( system->getLowLevelSystem(&lowLevelSystem) );
    ERRCHECK( lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0) );

    ERRCHECK( lowLevelSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT) );

    ERRCHECK( system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, &wavfile) );//inicializacion de fmod

    FMOD::Studio::Bank* masterBank = NULL;
    ERRCHECK( system->loadBankFile("Desktop/Master Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank) );

    FMOD::Studio::Bank* stringsBank = NULL;
    ERRCHECK( system->loadBankFile("Desktop/Master Bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank) );

    FMOD::Studio::Bank* ambienceBank = NULL;
    ERRCHECK( system->loadBankFile("Desktop/Surround_Ambience.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &ambienceBank) );

    FMOD::Studio::Bank* menuBank = NULL;
    ERRCHECK( system->loadBankFile("Desktop/UI_Menu.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &menuBank) );

    FMOD::Studio::Bank* weaponsBank = NULL;
    ERRCHECK( system->loadBankFile("Desktop/Weapons.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &weaponsBank) );
}

Interfaz_sonido::~Interfaz_sonido(){
}