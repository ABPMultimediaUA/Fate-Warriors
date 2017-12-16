#ifndef SRC_Trampas_manager_H_
#define SRC_Trampas_manager_H_

class Minas;
class Pinchos;
class Charcos_electrificados;

class Trampas_manager{
public:
	Trampas_manager();
	virtual ~Trampas_manager();

	unsigned short get_n_trampas_mina();
	unsigned short get_n_trampas_pincho();
	unsigned short get_n_trampas_charco();

	Minas** get_trampas_mina();
	Charcos_electrificados** get_trampas_charco();
	Pinchos** get_trampas_pinchos();

	void borra_mina(short _i_id);
	void borrar_mina();


private:
	Minas ** _minas;
	Charcos_electrificados ** _charcos;
	Pinchos ** _pinchos;

	unsigned short _n_minas;
	unsigned short _n_charcos;
	unsigned short _n_pinchos;



};

#endif /* SRC_Trampas_manager_H_ */
