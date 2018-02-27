#ifndef SRC_Trampas_manager_H_
#define SRC_Trampas_manager_H_

class Minas;
class Pinchos;

class Trampas_manager{
public:
	Trampas_manager();
	virtual ~Trampas_manager();

	unsigned short get_n_trampas_mina();
	unsigned short get_n_trampas_pincho();

	Minas** get_trampas_mina();
	Pinchos** get_trampas_pinchos();

	void borra_mina(short _i_id);
	void borrar_mina();


private:
	Minas ** _minas;
	Pinchos ** _pinchos;

	unsigned short _n_minas;
	unsigned short _n_pinchos;



};

#endif /* SRC_Trampas_manager_H_ */
