#include "Arbol_Decision_Manager.h"

#include <iostream>
#include <string>

#include "Blackboard.h"
#include "Nodos_Decision.h"
#include "../Game.h"

//NOMBRE DEL FICHERO DEL ARBOL
const std::string _fichero = "txt/Arbol_Decision.txt";

Arbol_Decision_Manager::Arbol_Decision_Manager() {
	_max_arboles = 1;

	_n_nodos = 0;
	_n_arboles = 0;

	//Creacion de las aciones
	_acciones = new Nodo_Decision_Final*[n_acciones];
	for(unsigned short _cont = 0; _cont < n_acciones; _cont++) {
		_acciones[_cont] = new Nodo_Decision_Final((Enum_Acciones)_cont);
	}
	
	// Lectura del fichero del arbol y creacion dinamica
	lee_fichero_y_crea_arbol(_fichero);

	//Asignacion de los arboles
	_arboles_decision = new Nodo_Decision*[_max_arboles];

	//std::cout << "N nodos " << _n_nodos << "\n";
	_arboles_decision[0] = _nodos_decision[2]; // Padre del arbol

}

Arbol_Decision_Manager::~Arbol_Decision_Manager() {
	//Desasignar arboles
	_arboles_decision[0] = nullptr;
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
	return _arboles_decision[0]->toma_decision(_blackboard);
}



//-------------------------------------- MAPEADOS PARA ENUM DE ACCION -------------------------//

	// Funciones para guardar los datos
	struct MapeadoAccion{			// Declaracion de los parametros
		const char* _nombre_objeto;
		enum Enum_Acciones (Arbol_Decision_Manager::*pmet)();
	};

	MapeadoAccion mapping_enum_acciones[] = {	// Definicion de los parametros
			{"Nada", &Arbol_Decision_Manager::get_nada},
			{"Andar", &Arbol_Decision_Manager::get_andar},
			{"Atacar", &Arbol_Decision_Manager::get_atacar},
			{"Esquivar", &Arbol_Decision_Manager::get_esquivar},
			{"Interactuar", &Arbol_Decision_Manager::get_interactuar},
			{0, &Arbol_Decision_Manager::get_error}
	};

//-------------------------------------- FIN MAPEADOS PARA CREAR NODOS-------------------------//





