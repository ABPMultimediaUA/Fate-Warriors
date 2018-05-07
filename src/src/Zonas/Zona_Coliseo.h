#ifndef ZONA_COLISEO_H_
#define ZONA_COLISEO_H_

#include "Zona.h"

class Zona_Coliseo : public Zona{
public:
	Zona_Coliseo(float _i_x, float _i_y, float _i_z, int long_x, int long_y, uint16_t num_enemigos, int rondas, uint8_t crec_enem, uint8_t music_ini, uint8_t music_fin);
    ~Zona_Coliseo();
    void actualizar_zona() override;

private:
    void iniciar_coliseo();
    void update_coliseo();
    bool _coliseo_iniciado;
    uint16_t _num_enemigos;
    int _rondas;

    uint8_t _crecimiento_enemigos;

    uint8_t _musica_inicio;
    uint8_t _musica_fin;
};

#endif /* ZONA_COLISEO_H_ */