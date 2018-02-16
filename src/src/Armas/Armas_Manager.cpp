#include "Armas_Manager.h"
#include "../Tiempo/Time.h"
#include "Arma.h"

 #include "AD_Ametralladora.h"
 #include "AC_Katana.h"
 #include "AD_Pistola.h"
 #include "../Nivel/Nivel.h"
#include "../Tiempo/Time.h"


// CONSTRUCTOR

Armas_Manager::Armas_Manager() {
    
    float mult = 4.9212625;
	_armas.push_back(new AD_Ametralladora(5,mult*18, mult*0, mult*15));
    
    _armas.push_back(new AC_Katana(5,mult*10, mult*0, mult*10));


    _numero_max = 3;

    Nivel* _nivel = Nivel::nivel_instancia();

    _nivel->nivel_get_numero_posiciones_spawn(cantidad_de_posiciones);
    posiciones = new float*[cantidad_de_posiciones];
    
    for(short i=0; i<cantidad_de_posiciones; i++){
         posiciones[i] = new float[2];
    }
    _nivel->nivel_get_posiciones_spawn(posiciones);

}

// DESTRUCTOR

Armas_Manager::~Armas_Manager(){
    
 for (short i = 0; i < _armas.size(); i++) {
    delete _armas[i];
  }
  _armas.clear();
  
    for (uint16_t i = 0; i<cantidad_de_posiciones; i++){
    delete[] posiciones[i];
  }
  delete[] posiciones;


}


// METODOS BORRAR

void Armas_Manager::borrar_arma(Arma* objeto){

    std::vector<Arma*>::iterator it;
    it = std::find(_armas.begin(), _armas.end(), objeto);
    if ( it != _armas.end()){
        _armas.erase(it);
        delete objeto;
    }
   
}

void Armas_Manager::borrar_arma(short id){
    delete _armas[id];
    _armas.erase(_armas.begin() + id);
}


/* -----------------    Metodos crear      ---------------- */


//---------------------------------- MAPEADOS PARA LAS ARMAS --------------------------//

	// Funciones para guardar los datos
	struct MapeadArmas{			// Declaracion de los parametros
		Enum_Nombre_Arma _nombre_objeto;
		void (Armas_Manager::*pmet)();
	};

	MapeadArmas mapping_tipo_arma_creada[] = {	// Definicion de los parametros
			{Nombre_Arma_Katana, &Armas_Manager::crear_katana},
			{Nombre_Arma_Ametralladora, &Armas_Manager::crear_ametralladora},
			{Nombre_Arma_Arco, &Armas_Manager::crear_pistola},
			{Nombre_Arma_Bazooka, &Armas_Manager::crear_pistola},
			{Nombre_Arma_Pistola, &Armas_Manager::crear_pistola},
			{Nombre_Arma_Nada, &Armas_Manager::crear_pistola}
	};


void Armas_Manager::anyadir_arma(){
    std::cout << " CREA UN ARMA \n" ;


    //Comprobar que arma va a crear
    MapeadArmas *_mapeado_clase = mapping_tipo_arma_creada;
	Enum_Nombre_Arma _arma = static_cast<Enum_Nombre_Arma>(rand() % Nombre_Arma_Nada);

    std::cout << _arma << "arma que crea" << std::endl;
	while(_mapeado_clase->_nombre_objeto!=Nombre_Arma_Nada){
		if(_arma == _mapeado_clase->_nombre_objeto){
			(this->*_mapeado_clase->pmet)();
		}
		++_mapeado_clase;   
	}
}

void Armas_Manager::crear_todas_las_armas_que_faltan(){
  
    for(uint16_t i=_armas.size(); i<_numero_max; i++){
       anyadir_arma();
    }
}

void Armas_Manager::crear_ametralladora(){
    Vector2 posicion = crear_posiciones_aleatorias();

	_armas.push_back(new AD_Ametralladora(5, posicion._x, 0, posicion._y));
}

void Armas_Manager::crear_pistola(){   
     Vector2 posicion = crear_posiciones_aleatorias();
	_armas.push_back(new AD_Pistola(5, posicion._x, 0, posicion._y));
}
void Armas_Manager::crear_katana(){
    Vector2 posicion = crear_posiciones_aleatorias();
	_armas.push_back(new AC_Katana(5, posicion._x, 0, posicion._y));
}


Vector2 Armas_Manager::crear_posiciones_aleatorias(){

    uint8_t posicion_al_azar;
    posicion_al_azar=rand() % cantidad_de_posiciones;

    return Vector2(posiciones[posicion_al_azar][0],posiciones[posicion_al_azar][1]);
}




/*
void Armas_Manager::crear_ametralladora(Vector2 posicion){
	_armas.push_back(new AD_Ametralladora(5, posicion._x, 0, posicion._y));
}
*/
/// METODOS GET 

std::vector<Arma*>* Armas_Manager::get_armas(){
    return &_armas;
}

