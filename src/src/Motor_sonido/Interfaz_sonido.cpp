#include <iostream>
//#include "fmod.hpp"
#include "FMOD/fmod_errors.h"
#include "Interfaz_sonido.h"

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

    //FMOD::Studio::System* system = NULL;
    ERRCHECK( FMOD::Studio::System::create(&system) );

    // The example Studio project is authored for 5.1 sound, so set up the system output mode to match
    //FMOD::System* lowLevelSystem = NULL;
    ERRCHECK( system->getLowLevelSystem(&lowLevelSystem) );
    ERRCHECK( lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0) );

    ERRCHECK( lowLevelSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT) );

    ERRCHECK( system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, &wavfile) );//inicializacion de fmod

    //FMOD::Studio::Bank* masterBank = NULL;
    ERRCHECK( system->loadBankFile("Banks/Master Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank) );

    //FMOD::Studio::Bank* stringsBank = NULL;
    ERRCHECK( system->loadBankFile("Banks/Master Bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank) );

    //FMOD::Studio::Bank* ambienceBank = NULL;
    ERRCHECK( system->loadBankFile("Banks/Surround_Ambience.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &ambienceBank) );

    //FMOD::Studio::Bank* menuBank = NULL;
    ERRCHECK( system->loadBankFile("Banks/UI_Menu.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &menuBank) );

    //FMOD::Studio::Bank* weaponsBank = NULL;
    ERRCHECK( system->loadBankFile("Banks/Weapons.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &weaponsBank) );
}

Interfaz_sonido::~Interfaz_sonido(){

    ERRCHECK( weaponsBank->unload() );
    ERRCHECK( menuBank->unload() );
    ERRCHECK( ambienceBank->unload() );
    ERRCHECK( stringsBank->unload() );
    ERRCHECK( masterBank->unload() );
    ERRCHECK( system->release() );
}

void Interfaz_sonido::CreateSound(){

    // Get the Looping Ambience event
    //FMOD::Studio::EventDescription* loopingAmbienceDescription = NULL;
    ERRCHECK( system->getEvent("event:/Ambience/Country", &loopingAmbienceDescription) );
    FMOD_GUID guid;
    char eventDescrPath[512];
    ERRCHECK( loopingAmbienceDescription->getID(&guid));
    ERRCHECK( loopingAmbienceDescription->getPath(eventDescrPath,512,NULL));
    std::cout << "Ambience/Country guid: " << std::hex << guid.Data1 << "-" << guid.Data2 << "-" << guid.Data3 << std::endl;
    std::cout << "Ambience/Country path: " << eventDescrPath << std::endl; 


    //FMOD::Studio::EventInstance* loopingAmbienceInstance = NULL;
    ERRCHECK( loopingAmbienceDescription->createInstance(&loopingAmbienceInstance) );

    // Get the 4 Second Surge event
    //FMOD::Studio::EventDescription* cancelDescription = NULL;
    ERRCHECK( system->getEvent("event:/UI/Cancel", &cancelDescription) );

    //FMOD::Studio::EventInstance* cancelInstance = NULL;
    ERRCHECK( cancelDescription->createInstance(&cancelInstance) );

    // Get the Single Explosion event
    //FMOD::Studio::EventDescription* explosionDescription = NULL;
    ERRCHECK( system->getEvent("event:/Weapons/Single-Shot", &explosionDescription) );

    // Start loading explosion sample data and keep it in memory
    ERRCHECK( explosionDescription->loadSampleData() );

}

void Interfaz_sonido::Disparar(){
    std::cout << "Disparar" << std::endl;
    ERRCHECK( explosionDescription->createInstance(&eventInstance) );

    ERRCHECK( eventInstance->start() );

    // Release will clean up the instance when it completes
    ERRCHECK( eventInstance->release() );
    std::cout << "Disparar2" << std::endl;
    Update();
    std::cout << "Disparar3" << std::endl;
}
void Interfaz_sonido::Ambiente(){
    std::cout << "Ambiente" << std::endl;
    ERRCHECK( loopingAmbienceInstance->start() );
    Update();
}
void Interfaz_sonido::Cancelar_ambiente(){
    std::cout << "Cancelar Ambiente" << std::endl;
    ERRCHECK( loopingAmbienceInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE) );
    Update();
}
void Interfaz_sonido::Cancelar(){
    std::cout << "Cancelar" << std::endl;
    ERRCHECK( cancelInstance->start() );
    Update();
}

void Interfaz_sonido::Update(){
    ERRCHECK( system->update() );
}

/*int main(int argv, char*args[])
{
  Interfaz_sonido* sonido = new Interfaz_sonido();

  sonido->CreateSound();

  sonido->Disparar();

  char algo;
  std::cin>>algo;
  if(algo=='1'){
  delete sonido;
  }
  return 0;
}*/
