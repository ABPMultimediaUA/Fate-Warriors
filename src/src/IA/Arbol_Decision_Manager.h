#ifndef SRC_ARBOL_DECISION_MANAGER_H_
#define SRC_ARBOL_DECISION_MANAGER_H_

#include <fstream>
#include <cstdint>

#include "Enum_Acciones.h"

class Blackboard;
class Nodo_Decision;
class Nodo_Decision_Final;

class Arbol_Decision_Manager {
public:
	Arbol_Decision_Manager();
	virtual ~Arbol_Decision_Manager();

	enum Enum_Acciones _tomar_decision(Blackboard* _blackboard);

	void crear_nodo_final(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision*& _i_izq, Nodo_Decision*& _i_der, uint8_t _i_id);
	void crear_nodo_medio(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision*& _i_izq, Nodo_Decision*& _i_der, uint8_t _i_id);
	void crear_nodo_error(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision*& _i_izq, Nodo_Decision*& _i_der, uint8_t _i_id);

	void crear_nodo_distancia(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id);
	void crear_nodo_lod(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id);
	void crear_nodo_rango_ataque_normal(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id); 

	
	enum Enum_Acciones get_nada();
	enum Enum_Acciones get_decidir();
	enum Enum_Acciones get_andar();
	enum Enum_Acciones get_atacar();
	enum Enum_Acciones get_coger_arma();
	enum Enum_Acciones get_usar_arma();
	enum Enum_Acciones get_saltar();
	enum Enum_Acciones get_protegerse();
	enum Enum_Acciones get_accionar();
	enum Enum_Acciones get_recibir_danyo();
	enum Enum_Acciones get_estar_derribado();
	enum Enum_Acciones get_error();

	void lee_fichero_y_crea_arbol(const std::string &_i_fichero);

private:
	uint16_t _max_nodos;
	uint8_t _max_arboles;

	uint16_t _n_nodos;
	uint8_t _n_arboles;

	//Nodos de decision
	Nodo_Decision** _nodos_decision;

	//Asignaciones de nodos que forman arboles
	Nodo_Decision** _arboles_decision;

	//Nodos acciones
	Nodo_Decision_Final** _acciones;
};

#endif /* SRC_ARBOL_DECISION_MANAGER_H_ */