// ------------------------------------- FUNCIONES DE TIPO NODOS -----------------------------//

	// Nodo con Nodos de Accion como nodos hijos izquierdo y derecho
	void Arbol_Decision_Manager::crear_nodo_final(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision*& _i_izq, Nodo_Decision*& _i_der, uint8_t _i_id) {
		enum Enum_Acciones _accion_i_izq, _accion_i_der;
		MapeadoAccion *_next_function;

		// LECTURA DE NODO IZQUIERDO
		_i_arbol_txt >> _i_iteracion;			// Lectura de la accion del nodo izuquierdo

		// Get accion
		_next_function = mapping_enum_acciones;
		while(_next_function->_nombre_objeto){
			if(_i_iteracion == _next_function->_nombre_objeto){
				_accion_i_izq = (this->*_next_function->pmet)();
			}

			++_next_function;
		}

		// LECTURA DE NODO DERECHO
		_i_arbol_txt >> _i_iteracion;			// Lectura de la accion del nodo derecho

		// Get accion
		_next_function = mapping_enum_acciones;
		while(_next_function->_nombre_objeto){
			if(_i_iteracion == _next_function->_nombre_objeto){
				_accion_i_der = (this->*_next_function->pmet)();
			}

			++_next_function;
		}


		// OBTENCION DE LAS ACCIONES
		_i_izq = _acciones[_accion_i_izq];
		_i_der = _acciones[_accion_i_der];

		// CONTROL DE ERRORES
		if(_i_izq == nullptr || _i_der == nullptr) {
			std::cerr << "\n\nError buscar los nodos finales del nodo con id = " << (int)_i_id << "\n";
			if(_i_izq == nullptr) std::cerr << "\nHubo un error con el nodo de accion izquierdo\n";
			if(_i_der == nullptr) std::cerr << "\nHubo un error con el nodo de accion derecho\n";

			std::cerr << std::endl;
			exit(0);
		}
	}

	// Nodo de Decision sin Nodos de Accion como hijos
	void Arbol_Decision_Manager::crear_nodo_medio(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision*& _i_izq, Nodo_Decision*& _i_der, uint8_t _i_id) {
		uint8_t _id_i_izq, _id_i_der;

		// LECTURA DE NODO IZQUIERDO
		_i_arbol_txt >> _i_iteracion;			// Lectura de la accion del nodo izuquierdo

		// Get accion
		_id_i_izq = std::atoi(_i_iteracion.c_str());
		

		// LECTURA DE NODO DERECHO
		_i_arbol_txt >> _i_iteracion;			// Lectura de la accion del nodo derecho

		// Get accion
		_id_i_der = std::atoi(_i_iteracion.c_str());


		// OBTENCION DE LAS ACCIONES (con control)
		if(_id_i_izq < _n_nodos)
			_i_izq = _nodos_decision[_id_i_izq];
		if(_id_i_der < _n_nodos)
			_i_der = _nodos_decision[_id_i_der];

		// CONTROL DE ERRORES
		if(_i_izq == nullptr || _i_der == nullptr) {
			std::cerr << "\n\nError buscar los nodos medios del nodo con id = " << (int)_i_id << "\n";
			if(_i_izq == nullptr) std::cerr << "\nHubo un error con el nodo izquierdo, que tiene de id = " << (int)_id_i_izq <<"\n";
			if(_i_der == nullptr) std::cerr << "\nHubo un error con el nodo derecho, que tiene de id = " << (int)_id_i_der <<"\n";

			std::cerr << std::endl;
			exit(0);
		}
	}

	// Nodo de Decision con un Nodo de Accion como hijo izquierdo
	void Arbol_Decision_Manager::crear_nodo_izquierda(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision*& _i_izq, Nodo_Decision*& _i_der, uint8_t _i_id) {
		enum Enum_Acciones _accion_i_izq;
		uint8_t _id_i_der;
		MapeadoAccion *_next_function;

		// LECTURA DE NODO IZQUIERDO
		_i_arbol_txt >> _i_iteracion;			// Lectura de la accion del nodo izuquierdo

		// Get accion
		_next_function = mapping_enum_acciones;
		while(_next_function->_nombre_objeto){
			if(_i_iteracion == _next_function->_nombre_objeto){
				_accion_i_izq = (this->*_next_function->pmet)();
			}

			++_next_function;
		}
		

		// LECTURA DE NODO DERECHO
		_i_arbol_txt >> _i_iteracion;			// Lectura de la accion del nodo derecho

		// Get accion
		_id_i_der = std::atoi(_i_iteracion.c_str());


		// OBTENCION DE LAS ACCIONES
		_i_izq = _acciones[_accion_i_izq];
		if(_id_i_der < _n_nodos)
			_i_der = _nodos_decision[_id_i_der];

		// CONTROL DE ERRORES
		if(_i_izq == nullptr || _i_der == nullptr) {
			std::cerr << "\n\nError buscar los nodos finales del nodo con id = " << (int)_i_id << "\n";
			if(_i_izq == nullptr) std::cerr << "\nHubo un error con el nodo de accion izquierdo\n";
			if(_i_der == nullptr) std::cerr << "\nHubo un error con el nodo derecho, que tiene de id = " << (int)_id_i_der <<"\n";

			std::cerr << std::endl;
			exit(0);
		}
	}

	// Nodo de Decision con un Nodo de Accion como hijo derecho
	void Arbol_Decision_Manager::crear_nodo_derecha(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision*& _i_izq, Nodo_Decision*& _i_der, uint8_t _i_id) {
		enum Enum_Acciones _accion_i_der;
		uint8_t _id_i_izq;
		MapeadoAccion *_next_function;

		// LECTURA DE NODO IZQUIERDO
		_i_arbol_txt >> _i_iteracion;			// Lectura de la accion del nodo izuquierdo

		// Get accion
		_id_i_izq = std::atoi(_i_iteracion.c_str());
		

		// LECTURA DE NODO DERECHO
		_i_arbol_txt >> _i_iteracion;			// Lectura de la accion del nodo derecho

		// Get accion
		_next_function = mapping_enum_acciones;
		while(_next_function->_nombre_objeto){
			if(_i_iteracion == _next_function->_nombre_objeto){
				_accion_i_der = (this->*_next_function->pmet)();
			}

			++_next_function;
		}


		// OBTENCION DE LAS ACCIONES (con control)
		if(_id_i_izq < _n_nodos)
			_i_izq = _nodos_decision[_id_i_izq];
		_i_der = _acciones[_accion_i_der];

		// CONTROL DE ERRORES
		if(_i_izq == nullptr || _i_der == nullptr) {
			std::cerr << "\n\nError buscar los nodos medios del nodo con id = " << (int)_i_id << "\n";
			if(_i_izq == nullptr) std::cerr << "\nHubo un error con el nodo izquierdo, que tiene de id = " << (int)_id_i_izq <<"\n";
			if(_i_der == nullptr) std::cerr << "\nHubo un error con el nodo de accion derecho\n";

			std::cerr << std::endl;
			exit(0);
		}
	}

	void Arbol_Decision_Manager::crear_nodo_error(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision*& _i_izq, Nodo_Decision*& _i_der, uint8_t _i_id) {
		// CONTROL DE ERRORES
		std::cerr << "\n\nError al definir la situacion del nodo con id = " << (int)_i_id << "\n";
		std::cerr << std::endl;
		exit(0);
	}

