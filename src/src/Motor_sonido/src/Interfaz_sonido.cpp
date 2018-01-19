#include <iostream>
//#include "fmod.hpp"
#include "FMOD/fmod_errors.h"
#include "Interfaz_sonido.h"
#include <cstdlib>
#include <fstream>

#include "Evento_pasos.h"


#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)

void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line)
{
    if (result != FMOD_OK)
    {
        std::cerr << file << "(" << line << "): FMOD error " << result << " - " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}
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

struct Ttxt2func{//declaracion de los parametros
	const char* _nombre_objeto;
	void (Interfaz_sonido::*pmet)(std::ifstream&, std::string&);
};

Ttxt2func mapping[] = {//definicion de los parametros
		{"AMBIENTE", &Interfaz_sonido::crear_ambiente},
		{"ARMAS", &Interfaz_sonido::crear_armas},
		{"CONSUMIBLES", &Interfaz_sonido::crear_consumibles},
		{"ESCENARIO", &Interfaz_sonido::crear_escenario},
        {"MENU", &Interfaz_sonido::crear_menu},
        {"txt/Eventosonidos/pasos.txt", &Interfaz_sonido::crear_pasos},
        {"PERSONAJE", &Interfaz_sonido::crear_personaje},
        {"VOCES", &Interfaz_sonido::crear_voces},
        {"INIT", &Interfaz_sonido::inicializacion},
		{0, 0}
};




Interfaz_sonido::Interfaz_sonido(std::string _i_fichero){
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
}

Interfaz_sonido::~Interfaz_sonido(){
    for(u_int8_t _cont = 0; _cont < _n_pasos; _cont++) {
		delete _eventos_pasos[_cont];
	}
	delete [] _eventos_pasos;
    /*ERRCHECK( weaponsBank->unload() );
    ERRCHECK( menuBank->unload() );
    ERRCHECK( ambienceBank->unload() );
    ERRCHECK( stringsBank->unload() );*/
    //ERRCHECK( pasosBank->unload() );
    ERRCHECK( masterBank->unload() );
    ERRCHECK( system->release() );
}

void Interfaz_sonido::system_update(){

    ERRCHECK( system->update() );
}
void Interfaz_sonido::inicializacion(std::ifstream& _i_sonidos_txt, std::string& _i_iteracion){
    
    _i_sonidos_txt>>_i_iteracion;//obtiene el valor de la id del origenre
	_n_pasos = std::atoi(_i_iteracion.c_str());

    _eventos_pasos= new Evento_pasos*[_n_pasos];
    u_int8_t cont=0;
    while(cont<_n_pasos){
        _eventos_pasos[cont]=nullptr;
    }
    _i_sonidos_txt>>_i_iteracion;
}

void Interfaz_sonido::crear_ambiente(std::ifstream& _i_sonidos_txt, std::string& _i_iteracion){

}
void Interfaz_sonido::crear_armas(std::ifstream& _i_sonidos_txt, std::string& _i_iteracion){

}
void Interfaz_sonido::crear_consumibles(std::ifstream& _i_sonidos_txt, std::string& _i_iteracion){

}
void Interfaz_sonido::crear_escenario(std::ifstream& _i_sonidos_txt, std::string& _i_iteracion){

}
void Interfaz_sonido::crear_menu(std::ifstream& _i_sonidos_txt, std::string& _i_iteracion){

}
void Interfaz_sonido::crear_pasos(std::ifstream& _i_sonidos_txt, std::string& _i_iteracion){
    //Evento_pasos *pasos_aux=_eventos_pasos[0];
    u_int8_t cont=0;

    _i_sonidos_txt>>_i_iteracion;//obtiene el valor de la id del origenre
	_n_pasos = std::atoi(_i_iteracion.c_str());
    std::ifstream _pasos_txt;    
    _pasos_txt.open(_i_iteracion);//apertura del fichero
	std::string _iteracion;

	if(_pasos_txt.fail()){//comprobacion de la apertura del fichero
		std::cout<<"Error al abrir el archivo de sonido/pasos" << _i_iteracion <<std::endl;
		exit(0);
	}
    do{
        _pasos_txt >> _iteracion;
        _eventos_pasos[cont] = new Evento_pasos(_iteracion, system);
        ++cont;
    }while(_iteracion!="Fin" && cont<_n_pasos);

    if(cont==_n_pasos && _iteracion!="Fin"){
        std::cout<<"ERROR CARGA SONIDO: demasiados sonidos de pasos"<<std::endl;
        exit(0);
    }else{

    }
}
void Interfaz_sonido::crear_personaje(std::ifstream& _i_sonidos_txt, std::string& _i_iteracion){

}
void Interfaz_sonido::crear_voces(std::ifstream& _i_sonidos_txt, std::string& _i_iteracion){

}

void Interfaz_sonido::Play_pasos(u_int8_t _i_n){
    _eventos_pasos[_i_n]->start();
    system_update();
}
