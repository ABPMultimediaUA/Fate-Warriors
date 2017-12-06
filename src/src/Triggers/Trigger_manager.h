#ifndef SRC_Trigger_manager_H_
#define SRC_Trigger_manager_H_

class Player;
class TriggerRegion_space;
class NPC;

class Trigger_manager {
public:
	Trigger_manager();
	virtual ~Trigger_manager();

	void toma_decisiones();
	void realiza_acciones();

private:
	//NPCs
	NPC** _enemigos;

	//Jugador
	Player* _jugador;
  
	//Triggers
	TriggerRegion_space ** _triggers;

};

#endif /* SRC_Trigger_manager_H_ */