// ------------------------------------- FIN FUNCIONES TIPO NODOS -----------------------------//





//---------------------------------- MAPEADOS DE TIPO DE NODOS --------------------------//

	// Funciones para guardar los datos
	struct MapeadoNodo{			// Declaracion de los parametros
		const char* _nombre_objeto;
		void (Arbol_Decision_Manager::*pmet)(std::ifstream&, std::string&, Nodo_Decision*& _i_izq, Nodo_Decision*& _i_der, uint8_t _i_id);
	};

	MapeadoNodo mapping_tipo_nodo[] = {	// Definicion de los parametros
			{"Final", &Arbol_Decision_Manager::crear_nodo_final},
			{"Medio", &Arbol_Decision_Manager::crear_nodo_medio},
			{"Izq", &Arbol_Decision_Manager::crear_nodo_izquierda},
			{"Der", &Arbol_Decision_Manager::crear_nodo_derecha},
			{0, &Arbol_Decision_Manager::crear_nodo_error}
	};

//-------------------------------- FIN MAPEADOS DE TIPO DE NODOS ------------------------//





// ------------------------------------- FUNCIONES CREACION CLASES NODOS -----------------------------//

	
	void Arbol_Decision_Manager::crear_ND_0(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id){
		//std::cout << std::endl << "NODO set_objetivo_personaje_enemigo_cerca" << std::endl;
		float _valor;

		// LECTURA DE VALOR DE CORTE
		_i_arbol_txt >> _i_iteracion;			// Lectura valor de corte
		//std::cout << _i_iteracion.c_str() << std::endl;

		// Almacenamiento y procesado del valor
		_valor = std::atof(_i_iteracion.c_str());

		_nodos_decision[_i_id] = new ND_0(*_i_izq, *_i_der, _valor); 
		_n_nodos++;
	}

	void Arbol_Decision_Manager::crear_ND_1(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id){
		//std::cout << std::endl << "NODO set_objetivo_personaje_enemigo_cerca" << std::endl;
		float _valor;

		// LECTURA DE VALOR DE CORTE
		_i_arbol_txt >> _i_iteracion;			// Lectura valor de corte
		//std::cout << _i_iteracion.c_str() << std::endl;

		// Almacenamiento y procesado del valor
		_valor = std::atof(_i_iteracion.c_str());

		_nodos_decision[_i_id] = new ND_1(*_i_izq, *_i_der, _valor); 
		_n_nodos++;
	}

	void Arbol_Decision_Manager::crear_ND_2(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id){
		//std::cout << std::endl << "NODO set_objetivo_personaje_enemigo_cerca" << std::endl;
		float _valor;

		// LECTURA DE VALOR DE CORTE
		_i_arbol_txt >> _i_iteracion;			// Lectura valor de corte
		//std::cout << _i_iteracion.c_str() << std::endl;

		// Almacenamiento y procesado del valor
		_valor = std::atof(_i_iteracion.c_str());

		_nodos_decision[_i_id] = new ND_2(*_i_izq, *_i_der, _valor); 
		_n_nodos++;
	}

	void Arbol_Decision_Manager::crear_ND_3(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id){
		//std::cout << std::endl << "NODO set_objetivo_personaje_enemigo_cerca" << std::endl;
		float _valor;

		// LECTURA DE VALOR DE CORTE
		_i_arbol_txt >> _i_iteracion;			// Lectura valor de corte
		//std::cout << _i_iteracion.c_str() << std::endl;

		// Almacenamiento y procesado del valor
		_valor = std::atof(_i_iteracion.c_str());

		_nodos_decision[_i_id] = new ND_3(*_i_izq, *_i_der, _valor); 
		_n_nodos++;
	}
	
	void Arbol_Decision_Manager::crear_nodo_lod(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id) {
		//std::cout << std::endl << "NODO LOD" << std::endl;
		uint8_t _valor;

		// LECTURA DE VALOR DE CORTE
		_i_arbol_txt >> _i_iteracion;			// Lectura valor de corte
		//std::cout << _i_iteracion << std::endl;
		_valor = std::atoi(_i_iteracion.c_str());

		_nodos_decision[_i_id] = new Nodo_Decision_LOD(*_i_izq, *_i_der, _valor); 
		_n_nodos++;
	}


