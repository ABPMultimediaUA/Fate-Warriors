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
	void crear_nodo_izquierda(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision*& _i_izq, Nodo_Decision*& _i_der, uint8_t _i_id);
	void crear_nodo_derecha(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision*& _i_izq, Nodo_Decision*& _i_der, uint8_t _i_id);
	void crear_nodo_error(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision*& _i_izq, Nodo_Decision*& _i_der, uint8_t _i_id);

	void crear_nodo_distancia(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id);
	void crear_nodo_lod(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id);
	void crear_nodo_rango_ataque_normal(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id); 
	void crear_nodo_vida_actual_prcnt(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id); 


	
	inline enum Enum_Acciones get_nada() { return Nada;}
	inline enum Enum_Acciones get_decidir() { return Decidir;}
	inline enum Enum_Acciones get_andar() { return Andar;}
	inline enum Enum_Acciones get_atacar() { return Atacar;}
	inline enum Enum_Acciones get_coger_arma() { return Coger_Arma;}
	inline enum Enum_Acciones get_usar_arma() { return Usar_Arma;}
	inline enum Enum_Acciones get_saltar() { return Saltar;}
	inline enum Enum_Acciones get_accionar() { return Accionar;}
	inline enum Enum_Acciones get_recibir_danyo() { return Recibir_danyo;}
	inline enum Enum_Acciones get_estar_derribado() { return Estar_derribado;}
	inline enum Enum_Acciones get_huir() { return Huir;}
	inline enum Enum_Acciones get_error() { return Error;}

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
