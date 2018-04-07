#ifndef INTERACTUABLE_MANAGER_H_
#define INTERACTUABLE_MANAGER_H_

class Llave;
class Puerta;
class Interruptor;
class Puerta_Pincho;
class Zona;

#include <vector>

class Interactuable_Manager {
public:
	Interactuable_Manager(Zona** _i_todas_las_zonas);
	~Interactuable_Manager();

    void update_interruptores();


	Llave** get_llaves();
    Puerta** get_puertas();
    //Interruptor** get_interruptores();
    Puerta_Pincho** get_puertas_pincho();

    std::vector<Interruptor*> get_interruptores();
    
	unsigned short get_n_llaves();
    unsigned short get_n_puertas();
    unsigned short get_n_puertas_pincho();
	
private:
	Llave** _llaves;
    Puerta** _puertas;
    std::vector<Interruptor*> _interrutoress;


    Puerta_Pincho** _puertas_pincho;

	unsigned short _n_llaves;
    unsigned short _n_puertas;
    unsigned short _n_puertas_pincho;

};

#endif /* INTERACTUABLE_MANAGER_H_ */