// ------------------------------------ FIN FUNCIONES CREACION CLASES NODOS  -----------------------------//





//-------------------------------------- MAPEADOS PARA CREAR NODOS -------------------------//

	// Funciones para guardar los datos
	struct MapeadoClaseNodo{			// Declaracion de los parametros
		const char* _nombre_objeto;
		void (Arbol_Decision_Manager::*pmet)(std::ifstream&, std::string&, Nodo_Decision* _izq, Nodo_Decision* _der, uint8_t _i_id);
	};

	MapeadoClaseNodo mapping_clase_nodo[] = {	// Definicion de los parametros

			{"ND_3", &Arbol_Decision_Manager::crear_ND_3},
			{"ND_2", &Arbol_Decision_Manager::crear_ND_2},
			{"ND_1", &Arbol_Decision_Manager::crear_ND_1},
			{"ND_0", &Arbol_Decision_Manager::crear_ND_0},


			{"LOD", &Arbol_Decision_Manager::crear_nodo_lod},
			{0, 0}
	};

//-------------------------------------- FIN MAPEADOS PARA CREAR NODOS -------------------------//





//------------------------------------- LECTURA Y TRATAMIENTO DE FICHERO ----------------------//

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

	// Lectura del numero de Nodos
	_arbol_txt >> _iteracion;	
	_max_nodos = std::atoi(_iteracion.c_str());
		
	std::cout << "Nº de nodos " << _max_nodos;

	//Creacion de los nodos
	_nodos_decision = new Nodo_Decision*[_max_nodos];

	_arbol_txt >> _iteracion;				// Lectura especial del primer caracter de la linea del Nodo
	
	while(_iteracion!="Fin"){
		_izq = nullptr;
		_der = nullptr;

		_arbol_txt >> _iteracion;			// Lectura id de Nodo FIN
		_id = std::atoi(_iteracion.c_str());
		std::cout << (int)_id << " ";


		// LECTURA DE TIPO DE NODO (MAPPING)
		_arbol_txt >> _iteracion;			// Lectura tipo de nodos hijos

		_next_function = mapping_tipo_nodo;
		
		while(_next_function->_nombre_objeto){
			if(_iteracion == _next_function->_nombre_objeto){
				(this->*_next_function->pmet)(_arbol_txt, _iteracion, _izq, _der, _id);
			}

			++_next_function;
		}
		
		// LECTURA DE TIPO DE NODO A CREAR (MAPPING)
		_arbol_txt >> _iteracion;			// Lectura tipo de Nodo a crear

		_mapeado_clase = mapping_clase_nodo;
		
		while(_mapeado_clase->_nombre_objeto){
			if(_iteracion == _mapeado_clase->_nombre_objeto){
				(this->*_mapeado_clase->pmet)(_arbol_txt,_iteracion, _izq, _der, _id);
			}

			++_mapeado_clase;
		}

		_arbol_txt >> _iteracion;			// Lectura valor de cambio de linea
	}

	//exit(0);
}