#include "Arbol_Decision_Manager.h"

#include <iostream>
#include <string>

#include "Blackboard.h"
#include "Nodos_Decision.h"

//NOMBRE DEL FICHERO DEL ARBOL
const std::string _fichero = "txt/Arbol_Decision.txt";

Arbol_Decision_Manager::Arbol_Decision_Manager() {
	_max_nodos = 3;
	_max_arboles = 1;

	_n_nodos = 0;
	_n_arboles = 0;

	//Creacion de las aciones
	_acciones = new Nodo_Decision_Final*[n_acciones];
	for(unsigned short _cont = 0; _cont < n_acciones; _cont++) {
		_acciones[_cont] = new Nodo_Decision_Final((Enum_Acciones)_cont);
	}

	//Creacion de los nodos
	_nodos_decision = new Nodo_Decision*[_max_nodos];

	//Lectura de fichero y eso [COMING SOON]
	_nodos_decision[0] = new Nodo_Decision_Distancia(*_acciones[Atacar], *_acciones[Andar], 3); _n_nodos++;
	_nodos_decision[1] = new Nodo_Decision_Distancia(*_acciones[Atacar], *_acciones[Andar], 3); _n_nodos++;
	_nodos_decision[2] = new Nodo_Decision_LOD(*_nodos_decision[0], *_nodos_decision[1], 1); _n_nodos++;
	

	lee_fichero_y_crea_arbol(_fichero);

	//Asignacion de los arboles
	_arboles_decision = new Nodo_Decision*[_max_arboles];

	_arboles_decision[0] = _nodos_decision[0];

}

Arbol_Decision_Manager::~Arbol_Decision_Manager() {
	//Desasignar arboles
	for(unsigned short _cont = 0; _cont < _n_arboles; _cont++) {
		_arboles_decision[_cont] = nullptr;
	}
	delete [] _arboles_decision;

	//Borrar nodos
	for(unsigned short _cont = 0; _cont < _n_nodos; _cont++) {
		delete _nodos_decision[_cont];
	}
	delete [] _nodos_decision;

	//Borrar acciones
	for(unsigned short _cont = 0; _cont < n_acciones; _cont++) {
		delete _acciones[_cont];
	}
	delete [] _acciones;
}


enum Enum_Acciones Arbol_Decision_Manager::_tomar_decision(Blackboard* _blackboard) {
	return _arboles_decision[_blackboard->get_tipo_enemigo()]->toma_decision(_blackboard);
}




//-------------------------------------- FUNCIONES PARA ENUM DE ACCION -------------------------//

	enum Enum_Acciones Arbol_Decision_Manager::get_andar(){
		return Andar;
	}
	enum Enum_Acciones Arbol_Decision_Manager::get_atacar(){
		return Atacar;
	}
	enum Enum_Acciones Arbol_Decision_Manager::get_error(){
		return Error;
	}

//------------------------------------ FIN FUNCIONES PARA ENUM DE ACCION -----------------------//





//-------------------------------------- MAPEADOS PARA ENUM DE ACCION -------------------------//

	// Funciones para guardar los datos
	struct MapeadoAccion{			// Declaracion de los parametros
		const char* _nombre_objeto;
		enum Enum_Acciones (Arbol_Decision_Manager::*pmet)();
	};

	MapeadoAccion mapping_enum_acciones[] = {	// Definicion de los parametros
			{"Andar", &Arbol_Decision_Manager::get_andar},
			{"Atacar", &Arbol_Decision_Manager::get_atacar},
			{0, &Arbol_Decision_Manager::get_error}
	};

//-------------------------------------- FIN MAPEADOS PARA CREAR NODOS-------------------------//





// ------------------------------------- FUNCIONES DE TIPO NODOS -----------------------------//


void Arbol_Decision_Manager::crear_nodo_final(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _izq, Nodo_Decision* _der, uint8_t _i_id) {
	enum Enum_Acciones _accion_izq, _accion_der;
	MapeadoAccion *_next_function;

	// LECTURA DE NODO IZQUIERDO
	_i_arbol_txt >> _i_iteracion;			// Lectura de la accion del nodo izuquierdo

	// Get accion
	_next_function = mapping_enum_acciones;
	while(_next_function->_nombre_objeto){
		if(_i_iteracion == _next_function->_nombre_objeto){
			_accion_izq = (this->*_next_function->pmet)();
		}

		++_next_function;
	}

	// LECTURA DE NODO DERECHO
	_i_arbol_txt >> _i_iteracion;			// Lectura de la accion del nodo derecho

	// Get accion
	_next_function = mapping_enum_acciones;
	while(_next_function->_nombre_objeto){
		if(_i_iteracion == _next_function->_nombre_objeto){
			_accion_der = (this->*_next_function->pmet)();
		}

		++_next_function;
	}


	// OBTENCION DE LAS ACCIONES
	_izq = _acciones[_accion_izq];
	_der = _acciones[_accion_der];

	// CONTROL DE ERRORES
	if(_izq == nullptr || _der == nullptr) {
		std::cout << "\n\nError buscar los nodos finales del nodo con id = " << (int)_i_id << "\n";
		if(_izq == nullptr) std::cout << "\nHubo un error con el nodo izquierdo\n";
		if(_der == nullptr) std::cout << "\nHubo un error con el nodo derecho\n";

		std::cout << std::endl;
		exit(0);
	}
}

