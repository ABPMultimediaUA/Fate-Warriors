#ifndef SRC_OPCION_H_
#define SRC_OPCION_H_

class Opcion {
public:
	Opcion();
	virtual ~Opcion();

	Opcion* update(double _i_tiempo, Opcion* _this);

	virtual Opcion* update_opcion(double _i_tiempo);

	void set_opciones(Opcion* _i_opcion_anterior, Opcion* _i_opcion_siguiente);

protected:
	Opcion *_opcion_anterior;
	Opcion *_opcion_siguiente;

private: 
	void set_opcion_anterior(Opcion* _i_opcion);
	void set_opcion_siguiente(Opcion* _i_opcion);
};

#endif /* SRC_OPCION_H_ */