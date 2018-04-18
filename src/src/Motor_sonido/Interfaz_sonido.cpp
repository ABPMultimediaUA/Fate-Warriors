#include <iostream>
//#include "fmod.hpp"
#include "FMOD/fmod_errors.h"
#include "Interfaz_sonido.h"
#include <cstdlib>
#include <fstream>

#include "Evento_pasos.h"
#include "Evento_pasos.h"
#include "Evento_ambiente.h"
#include "Evento_armas.h"
#include "Evento_consumibles.h"
#include "Evento_escenario.h"
#include "Evento_menu.h"
#include "Evento_personaje.h"
#include "Evento_voces.h"
#include "Evento_musica.h"

/*ambiente:
cuervos = 0
lluvia = 1
radio = 2
VientoC = 3
VientoD = 4

armas:
ametralladora = 0
bate = 1
katana = 2
latigo = 3
mangual = 4
pistola = 5
señal = 6

Consumibles:
agua = 0
carne = 1
patatas = 2

Escenario:
abrirPuerta = 0
CogerLLave = 1
explosionMina = 2
generadorOff = 3
generadorOn = 4
interruptor = 5
pinchos = 6
pisarMina = 7
puertaBestia = 8

Menu:
acceptar = 0
mover = 1

Musica:

Menu = 0
Online1 = 1
Online2 = 2
Lose1 = 3
Lose2 = 4
Lose3 = 5
Win1 = 6
Win2 = 7
Win3 = 8
Equilibrado1 = 9
Equilibrado2 = 10
Equilibrado3 = 11
Equilibrado4 = 12
Equilibrado5 = 13

Pasos:
arena = 0
asfalto = 1
bestia = 2
cadena = 3

personaje:
dash = 0
golpe = 1
powerUp = 2
salto = 3
salud = 4

voces:
bestia/ataque = 0
bestia/morir = 1
bestia/queja = 2
npc/ataque = 3
npc/morir = 4
npc/queja = 5
personajeM/ataque = 6
personajeM/morir = 7
personajeM/queja = 8*/

#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)

void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line)
{
    if (result != FMOD_OK)
    {
        std::cerr << file << "(" << line << "): FMOD error " << result << " - " << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}

struct Ttxt2func{//declaracion de los parametros
	const char* _nombre_objeto;
	void (Interfaz_sonido::*pmet)(std::string);
};

Ttxt2func mapping_sonido[] = {//definicion de los parametros
		{"txt/Eventosonidos/ambiente.txt", &Interfaz_sonido::crear_ambiente},
		{"txt/Eventosonidos/armas.txt", &Interfaz_sonido::crear_armas},
		{"txt/Eventosonidos/consumibles.txt", &Interfaz_sonido::crear_consumibles},
		{"txt/Eventosonidos/escenario.txt", &Interfaz_sonido::crear_escenario},
        {"txt/Eventosonidos/menu.txt", &Interfaz_sonido::crear_menu},
        {"txt/Eventosonidos/pasos.txt", &Interfaz_sonido::crear_pasos},
        {"txt/Eventosonidos/personaje.txt", &Interfaz_sonido::crear_personaje},
        {"txt/Eventosonidos/voces.txt", &Interfaz_sonido::crear_voces},
        {"txt/Eventosonidos/musica.txt", &Interfaz_sonido::crear_musica},
        {"txt/Eventosonidos/canales.txt", &Interfaz_sonido::crear_canales},
		{0, 0}
};


Interfaz_sonido* Interfaz_sonido::instancia = 0;

Interfaz_sonido* Interfaz_sonido::GetInstancia(){
	if(instancia == 0){
		std::string fichero="txt/bancosonidos.txt";
		instancia= new Interfaz_sonido(fichero);
	}
	return instancia;
}

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
		_next=mapping_sonido;
		//std::cout<<_iteracion<<std::endl;
		while (_next->_nombre_objeto){
			if(_iteracion==_next->_nombre_objeto){
				(this->*_next->pmet)(_iteracion);
                break;
			}

			++_next;
		}
        _sonidos_txt>>_iteracion;
		/*if(_iteracion=="NODO"){
			sonidos_crear_nodo(_sonidos_txt, _iteracion);
		}else if(_iteracion=="PASILLO"){
			sonidos_crear_pasillo(_sonidos_txt, _iteracion);//llamada a la funcion de crear un nuevo pasillo
		}*/
    }
    _sonidos_txt.close();//cierre del fichero

    _volumen_musica = 5;
    _volumen_sfx = 5;
    _volumen_voces = 5;
}

