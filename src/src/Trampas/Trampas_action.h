#ifndef SRC_Trampas_action_H_
#define SRC_Trampas_action_H_

class Minas;
class Pinchos;
class Charcos_electrificados;
class Trampas_manager;
class Player;

class Trampas_action{
public:
	Trampas_action();
	virtual ~Trampas_action();

	void comprobar_trampas_mina();
	void eliminar_trampas_mina();
	Charcos_electrificados** comprobar_trampas_charco();
	Pinchos** comprobar_trampas_pinchos();
	void update();

private:

	Minas ** _minas;
	Charcos_electrificados ** _charcos;
	Pinchos ** _pinchos;
	Trampas_manager* _trampas;
	Player * _player;

};

#endif /* SRC_Trampas_action_H_ */