void Arbol_Decision_Manager::crear_nodo_medio(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _izq, Nodo_Decision* _der, uint8_t _i_id) {
	uint8_t _id_izq, _id_der;

	// LECTURA DE NODO IZQUIERDO
	_i_arbol_txt >> _i_iteracion;			// Lectura de la accion del nodo izuquierdo

	// Get accion
	_id_izq = std::atoi(_i_iteracion.c_str());
	

	// LECTURA DE NODO DERECHO
	_i_arbol_txt >> _i_iteracion;			// Lectura de la accion del nodo derecho

	// Get accion
	_id_der = std::atoi(_i_iteracion.c_str());


	// OBTENCION DE LAS ACCIONES (con control)
	if(_id_izq < _n_nodos)
		_izq = _nodos_decision[_id_izq];
	if(_id_der < _n_nodos)
		_der = _nodos_decision[_id_der];

	// CONTROL DE ERRORES
	if(_izq == nullptr || _der == nullptr) {
		std::cout << "\n\nError buscar los nodos medios del nodo con id = " << (int)_i_id << "\n";
		if(_izq == nullptr) std::cout << "\nHubo un error con el nodo izquierdo, que tiene de id = " << (int)_id_izq <<"\n";
		if(_der == nullptr) std::cout << "\nHubo un error con el nodo derecho, que tiene de id = " << (int)_id_der <<"\n";

		std::cout << std::endl;
		exit(0);
	}
}

// ------------------------------------ FIN FUNCIONES TIPO NODOS -----------------------------//





// ------------------------------------- FUNCIONES CREACION CLASES NODOS -----------------------------//

	void Arbol_Decision_Manager::crear_nodo_distancia(std::ifstream& _i_arbol_txt, std::string& _i_iteracion) {
		std::cout << std::endl << "NODO DISTANCIA" << std::endl;

	}

	void Arbol_Decision_Manager::crear_nodo_lod(std::ifstream& _i_arbol_txt, std::string& _i_iteracion) {
		std::cout << std::endl << "NODO LOD" << std::endl;

	}

	void Arbol_Decision_Manager::crear_nodo_rango_ataque_normal(std::ifstream& _i_arbol_txt, std::string& _i_iteracion) {
		std::cout << std::endl << "NODO RANGO NORMAL" << std::endl;

	}

// ------------------------------------ FIN FUNCIONES CREACION CLASES NODOS  -----------------------------//





//-------------------------------------- MAPEADOS PARA CREAR NODOS -------------------------//

	// Funciones para guardar los datos
	struct MapeadoNodo{			// Declaracion de los parametros
		const char* _nombre_objeto;
		void (Arbol_Decision_Manager::*pmet)(std::ifstream&, std::string&, Nodo_Decision* _izq, Nodo_Decision* _der, uint8_t _i_id);
	};

	MapeadoNodo mapping_tipo_nodo[] = {	// Definicion de los parametros
			{"Final", &Arbol_Decision_Manager::crear_nodo_final},
			{"Medio", &Arbol_Decision_Manager::crear_nodo_medio},
			{0, 0}
	};


	// Funciones para guardar los datos
	struct MapeadoClaseNodo{			// Declaracion de los parametros
		const char* _nombre_objeto;
		void (Arbol_Decision_Manager::*pmet)(std::ifstream&, std::string&);
	};

	MapeadoClaseNodo mapping_clase_nodo[] = {	// Definicion de los parametros
			{"Distancia", &Arbol_Decision_Manager::crear_nodo_distancia},
			{"LOD", &Arbol_Decision_Manager::crear_nodo_lod},
			{"Rango_Ataque_Normal", &Arbol_Decision_Manager::crear_nodo_rango_ataque_normal},
			{0, 0}
	};

//-------------------------------------- FIN MAPEADOS PARA CREAR NODOS -------------------------//







//---------------------------------------- LECTURA Y TRATAMIENTO DE FICHERO ----------------------//

void Arbol_Decision_Manager::lee_fichero_y_crea_arbol(const std::string &_i_fichero) {
	uint8_t _id;
	std::ifstream _arbol_txt;
	MapeadoNodo *_next_function;
	MapeadoClaseNodo *_mapeado_clase;
	Nodo_Decision *_izq, *_der;

	_arbol_txt.open(_i_fichero); 			// Apertura del fichero
	std::string _iteracion;

	if(_arbol_txt.fail()){ 					// Comprobacion de la apertura del fichero
		std::cout << "\n\nError al abrir el archivo " << _fichero << "\n\n";
		exit(0);
	}

	_arbol_txt >> _iteracion;				// Lectura especial del primer id de Nodo
	
	while(_iteracion!="Fin"){
		_izq = nullptr;
		_der = nullptr;

		_arbol_txt >> _iteracion;			// Lectura id de Nodo FIN
		_id = std::atoi(_iteracion.c_str());
		std::cout << (int)_id << " ";


		// LECTURA DE TIPO DE NODO (MAPPING)
		_arbol_txt >> _iteracion;			// Lectura tipo de nodos hijos
		std::cout << _iteracion << " ";

		_next_function = mapping_tipo_nodo;
		
		while(_next_function->_nombre_objeto){
			if(_iteracion == _next_function->_nombre_objeto){
				(this->*_next_function->pmet)(_arbol_txt, _iteracion, _izq, _der, _id);
			}

			++_next_function;
		}

		
		// LECTURA DE TIPO DE NODO A CREAR (MAPPING)
		_arbol_txt >> _iteracion;			// Lectura tipo de Nodo a crear
		std::cout << _iteracion << " ";

		_mapeado_clase = mapping_clase_nodo;
		
		while(_mapeado_clase->_nombre_objeto){
			if(_iteracion == _mapeado_clase->_nombre_objeto){
				(this->*_mapeado_clase->pmet)(_arbol_txt,_iteracion);
			}

			++_mapeado_clase;
		}

		// LECTURA DE VALOR DE CORTE
		_arbol_txt >> _iteracion;			// Lectura valor de corte
		std::cout << _iteracion << std::endl;


		_arbol_txt >> _iteracion;			// Lectura valor de cambio de linea
	}

	exit(0);
}