Interfaz_sonido::~Interfaz_sonido(){
    for(uint8_t _cont = 0; _cont < _n_ambiente; _cont++) {
		delete _eventos_ambiente[_cont];
	}
	delete [] _eventos_ambiente;
    for(uint8_t _cont = 0; _cont < _n_armas; _cont++) {
		delete _eventos_armas[_cont];
	}
	delete [] _eventos_armas;
    for(uint8_t _cont = 0; _cont < _n_consumibles; _cont++) {
		delete _eventos_consumibles[_cont];
	}
	delete [] _eventos_consumibles;
    for(uint8_t _cont = 0; _cont < _n_escenario; _cont++) {
		delete _eventos_escenario[_cont];
	}
	delete [] _eventos_escenario;
    for(uint8_t _cont = 0; _cont < _n_menu; _cont++) {
		delete _eventos_menu[_cont];
	}
	delete [] _eventos_menu;
    for(uint8_t _cont = 0; _cont < _n_pasos; _cont++) {
		delete _eventos_pasos[_cont];
	}
	delete [] _eventos_pasos;
    for(uint8_t _cont = 0; _cont < _n_personaje; _cont++) {
		delete _eventos_personaje[_cont];
	}
	delete [] _eventos_personaje;
    for(uint8_t _cont = 0; _cont < _n_voces; _cont++) {
		delete _eventos_voces[_cont];
	}
	delete [] _eventos_voces;
    ERRCHECK( AmbienteBank->unload() );
    ERRCHECK( ArmasBank->unload() );
    ERRCHECK( ConsumiblesBank->unload() );
    ERRCHECK( EscenarioBank->unload() );
    ERRCHECK( MenuBank->unload() );
    ERRCHECK( PersonajeBank->unload() );
    ERRCHECK( VocesBank->unload() );
    ERRCHECK( PasosBank->unload() );
    ERRCHECK( masterBank->unload() );

    /*ERRCHECK( _chanel_voces->unload() );
    ERRCHECK( _chanel_efectos->unload() );
    ERRCHECK( _chanel_sfx->unload() );*/
    ERRCHECK( system->release() );
}

void Interfaz_sonido::system_update(){

    ERRCHECK( system->update() );
}

/***************************************CREACION SONIDOS***********************************************/

