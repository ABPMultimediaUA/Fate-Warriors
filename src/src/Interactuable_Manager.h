#ifndef INTERACTUABLE_MANAGER_H_
#define INTERACTUABLE_MANAGER_H_

class Llave;
class Puerta;
class Interruptor;

class Interactuable_Manager {
public:
	Interactuable_Manager();
	~Interactuable_Manager();

	Llave** get_llaves();
    Puerta** get_puertas();
    Interruptor** get_interruptores();
    
	unsigned short get_n_llaves();
    unsigned short get_n_puertas();
    unsigned short get_n_interruptores();
	
private:
	Llave** _llaves;
    Puerta** _puertas;
    Interruptor** _interruptores;

	unsigned short _n_llaves;
    unsigned short _n_puertas;
    unsigned short _n_interruptores;

};

#endif /* INTERACTUABLE_MANAGER_H_ */
