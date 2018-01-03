/*==============================================================================
Simple Event Example
Copyright (c), Firelight Technologies Pty, Ltd 2012-2016.

This example demonstrates the various ways of playing an event.

#### Explosion Event ####
This event is played as a one-shot and released immediately after it has been
created.

#### Looping Ambience Event ####
A single instance is started or stopped based on user input.

#### Cancel Event ####
This instance is started and if already playing, restarted.

==============================================================================*/
#include <iostream>
#include "fmod_studio.hpp"
//#include "fmod.hpp"
#include "fmod_errors.h"


int main(int argv, char*args[])
{
    char wavfile[] = "";//variable donde depositar el wav(en el caso de que se hiciera)
    //char** extraDriverData = &wavfile;
    //char banksPath[] = "Desktop/";
    //Common_Init(&extraDriverData);

    FMOD::Studio::System* system = NULL;
    ERRCHECK( FMOD::Studio::System::create(&system) );

    // The example Studio project is authored for 5.1 sound, so set up the system output mode to match
    FMOD::System* lowLevelSystem = NULL;
    ERRCHECK( system->getLowLevelSystem(&lowLevelSystem) );
    ERRCHECK( lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0) );

    ERRCHECK( lowLevelSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT) );
    /*if (argv>1) {
    	  char * output = args[1];
    	  /*if (strcmp(output,"AUTO")==0)
    		    ERRCHECK( lowLevelSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT) );
    	  else if (strcmp(output, "WAV")==0)
  		    ERRCHECK( lowLevelSystem->setOutput(FMOD_OUTPUTTYPE_WAVWRITER) );
    	  else if (strcmp(output, "WAV_NRT")==0)
    		    ERRCHECK( lowLevelSystem->setOutput(FMOD_OUTPUTTYPE_WAVWRITER_NRT) );
    }*/

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

    // Get the Looping Ambience event
    FMOD::Studio::EventDescription* loopingAmbienceDescription = NULL;
    ERRCHECK( system->getEvent("event:/Ambience/Country", &loopingAmbienceDescription) );
    FMOD_GUID guid;
    char eventDescrPath[512];
    ERRCHECK( loopingAmbienceDescription->getID(&guid));
    ERRCHECK( loopingAmbienceDescription->getPath(eventDescrPath,512,NULL));
    std::cout << "Ambience/Country guid: " << std::hex << guid.Data1 << "-" << guid.Data2 << "-" << guid.Data3 << std::endl;
    std::cout << "Ambience/Country path: " << eventDescrPath << std::endl; 


    FMOD::Studio::EventInstance* loopingAmbienceInstance = NULL;
    ERRCHECK( loopingAmbienceDescription->createInstance(&loopingAmbienceInstance) );

    // Get the 4 Second Surge event
    FMOD::Studio::EventDescription* cancelDescription = NULL;
    ERRCHECK( system->getEvent("event:/UI/Cancel", &cancelDescription) );

    FMOD::Studio::EventInstance* cancelInstance = NULL;
    ERRCHECK( cancelDescription->createInstance(&cancelInstance) );

    // Get the Single Explosion event
    FMOD::Studio::EventDescription* explosionDescription = NULL;
    ERRCHECK( system->getEvent("event:/Explosions/Single Explosion", &explosionDescription) );

    // Start loading explosion sample data and keep it in memory
    ERRCHECK( explosionDescription->loadSampleData() );

    int choice=0;
    FMOD::Studio::EventInstance* eventInstance = NULL;
    do
    {
        std::cout << "Choose (0: exit, 1: Shot, 2: Ambient start, 3: Ambient stop, 4: Cancel sound): ";
        std::cin >> choice;

        switch(choice) {
          case 1:
            // One-shot event
            ERRCHECK( explosionDescription->createInstance(&eventInstance) );

            ERRCHECK( eventInstance->start() );

            // Release will clean up the instance when it completes
            ERRCHECK( eventInstance->release() );
            break;

          case 2:

            ERRCHECK( loopingAmbienceInstance->start() );
            break;

          case 3:
            ERRCHECK( loopingAmbienceInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE) );
            break;

          case 4:
            // Calling start on an instance will cause it to restart if it's already playing
            ERRCHECK( cancelInstance->start() );
            break;
        }

        ERRCHECK( system->update() );

    } while (choice != 0);

    ERRCHECK( weaponsBank->unload() );
    ERRCHECK( menuBank->unload() );
    ERRCHECK( ambienceBank->unload() );
    ERRCHECK( stringsBank->unload() );
    ERRCHECK( masterBank->unload() );

    ERRCHECK( system->release() );

    return 0;
}