void Interfaz_sonido::crear_ambiente(std::string _i_iteracion){
    uint8_t cont=0;
    std::ifstream _ambiente_txt;    
    _ambiente_txt.open(_i_iteracion);//apertura del fichero
	std::string _iteracion;
    std::cout<<_i_iteracion<<std::endl;
	if(_ambiente_txt.fail()){//comprobacion de la apertura del fichero
		std::cout<<"Error al abrir el archivo de sonido/ambiente" << _i_iteracion <<std::endl;
		exit(0);
	}

    _ambiente_txt>>_iteracion;
    ERRCHECK( system->loadBankFile(_iteracion.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &AmbienteBank) );
     _ambiente_txt>>_iteracion;//obtiene el valor de la id del origenre
	_n_ambiente = std::atoi(_iteracion.c_str());

    _eventos_ambiente= new Evento_ambiente*[_n_ambiente];

    cont=0;
    do{
        _ambiente_txt >> _iteracion;
        _eventos_ambiente[cont] = new Evento_ambiente(_iteracion, system);
        ++cont;
    }while(cont<_n_ambiente);

    _ambiente_txt.close();
}
void Interfaz_sonido::crear_armas(std::string _i_iteracion){
    uint8_t cont=0;
    std::ifstream _armas_txt;    
    _armas_txt.open(_i_iteracion);//apertura del fichero
	std::string _iteracion;
    std::cout<<_i_iteracion<<std::endl;
	if(_armas_txt.fail()){//comprobacion de la apertura del fichero
		std::cout<<"Error al abrir el archivo de sonido/armas" << _i_iteracion <<std::endl;
		exit(0);
	}

    _armas_txt>>_iteracion;
    ERRCHECK( system->loadBankFile(_iteracion.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &ArmasBank) );
     _armas_txt>>_iteracion;//obtiene el valor de la id del origenre
	_n_armas = std::atoi(_iteracion.c_str());

    _eventos_armas= new Evento_armas*[_n_armas];

    cont=0;
    do{
        _armas_txt >> _iteracion;
        _eventos_armas[cont] = new Evento_armas(_iteracion, system);
        ++cont;
    }while(cont<_n_armas);

    _armas_txt.close();
}
void Interfaz_sonido::crear_consumibles(std::string _i_iteracion){
    uint8_t cont=0;
    std::ifstream _consumibles_txt;    
    _consumibles_txt.open(_i_iteracion);//apertura del fichero
	std::string _iteracion;
    std::cout<<_i_iteracion<<std::endl;
	if(_consumibles_txt.fail()){//comprobacion de la apertura del fichero
		std::cout<<"Error al abrir el archivo de sonido/consumibles" << _i_iteracion <<std::endl;
		exit(0);
	}

    _consumibles_txt>>_iteracion;
    ERRCHECK( system->loadBankFile(_iteracion.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &ConsumiblesBank) );
     _consumibles_txt>>_iteracion;//obtiene el valor de la id del origenre
	_n_consumibles = std::atoi(_iteracion.c_str());

    _eventos_consumibles= new Evento_consumibles*[_n_consumibles];

    cont=0;
    do{
        _consumibles_txt >> _iteracion;
        _eventos_consumibles[cont] = new Evento_consumibles(_iteracion, system);
        ++cont;
    }while(cont<_n_consumibles);

    _consumibles_txt.close();
}
void Interfaz_sonido::crear_escenario(std::string _i_iteracion){
    uint8_t cont=0;
    std::ifstream _escenario_txt;    
    _escenario_txt.open(_i_iteracion);//apertura del fichero
	std::string _iteracion;
    std::cout<<_i_iteracion<<std::endl;
	if(_escenario_txt.fail()){//comprobacion de la apertura del fichero
		std::cout<<"Error al abrir el archivo de sonido/escenario" << _i_iteracion <<std::endl;
		exit(0);
	}

    _escenario_txt>>_iteracion;
    ERRCHECK( system->loadBankFile(_iteracion.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &EscenarioBank) );
     _escenario_txt>>_iteracion;//obtiene el valor de la id del origenre
	_n_escenario = std::atoi(_iteracion.c_str());

    _eventos_escenario= new Evento_escenario*[_n_escenario];

    cont=0;
    do{
        _escenario_txt >> _iteracion;
        _eventos_escenario[cont] = new Evento_escenario(_iteracion, system);
        ++cont;
    }while(cont<_n_escenario);

    _escenario_txt.close();
}
void Interfaz_sonido::crear_menu(std::string _i_iteracion){
    uint8_t cont=0;
    std::ifstream _menu_txt;    
    _menu_txt.open(_i_iteracion);//apertura del fichero
	std::string _iteracion;
    std::cout<<_i_iteracion<<std::endl;
	if(_menu_txt.fail()){//comprobacion de la apertura del fichero
		std::cout<<"Error al abrir el archivo de sonido/menu" << _i_iteracion <<std::endl;
		exit(0);
	}

    _menu_txt>>_iteracion;
    ERRCHECK( system->loadBankFile(_iteracion.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &MenuBank) );
     _menu_txt>>_iteracion;//obtiene el valor de la id del origenre
	_n_menu = std::atoi(_iteracion.c_str());

    _eventos_menu= new Evento_menu*[_n_menu];

    cont=0;
    do{
        _menu_txt >> _iteracion;
        _eventos_menu[cont] = new Evento_menu(_iteracion, system);
        ++cont;
    }while(cont<_n_menu);

    _menu_txt.close();
}
void Interfaz_sonido::crear_pasos(std::string _i_iteracion){
   
    uint8_t cont=0;
    std::ifstream _pasos_txt;    
    _pasos_txt.open(_i_iteracion);//apertura del fichero
	std::string _iteracion;
    std::cout<<_i_iteracion<<std::endl;
	if(_pasos_txt.fail()){//comprobacion de la apertura del fichero
		std::cout<<"Error al abrir el archivo de sonido/pasos" << _i_iteracion <<std::endl;
		exit(0);
	}

    _pasos_txt>>_iteracion;
    ERRCHECK( system->loadBankFile(_iteracion.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &PasosBank) );
     _pasos_txt>>_iteracion;//obtiene el valor de la id del origenre
	_n_pasos = std::atoi(_iteracion.c_str());

    _eventos_pasos= new Evento_pasos*[_n_pasos];

    cont=0;
    do{
        _pasos_txt >> _iteracion;
        _eventos_pasos[cont] = new Evento_pasos(_iteracion, system);
        ++cont;
    }while(cont<_n_pasos);

    _pasos_txt.close();
}
void Interfaz_sonido::crear_personaje(std::string _i_iteracion){
    uint8_t cont=0;
    std::ifstream _personaje_txt;    
    _personaje_txt.open(_i_iteracion);//apertura del fichero
	std::string _iteracion;
    std::cout<<_i_iteracion<<std::endl;
	if(_personaje_txt.fail()){//comprobacion de la apertura del fichero
		std::cout<<"Error al abrir el archivo de sonido/personaje" << _i_iteracion <<std::endl;
		exit(0);
	}

    _personaje_txt>>_iteracion;
    ERRCHECK( system->loadBankFile(_iteracion.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &PersonajeBank) );
     _personaje_txt>>_iteracion;//obtiene el valor de la id del origenre
	_n_personaje = std::atoi(_iteracion.c_str());

    _eventos_personaje= new Evento_personaje*[_n_personaje];

    cont=0;
    do{
        _personaje_txt >> _iteracion;
        _eventos_personaje[cont] = new Evento_personaje(_iteracion, system);
        ++cont;
    }while(cont<_n_personaje);

    _personaje_txt.close();
}
void Interfaz_sonido::crear_voces(std::string _i_iteracion){
    uint8_t cont=0;
    std::ifstream _voces_txt;    
    _voces_txt.open(_i_iteracion);//apertura del fichero
	std::string _iteracion;
    std::cout<<_i_iteracion<<std::endl;
	if(_voces_txt.fail()){//comprobacion de la apertura del fichero
		std::cout<<"Error al abrir el archivo de sonido/voces" << _i_iteracion <<std::endl;
		exit(0);
	}

    _voces_txt>>_iteracion;
    ERRCHECK( system->loadBankFile(_iteracion.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &VocesBank) );
     _voces_txt>>_iteracion;//obtiene el valor de la id del origenre
	_n_voces = std::atoi(_iteracion.c_str());

    _eventos_voces= new Evento_voces*[_n_voces];

    cont=0;
    do{
        _voces_txt >> _iteracion;
        _eventos_voces[cont] = new Evento_voces(_iteracion, system);
        ++cont;
    }while(cont<_n_voces);

    _voces_txt.close();
}
void Interfaz_sonido::crear_musica(std::string _i_iteracion){
    uint8_t cont=0;
    std::ifstream _musica_txt;    
    _musica_txt.open(_i_iteracion);//apertura del fichero
	std::string _iteracion;
    std::cout<<_i_iteracion<<std::endl;
	if(_musica_txt.fail()){//comprobacion de la apertura del fichero
		std::cout<<"Error al abrir el archivo de sonido/musica" << _i_iteracion <<std::endl;
		exit(0);
	}

    _musica_txt>>_iteracion;
    ERRCHECK( system->loadBankFile(_iteracion.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &MusicaBank) );
     _musica_txt>>_iteracion;//obtiene el valor de la id del origenre
	_n_musica = std::atoi(_iteracion.c_str());

    _eventos_musica= new Evento_musica*[_n_musica];

    cont=0;
    do{
        _musica_txt >> _iteracion;
        _eventos_musica[cont] = new Evento_musica(_iteracion, system);
        ++cont;
    }while(cont<_n_musica);

    _musica_txt.close();
}
void Interfaz_sonido::crear_canales(std::string _i_iteracion){
    uint8_t cont=0;
    std::ifstream _canales_txt;    
    _canales_txt.open(_i_iteracion);//apertura del fichero
	std::string _iteracion;
    std::cout<<_i_iteracion<<std::endl;
	if(_canales_txt.fail()){//comprobacion de la apertura del fichero
		std::cout<<"Error al abrir el archivo de sonido/canales" << _i_iteracion <<std::endl;
		exit(0);
	}

    

    
    
    //ERRCHECK(system->getBus(_iteracion.c_str(),_chanel_voces));


    _canales_txt >> _iteracion;
    ERRCHECK(system->getBus(_iteracion.c_str(),&_bus_musica));//carga de menu

    _canales_txt >> _iteracion;
    ERRCHECK(system->getBus(_iteracion.c_str(),&_bus_voces));//carga de sfx

    _canales_txt >> _iteracion;
    ERRCHECK(system->getBus(_iteracion.c_str(),&_bus_sfx));//carga de voces

    _canales_txt >> _iteracion;
    ERRCHECK(system->getBus(_iteracion.c_str(),&_bus_menu));//carga de voces

    _bus_sfx->lockChannelGroup();

    _canales_txt.close();
}

