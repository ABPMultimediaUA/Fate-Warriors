#include <iostream>
//#include "fmod.hpp"
#include "FMOD/fmod_errors.h"
#include "Interfaz_sonido.h"


/*enum Enum_Acciones Arbol_Decision_Manager::get_Ambiente(){
	return Ambiente;
}
struct MapeadoAccion{			// Declaracion de los parametros
	const char* _nombre_objeto;
	enum Enum_Acciones (Intefaz_sonido::*pmet)();
};

MapeadoAccion mapping_enum_acciones[] = {	// Definicion de los parametros
    {"Estar_derribado", &Intefaz_sonido::get_estar_derribado},
	{0, 0}
};*/

struct Tinstance2func{//declaracion de los parametros
	const char* _nombre_objeto;
	void (Interfaz_sonido::*pmet)(std::ifstream&, std::string&);
};

Ttxt2func mapping[] = {//definicion de los parametros
		{"PASILLO", &Interfaz_sonido::Interfaz_sonido_crear_pasillo},
		{"NODO", &Interfaz_sonido::Interfaz_sonido_crear_nodo},
		{"ARISTA", &Interfaz_sonido::Interfaz_sonido_crear_arista},
		{"ADYACENTE", &Interfaz_sonido::Interfaz_sonido_crear_adyacentes},
		{0, 0}
};




Interfaz_sonido::Interfaz_sonido(std::string &_i_fichero){
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




    std::ifstream _sonidos_txt;
	Ttxt2func *_next;

	_sonidos_txt.open(_i_fichero);//apertura del fichero
	std::string _iteracion;
		if(_sonidos_txt.fail()){//comprobacion de la apertura del fichero
			std::cout<<"Error al abrir el archivo de sonido" << _i_fichero <<std::endl;
			exit(0);
		}
	_sonidos_txt >> _iteracion;//primera lectura de nombre de clase a introducir
	while(_iteracion!="Fin"){//bucle de lectura del fichero
		_next=mapping;
		//std::cout<<_iteracion<<std::endl;
		while (_next->_nombre_objeto){
			if(_iteracion==_next->_nombre_objeto){
				(this->*_next->pmet)(_sonidos_txt,_iteracion);
			}

			++_next;
		}
		/*if(_iteracion=="NODO"){
			sonidos_crear_nodo(_sonidos_txt, _iteracion);
		}else if(_iteracion=="PASILLO"){
			sonidos_crear_pasillo(_sonidos_txt, _iteracion);//llamada a la funcion de crear un nuevo pasillo
		}*/
    }
    _sonidos_txt.close();//cierre del fichero
    char wavfile[] = "";//variable donde depositar el wav(en el caso de que se hiciera)

   
}

Interfaz_sonido::~Interfaz_sonido(){

    /*ERRCHECK( weaponsBank->unload() );
    ERRCHECK( menuBank->unload() );
    ERRCHECK( ambienceBank->unload() );
    ERRCHECK( stringsBank->unload() );*/
    ERRCHECK( pasosBank->unload() );
    ERRCHECK( masterBank->unload() );
    ERRCHECK( system->release() );
}

void Interfaz_sonido::CreateSound(){

    // Get the Looping Ambience event
    //FMOD::Studio::EventDescription* loopingAmbienceDescription = NULL;
    /*ERRCHECK( system->getEvent("event:/Ambience/Country", &loopingAmbienceDescription) );
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
    ERRCHECK( cancelDescription->createInstance(&cancelInstance) );*/

    // Get the Single Explosion event
    //FMOD::Studio::EventDescription* explosionDescription = NULL;
    ERRCHECK( system->getEvent("event:/Pasos/Cadena", &pasosCadena) );

    // Start loading explosion sample data and keep it in memory
    ERRCHECK( pasosCadena->loadSampleData() );

    ERRCHECK( system->getEvent("event:/Pasos/Arena", &pasosArena) );

    // Start loading explosion sample data and keep it in memory
    ERRCHECK( pasosArena->loadSampleData() );

    ERRCHECK( system->getEvent("event:/Pasos/Asfalto", &pasosAsfalto) );

    // Start loading explosion sample data and keep it in memory
    ERRCHECK( pasosAsfalto->loadSampleData() );

}

void Interfaz_sonido::PasosCadena(){
    std::cout << "PasosCadena" << std::endl;
    ERRCHECK( pasosCadena->createInstance(&eventInstance) );

    ERRCHECK( eventInstance->start() );

    // Release will clean up the instance when it completes
    ERRCHECK( eventInstance->release() );
    Update();
}
void Interfaz_sonido::PasosArena(){
    std::cout << "PasosArena" << std::endl;
    ERRCHECK( pasosArena->createInstance(&eventInstance) );

    ERRCHECK( eventInstance->start() );

    // Release will clean up the instance when it completes
    ERRCHECK( eventInstance->release() );
    Update();
}
void Interfaz_sonido::PasosAsfalto(){
    std::cout << "PasosAsfalto" << std::endl;
    ERRCHECK( pasosAsfalto->createInstance(&eventInstance) );

    ERRCHECK( eventInstance->start() );

    // Release will clean up the instance when it completes
    ERRCHECK( eventInstance->release() );
    Update();
}
/*void Interfaz_sonido::Ambiente(){
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
}*/

void Interfaz_sonido::Update(){
    ERRCHECK( system->update() );
}
