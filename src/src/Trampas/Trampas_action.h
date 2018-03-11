#ifndef SRC_Trampas_action_H_
#define SRC_Trampas_action_H_

class Minas;
class Pinchos;
class Trampas_manager;


class Trampas_action{
public:
	Trampas_action();
	virtual ~Trampas_action();

	void comprobar_trampas_mina();
	void eliminar_trampas_mina();
	Pinchos** comprobar_trampas_pinchos();
	void update();

private:

	Minas ** _minas;
	Pinchos ** _pinchos;
	Trampas_manager* _trampas;

};

#endif /* SRC_Trampas_action_H_ */
