#ifndef SRC_ACTION_MANAGER_H_
#define SRC_ACTION_MANAGER_H_

class Character;
class Interfaz_Toma_Decision;
class NPC;
class Path_Manager;

class Action_Manager {
public:
	Action_Manager();
	virtual ~Action_Manager();

	void realiza_accion(NPC* _i_npc);

	void mover(Character* _i_personaje, unsigned short _i_direccion);

	Interfaz_Toma_Decision* get_interfaz();

private:
	Interfaz_Toma_Decision *_interfaz_decision; 	//Interfaz que permite la comunicacion entre toma de decision y datos
	Path_Manager *_path_manager; 					//Path manager que busca el camino a seguir para el enemigo

};

#endif /* SRC_ACTION_MANAGER_H_ */