/***************************************PLAY SONIDOS***********************************************/

void Interfaz_sonido::Play_ambiente(uint8_t _i_n){
    if(_i_n>=_n_ambiente){
        std::cout<<"ERROR SONIDO: ambiente solicitado no existente: "<<(int)_i_n<<std::endl;
        exit(0);
    }
    _eventos_ambiente[_i_n]->start();
    system_update();
}
void Interfaz_sonido::Play_armas(uint8_t _i_n){
    if(_i_n>=_n_armas){
        std::cout<<"ERROR SONIDO: armas solicitado no existente: "<<(int)_i_n<<std::endl;
        exit(0);
    }
    _eventos_armas[_i_n]->start();
    system_update();
}
void Interfaz_sonido::Play_consumibles(uint8_t _i_n){
    if(_i_n>=_n_consumibles){
        std::cout<<"ERROR SONIDO: consumible solicitado no existente: "<<(int)_i_n<<std::endl;
        exit(0);
    }
    _eventos_consumibles[_i_n]->start();
    system_update();
}
void Interfaz_sonido::Play_escenario(uint8_t _i_n){
    if(_i_n>=_n_escenario){
        std::cout<<"ERROR SONIDO: escenario solicitado no existente: "<<(int)_i_n<<std::endl;
        exit(0);
    }
    _eventos_escenario[_i_n]->start();
    system_update();
}
void Interfaz_sonido::Play_menu(uint8_t _i_n){
    if(_i_n>=_n_menu){
        std::cout<<"ERROR SONIDO: menu solicitado no existente: "<<(int)_i_n<<std::endl;
        exit(0);
    }
    _eventos_menu[_i_n]->start();
    system_update();
}
void Interfaz_sonido::Play_personaje(uint8_t _i_n){
    if(_i_n>=_n_personaje){
        std::cout<<"ERROR SONIDO: personaje solicitado no existente: "<<(int)_i_n<<std::endl;
        exit(0);
    }
    _eventos_personaje[_i_n]->start();
    system_update();
}
void Interfaz_sonido::Play_voces(uint8_t _i_n){
    if(_i_n>=_n_voces){
        std::cout<<"ERROR SONIDO: voce solicitado no existente: "<<(int)_i_n<<std::endl;
        exit(0);
    }
    _eventos_voces[_i_n]->start();
    system_update();
}
void Interfaz_sonido::Play_pasos(uint8_t _i_n){
    if(_i_n>=_n_pasos){
        std::cout<<"ERROR SONIDO: paso solicitado no existente: "<<(int)_i_n<<std::endl;
        exit(0);
    }
    _eventos_pasos[_i_n]->start();
    system_update();
}
void Interfaz_sonido::Play_musica(uint8_t _i_n){
    if(_i_n>=_n_musica){
        std::cout<<"ERROR SONIDO: musica solicitado no existente: "<<(int)_i_n<<std::endl;
        exit(0);
    }
    _eventos_musica[_i_n]->start();
    system_update();
}


