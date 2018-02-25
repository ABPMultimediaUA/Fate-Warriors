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


	void crear_ND_5(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id);
	void crear_ND_6(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id);
	void crear_ND_11(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id);
	void crear_ND_12(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id);
	void crear_ND_15(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id);
	void crear_ND_16(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id);
	void crear_ND_18(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id);
	void crear_ND_19(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id);



	void crear_nodo_set_objetivo_personaje_enemigo_cerca(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id);
	void crear_nodo_distancia_objetivo(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id);
	void crear_nodo_lod(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id);
	void crear_nodo_vida_actual_prcnt(std::ifstream& _i_arbol_txt, std::string& _i_iteracion, Nodo_Decision* _i_izq, Nodo_Decision* _i_der, uint8_t _i_id); 


	
	inline enum Enum_Acciones get_nada() { return Nada;}
	inline enum Enum_Acciones get_andar() { return Andar;}
	inline enum Enum_Acciones get_atacar() { return Atacar;}
	inline enum Enum_Acciones get_esquivar() { return Accion_Dash;}
	inline enum Enum_Acciones get_interactuar() { return Accion_Interactuar;}

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
