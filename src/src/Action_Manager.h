#ifndef SRC_ACTION_MANAGER_H_
#define SRC_ACTION_MANAGER_H_

class Character;
class Interfaz_Datos;
class NPC;
class Path_Manager;

class Action_Manager {
public:
	Action_Manager();
	virtual ~Action_Manager();

	void realiza_accion(NPC* _i_npc);

	void mover(Character* _i_personaje, unsigned short _i_direccion);

	Interfaz_Datos* get_interfaz();
    
    void comprobar_objetos_interactuables_cercanos(Character* _i_personaje);

	void atacar(Character* _i_personaje);

private:
	Interfaz_Datos *_interfaz_decision; 	//Interfaz que permite la comunicacion entre toma de decision y datos
	Path_Manager *_path_manager; 					//Path manager que busca el camino a seguir para el enemigo

};

#endif /* SRC_ACTION_MANAGER_H_ */