/***************************************STOP SONIDOS***********************************************/

/*void Interfaz_sonido::Stop_pasos(uint8_t _i_n){
    if(_i_n>=_n_pasos){
        std::cout<<"ERROR SONIDO: paso solicitado no existente: "<<(int)_i_n<<std::endl;
        exit(0);
    }
    _eventos_pasos[_i_n]->stop();
    system_update();
}*/
void Interfaz_sonido::Stop_ambiente(uint8_t _i_n){
    if(_i_n>=_n_ambiente){
        std::cout<<"ERROR SONIDO: ambiente solicitado no existente: "<<(int)_i_n<<std::endl;
        exit(0);
    }
    _eventos_ambiente[_i_n]->stop();
    system_update();
}
void Interfaz_sonido::Stop_musica(uint8_t _i_n){
    if(_i_n>=_n_musica){
        std::cout<<"ERROR SONIDO: musica solicitado no existente: "<<(int)_i_n<<std::endl;
        exit(0);
    }
    _eventos_musica[_i_n]->stop();
    system_update();
}
void Interfaz_sonido::Stop_game(){
    uint8_t cont=_n_ambiente;
    while(cont){
        --cont;
        Stop_ambiente(cont);
    }
    cont=_n_musica;
    while(cont){
        --cont;
        Stop_musica(cont);
    }

}
/***************************************VOLUMEN SONIDOS***********************************************/

void Interfaz_sonido::set_volumen_musica(float _i_v){
    ERRCHECK(_bus_musica->setVolume(_i_v));
    system_update();
}
void Interfaz_sonido::set_volumen_voces(float _i_v){
    ERRCHECK(_bus_voces->setVolume(_i_v));
    system_update();
}
void Interfaz_sonido::set_volumen_sfx(float _i_v){
    ERRCHECK(_bus_sfx->setVolume(_i_v));
    system_update();
}
void Interfaz_sonido::set_volumen_menu(float _i_v){
    ERRCHECK(_bus_menu->setVolume(_i_v));
    system_update();
}


/*******************************************PAUSA**************************************************/
void Interfaz_sonido::Pausa(){
    ERRCHECK(_bus_musica->setPaused(true));
    ERRCHECK(_bus_voces->setPaused(true));
    ERRCHECK(_bus_sfx->setPaused(true));
    ERRCHECK(_bus_menu->setPaused(true));
}
void Interfaz_sonido::Quitar_pausa(){
   /* uint8_t cont=_n_pasos;
    while(cont){
        --cont;
        _eventos_pasos[cont]->quit_pause();
    }*/
    //_eventos_pasos[0]->quit_pause();
}
