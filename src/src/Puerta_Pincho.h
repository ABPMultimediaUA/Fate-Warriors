#ifndef HEADERS_PUERTA_PINCHO_H_
#define HEADERS_PUERTA_PINCHO_H_

class Pinchos;
class Time;
class Zona;

class Puerta_Pincho {
public:

	Puerta_Pincho(short id, float _i_x, float _i_y, float _i_z, Zona* _i_asociada_1, Zona* _i_asociada_2);
	virtual ~Puerta_Pincho();
    void update();
    void activar();
    void desactivar();
    bool comprobar_si_finalizo_el_tiempo();
    bool get_activado();
    void comprobar_a_quien_danya();

private:
    Pinchos* _pinchos;
    Zona* _zona_asociada1;
    Zona* _zona_asociada2;
    Time* _reloj;
    bool _activado;
    double _tiempo_restante;
};

#endif /* HEADERS_PUERTA_PINCHO_H_ */
