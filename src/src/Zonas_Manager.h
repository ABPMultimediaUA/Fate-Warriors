#ifndef ZONAS_MANAGER_H_
#define ZONAS_MANAGER_H_

class Zona;

class Zonas_Manager {
public:
	Zonas_Manager();
	~Zonas_Manager();

	void actualizar_zonas();
	Zona** get_zonas();
    
	unsigned short get_n_zonas();
	
private:
	Zona** _zonas;

	unsigned short _n_zonas;
};

#endif /* ZONAS_MANAGER_H_ */
